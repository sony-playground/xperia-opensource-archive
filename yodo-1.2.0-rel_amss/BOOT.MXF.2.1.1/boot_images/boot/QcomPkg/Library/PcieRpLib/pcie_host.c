/*
  @file pcie_host.c
  @brief PCIe host bus driver implementation.

  This file contains the implementation of the PCIe host bus interface API's

*/
/*
 ==============================================================================

          Edit History


  when       who     what, where, why
  --------   ---     ---------------------------------------------------------
  03/08/21   Yg      Adapt to new driver implementation
  03/05/20   Yg      Add MSI support
  11/15/19   Yg      Ported to ADSP
  05/08/18   MK      Created

 ==============================================================================
     Copyright (c) 2018 - 2021 QUALCOMM Technologies Incorporated
     All Rights Reserved.  Qualcomm Confidential and Proprietary.
 ==============================================================================
*/

#include "pcie_host_r.h"
#include "pcie_mem_rsrc.h"
#include "pcie_host_log.h"
#include "pcie_reg_offsets.h"
#include "string.h"
#include "pcie_rp.h"

#define PCIE_INVALID_VAL       0xFFFFFFFF
#define IS_VALID_VAL(x)        (((x) != PCIE_INVALID_VAL) && ((x) != 0))

#define PROBE_CB_ISSUED_TO_GENERIC_CLIENT    (0x1)
#define PROBE_CB_ISSUED_TO_SPECIFIC_CLIENT   (0x2)

#define MEMORY_IO_TYPE_REQUEST_MASK   0x1
#define REQUEST_TYPE_MEMORY           0x0
#define REQUEST_TYPE_IO               0x1

#define ADDRESS_DECODING_SIZE_MASK    0x6
#define ADDRESS_DECODING_SIZE_SHIFT   0x1

#define ADDRESS_DECODE_32_BIT   0x0
#define ADDRESS_DECODE_64_BIT   0x2

#define SIZE_64K   (1 << 16)

#define PAGE_SIZE    4096

/* Condenses bus,dev,function values to a single uint32 integer */
#define PCIE_BDF(b,d,f) (((b&0xFF)<<8)|((d&0x1F)<<3)|((f&0x7)))

/* splits the rbdf value into bus, dev, func (for printing purposes) */
#define PCIE_SPLIT_BDF(bdf)    ((bdf >> 8) & 0xFF), ((bdf >> 3) & 0x1F), (bdf & 0x7)

/* Macro to pack memory base and limit values to their respective fields*/
#define PCIE_MEM_CFG(base, limit) ( (((limit>>20)&0xFFF)<<20)|(((base>>20)&0xFFF)<<4) )

/* retrieves the rootport value from a rbdf value */
#define PCIE_GET_RC(rbdf) ((rbdf&0x70000)>>16)

/*******************************************************************************
 *    MSI related
 ******************************************************************************/
// TODO: Still need to handle getting MSI configuration from cfg struct.
//#define ENABLE_MSI

#define MAX_MSI_VECTORS     32

typedef struct{
   pcie_msi_callback_fn_t msi_cb_fn;
   void* arg;
}msi_cb_client_info_t;
/******************************************************************************/

/* Context to represent and track the root_port */
struct __pcie_root_port
{
   uint64     dbi_base;
   uint64     parf_base;

   uint32     rsrv1;
   uint8      port_index;
   uint8      port_state;
   uint8      rsrv;
   uint8      handle_in_use;
};

/* Context to represent PCIe device descriptor, one per port to track at
 * the port level (Upstream and downstream on all buses) */
struct __pcie_dev
{
   pcie_root_port_t    *root_h;   
   pcie_rp_handle      *rp_handle;
   uint32               bdf;             
   uint16               vendor_id;        
   uint16               device_id;        
   uint32               class_code;       
   uint8                header;           
   uint8                primary_bus;      
   uint8                secondary_bus;    
   uint8                subordinate_bus;  
   uint64               mem_base;         
   uint64               mem_limit;        
   pcie_dev_t          *ds_port;      
   pcie_dev_t          *children;    
   pcie_dev_t          *peer;        

   pcie_mem_region_t    bars[PCIE_MAX_BARS];

#ifdef ENABLE_MSI_SUPPORT
   uint64               msi_intr_message_addr;
   uint64               msi_intr_message_data;

   msi_cb_client_info_t msi_cb_clients[MAX_MSI_VECTORS];

   uint32               msi_ctrl_reg_offset;
   uint32               msi_mask_reg_offset;     /// TODO: Move these into a different struct and generalize for both SNPS/IPCC solutions
   uint32               msi_dev_offset;
   uint32               msi_target_dst_addr;
#endif                   

   uint32               handle_in_use;  // Split this to uint8 to add more small fields
};

/* PCI Config Header */
#define PCIE_CFG_DEVVENDID                       (0x0000)
#define PCIE_CFG_CMDSTTS                         (0x0004)
#define PCIE_CFG_REVCLASS                        (0x0008)
#define PCIE_CFG_HDRTYPE                         (0x000C)
#define PCIE_CFG_BAR(bar)                        (0x0010+4*(bar))
#define PCIE_CFG_TYPE1_BUS                       (0x0018)
#define PCIE_CFG_TYPE1_MEMBASELIMIT              (0x0020)
#define PCIE_CFG_TYPE1_PREFETCH_MEMBASELIMIT     (0x0024)
#define PCIE_CFG_TYPE1_PREFETCH_UPPER_MEMBASE    (0x0028)
#define PCIE_CFG_TYPE1_PREFETCH_UPPER_MEMLIMIT   (0x002C)
#define PCIE_CFG_TYPE1_IOBASELIMIT               (0x0030)
#define PCIE_CFG_CAPABILITY_PTR                  (0x0034)
#define PCIE_CFG_EXTENDED_CAPABILITY_PTR         (0x0100)

/* PCIe root port devices, TODO: Eval to see if just one inst per port is good */
pcie_root_port_t pcie_root_port_handles[PCIE_MAX_ACTIVE_ROOT_PORTS];

/* Maximum number of PCIe device handles supported one per port.
 * TODO: Allocate memory instead of build time allocation */
#define MAX_PCIE_DEVICES                    (PCIE_MAX_ACTIVE_ROOT_PORTS * 2)

/* PCIe devices table to gather devices discovered under the root ports */
static pcie_dev_t   pcie_dev_handles[MAX_PCIE_DEVICES];

/* Driver descriptor */
typedef struct{
   pcie_device_info_t   device_id;
   pcie_probefn_t       probe_fn;
   void*                user_data;
}pcie_client_info_t;

/* Driver descriptor table TODO: Allocate this memory dynamically and remove restriction */
static pcie_client_info_t pcie_probe_clients[MAX_PCIE_CLIENTS];

/* Init status of the PCIe host driver */
static uint32 pcie_host_lib_initialized = FALSE;

pcie_dev_t* pcie_scan_bus (pcie_root_port_t *root_h, pcie_dev_t *ds_port, uint8 bus);

#ifdef ARRAY_SIZE
#undef ARRAY_SIZE
#endif
#define ARRAY_SIZE(array) (sizeof(array)/sizeof(array[0]))

/******************************************************************************
 *         Context alloc/free functions
 ******************************************************************************/
pcie_dev_t *alloc_dev_context (void)
{
   int i;
   pcie_dev_t *handle;

   /* TODO: Perform this operation within a locked context */
   for (i = 0; i < ARRAY_SIZE(pcie_dev_handles); i++)
   {
      handle = &pcie_dev_handles[i];
      if (handle->handle_in_use == 0)
      {
         handle->handle_in_use = 1;
         return handle;
      }
   }
   return NULL;
}

void free_dev_context (pcie_dev_t *dev)
{
   if (dev == NULL)
      return;

   /* TODO: Perform this operation within a locked context */
   /* Just clear the memory, so the inuse flag gets cleared setting this free */
   memset (dev, 0, sizeof(dev[0]));
}

pcie_root_port_t *alloc_root_port_handle (void)
{
   int i;
   pcie_root_port_t *handle;

   /* TODO: Perform this operation within a locked context */
   for (i = 0; i < ARRAY_SIZE(pcie_root_port_handles); i++)
   {
      handle = &pcie_root_port_handles[i];
      if (handle->handle_in_use == 0)
      {
         handle->handle_in_use = 1;
         return handle;
      }
   }
   return NULL;
}

void free_root_port_handle (pcie_root_port_t *dev)
{
   if (dev == NULL)
      return;

   memset (dev, 0, sizeof(dev[0]));
}

pcie_root_port_t *get_root_port_handle (uint32 port_index)
{
   int i;
   pcie_root_port_t *handle;
   pcie_status_t status;
   pcie_mem_resource_t mem_resources;

   /* TODO: Perform this operation within a locked context */
   for (i = 0; i < ARRAY_SIZE(pcie_root_port_handles); i++)
   {
      handle = &pcie_root_port_handles[i];
      if ((handle->handle_in_use != 0) && (handle->port_index == port_index))
         return handle;
   }

   handle = alloc_root_port_handle ();
   if (handle == NULL)
   {
      PCIE_HOST_LOG_ERROR ("Out of resources for Port handle %d\n", port_index);
      return NULL;
   }

   handle->port_index = port_index;
   handle->port_state = 0;

//   if (pcie_rp_is_port_link_up (port_index))
//   {
//      PCIE_HOST_LOG_ERROR ("Port link was up, powering down...%d\n", port_index);
//      if (pcie_rp_powerdown_ports (1 << port_index) != PCIE_SUCCESS)
//         PCIE_HOST_LOG_ERROR ("Failed power down operation\n");
//   }

   status = pcie_rp_get_mem_resources (port_index, PCIE_RESOURCE_PARF_BASE, &mem_resources);
   if (status != PCIE_SUCCESS)
   {
      PCIE_HOST_LOG_ERROR ("Unable to get mem resource info %d\n", port_index);
      free_root_port_handle (handle);
      return NULL;
   }
   handle->parf_base = mem_resources.va;

   status = pcie_rp_get_mem_resources (port_index, PCIE_RESOURCE_DBI_BASE, &mem_resources);
   if (status != PCIE_SUCCESS)
   {
      PCIE_HOST_LOG_ERROR ("Unable to get mem resource info %d\n", port_index);
      free_root_port_handle (handle);
      return NULL;
   }
   handle->dbi_base = mem_resources.va;
   
   return handle;
}

/******************************************************************************
 *        PCIe register read/write functions
 ******************************************************************************/
void pcie_write_reg (uintnt base, uint32 offset, uint32 val)
{
   uintnt addr = base + offset;
   (*((volatile uint32 *)(addr))) = val;
}

void pcie_write_reg_field (uintnt base, uint32 offset, uint32 mask, uint32 shift, uint32 field_val)
{
   uintnt addr = base + offset;
   uint32 regval = (*((volatile uint32 *)(addr)));

   regval &= ~mask;
   regval = regval | (field_val << shift);
   (*((volatile uint32 *)(addr))) = regval;
}

uint32 pcie_read_reg (uintnt base, uint32 offset)
{
   uintnt addr = base + offset;
   return (*((volatile uint32 *)(addr)));
}

/* ------  DBI/Config space registers  ------ */
uint32 pcie_cfg_read (pcie_root_port_t *root_h, uint32 bdf, uint32 offset)
{
   uintnt cfgbase;
   // bdf = bdf & 0xFF;  we do need bus info
   cfgbase = root_h->dbi_base + (bdf << 12);
   return pcie_read_reg (cfgbase, offset);
}

void pcie_cfg_write (pcie_root_port_t *root_h, uint32 bdf, uint32 offset, uint32 val)
{
   uintnt cfgbase;
   // bdf = bdf & 0xFF;  we do need bus info
   cfgbase = root_h->dbi_base + (bdf << 12);
   return pcie_write_reg (cfgbase, offset, val);
}

/* ------  PARF registers  ------ */
uint32 parf_reg_read (pcie_root_port_t *root_h, uint32 offset)
{
   uintnt reg_base = root_h->parf_base;
   return pcie_read_reg (reg_base, offset);
}

void parf_reg_write (pcie_root_port_t *root_h, uint32 offset, uint32 val)
{
   uintnt reg_base = root_h->parf_base;
   return pcie_write_reg (reg_base, offset, val);
}

/******************************************************************************
 *         Bus scanning functions
 ******************************************************************************/
/* Support only 1 device per bus and 1 function per device. Adjust these to scan for more */
#define MAX_BUSES_SCAN_PER_ROOT_PORT       2
#define MAX_DEVICES_SCAN_PER_BUS           1
#define MAX_FUNCS_SCAN_PER_DEVICE          1

void pcie_fetch_deviceinfo (pcie_dev_t *pcie_dev)
{
   uint32 val;
   /* First vendor id and device id */
   val = pcie_cfg_read (pcie_dev->root_h, pcie_dev->bdf, PCIE_CFG_DEVVENDID);
   pcie_dev->vendor_id = val & 0xFFFF;
   pcie_dev->device_id = (val >> 16) & 0xFFFF;

   /* Class Code */
   val = pcie_cfg_read (pcie_dev->root_h, pcie_dev->bdf, PCIE_CFG_REVCLASS);
   pcie_dev->class_code = (val & 0xFFFFFF00) >> 8;

   /* Header */
   val = pcie_cfg_read (pcie_dev->root_h, pcie_dev->bdf, PCIE_CFG_HDRTYPE );
   pcie_dev->header = (val & 0x7F0000) >> 16;

   /* Todo: For some devices need to wait for the capabilities to showup
    * after enumeration (typically 100ms), so evaluate if this is the right
    * place and move if appropriate */
}

/** Macro to pack primary, secondary and subordinate buses to their respective fields*/
#define PCIE_BUS_CFG(pri,sec,sub) ((sub & 0xFF)<<16|(sec & 0xFF)<<8|(pri&0xFF))

/* TODO: Limit all the code to 80 columns */
pcie_dev_t * pcie_scan_device (pcie_root_port_t *root_h, pcie_dev_t *ds_port, uint16 bdf)
{
   uint32 dev_id = PCIE_INVALID_VAL;
   pcie_dev_t *pdev = NULL;
   pcie_dev_t *child = NULL;
   uint8 bus;

   if (root_h == NULL)
      return NULL;

   dev_id = pcie_cfg_read (root_h, bdf, PCIE_CFG_DEVVENDID);

   if (!IS_VALID_VAL (dev_id))
      return NULL;

   pdev = alloc_dev_context ();
   if (pdev == NULL)
      return NULL;

   if (ds_port == NULL)
      ds_port = pdev;

   pdev->root_h = root_h;
   pdev->ds_port = ds_port;
   pdev->bdf = bdf;

   /* Populate with the right information */
   pcie_fetch_deviceinfo (pdev);

   /* If header is Type 1, initiate a bus scan */
   if (pdev->header == 1)
   {
      bus = bdf >> 8;
      pdev->primary_bus = bus;
      pdev->secondary_bus = bus + 1;
      pdev->subordinate_bus = MAX_BUSES_SCAN_PER_ROOT_PORT;

      /* Update the bus config of the type 1 device before scanning below.
       * We will correct it to the actual depth once the scan returns */
      pcie_cfg_write (pdev->root_h, pdev->bdf, PCIE_CFG_TYPE1_BUS,
            PCIE_BUS_CFG (pdev->primary_bus, pdev->secondary_bus, pdev->subordinate_bus));

      child = pcie_scan_bus (root_h, pdev, pdev->secondary_bus);

      pdev->children = child;
      pdev->ds_port->subordinate_bus = pdev->subordinate_bus;

      pcie_cfg_write (pdev->root_h, pdev->bdf, PCIE_CFG_TYPE1_BUS,
            PCIE_BUS_CFG (pdev->primary_bus, pdev->secondary_bus, pdev->subordinate_bus));
   }

   return pdev;
}

pcie_dev_t* pcie_scan_bus (pcie_root_port_t *root_h, pcie_dev_t *ds_port, uint8 bus)
{
   uint8 func = 0;
   uint8 dev = 0;
   uint32 dev_id;
   pcie_dev_t *child;
   pcie_dev_t *peer = NULL;
   pcie_dev_t *head = NULL;

   if (root_h == NULL)
      return NULL;

   for (dev = 0; dev < MAX_DEVICES_SCAN_PER_BUS; dev++)
   {
      /* Check if we have a valid device */
      dev_id = pcie_cfg_read (root_h, PCIE_BDF (bus, dev, 0), PCIE_CFG_DEVVENDID);

      if (!IS_VALID_VAL (dev_id))
         return head;

      for (func = 0; func < MAX_FUNCS_SCAN_PER_DEVICE; func++)
      {
         child = pcie_scan_device (root_h, ds_port, PCIE_BDF (bus, dev, func));

         if (child == NULL)
         {
            /* No more functions found in the device
             * For now we will stop at the first failure
             * and not scan the entire range  */
            break;
         }

         if (head == NULL)
            head = child;

         if (peer == NULL)
            peer = child;
         else
         {
            peer->peer = child;
            peer = peer->peer;
         }
      }
   }

   return head;
}

/******************************************************************************
 *         BAR resources allocation & assign
 ******************************************************************************/

pcie_status_t pcie_assign_bars (pcie_dev_t *pdev, pcie_mem_ctxt* rc_ctxt)
{
   uint8 bar, num_bars;
   uint32 val, addr_size, mem_io_type;
   uint64_t mem_addr;
   uint64_t pa_base, rsrc_sz, limit;

   num_bars = (pdev->header) ? 2 : 6;

   if (pdev->header == 0)
      PCIE_HOST_LOG_LOADER ("Found PCIe dev %X:%X on port %X\r\n", pdev->vendor_id, pdev->device_id, pdev->root_h->port_index);

   for (bar = 0; bar < num_bars; bar++)
   {
      pcie_cfg_write (pdev->root_h, pdev->bdf, PCIE_CFG_BAR (bar), 0xFFFFFFFF);

      val = pcie_cfg_read (pdev->root_h, pdev->bdf, PCIE_CFG_BAR (bar));

      addr_size = (val & ADDRESS_DECODING_SIZE_MASK) >> ADDRESS_DECODING_SIZE_SHIFT;
      mem_io_type = (val & MEMORY_IO_TYPE_REQUEST_MASK);

      if (val == 0x00000000 || val == 0xFFFFFFFF  || mem_io_type == REQUEST_TYPE_IO ||
          ((addr_size != ADDRESS_DECODE_32_BIT) && (addr_size != ADDRESS_DECODE_64_BIT)))
      {
         /* Invalid bar */
#ifdef SUPPORT_NON_IDENTITY_VIRTUAL_MAPPING
         pdev->bars[bar].va = 0x0;
#endif
         pdev->bars[bar].pa = 0x0;
         pdev->bars[bar].sz = 0x0;
      }
      else
      {
         /* Determine the size based on writable bits set by the config reg */
         pdev->bars[bar].sz = (~(val & (~0xF))) + 1;

         if (pdev->bars[bar].sz != 0x0)
         {
            if (allocate_mem (rc_ctxt, pdev->bars[bar].sz, &mem_addr) != MEM_RSRC_SUCCESS)
            {
               PCIE_HOST_LOG_ERROR ("++ {%d:%d:%d}-- Error! Out of resources : Sz 0x%X Aborting",
                     PCIE_SPLIT_BDF (pdev->bdf), pdev->bars[bar].sz);
               /* There is no recovery from this...We will have an imbalanced PCI tree..*/
               return PCIE_ERROR;
            }
            pdev->bars[bar].pa = mem_addr;
            // pdev->bars[bar].va = res->mmio_space.va;

            if (pdev->header == 0)
               PCIE_HOST_LOG_LOADER ("  BAR%d : 0x%X  0x%X\r\n", bar, mem_addr, pdev->bars[bar].sz);
         }
         else
         {
            pdev->bars[bar].pa = 0;
#ifdef SUPPORT_NON_IDENTITY_VIRTUAL_MAPPING
            pdev->bars[bar].va = 0;
#endif
         }

         /* Assign the BAR resource */
         pcie_cfg_write (pdev->root_h, pdev->bdf, PCIE_CFG_BAR (bar), pdev->bars[bar].pa);

         if (addr_size == ADDRESS_DECODE_64_BIT)
         {
            /* 64-bit bar */
            bar++;
            pcie_cfg_write (pdev->root_h, pdev->bdf,
                  PCIE_CFG_BAR (bar), (uint32)(pdev->bars[bar].pa >> 32));
         }
      }
   }

   if (get_allocated_range (rc_ctxt, &pa_base, &rsrc_sz) != MEM_RSRC_SUCCESS)
   {
      PCIE_HOST_LOG_ERROR ("Memory resource failure", pdev->vendor_id);
      return PCIE_ERROR;
   }
   limit = pa_base + rsrc_sz;

   /* Though these don't matter from Type 0 header perspective, would help with debugging info for both
    * to see how much range each is spanning over. (Note these values are still not accurate for complex
    * topology yet, until a new instance is used to pass down to children and tracking for peers) */
   pdev->mem_base = pa_base;
   pdev->mem_limit = limit;

   return PCIE_SUCCESS;
}

pcie_status_t pcie_assign_resources_per_device (pcie_dev_t *pdev, pcie_mem_ctxt* rc_ctxt)
{
   pcie_dev_t *peer;
   uint64_t pa_base, rsrc_sz, limit;

   if (get_resource_range (rc_ctxt, &pa_base, &rsrc_sz) != MEM_RSRC_SUCCESS)
   {
      PCIE_HOST_LOG_ERROR ("Memory resource failure", pdev->vendor_id);
      return PCIE_INVALID_PARAM;
   }

   /* We start with the entire range */
   pdev->mem_base = pa_base;
   limit = pa_base + rsrc_sz;
   pdev->mem_limit = limit;

   peer = pdev->peer;

   /* First we assign resources to the device itself */
   pcie_assign_bars (pdev, rc_ctxt);

   /* Check if the device has peers on the same bus...if so assign their resources first */
   if (peer)
      pcie_assign_resources_per_device (peer, rc_ctxt);

   /* Now assign resources to the children if there are any */
   if (pdev->header == 1)
   {
      /* Here ideally we should create a fresh instance of a chunk of
       * memory to be used going down the tree and mark the consumed
       * memory as allocated and configure the base and limit appropriately
       * But in that case there is a possibility of fragmenting the memory
       * even more since we would have considered just one chunk where
       * the other chunk would have helped with avoiding fragmentation.
       * TODO: for supporting deep tree */
      if (pdev->children)
      {
//         PCIE_HOST_LOG_LOW ("Call child => 0x%X", pdev->vendor_id);

         pcie_assign_resources_per_device (pdev->children, rc_ctxt);
      }
 
      if (get_allocated_range (rc_ctxt, &pa_base, &rsrc_sz) != MEM_RSRC_SUCCESS)
      {
         PCIE_HOST_LOG_ERROR ("Memory resource failure", pdev->vendor_id);
         return PCIE_ERROR;
      }
      limit = pa_base + rsrc_sz;

      pdev->mem_base = pa_base;
      pdev->mem_limit = limit;
      pcie_cfg_write (pdev->root_h, pdev->bdf, PCIE_CFG_TYPE1_MEMBASELIMIT,
                      PCIE_MEM_CFG (pdev->mem_base, pdev->mem_limit));

      /* Disable Prefetch and IO spaces */
      pcie_cfg_write (pdev->root_h, pdev->bdf, PCIE_CFG_TYPE1_PREFETCH_MEMBASELIMIT,
                      PCIE_MEM_CFG (0xFFFFFFFF, 0x0));

      pcie_cfg_write (pdev->root_h, pdev->bdf, PCIE_CFG_TYPE1_IOBASELIMIT,
                      PCIE_MEM_CFG (0xFFFFFFFF, 0x0));

   }

   return PCIE_SUCCESS;
}

pcie_status_t pcie_assign_resources (pcie_dev_t *root_port)
{
   pcie_mem_resource_t mem_res;
   pcie_mem_ctxt* rc_ctxt;
   pcie_status_t status;
   uint32 port_index;

   if (root_port == NULL)
      return PCIE_INVALID_PARAM;

   port_index = root_port->root_h->port_index;
   status = pcie_rp_get_mem_resources (port_index, PCIE_RESOURCE_NON_PREFETCH_MEM_SPACE, &mem_res);

   if (status != PCIE_SUCCESS)
   {
     PCIE_HOST_LOG_ERROR ("No resources for %d\n", port_index);
     return PCIE_ERROR;
   }

   rc_ctxt = open_mem_resource (mem_res.pa, mem_res.sz);

   if (rc_ctxt == NULL)
   {
     PCIE_HOST_LOG_ERROR ("Resource failure...\n");
     return PCIE_ERROR;
   }

   while (root_port)
   {
      pcie_assign_resources_per_device (root_port, rc_ctxt);

      root_port = root_port->peer;
   }

   close_mem_resource (rc_ctxt);

   return PCIE_SUCCESS;
}

/******************************************************************************
 *         Probe callback functions
 ******************************************************************************/

void pcie_dispatch_probe_cb (pcie_dev_t *pdev, pcie_client_info_t *client_info)
{
   int bar;
   pcie_dev_probe_cb_payload_t cb_payload;

   if ((client_info == NULL)  || (client_info->probe_fn == NULL) || (pdev->header != 0)) // Callback only for Type 0 headers
      return;

   if  ((client_info->device_id.class_id == PCIE_ID_ANY ||
         client_info->device_id.class_id == pdev->class_code) &&
        (client_info->device_id.vendor_id == PCIE_ID_ANY ||
         client_info->device_id.vendor_id == pdev->vendor_id) &&
        (client_info->device_id.device_id == PCIE_ID_ANY ||
         client_info->device_id.device_id == pdev->device_id))
   {
      for (bar = 0; bar < PCIE_MAX_BARS; bar++)
         cb_payload.rsrc.bars[bar] = pdev->bars[bar];

      cb_payload.dev_ids.vendor_id = pdev->vendor_id;
      cb_payload.dev_ids.device_id = pdev->device_id;
      cb_payload.dev_ids.class_id = pdev->class_code;
      cb_payload.dev_ids.rbdf_info = pdev->bdf | (pdev->root_h->port_index << 16);
      cb_payload.cfg_space = (uint32*)(pdev->root_h->dbi_base + (pdev->bdf << 12));  // TODO: or should the handle return the config space addr?

      client_info->probe_fn (pdev, &cb_payload, client_info->user_data);
   }
}

void pcie_probe (pcie_client_info_t *client_info)
{
   int i, d;
   pcie_dev_t* dev_handle;

   if (client_info)
   {
     /* Result of a new client registration, we can issue callback
      * to this client on potentially all enumerated devices */
     for (d = 0; d < MAX_PCIE_DEVICES; d++)
     {
        dev_handle = &pcie_dev_handles[d];
        if (dev_handle->handle_in_use)
           pcie_dispatch_probe_cb (dev_handle, client_info);
     }
   }
   else
   {
     /* Result of a new device discovery, so issue callback to clients
      * that didn't get a callback, filtering happens in the dispatch call */
     for (d = 0; d < MAX_PCIE_DEVICES; d++)
     {
        dev_handle = &pcie_dev_handles[d];
        if (dev_handle->handle_in_use == 0)
           continue;

        for (i = 0; i < MAX_PCIE_CLIENTS; i++)
        {
           client_info = &pcie_probe_clients[i];
           pcie_dispatch_probe_cb (dev_handle, client_info);
        }
     }
   }
}

pcie_status_t pcie_root_port_bus_scan (pcie_root_port_t *root_h)
{
   pcie_status_t pstatus;
   pcie_dev_t *handle;

   if (root_h == NULL)
      return PCIE_INVALID_PARAM;

   /* Now scan throughout the tree on this root port */
   handle = pcie_scan_device (root_h, NULL, 0);
   if (handle == NULL)
      return PCIE_ERROR;

   /* Now assign resources to the devices */
   pstatus = pcie_assign_resources (handle);

   return pstatus;
}


/******************************************************************************
 *         Public functions
 ******************************************************************************/

/* TODO: Make file/function/folder names uniform here we have host/rc etc */
pcie_status_t pcie_rc_init (void)
{
   if (pcie_host_lib_initialized == TRUE)
      return PCIE_SUCCESS;

   memset (pcie_root_port_handles, 0, sizeof(pcie_root_port_handles));
   memset (pcie_dev_handles, 0, sizeof(pcie_dev_handles));

   pcie_osal_init();

   if (pcie_rp_lib_init () != PCIE_SUCCESS)
      return PCIE_ERROR;

   pcie_host_lib_initialized = TRUE;

   return PCIE_SUCCESS;
}

pcie_status_t pcie_bus_initialize (uint32 rc_index)
{
   pcie_root_port_t *root_h;

   root_h = get_root_port_handle (rc_index);
   if (root_h == NULL)
      return PCIE_ERROR;

   return pcie_root_port_bus_scan (root_h);
}

pcie_status_t pcie_enumerate(uint32 rc_index)
{
   pcie_root_port_t *root_h;
   pcie_status_t pstatus;

   /* Initialize the lib if not already */
   if (pcie_rc_init() != PCIE_SUCCESS)
      return PCIE_ERROR;

   root_h = get_root_port_handle (rc_index);
   if (root_h == NULL)
      return PCIE_ERROR;

   pstatus = pcie_rp_enumerate_ports (1 << rc_index);
   if (pstatus != PCIE_SUCCESS)
      return pstatus;

//   root_h->port_state = PORT_ENUMERATED; TODO needed?

   pstatus = pcie_root_port_bus_scan (root_h);
   if (pstatus != PCIE_SUCCESS)
      return pstatus;

   /* Issue probe callback to all registered clients */
   pcie_probe (NULL);

   return PCIE_SUCCESS;
}

pcie_status_t pcie_reset (uint32 rc_index)
{
   int i;
   pcie_dev_t *handle;

   /* TODO: Operate any pcie_dev_handles operation within a lock */
   /* Clear all device handles related to this Root port */
   for (i = 0; i < MAX_PCIE_DEVICES; i++)
   {
      handle = &pcie_dev_handles[i];
      if (handle->handle_in_use == 0)
         continue;

      if (handle->root_h->port_index == rc_index)
         free_dev_context (handle);
   }

   return pcie_rp_powerdown_port (rc_index);
}


pcie_status_t pcie_register_device (const pcie_device_info_t *device_id_ptr, pcie_probefn_t probe_fn, void* user_data)
{
   pcie_client_info_t *client_info = NULL;
   int i;

   if (pcie_rc_init() != PCIE_SUCCESS)
      return PCIE_ERROR;

   /* TODO: add locks here */
   for (i=0; i < MAX_PCIE_CLIENTS; ++i)
   {
      client_info = &pcie_probe_clients[i];
      if (client_info->probe_fn == NULL)
      {
         client_info->device_id = *device_id_ptr;
         client_info->probe_fn = *probe_fn;
         client_info->user_data = user_data;
         break;
      }
   }

   if (i == MAX_PCIE_CLIENTS)
      return PCIE_ERROR;

   if (client_info != NULL)
      pcie_probe (client_info);

   return PCIE_SUCCESS;
}

pcie_status_t pcie_unregister_device (const pcie_device_info_t *device_id_ptr, pcie_probefn_t probe_fn, void* user_data)
{
   pcie_client_info_t *client_info = NULL;
   int i;

   for (i=0; i < MAX_PCIE_CLIENTS; ++i)
   {
      client_info = &pcie_probe_clients[i];
      if ((client_info->probe_fn == probe_fn) &&
          (client_info->user_data == user_data) &&
          (client_info->device_id.vendor_id == device_id_ptr->vendor_id) &&
          (client_info->device_id.device_id == device_id_ptr->device_id) &&
          (client_info->device_id.class_id == device_id_ptr->class_id))
      {
         client_info->probe_fn = NULL;
         client_info->user_data = NULL;
         return PCIE_SUCCESS;
      }
   }

   return PCIE_ERROR;
}

pcie_dev_t *pcie_get_parent (pcie_dev_t *pdev)
{
   return pdev->ds_port;
}

pcie_status_t pcie_enable_device (pcie_dev_t *pdev)
{
   uint32 val;

   if (pdev == NULL)
      return PCIE_INVALID_PARAM;

#define PCIE_MEMORY_SPACE_ENABLE     0x2
#define PCIE_BUS_MASTER_ENABLE       0x4
  // EP should not generate any MEM requests until RC has enabled BME
  // HOST RC should not generate any MEM requests until MSE is enabled
  // So enable both now instead of giving option to client to pick and choose

   // Enable BME and MSE
   val = PCIE_MEMORY_SPACE_ENABLE | PCIE_BUS_MASTER_ENABLE;
   pcie_config_rw (pdev, PCIE_OPER_WRITE, PCIE_CFG_CMDSTTS, &val);

   return PCIE_SUCCESS;
}

pcie_status_t pcie_disable_device (pcie_dev_t *pdev)
{
   uint32 val = 0x0;

   if (NULL == pdev)
      return PCIE_INVALID_PARAM;

   pcie_config_rw (pdev, PCIE_OPER_WRITE, PCIE_CFG_CMDSTTS, &val);

   return PCIE_SUCCESS;
}

pcie_status_t pcie_config_rw (pcie_dev_t *pdev, pcie_rw_op_t operation, uint32 offset, uint32 *val)
{
   if (NULL == pdev)
      return PCIE_INVALID_PARAM;

   if (PCIE_OPER_WRITE == operation)
      pcie_cfg_write (pdev->root_h, pdev->bdf, offset, *val);
   else
      *val = pcie_cfg_read (pdev->root_h, pdev->bdf, offset);

   return PCIE_SUCCESS;
}

#if 0
void set_memory_space_busmastering (pcie_root_port_t *root_h, int enable)
{
   uint32 val;

   val = pcie_cfg_read (root_h, BDF_VAL_0, STATUS_COMMAND_DBI_OFFSET);
   if (enable)
   {
     SET_MASK_VAL (val, TYPE1_STATUS_COMMAND_REG_BME, 1);
     SET_MASK_VAL (val, TYPE1_STATUS_COMMAND_REG_MSE, 1);
   }
   else
   {
     SET_MASK_VAL (val, TYPE1_STATUS_COMMAND_REG_BME, 0);
     SET_MASK_VAL (val, TYPE1_STATUS_COMMAND_REG_MSE, 0);
   }
   pcie_cfg_write (root_h, BDF_VAL_0, STATUS_COMMAND_DBI_OFFSET, val);
}



#endif

/******************************************************************************
 *         MSI related functions
 ******************************************************************************/

#ifdef ENABLE_MSI_SUPPORT
#define CAPABILITY_ID_MSI                     0x05
#define CAPABILITY_ID_PCI_EXPRESS             0x10

/* Advanced Error Reporting */
#define EXT_CAPABILITY_ID_AER               0x0001

/* TPL Processing Hints */
#define EXT_CAPABILITY_ID_TPH               0x0017

/* Latency Tolerance Reporting */
#define EXT_CAPABILITY_ID_LTR               0x0018

/* Secondary PCIe */
#define EXT_CAPABILITY_ID_SEC_PCIE          0x0019

/* L1 PM substates */
#define EXT_CAPABILITY_ID_L1_PM_SS          0x001E

#define BDF_VAL_0      0

/* MSI ext capabilities bit definition macros */
#define MSI_MESSAGE_CONTROL_BIT_OFFSET      16

#define MSI_ENABLE_OFFSET                      (MSI_MESSAGE_CONTROL_BIT_OFFSET + 0)
#define MSI_MULTI_MSG_CAPABLE_OFFSET           (MSI_MESSAGE_CONTROL_BIT_OFFSET + 1)
#define MSI_MULTI_MSG_ENABLE_OFFSET            (MSI_MESSAGE_CONTROL_BIT_OFFSET + 4)
#define MSI_ADDR_64_BIT_CAPABLE_OFFSET         (MSI_MESSAGE_CONTROL_BIT_OFFSET + 7)
#define MSI_PER_VECTOR_MASK_CAPABLE_OFFSET     (MSI_MESSAGE_CONTROL_BIT_OFFSET + 8)
#define MSI_EXTENDED_MSG_DATA_CAPABLE_OFFSET   (MSI_MESSAGE_CONTROL_BIT_OFFSET + 9)
#define MSI_EXTENDED_MSG_DATA_ENABLE_OFFSET    (MSI_MESSAGE_CONTROL_BIT_OFFSET + 10)

#define MSI_ENABLE_MASK                        (1 << MSI_ENABLE_OFFSET)
#define MSI_ADDR_64_BIT_CAPABLE_MASK           (1 << MSI_ADDR_64_BIT_CAPABLE_OFFSET)
#define MSI_PER_VECTOR_MASK_CAPABLE_MASK       (1 << MSI_PER_VECTOR_MASK_CAPABLE_OFFSET)
#define MSI_EXTENDED_MSG_DATA_CAPABLE_MASK     (1 << MSI_EXTENDED_MSG_DATA_CAPABLE_OFFSET)
#define MSI_EXTENDED_MSG_DATA_ENABLE_MASK      (1 << MSI_EXTENDED_MSG_DATA_ENABLE_OFFSET)

/* TODO: if code space is not of concern, then make this runtime switchable */
//#define ENABLE_MSI_MAPPING_SNPS_INTR

#ifdef USE_INTERRUPTS_FOR_MSI
#ifdef ENABLE_MSI_MAPPING_SNPS_INTR
#define GET_LEAST_SET_BIT(x)   (x ^ (x & (x - 1)))
static void pcie_msi_snps_isr (void* arg)
{
   uint32 vector;
   pcie_dev_t *pdev = (pcie_dev_t*)arg;
   uint32 int_status, int_to_service;

   if (pdev == NULL)
      return;

   int_status = pcie_cfg_read (pdev->root_h, pdev->bdf, pdev->msi_mask_reg_offset + 8);

   while (int_status)
   {
      int_to_service = GET_LEAST_SET_BIT (int_status);

      /* Clear the flag so it stops interrupting */
      pcie_cfg_write (pdev->root_h, pdev->bdf, pdev->msi_mask_reg_offset + 8, int_to_service);

      int_status = int_status & (~int_to_service);

      /* Dispatch a callback from here to the registered client if any */
      for (vector = 0; vector < MAX_MSI_VECTORS; ++vector)
      {
         if (int_to_service == (1 << vector))
         {
            if (pdev->msi_cb_clients[vector].msi_cb_fn)
              pdev->msi_cb_clients[vector].msi_cb_fn (vector, pdev->msi_cb_clients[vector].arg);
            break;
         }
      }
   }
}
#else
static void pcie_msi_ipcc_isr (IPCC_CBData ctxt, IPCC_Client sender_id, IPCC_Signal sig)
{
   pcie_dev_t *pdev = (pcie_dev_t*)ctxt;

   if (pdev == NULL)
      return;

   if (pdev && (sig < MAX_MSI_VECTORS) && (pdev->msi_cb_clients[sig].msi_cb_fn != NULL))
   {
      pdev->msi_cb_clients[sig].msi_cb_fn (sig, pdev->msi_cb_clients[sig].arg);
   }
}

#endif

static pcie_status_t configure_msi (pcie_dev_t *pdev, uint64 msg_addr, uint32 msg_data)
{
   uint16 msg_cnt, data_loc;
   uint32 msi_val, msg;
   uint64              ep_cap_addr;
   pcie_status_t       status = PCIE_SUCCESS;
   pcie_rp_handle*     rp_handle;

   if ((pdev == NULL) || (msg_addr == 0) || (msg_data == 0))
      return PCIE_INVALID_PARAM;

   rp_handle = pcie_rp_get_port_handle (pdev->root_h->port_index);
   if (rp_handle == NULL)
      return PCIE_INVALID_PARAM;

   if (pcie_rp_is_port_link_up (pdev->root_h->port_index) == 0)
      return PCIE_NOT_READY;

   status = pcie_rp_get_ep_capability (rp_handle, CAPABILITY_ID_MSI, &ep_cap_addr);

   if (status != PCIE_SUCCESS)
      return PCIE_NOT_FOUND;

   /* TODO: Check if the following need to be applied to Host side aswell */
   data_loc = 0;
   msi_val = MmioRead32 (ep_cap_addr);

   msg_cnt = (msi_val >> MSI_MULTI_MSG_CAPABLE_OFFSET) & 7;      // TODO: Store the number of MSI's supported to track
   msi_val = msi_val | (msg_cnt << MSI_MULTI_MSG_ENABLE_OFFSET);  // Enable max capable it advertized or limit to what we need

   pcie_write_reg (ep_cap_addr, data_loc, msi_val);

   //MemoryFence ();

   data_loc += 4;

   msg = (uint32)(msg_addr & 0xFFFFFFFF);
   // First write the message address/data values
   pcie_write_reg (ep_cap_addr, data_loc, msg);  // LS address
   data_loc += 4;

   msg = (uint32)((msg_addr >> 32) & 0xFFFFFFFF);
   if (msi_val & MSI_ADDR_64_BIT_CAPABLE_MASK)
   {
      pcie_write_reg (ep_cap_addr, data_loc, 0);  // MS address
      data_loc += 4;
   }
   else if (msg != 0)
   {
      // ERROR..!! Message address is 64 bit but the MSI is not 64 bit addr capable..!!
      PCIE_HOST_LOG_ERROR ("MSI is not 64 bit addr capable");
      // TODO: determine all error conditions first and bail out before modifying anything
      return PCIE_ERROR;
   }

   if (msi_val & MSI_EXTENDED_MSG_DATA_CAPABLE_MASK)
      pcie_write_reg (ep_cap_addr, data_loc, msg_data);
   else if ((msg_data >> 16) & 0xFFFF)
   {
      // TODO: determine all error conditions first and bail out before modifying anything
      PCIE_HOST_LOG_ERROR ("MSI doesn't support extended msg data");
      return PCIE_ERROR;
   }
   else
      pcie_write_reg (ep_cap_addr, data_loc, msg_data);

   data_loc += 4;

   if (msi_val & MSI_PER_VECTOR_MASK_CAPABLE_MASK)
      pcie_write_reg (ep_cap_addr, data_loc, 0);  // Unmask all

   // Enable extended data if supported, need to preserve and write msi_val to take effect
   if (msi_val & MSI_EXTENDED_MSG_DATA_CAPABLE_MASK)
      msi_val = msi_val | MSI_EXTENDED_MSG_DATA_ENABLE_MASK;

   // Now enable MSI on device EP side
   msi_val = msi_val | MSI_ENABLE_MASK;
   pcie_write_reg (ep_cap_addr, data_loc, msi_val);

   return PCIE_SUCCESS;
}
#endif

pcie_status_t pcie_enable_msi (pcie_dev_t *pdev)
{
#ifdef USE_INTERRUPTS_FOR_MSI
   
#ifdef ENABLE_MSI_MAPPING_SNPS_INTR
   /* TODO: Move this to a different function */
   if (pdev->rc_dev->rc_cfg->msi_config)
   {
         // Write Message Data
         //     For SNPS interrupts, dev 4 intr starts with 32*4
      pdev->msi_ctrl_reg_offset = pdev->rc_dev->rc_cfg->msi_config->msi_ctrl_reg_offset;
      pdev->msi_dev_offset = pdev->rc_dev->rc_cfg->msi_config->local_msi_dev_num;
      pdev->msi_target_dst_addr = pdev->rc_dev->rc_cfg->msi_config->msi_target_dst_addr;
      pdev->msi_mask_reg_offset = pdev->rc_dev->rc_cfg->msi_config->msi_ctrl_reg_offset + 8 + (0xC * pdev->msi_dev_offset);

      /* Setup for Parent as well since in ISR we will be using parent */
      if (pdev->parent)
      {
         pdev->parent->msi_ctrl_reg_offset = pdev->msi_ctrl_reg_offset;
         pdev->parent->msi_dev_offset = pdev->msi_dev_offset;
         pdev->parent->msi_target_dst_addr = pdev->msi_target_dst_addr;
         pdev->parent->msi_mask_reg_offset = pdev->msi_mask_reg_offset;

      }
      if (configure_msi (pdev, pdev->msi_target_dst_addr, pdev->msi_dev_offset * 32) == PCIE_SUCCESS)
      {
         int status;
         uint32 msi_snps_vect;

         if (pdev->parent)
         {
            pcie_cfg_write (pdev->parent->rc_dev, pdev->parent->rbdf, pdev->msi_ctrl_reg_offset, pdev->msi_target_dst_addr);  // LS address
            pcie_cfg_write (pdev->parent->rc_dev, pdev->parent->rbdf, pdev->msi_ctrl_reg_offset + 4, 0x0);  // MS address

            /* Now enable MSI on the RC side (This has to be on the Bus 0 Type 1) */
            /* For ADSP only pcie_int_msi_dev4 and pcie_int_msi_dev5 for gen3x1 */
            // dev4 => Intr numbers 128 - 159
            pcie_cfg_write (pdev->parent->rc_dev, pdev->parent->rbdf, pdev->msi_mask_reg_offset, 0xFFFFFFFF);  // Enable all 32 interrupts
            pcie_cfg_write (pdev->parent->rc_dev, pdev->parent->rbdf, pdev->msi_mask_reg_offset + 4, 0x0);  // Unmask all interrupts
         }

         /* Status will be on the RC side, so use the parent which correspond to RC */
         msi_snps_vect = pdev->rc_dev->rc_cfg->msi_config->msi_sys_vector;
         status = pcie_osal_isr_register (&pdev->irq_hdl, msi_snps_vect, pcie_msi_snps_isr, (void*)pdev->parent);

         if (status)
         {
            PCIE_HOST_LOG_ERROR ("ISR Reg fail");
            return PCIE_ERROR;
         }

         // pcie_osal_irq_disable(&pdev->irq_hdl);
         pcie_osal_irq_enable(&pdev->irq_hdl);
      }
   }

#else
   {
      IPCC_Handle pcie_ipcc_h = NULL;
      IPCCErr ipcc_err;
      uintptr_t msg_addr;

      // TODO: Move this IPCC_P_COMPUTEL0 into target specific configurable data
      ipcc_err = IPCC_Attach(&pcie_ipcc_h, IPCC_P_COMPUTEL0); 
      if (ipcc_err != IPCC_EOK)
      {
         PCIE_HOST_LOG_ERROR ("IPCC attach failed");
         // TODO: Add more error codes to represent the individual errors
         return PCIE_ERROR;
      }

      pdev->ipcc_h = pcie_ipcc_h;

      ipcc_err = IPCC_GetTriggerAddressAndData(pcie_ipcc_h,
                                               IPCC_C_CDSP,
                                               0,
                                               &msg_addr,
                                               &pdev->msi_intr_message_data);
      if (ipcc_err != IPCC_EOK)
      {
         PCIE_HOST_LOG_ERROR ("IPCC get MSI msg info failed");
         // TODO: Add more error codes to represent the individual errors
         return PCIE_ERROR;
      }
      pdev->msi_intr_message_addr = msg_addr;

      // TODO: make IPCC_C_CDSP as per target configurable data
      ipcc_err = IPCC_RegisterInterrupt(pcie_ipcc_h,
                                        IPCC_C_CDSP,
                                        0,                     // min
                                        MAX_MSI_VECTORS - 1,   // max (not count)
                                        pcie_msi_ipcc_isr,
                                        pdev);

      if (ipcc_err != IPCC_EOK)
      {
         PCIE_HOST_LOG_ERROR ("IPCC intr register failed");
         return PCIE_ERROR;
      }

      if (configure_msi (pdev, pdev->msi_intr_message_addr, pdev->msi_intr_message_data)  != PCIE_SUCCESS)
      {
         PCIE_HOST_LOG_ERROR ("MSI config failed");
         // TODO: Add more error codes to represent the individual errors
         return PCIE_ERROR;
      }
   }
#endif
#endif

   return PCIE_SUCCESS;
}

pcie_status_t pcie_register_msi_callback (pcie_dev_t *pdev, uint32 msi_vector, pcie_msi_callback_fn_t msi_cb_fn, void* arg, uint64* trig_addr_ptr, uint32* trig_data_ptr)
{
   if ((NULL == pdev) || (msi_vector >= MAX_MSI_VECTORS) || (msi_cb_fn == NULL))
      return PCIE_ERROR;

   pdev->msi_cb_clients[msi_vector].msi_cb_fn = msi_cb_fn;
   pdev->msi_cb_clients[msi_vector].arg = arg;

   if (trig_addr_ptr)
      *trig_addr_ptr = pdev->msi_intr_message_addr;

   if (trig_data_ptr)
      *trig_data_ptr = pdev->msi_intr_message_data + msi_vector;

   return PCIE_SUCCESS;
}


pcie_status_t pcie_unregister_msi_callback (pcie_dev_t *pdev, uint32 msi_vector, pcie_msi_callback_fn_t msi_cb_fn)
{
   /* TODO: Add implementation here */
   return PCIE_SUCCESS;
}

pcie_status_t pcie_msi_enable_int (pcie_dev_t *pdev, uint32 msi_vector)
{
   /* TODO: Add implementation here */
   return PCIE_SUCCESS;
}

pcie_status_t pcie_msi_disable_int (pcie_dev_t *pdev, uint32 msi_vector)
{
   /* TODO: Add implementation here */
   return PCIE_SUCCESS;
}

#endif

#ifdef ENABLE_TEST_CODE

pcie_dev_t *test_dev;
uint64 bar0_addr, bar0_sz;

void test_probe_cb (pcie_dev_t *pdev, const pcie_dev_probe_cb_payload_t *cb_data, void* user_data)
{
   /* Store handle */
   test_dev = pdev;

   /* Extract BAR info */
   bar0_addr = cb_data->rsrc.bars[0].pa;
   bar0_sz = cb_data->rsrc.bars[0].sz;

   PCIE_HOST_LOG_ERROR ("BAR0 : %lX, %lX\n", bar0_addr, bar0_sz);
//   pcie_enable_device (test_dev);  // Enable here instead if required
   return;
}

void pcie_host_stub_test (void)
{
  pcie_device_info_t test_info;

  test_info.vendor_id = PCIE_ID_ANY;
  test_info.device_id = PCIE_ID_ANY;
  test_info.class_id = PCIE_ID_ANY;
  test_info.rbdf_info = 0; // will have the port info

  /* Init PCIe driver */
//  pcie_rc_init ();

  /* Register for callback on device discovery */
  pcie_register_device (&test_info, test_probe_cb, NULL);

  /* Start enumerating the attached devices */
  pcie_enumerate (2);

  /* if a device is found enable it before using */
  pcie_enable_device (test_dev);

  pcie_enumerate (4);

  /* if a device is found enable it before using */
  pcie_enable_device (test_dev);

  pcie_enumerate (6);

  /* if a device is found enable it before using */
  pcie_enable_device (test_dev);
}


#endif

