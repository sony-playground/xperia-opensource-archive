/**---------------------------------------------------------------------------
 *
 *  @file  :  usb4_platform_uc_target.c
 *
 *
 *  @brief :  usb4 platform uC implementation
 *
 *   Copyright (c) 2018-2021 Qualcomm Technologies Incorporated.
 *   All Rights Reserved.
 *   Qualcomm Confidential and Proprietary
 *--------------------------------------------------------------------------*/

#include <Library/QcomLib.h>
#include <Protocol/EFIPIL.h>
#include "Usb4Log.h"
#include "usb4_platform_target.h"
#include "msmhwio_usb4.h"
#include <Library/BaseMemoryLib.h>

#ifdef USB_USE_STATIC_LOAD_METHOD
volatile boolean usb4_use_static_load_method = TRUE;
#else // ~USB_USE_STATIC_LOAD_METHOD
volatile boolean usb4_use_static_load_method = FALSE;
#endif // ~USB_USE_STATIC_LOAD_METHOD


/* Declared in VVHAL_usb4_platform_interrupts.cpp */
extern USB4_intDesc g_usb4_platform_interrupts_core0[];
extern UINT32 g_usb4_platform_interrupts_core0_size;
extern USB4_intDesc g_usb4_platform_interrupts_core1[];
extern UINT32 g_usb4_platform_interrupts_core1_size;

/*----------------------------------------------------------------------------
 * Macros and definitions
 *--------------------------------------------------------------------------*/
/*LOG BUFFER MACROS*/
#define LOG_MAX_NUM_OF_ENTRIES 5
#define LOG_MAX_ENTRY_SIZE 5
#define LOG_SIZE_BYTES 100

enum UcEventOpcode
{
    UcEventOpcode_Zero              = 0x0,
    UcEventOpcode_Message           = 0x1,
    UcEventOpcode_PropreietyError   = 0x2,
    UcEventOpcode_TestResult        = 0x3,
    UcEventOpcode_SleepDone         = 0x4,
    UcEventOpcode_ExitOffline       = 0x5,
    UcEventOpcode_Disconnect        = 0x6,
};

#pragma pack(push)
#pragma pack(1)
typedef struct
{
    UINT32 numOfEntries : 16;
    UINT32 entrySize    : 16;
    UINT32 next;
    UINT32 unread; /* Number of unread entries */
    UINT32 reserved;
    UINT8  pEvents[1];
} UcEventsRing;
#pragma pack(pop)

/*----------------------------------------------------------------------------
* Global variables
*--------------------------------------------------------------------------*/

/* USB4 Partition Guid */
extern EFI_GUID gUsb4FwPartiGuid ;
  
/* USB4 Backup Partition Guid */
extern EFI_GUID gBackupUsb4FwPartiGuid ;

static UINT32 s_USB4_FW_array[] =
{
    #include "usb4_uc_fw_image.h"
};

#if defined(USB4_COMPILING_GEN_EMU)
    DEO_MUTEX_DECLARE(static s_usb4_platform_mutex0); // one instance for each core
    DEO_MUTEX_DECLARE(static s_usb4_platform_mutex1); // one instance for each core
#endif /* USB4_COMPILING_GEN_EMU */


/*----------------------------------------------------------------------------
 * Static local functions
 *--------------------------------------------------------------------------*/
/**
 * @brief parse n bytes from buff as int (hex) 
 * @param [in] str start of string to parse
 * @param [in] n number of characters to parse
 * @param [out] val UINT32 parsed from hex string
 * @return 0 on success, other on failure
 */
#if 0
int parse_hex_UINT32(const char* str, UINT32 n, UINT32* val)
{
    char tmp[9] = { 0x0 };
    
    if (n > 8)
    {
        USB4_ERROR_STACK_MSG(-1, "n > 8");
        return 0;
    }
    
    usb4_mem_memcpy(tmp, str, n);
    tmp[n] = 0;
    
    *val = (UINT32)(strtoul(tmp, NULL, 16));
    
    return 0;
}
#endif

/**
 * @brief Byte swap unsigned int
 * @param [in] val value to byte swap  
 * @return swapped byte
 */
static UINT32 swap_UINT32(UINT32 val)
{
    val = ((val << 8) & 0xFF00FF00 ) | ((val >> 8) & 0xFF00FF ); 
    return (val << 16) | (val >> 16);
}

#if 0
/**
 * @brief load fw from hex file
 * @param [in] fp opened file pointer "rb" of the fw hex file
 * @param [in] pFirmWareAddress fw will be loaded to that address
 * @return 0 on success, other on failure
 */
static int loadFwFromFsHexFile(FILE *fp, UINT8* pFirmWareAddress)
{
    char line[64] = {0x0};
    char* str;
    
    UINT32 numbytes = 0;
    UINT32 offset = 0;
    UINT32 type = 0;
    UINT32 val;
    UINT32 fw_version = 0;
    UINT32* dst;
    
    USB4_LOG_INFO("Loading FW from file...\n");

    while (NULL != fgets(line, ARR_SIZE(line), fp)) 
    {
        if (0 != parse_hex_UINT32(line + 1, 2, &numbytes)) // 2 bytes start at 1
        {
            USB4_ERROR_STACK(-1);
            return -1;
        }
        
        if (0 != parse_hex_UINT32(line + 3, 4, &offset)) // 4 bytes start at 3
        {
            USB4_ERROR_STACK(-1);
            return -1;
        }
        
        if (0 != parse_hex_UINT32(line + 7, 2, &type)) // 2 bytes start at 7
        {
            USB4_ERROR_STACK(-1);
            return -1;
        }
        
        if (0x0 != type)
        {
            return 0;
        }
        
        if (0 != (numbytes & 0x3))
        {
            USB4_LOG_WARNING("garbage padding (length not dword aligned): %s", line);
        }
        
        str = line + 9; // start of the 1st hex string
        
        for (UINT32 i = 0; i < numbytes; i += 4)
        {
            if (0 != parse_hex_UINT32(str, 8, &val))
            {
                return -1;
            }
            
            // swap endianess
            val = swap_UINT32(val);
            
            if ((0 == fw_version) && (4 == i))
            {
                USB4_LOG_INFO(" - Deteceted FW version 0x%08X\n", val);
                fw_version = 1;
            }
            
            dst = (UINT32*)(pFirmWareAddress + offset + i);
            *dst = val;
            
            str += 8; // continue parsing next 8 chars
        }
    }
    
    USB4_ERROR_STACK_MSG(-1, "Missing EOD sign");
    return -1;
}
#endif


#define SWAP_BYTES(x,y)  do {           \
                           UINT8 t;     \
                           t = (x);     \
                           (x) = (y);   \
                           (y) = t;     \
                         } while(0)


/* Convert Byte Stream data to GUID format.
 * For example:
 * if Cfg has data in below format:
 *    DEA0BA2C CBDD 4805 B4F9 F428251C3E98
 *
 * Need to be converted into GUID format (Considering integer and endianness)
 *    DEA0BA2C CBDD 4805 B4F9 F428251C3E98 is equal to stream as follows
 *    2C BA A0 DE DD CB 05 48 B4 F9 F4 28 25 1C 3E 98
 * */
static void AdjustGUID(UINT8* Buffer)
{
  /* DWord */
  SWAP_BYTES(Buffer[0], Buffer[3]);
  SWAP_BYTES(Buffer[1], Buffer[2]);

  /* Word */
  SWAP_BYTES(Buffer[4], Buffer[5]);

  /* Word */
  SWAP_BYTES(Buffer[6], Buffer[7]);
}


/*----------------------------------------------------------------------------
 * uC functions
 *--------------------------------------------------------------------------*/
/*====================== VVHAL_usb4_platform_uC_target ===================*/
void Usb4PlatformUcInit(usb4_platform_uC_ctx_t* usb4_platform_uC_ctx, UINT8* coreBaseAddress, UINT32 coreIdx) // Constructor
{
    // VVHAL_usb4_platform_uC(),
    usb4_platform_uC_ctx->m_coreBaseAddress = coreBaseAddress;
    usb4_platform_uC_ctx->m_pNextPtrAddr = NULL;
    usb4_platform_uC_ctx->m_coreIdx = coreIdx;
    usb4_platform_uC_ctx->m_numEntries = 0;

    usb4_platform_uC_ctx->m_entrySize_bytes = 0;
    usb4_platform_uC_ctx->m_pEventsAddr = NULL;

    usb4_platform_uC_ctx->m_nextEvent = 0;

    usb4_platform_uC_ctx->m_lastTestRes = 0;
    usb4_platform_uC_ctx->m_lastTestNumber = 0;
    usb4_platform_uC_ctx->m_numTestRes = 0;
    usb4_platform_uC_ctx->m_lastPropErr = 0;
    usb4_platform_uC_ctx->m_lastProgCnt = 0;
    usb4_platform_uC_ctx->m_numPropErr = 0;
    usb4_platform_uC_ctx->m_sleepDoneCnt = 0;
    usb4_platform_uC_ctx->m_MsgRing = NULL;
}

void Usb4PlatformUcDeInit(usb4_platform_uC_ctx_t* usb4_platform_uC_ctx) // Destructor
{
  Usb4PlatformUcDeActivateUc(usb4_platform_uC_ctx);
}

int Usb4PlatformUcLoadFW(usb4_platform_uC_ctx_t* usb4_platform_uC_ctx)
{
  EFI_STATUS Status = EFI_LOAD_ERROR;
  PIL_SUBSYS_CFG_TYPE usb4_cfg = {};
#if 0
  CHAR8*              PartGuidStr = "3FA03C7A 9FDC 498B A2A8 DE11EE339790"; // Primary
#endif
  EFI_PIL_PROTOCOL*   PILProtocol = NULL;

#if 0
    FILE *file = NULL;
#endif
    UINT32 offset;
    UINT32 length;
    UINT32* image = (UINT32*)(s_USB4_FW_array);
    UINT32* end_of_image = image + ARR_SIZE(s_USB4_FW_array); /* / sizeof(dword) */
    UINT8* FirmWareAddress;
    UINT8* pUcPerBase;

    // Disable the UC
    pUcPerBase = usb4_platform_uC_ctx->m_coreBaseAddress + USB4_UC_PER_REG_BASE_OFFS;
    HWIO_OUTX(pUcPerBase, USB4_UC_REGS_INSIDE_USB4__CONTROL, 0x0);

    /* Assign FW destination address */
    FirmWareAddress = usb4_platform_uC_ctx->m_coreBaseAddress + USB4_UC_RAM_REG_BASE_OFFS;
    USB4_ASSERT(NULL != FirmWareAddress);
    
    if (usb4_use_static_load_method)
    {
#if 0
      file = fopen(s_fw_filename, "rb");
      if (NULL != file)
      {
          if (0 != loadFwFromFsHexFile(file, FirmWareAddress))
          {
              USB4_ERROR_STACK(-1);
              goto ErrorHandling;
          }
          fclose(file);
          file = NULL;
      }
      else
#endif
      {
          Usb4Log1(USB4_LOG_CFG, Usb4PlatformUcLoadFW__Params__LoadingCompiledFWVersion, 0, s_USB4_FW_array[3]);
          // USB4_LOG_INFO("Loading compiled FW version 0x%08X\n", s_USB4_FW_array[3]);    
      
          /*load uC from compiled version */
          while (image < end_of_image)
          {
              offset = *image++;
              length = *image++;
              // TODO: AC may need to replace this with custom loop byte by byte copying
              usb4_mem_memcpy_custom(FirmWareAddress + offset, (UINT8*)(image), length<<2);
              image += length;
          }
      }
    }
    else // PIL loading method
    {
      // GUID 3FA03C7A-9FDC-498B-A2A8-DE11EE339790 Primary
      // GUID A3381699-350C-465E-BD5D-FA3AB901A39A Backup
      if (1 == usb4_platform_uC_ctx->m_coreIdx) // Same image is loaded to both USB cores on HYP side, load after clocks on for both core 0 and 1
      {
        usb4_cfg.Version = 2;
        usb4_cfg.Type = ELF_SINGLE;

        /* Load From "USB4FW" Partition */        
        CopyGuid(&(usb4_cfg.PartiGuid), (CONST GUID  *)&gUsb4FwPartiGuid);
        CopyGuid(&(usb4_cfg.BackupPartiGuid), (CONST GUID  *)&gBackupUsb4FwPartiGuid);
        
        AsciiStrToUnicodeStrS("USB4FW", usb4_cfg.FwName, NAME_MAX_LENGTH);

        usb4_cfg.SubsysID = 0x20; // TZ_PIL_AUTH_USB4FW_PROC
  //      usb4_cfg.ResvRegionStart = (UINT64)(FirmWareAddress); // PIL framework does not support device memory
        usb4_cfg.ResvRegionStart = 0x808A1000; // Manually carve out RAM region, memscpy to final destination in TZ
        usb4_cfg.ResvRegionSize = 0xE000;
        usb4_cfg.ImageLoadInfo = TRUE;
        usb4_cfg.OverrideElfAddr = TRUE;
        usb4_cfg.Unlock = TRUE;

        Status = gBS->LocateProtocol(&gEfiPilProtocolGuid, NULL, (VOID **)&PILProtocol);
        if ((EFI_SUCCESS != Status) && (NULL == PILProtocol))
        {
          Usb4Log1(USB4_LOG_ERR, Usb4UcLoadFirmware__Err_Failed_LocateEfiPil, 0, usb4_platform_uC_ctx->m_coreIdx);
        }
        else
        {
          if (NULL != PILProtocol)
          {
            /* Now load the SPSS with the cfg created above */
            Status = PILProtocol->ProcessPilImageExt(&usb4_cfg);
            if ((EFI_SUCCESS != Status))
            {
              Usb4Log1(USB4_LOG_ERR, Usb4UcLoadFirmware__Err_Failed_ProcessPil, 0, usb4_platform_uC_ctx->m_coreIdx);
            }
          }
          else
          {
            Usb4Log1(USB4_LOG_ERR, Usb4UcLoadFirmware__Err_Failed_ProcessPil, 0, usb4_platform_uC_ctx->m_coreIdx);
          }
        }
      }
    }
    
    return 0;
#if 0
ErrorHandling:
    if (NULL != file)
    {
        fclose(file);
        file = NULL;
    }
    return -1;
#endif
};

int Usb4PlatformUcActivateUc(usb4_platform_uC_ctx_t* usb4_platform_uC_ctx)
{
    int rc;
    UINT8* pUcPerBase;
    UINT8* pUcRamBase;
    UINT8* pPgPropBase;
    UINT8* pRCRouterCsBase;
    UcEventsRing* pRing = NULL;
    UINT32 offset_bytes;
// #ifdef USB4_COMPILING_GEN_EMU_VELOCE
//    UINT32 RR_timeout = 50000;
// #else // !USB4_COMPILING_GEN_EMU_VELOCE
    UINT32 RR_timeout = 1000;
// #endif // !USB4_COMPILING_GEN_EMU_VELOCE

#if defined(USB4_COMPILING_GEN_EMU)
    deo_mutex_t* pMutex;
#endif /* USB4_COMPILING_GEN_EMU */

    pUcPerBase = usb4_platform_uC_ctx->m_coreBaseAddress + USB4_UC_PER_REG_BASE_OFFS;
    pUcRamBase = usb4_platform_uC_ctx->m_coreBaseAddress + USB4_UC_RAM_REG_BASE_OFFS;
    pPgPropBase = usb4_platform_uC_ctx->m_coreBaseAddress + PG_PROP_REG_BASE_OFFS;
    pRCRouterCsBase = usb4_platform_uC_ctx->m_coreBaseAddress + ROUTER_CONFIG_PROP_REG_BASE_OFFS;

    /* uC is already active, so all the relevant stuff was done already */
    if (1 == HWIO_INXF(pUcPerBase, USB4_UC_REGS_INSIDE_USB4__CONTROL, UC_ENABLE))
    {
        return 0;
    }
    
    /* Requested by Eran for the FCM to manage the credits properly */
    HWIO_OUTXF(pPgPropBase, USB4_FCM_2_CFG, DISABLE_CP_ANY_HOPID, 0x0);

#if defined(USB4_COMPILING_GEN_EMU)
    pMutex = (0x0 == usb4_platform_uC_ctx->m_coreIdx) ? &s_usb4_platform_mutex0 : 
                                  &s_usb4_platform_mutex1;
    if (NULL == pMutex->lock)
    {
        if (DEO_SUCCESS != VVDRV_deo_mutex_create(pMutex, DEO_MUTEX_ATTR_CRITICAL_SECTION))
        {
            // Mutex is requred in enviorments with threads and there might be
            // a pending ISR running even after we masked the IRQs
            USB4_ERROR_STACK_MSG(-1, "Mutex creation failure\n");
            goto ErrorHandling;
        }
    }
    if (DEO_SUCCESS != VVDRV_deo_mutex_lock(pMutex))
	{
		USB4_ERROR_STACK(-1);
		goto ErrorHandling;
	}
#endif /* USB4_COMPILING_GEN_EMU */

    if (NULL == usb4_platform_uC_ctx->m_MsgRing)
    {
        // usb4_platform_uC_ctx->m_MsgRing = new (std::nothrow)VVHAL_usb4_platform_uC_target_MsgRing();
        usb4_platform_uC_ctx->m_MsgRing = usb4_mem_alloc(sizeof(usb4_platform_uC_target_MsgRing_ctx_t), 0);
        if (NULL == usb4_platform_uC_ctx->m_MsgRing)
        {
            USB4_ERROR_STACK_MSG(-1, "message ring failed\n");
            goto ErrorHandling;
        }
    }

    //Clear Router Ready
    HWIO_OUTXF(pRCRouterCsBase, USB4_RC_ROUTER_CS_6, RR, 0);

    // UC_Enable = 1
    HWIO_OUTXF(pUcPerBase, USB4_UC_REGS_INSIDE_USB4__CONTROL, UC_ENABLE, 1);

    //Poll for RR
    USB4_WHILE_WITH_TIMEOUT(1 != HWIO_INXF(pRCRouterCsBase, USB4_RC_ROUTER_CS_6, RR), RR_timeout, rc);
    USB4_ASSERT_MSG(0 == rc, "Uc didn't set router ready within specified timeout");

    // Read uC event ring details and store data to skip ahb access later
    offset_bytes = HWIO_INX(pUcPerBase, USB4_UC_REGS_FW_INT_STATUS_SET);
    pRing = (UcEventsRing*)(HWIO_ADDRXI(pUcRamBase, IRAM_DWORD_n, 0) + offset_bytes);

    usb4_platform_uC_ctx->m_numEntries = pRing->numOfEntries;
    usb4_platform_uC_ctx->m_entrySize_bytes = pRing->entrySize;
    usb4_platform_uC_ctx->m_pNextPtrAddr = &(pRing->next);
    usb4_platform_uC_ctx->m_pNumOfNewEntries =  &(pRing->unread);
    usb4_platform_uC_ctx->m_pEventsAddr = pRing->pEvents;

    // initialize local variables which handle the uC ring
    usb4_platform_uC_ctx->m_nextEvent = 0;
    usb4_platform_uC_ctx->m_lastTestRes = 0;
    usb4_platform_uC_ctx->m_lastTestNumber = 0;
    usb4_platform_uC_ctx->m_numTestRes = 0;
    usb4_platform_uC_ctx->m_lastPropErr = 0;
    usb4_platform_uC_ctx->m_lastProgCnt = 0;
    usb4_platform_uC_ctx->m_numPropErr = 0;
    usb4_platform_uC_ctx->m_sleepDoneCnt = 0;

    if (0 != Usb4PlatformUcMsgRingInit(usb4_platform_uC_ctx->m_MsgRing, usb4_platform_uC_ctx->m_numEntries * 5, usb4_platform_uC_ctx->m_entrySize_bytes))
    {
        USB4_ERROR_STACK_MSG(-1, "m_MsgRing.init failed\n");
        goto ErrorHandling;
    }

    // Enable interrupt from uC to interrupt controller
    HWIO_OUTXF(pUcPerBase, USB4_UC_REGS_FW_INT_MASK, MASK_FW_INT, 1); // MASK=1 is en
#if defined(USB4_COMPILING_GEN_EMU)
	if (DEO_SUCCESS != VVDRV_deo_mutex_unlock(pMutex))
	{
		return -1;
	}
#endif /* USB4_COMPILING_GEN_EMU */
    return 0;
ErrorHandling:
#if defined(USB4_COMPILING_GEN_EMU)
	(void) VVDRV_deo_mutex_unlock(pMutex);
#endif /* USB4_COMPILING_GEN_EMU */
    if (0 != Usb4PlatformUcDeActivateUc(usb4_platform_uC_ctx))
    {
        USB4_ERROR_STACK_MSG(-1, "Deactivate as part of recovery failed");
    }
    return -1;
};

int Usb4PlatformUcDeActivateUc(usb4_platform_uC_ctx_t* usb4_platform_uC_ctx)
{
    UINT8* UcPer;
    UINT8* routerConfigProprietary;

#if defined(USB4_COMPILING_GEN_EMU)
    deo_mutex_t* pMutex;                                               
    pMutex = (0x0 == usb4_platform_uC_ctx->m_coreIdx) ? &s_usb4_platform_mutex0 : 
                                  &s_usb4_platform_mutex1;
    if (NULL != pMutex->lock)
    {
        if (DEO_SUCCESS != VVDRV_deo_mutex_destroy(pMutex))
        {
            // Mutex is requred in enviorments with threads and there might be
            // a pending ISR running even after we masked the IRQs
            USB4_ERROR_STACK_MSG(-1, "Mutex destroy failure\n");
        }
        pMutex->lock = NULL;
    }
#endif /* USB4_COMPILING_GEN_EMU */

    UcPer = usb4_platform_uC_ctx->m_coreBaseAddress + USB4_UC_PER_REG_BASE_OFFS;
    routerConfigProprietary = usb4_platform_uC_ctx->m_coreBaseAddress + ROUTER_CONFIG_PROP_REG_BASE_OFFS;

    //UC_Enable = 0
    HWIO_OUTXF(UcPer, USB4_UC_REGS_INSIDE_USB4__CONTROL, UC_ENABLE, 0);

    // Disable interrupt from uC to interrupt controller
    HWIO_OUTXF(UcPer, USB4_UC_REGS_FW_INT_MASK, MASK_FW_INT, 0); // MASK=0 is dis

    // Clear RR
    HWIO_OUTXF(routerConfigProprietary, USB4_RC_ROUTER_CS_6, RR, 0);

    if (NULL != usb4_platform_uC_ctx->m_MsgRing)
    {
        Usb4PlatformUcMsgRingDestroy(usb4_platform_uC_ctx->m_MsgRing);
        usb4_mem_free(usb4_platform_uC_ctx->m_MsgRing);
        usb4_platform_uC_ctx->m_MsgRing = NULL;
    }

    // Ring acceess / configuration must be zeroed or we will not follow the ring
    usb4_platform_uC_ctx->m_pNextPtrAddr = 0;
    usb4_platform_uC_ctx->m_pNumOfNewEntries = 0;
    usb4_platform_uC_ctx->m_numEntries = 0;
    usb4_platform_uC_ctx->m_entrySize_bytes = 0;
    usb4_platform_uC_ctx->m_pEventsAddr = 0;

    usb4_platform_uC_ctx->m_nextEvent = 0;
    usb4_platform_uC_ctx->m_lastTestRes = 0;
    usb4_platform_uC_ctx->m_lastTestNumber = 0;
    usb4_platform_uC_ctx->m_numTestRes = 0;
    usb4_platform_uC_ctx->m_lastPropErr = 0;
    usb4_platform_uC_ctx->m_lastProgCnt = 0;
    usb4_platform_uC_ctx->m_numPropErr = 0;

    return 0;
};

void Usb4PlatformUcHandleUcEvents(usb4_platform_uC_ctx_t* usb4_platform_uC_ctx)
{
    UINT8* pUcPerBase;
    UINT8* p;
    UINT32 last = 0xFFFFFFFF;
    UINT32 numberOfNewEvents;
    UINT8 opcode;
    UINT8 *params;

#if defined(USB4_COMPILING_GEN_EMU)
    deo_mutex_t* pMutex = (0x0 == usb4_platform_uC_ctx->m_coreIdx) ? &s_usb4_platform_mutex0 :
                                               &s_usb4_platform_mutex1;
    if ((NULL == pMutex) || (NULL == pMutex->lock))
    {
    	return;
    }
#endif /* USB4_COMPILING_GEN_EMU */

    if ((NULL == usb4_platform_uC_ctx->m_pNextPtrAddr) || (NULL == usb4_platform_uC_ctx->m_pEventsAddr))
    {
        return;
    }

    pUcPerBase = usb4_platform_uC_ctx->m_coreBaseAddress + USB4_UC_PER_REG_BASE_OFFS;

    if (0 == HWIO_INX(pUcPerBase, USB4_UC_REGS_FW_INT_STATUS))
    {
        return;
    }

#if defined(USB4_COMPILING_GEN_EMU)
    if (DEO_SUCCESS != VVDRV_deo_mutex_lock(pMutex))
    {
        return;
    }
#endif /* USB4_COMPILING_GEN_EMU */

    do
    {
        if (last != *usb4_platform_uC_ctx->m_pNextPtrAddr)
        {
            numberOfNewEvents = *usb4_platform_uC_ctx->m_pNumOfNewEntries;
            HWIO_OUTX(pUcPerBase, USB4_UC_REGS_FW_INT_CLR, 0x1);
            last = *usb4_platform_uC_ctx->m_pNextPtrAddr; // ahb access here
            if (numberOfNewEvents >= usb4_platform_uC_ctx->m_numEntries) /* There was a wrap-around since last read */
            {
                /* Take the whole ring - since we can't prevent FW from writing new entries, some info may be corrupted, as we are reading
                 * while uC is writing */
                usb4_platform_uC_ctx->m_nextEvent = (last + 1) & (usb4_platform_uC_ctx->m_numEntries - 1);
            }
        }

        while (usb4_platform_uC_ctx->m_nextEvent != last)
        {
            p = usb4_platform_uC_ctx->m_pEventsAddr + (usb4_platform_uC_ctx->m_nextEvent * usb4_platform_uC_ctx->m_entrySize_bytes);
            opcode = p[0];
            params = p + 1;
            switch (opcode)
            {
                case UcEventOpcode_Zero:
                    Usb4Log(USB4_LOG_CFG, Usb4PlatformUcHandleUcEvents__Error__InvalidOpCodeError, 0);
                    // USB4_LOG_ERROR("Invalid opcode Error!\n");
                    while(1);

                case (UcEventOpcode_Message):
                    Usb4PlatformUcMsgRingPush(usb4_platform_uC_ctx->m_MsgRing, params);
                    break;

                case (UcEventOpcode_PropreietyError):
                    usb4_platform_uC_ctx->m_lastPropErr = *params;
                    if (usb4_platform_uC_ctx->m_lastPropErr > 1)
                    {
                        usb4_platform_uC_ctx->m_lastProgCnt = *(UINT16*)(p + 2);
                    }
                    else
                    {
                        usb4_platform_uC_ctx->m_lastProgCnt = 0;
                    }
                    // USB4_LOG_WARNING("Core[%u] uC signaled error %u: ", m_coreIdx, m_lastPropErr);
                    Usb4Log2(USB4_LOG_CFG, Usb4PlatformUcHandleUcEventsError__Params__Core_uCSignaledError, 0, usb4_platform_uC_ctx->m_coreIdx, usb4_platform_uC_ctx->m_lastPropErr);
                    switch(usb4_platform_uC_ctx->m_lastPropErr)
                    {
                        case 0x1:
                            // USB4_LOG_WARNING("Invalid opcode\n");
                            Usb4Log(USB4_LOG_CFG, Usb4PlatformUcHandleUcEventsInvalidOpCode__Error, 0);
                            break;
                        case 0x2:
                            // USB4_LOG_WARNING("Exception; PC: %u\n", m_lastProgCnt);
                            Usb4Log1(USB4_LOG_CFG, Usb4PlatformUcHandleUcEventsError__Params__ExceptionPC, 0, usb4_platform_uC_ctx->m_lastProgCnt);
                            break;
                        case 0x3:
                            // USB4_LOG_WARNING("Fatal error PC: %u\n", m_lastProgCnt);
                            Usb4Log1(USB4_LOG_CFG, Usb4PlatformUcHandleUcEventsError__Params__FatalErrorPC, 0, usb4_platform_uC_ctx->m_lastProgCnt);
                            break;
                        case 0x4:
                            // USB4_LOG_WARNING("Warning PC: %u\n", m_lastProgCnt);
                            Usb4Log1(USB4_LOG_CFG, Usb4PlatformUcHandleUcEventsError__Params__WarningPC, 0, usb4_platform_uC_ctx->m_lastProgCnt);
                            break;
                        case 0x5:
                            // USB4_LOG_WARNING("HSE failed, Phase: %u\n", m_lastProgCnt);
                            Usb4Log1(USB4_LOG_CFG, Usb4PlatformUcHandleUcEventsError__Params__HSEFailed, 0, usb4_platform_uC_ctx->m_lastProgCnt);
                            break;
                        case 0x6:
                            // USB4_LOG_WARNING("HIA reset failed\n");
                            Usb4Log(USB4_LOG_CFG, Usb4PlatformUcHandleUcEventsHIAResetFailed__Error, 0);
                            usb4_platform_uC_ctx->m_lastProgCnt = 0;
                            break;
                        case 0x7:
                            // USB4_LOG_WARNING("HW version mismatch, Expected version %u\n", m_lastProgCnt);
                            Usb4Log1(USB4_LOG_CFG, Usb4PlatformUcHandleUcEventsError__Params__HwVersionMismatchExpectedVersion, 0, usb4_platform_uC_ctx->m_lastProgCnt);
                            break;
                        default:
                            // USB4_LOG_WARNING("Unknown\n");
                            Usb4Log(USB4_LOG_CFG, Usb4PlatformUcHandleUcEventsUnknown__Error, 0);
                            usb4_platform_uC_ctx->m_lastProgCnt = 0;
                            break;
                    }

                    usb4_platform_uC_ctx->m_numPropErr++;
                    break;
                case (UcEventOpcode_TestResult):
                    usb4_platform_uC_ctx->m_lastTestRes = p[1];
                    usb4_platform_uC_ctx->m_lastTestNumber = p[3];
                    usb4_platform_uC_ctx->m_numTestRes++;
                    break;
                case (UcEventOpcode_SleepDone):
                    usb4_platform_uC_ctx->m_sleepDoneCnt++;
                    break;
                case (UcEventOpcode_ExitOffline):
                    // USB4_LOG_WARNING("Core[%u] uC signaled \"Exit Offline\"\n", m_coreIdx);
                    Usb4Log1(USB4_LOG_CFG, Usb4PlatformUcHandleUcEventsUCSignaledExitOffline__Warn__Core, 0, usb4_platform_uC_ctx->m_coreIdx);
                    break;
                case (UcEventOpcode_Disconnect):
                    // USB4_LOG_WARNING("Core[%u] uC signaled Disconnect:", m_coreIdx);
                    Usb4Log1(USB4_LOG_CFG, Usb4PlatformUcHandleUcEventsUCSignaledDisconnect__Warn__Core, 0, usb4_platform_uC_ctx->m_coreIdx);
                    switch(p[1])
                    {
                        case 0x0:
                            // USB4_LOG_WARNING("Reason %d - LT_LROFF received from link partner\n", p[1]);
                            Usb4Log1(USB4_LOG_CFG, Usb4PlatformUcHandleUcEventsDisconnectLtLroffReceivedFromLinkPartner__Warn__Reason, 0, p[1]);
                            break;
                        case 0x1:
                            // USB4_LOG_WARNING("Reason %d - our SBRX was driven low for tDisconnectRx time by link partner\n", p[1]);
                            Usb4Log1(USB4_LOG_CFG, Usb4PlatformUcHandleUcEventsDisconnectOurSbrxWasDrivenLowForTDisconnectRxTimeByLinkPartner__Warn__Reason, 0, p[1]);
                            break;
                        case 0x2:
                            // USB4_LOG_WARNING("Reason %d - FW initiated disconnect due to Training Abort indication from Port Group\n", p[1]);
                            Usb4Log1(USB4_LOG_CFG, Usb4PlatformUcHandleUcEventsDisconnectFwInitiatedDisconnectDueToTrainingAbortIndicastionFromPortGroup__Warn__Reason, 0, p[1]);
                            break;
                        case 0x3:
                            // USB4_LOG_WARNING("Reason %d - FW initiated disconnect due to Bonding Fail indication from Port Group\n", p[1]);
                            Usb4Log1(USB4_LOG_CFG, Usb4PlatformUcHandleUcEventsDisconnectFwInitiatedDisconnectDueToBondingFailIndicationFromPortGroup__Warn__Reason, 0, p[1]);
                            break;
                        case 0x4:
                            // USB4_LOG_WARNING("Reason %d - FW sends this reason as part of Downstream Port Reset flow\n", p[1]);
                            Usb4Log1(USB4_LOG_CFG, Usb4PlatformUcHandleUcEventsDisconnectFwSendsThisReasonAsPartOfDownstreamPortResetFlow__Warn__Reason, 0, p[1]);
                            break;
                        case 0x5:
                            // USB4_LOG_WARNING("Reason %d - Compliance Software or CM issued port operation \"Router Offline Mode\" with EOM=1\n", p[1]);
                            Usb4Log1(USB4_LOG_CFG, Usb4PlatformUcHandleUcEventsDisconnectComplianceSoftwareOrCmIssuedPortOpoerationRouterOfflineModeWithEOM1__Warn__Reason, 0, p[1]);
                            break;
                        case 0x6:
                            // USB4_LOG_WARNING("Reason %d - Qdriver sent \"Physical disconnect\" command while link was still established\n", p[1]);
                            Usb4Log1(USB4_LOG_CFG, Usb4PlatformUcHandleUcEventsDisconnectQdriverSentPhysicalDisconnectCommandWhileLinkWasStillEstablished__Warn__Reason, 0, p[1]);
                            break;
                        case 0x7:
                            // USB4_LOG_WARNING("Reason %d - Lane0 was disabled by CM via config space\n", p[1]);
                            Usb4Log1(USB4_LOG_CFG, Usb4PlatformUcHandleUcEventsDisconnectLane0WasDisabledByCmViaConfigSpace__Warn__Reason, 0, p[1]);
                            break;
                        case 0x8:
                            // USB4_LOG_WARNING("Reason %d - Received LT_FALL for Lane0 from device\n", p[1]);
                            Usb4Log1(USB4_LOG_CFG, Usb4PlatformUcHandleUcEventsDisconnectReceivedLtFallForLane0FromDevice__Warn__Reason, 0, p[1]);
                            break;
                        default:
                            // USB4_LOG_WARNING("Reason %d - Unknown\n", p[1]);
                            Usb4Log1(USB4_LOG_CFG, Usb4PlatformUcHandleUcEventsDisconnectUnknown__Warn__Reason, 0, p[1]);
                            break;
                    }
                    break;
                default:
                    break;
            }
            //p[0] = 0;
            usb4_platform_uC_ctx->m_nextEvent = (usb4_platform_uC_ctx->m_nextEvent + 1) & (usb4_platform_uC_ctx->m_numEntries - 1);
        }
    } while (last != *usb4_platform_uC_ctx->m_pNextPtrAddr); // ahb access here to handle race

#if defined(USB4_COMPILING_GEN_EMU)
	if (DEO_SUCCESS != VVDRV_deo_mutex_unlock(pMutex))
	{
		return;
	}
#endif /* USB4_COMPILING_GEN_EMU */
}

int Usb4PlatformUcGetTestResult(usb4_platform_uC_ctx_t* usb4_platform_uC_ctx, UINT32* pLastRes, UINT32* pLastTestNum, UINT32* pNum)
{
    int result;

    result = Usb4PlatformUcMaskIrq(usb4_platform_uC_ctx, TRUE);
    if (0 != result)
    {
        USB4_ERROR_STACK(result);
        return result;
    }

    /* In case of polling mode, need to get results from uC explicitly */
    Usb4PlatformUcHandleUcEvents(usb4_platform_uC_ctx);

    *pLastRes = usb4_platform_uC_ctx->m_lastTestRes;
    *pLastTestNum = usb4_platform_uC_ctx->m_lastTestNumber;
    *pNum = usb4_platform_uC_ctx->m_numTestRes;
    usb4_platform_uC_ctx->m_numTestRes = 0;

    result = Usb4PlatformUcMaskIrq(usb4_platform_uC_ctx, FALSE);
    if (0 != result)
    {
        USB4_ERROR_STACK(result);
        return result;
    }

    return 0;
}

int Usb4PlatformUcGetPropreitryError(usb4_platform_uC_ctx_t* usb4_platform_uC_ctx, UINT32* pLastErr, UINT32* pProgramCounter, UINT32* pNum)
{
    int result;

    result = Usb4PlatformUcMaskIrq(usb4_platform_uC_ctx, TRUE);
    if (0 != result)
    {
        USB4_ERROR_STACK(result);
        return result;
    }
    
    /* In case of polling mode, need to get results from uC explicitly */
    Usb4PlatformUcHandleUcEvents(usb4_platform_uC_ctx);

    *pLastErr = usb4_platform_uC_ctx->m_lastPropErr;
    *pProgramCounter = usb4_platform_uC_ctx->m_lastProgCnt;
    *pNum = usb4_platform_uC_ctx->m_numPropErr;
    usb4_platform_uC_ctx->m_numPropErr = 0;

    result = Usb4PlatformUcMaskIrq(usb4_platform_uC_ctx, FALSE);
    if (0 != result)
    {
        USB4_ERROR_STACK(result);
        return result;
    }

    return 0;
}

int Usb4PlatformUcGetSleepDoneCounter(usb4_platform_uC_ctx_t* usb4_platform_uC_ctx, UINT32* pNumSleepDone)
{
    int result;

    result = Usb4PlatformUcMaskIrq(usb4_platform_uC_ctx, TRUE);
    if (0 != result)
    {
        USB4_ERROR_STACK(result);
        return result;
    }

    /* In case of polling mode, need to get results from uC explicitly */
    Usb4PlatformUcHandleUcEvents(usb4_platform_uC_ctx);

    *pNumSleepDone = usb4_platform_uC_ctx->m_sleepDoneCnt;

    result = Usb4PlatformUcMaskIrq(usb4_platform_uC_ctx, FALSE);
    if (0 != result)
    {
        USB4_ERROR_STACK(result);
        return result;
    }

    return 0;
}

int Usb4PlatformUcMaskIrq(usb4_platform_uC_ctx_t* usb4_platform_uC_ctx, BOOLEAN bMask)
{
    UINT8* pUcPerBase;
    UINT32 newVal;
    pUcPerBase = usb4_platform_uC_ctx->m_coreBaseAddress + USB4_UC_PER_REG_BASE_OFFS;

    newVal = (TRUE == bMask) ? 0x0 : 0x1;
    HWIO_OUTX(pUcPerBase, USB4_UC_REGS_FW_INT_MASK, newVal);// UnMask uC interrupt

    return 0;
}

int Usb4PlatformUcGetNumUcMsgs(usb4_platform_uC_ctx_t* usb4_platform_uC_ctx, UINT32* pNum)
{
    int result = 0;

    result = Usb4PlatformUcMaskIrq(usb4_platform_uC_ctx, TRUE);
    if (0 != result)
    {
        USB4_ERROR_STACK(result);
        return result;
    }

    /* In case of polling mode, need to get results from uC explicitly */
    Usb4PlatformUcHandleUcEvents(usb4_platform_uC_ctx);

    result = Usb4PlatformUcMsgRingGetNumMsgs(usb4_platform_uC_ctx->m_MsgRing, pNum);
    if (0 != result)
    {
        (void)Usb4PlatformUcMaskIrq(usb4_platform_uC_ctx, FALSE);
        USB4_ERROR_STACK(result);
        return -1;
    }

    result = Usb4PlatformUcMaskIrq(usb4_platform_uC_ctx, FALSE);
    if (0 != result)
    {
        USB4_ERROR_STACK(result);
        return result;
    }
    return 0;
}

int Usb4PlatformUcGetUCEntrySizeBaytes(usb4_platform_uC_ctx_t* usb4_platform_uC_ctx, UINT32* pSizeBytes)
{
    int result = 0;

    result = Usb4PlatformUcMaskIrq(usb4_platform_uC_ctx, TRUE);
    if (0 != result)
    {
        USB4_ERROR_STACK(result);
        return result;
    }

    /* In case of polling mode, need to get results from uC explicitly */
    Usb4PlatformUcHandleUcEvents(usb4_platform_uC_ctx);

    result = Usb4PlatformUcMsgRingGetEntrySize(usb4_platform_uC_ctx->m_MsgRing, pSizeBytes);
    if (0 != result)
    {
        (void)Usb4PlatformUcMaskIrq(usb4_platform_uC_ctx, FALSE);
        USB4_ERROR_STACK(result);
        return result;
    }

    result = Usb4PlatformUcMaskIrq(usb4_platform_uC_ctx, FALSE);
    if (0 != result)
    {
        USB4_ERROR_STACK(result);
        return result;
    }
    
    return 0;
}

int Usb4PlatformUcPrintUcMsgs(usb4_platform_uC_ctx_t* usb4_platform_uC_ctx)
{
    int result = 0;
    UINT32 numOfMsgs = 0;

    if ((NULL == usb4_platform_uC_ctx->m_coreBaseAddress) || (NULL == usb4_platform_uC_ctx->m_MsgRing))
    {
    	return 0;
    }

    result = Usb4PlatformUcMaskIrq(usb4_platform_uC_ctx, TRUE);
    if (0 != result)
    {
        USB4_ERROR_STACK(result);
        goto Exit;
    }

    /* In case of polling mode, need to get results from uC explicitly */
    Usb4PlatformUcHandleUcEvents(usb4_platform_uC_ctx);

    {/* Printing of messages needs to be protected by a Mutex, since it updates the ring, and in case of
    	multiple threads printing, there are race conditions */
#if defined(USB4_COMPILING_GEN_EMU)
		deo_mutex_t* pMutex = (0x0 == usb4_platform_uC_ctx->m_coreIdx) ? &s_usb4_platform_mutex0 :
												   &s_usb4_platform_mutex1;
		if ((NULL == pMutex) || (NULL == pMutex->lock))
		{
			USB4_ERROR_STACK(-1);
			result = -1;
			goto UnmaskAndExit;
		}
		if (DEO_SUCCESS != VVDRV_deo_mutex_lock(pMutex))
		{
			USB4_ERROR_STACK(-1);
			result = -1;
			goto UnmaskAndExit;
		}
#endif /* USB4_COMPILING_GEN_EMU */

		if (0 != Usb4PlatformUcMsgRingGetNumMsgs(usb4_platform_uC_ctx->m_MsgRing, &numOfMsgs))
		{
			USB4_ERROR_STACK(-1);
			result = -1;
			goto UnmaskAndExit;
		}

		if (0 != numOfMsgs)
		{
			if (0 != Usb4PlatformUcMsgRingPrintMsgs(usb4_platform_uC_ctx->m_MsgRing, usb4_platform_uC_ctx->m_coreIdx))
			{
				USB4_ERROR_STACK(-1);
				result = -1;
				goto UnmaskAndExit;
			}
		}

#if defined(USB4_COMPILING_GEN_EMU)
		(void)VVDRV_deo_mutex_unlock(pMutex);
#endif /* USB4_COMPILING_GEN_EMU */
    }
UnmaskAndExit:
    if (0 !=  Usb4PlatformUcMaskIrq(usb4_platform_uC_ctx, FALSE))
    {
        USB4_ERROR_STACK(-1);
    }
Exit:
    return result;
}

int Usb4PlatformUcPopUcMsg(usb4_platform_uC_ctx_t* usb4_platform_uC_ctx, UINT8* buff)
{
    int result = 0;

    result = Usb4PlatformUcMaskIrq(usb4_platform_uC_ctx, TRUE);
    if (0 != result)
    {
        USB4_ERROR_STACK(result);
        return result;
    }

    /* In case of polling mode, need to get results from uC explicitly */
    Usb4PlatformUcHandleUcEvents(usb4_platform_uC_ctx);

    if (0 != Usb4PlatformUcMsgRingPop(usb4_platform_uC_ctx->m_MsgRing, buff))
    {
        (void)Usb4PlatformUcMaskIrq(usb4_platform_uC_ctx, FALSE);
        USB4_ERROR_STACK(-1);
        return -1;
    }

    result = Usb4PlatformUcMaskIrq(usb4_platform_uC_ctx, FALSE);
    if (0 != result)
    {
        USB4_ERROR_STACK(result);
        return result;
    }

    return 0;
}

int Usb4PlatformUcPeekUcMsg(usb4_platform_uC_ctx_t* usb4_platform_uC_ctx, UINT8* buff)
{
    int result = 0;

    result = Usb4PlatformUcMaskIrq(usb4_platform_uC_ctx, TRUE);
    if (0 != result)
    {
        USB4_ERROR_STACK(result);
        return result;
    }

    /* In case of polling mode, need to get results from uC explicitly */
    Usb4PlatformUcHandleUcEvents(usb4_platform_uC_ctx);

    if (0 != Usb4PlatformUcMsgRingPeek(usb4_platform_uC_ctx->m_MsgRing, buff))
    {
        (void)Usb4PlatformUcMaskIrq(usb4_platform_uC_ctx, FALSE);
        USB4_ERROR_STACK(-1);
        return -1;
    }

    result = Usb4PlatformUcMaskIrq(usb4_platform_uC_ctx, FALSE);
    if (0 != result)
    {
        USB4_ERROR_STACK(result);
        return result;
    }

    return 0;
}

/*---------------------------------------------------------------------------*/
int Usb4PlatformUcIoctl(usb4_platform_uC_ctx_t* usb4_platform_uC_ctx, usb4_uc_ioctl_t* pIoctl)
{
    int rc = 0;
    UINT8* UcPer = NULL;

    UcPer = usb4_platform_uC_ctx->m_coreBaseAddress + USB4_UC_PER_REG_BASE_OFFS;
    
    HWIO_OUTX(UcPer, USB4_UC_REGS_SW_TRIGGERS_UC_IRQ, pIoctl->raw);
    
    /* Wait for register to become 0 - means uC started execution */
    USB4_WHILE_WITH_TIMEOUT(0 != HWIO_INX(UcPer, USB4_UC_REGS_SW_TRIGGERS_UC_IRQ), 1000, rc)
    return rc;
}


/*----------------------------------------------------------------------------
* VVHAL_usb4_platform_uC_target_MsgRing Functions implementation
*--------------------------------------------------------------------------*/

int Usb4PlatformUcMsgRingInit(usb4_platform_uC_target_MsgRing_ctx_t* usb4_platform_uC_target_MsgRing_ctx, UINT32 max_entries, UINT32 entrySize_bytes)
{
    Usb4PlatformUcMsgRingDestroy(usb4_platform_uC_target_MsgRing_ctx); // TODO: AC why does the code have a destroy in the init function?  Looks like for zero initialization
    usb4_platform_uC_target_MsgRing_ctx->m_pBuff = NULL;
    usb4_platform_uC_target_MsgRing_ctx->m_size_bytes = 0;
    usb4_platform_uC_target_MsgRing_ctx->m_entrySizeBytes = 0;
    usb4_platform_uC_target_MsgRing_ctx->m_maxEntries = 0;
    usb4_platform_uC_target_MsgRing_ctx->m_printIdx = 0;
    usb4_platform_uC_target_MsgRing_ctx->m_pushIdx = 0;
    usb4_platform_uC_target_MsgRing_ctx->m_numMsgs = 0;

    usb4_platform_uC_target_MsgRing_ctx->m_maxEntries = max_entries;
    usb4_platform_uC_target_MsgRing_ctx->m_entrySizeBytes = entrySize_bytes;

    usb4_platform_uC_target_MsgRing_ctx->m_size_bytes = usb4_platform_uC_target_MsgRing_ctx->m_maxEntries * entrySize_bytes;
    usb4_platform_uC_target_MsgRing_ctx->m_pBuff = (UINT8*)(usb4_mem_alloc(usb4_platform_uC_target_MsgRing_ctx->m_size_bytes, 0x0));
    if (NULL == usb4_platform_uC_target_MsgRing_ctx->m_pBuff)
    {
        USB4_ERROR_STACK(-1);
        return -1;
    }

    return 0;
}

void Usb4PlatformUcMsgRingDestroy(usb4_platform_uC_target_MsgRing_ctx_t* usb4_platform_uC_target_MsgRing_ctx)
{
    if (NULL != usb4_platform_uC_target_MsgRing_ctx->m_pBuff)
    {
        usb4_mem_free(usb4_platform_uC_target_MsgRing_ctx->m_pBuff);
        usb4_platform_uC_target_MsgRing_ctx->m_pBuff = NULL;
    }

    usb4_platform_uC_target_MsgRing_ctx->m_size_bytes = 0;
    usb4_platform_uC_target_MsgRing_ctx->m_entrySizeBytes = 0;
    usb4_platform_uC_target_MsgRing_ctx->m_maxEntries = 0;
    usb4_platform_uC_target_MsgRing_ctx->m_printIdx = 0;
    usb4_platform_uC_target_MsgRing_ctx->m_pushIdx = 0;
    usb4_platform_uC_target_MsgRing_ctx->m_numMsgs = 0;
}

int Usb4PlatformUcMsgRingPush(usb4_platform_uC_target_MsgRing_ctx_t* usb4_platform_uC_target_MsgRing_ctx, UINT8* pMsg)
{
    UINT8* dst;
    // UINT32 i = 0;

    dst = usb4_platform_uC_target_MsgRing_ctx->m_pBuff + usb4_platform_uC_target_MsgRing_ctx->m_pushIdx;
    while (*pMsg != 0)
    {
        *dst = *pMsg;
        ++dst;
        ++pMsg;
    }
    *dst = 0;

    usb4_platform_uC_target_MsgRing_ctx->m_pushIdx = (usb4_platform_uC_target_MsgRing_ctx->m_pushIdx + usb4_platform_uC_target_MsgRing_ctx->m_entrySizeBytes) % usb4_platform_uC_target_MsgRing_ctx->m_size_bytes;
    if (usb4_platform_uC_target_MsgRing_ctx->m_numMsgs < usb4_platform_uC_target_MsgRing_ctx->m_maxEntries)
    {
        usb4_platform_uC_target_MsgRing_ctx->m_numMsgs++;
    }

    return 0;
}

int Usb4PlatformUcMsgRingGetNumMsgs(usb4_platform_uC_target_MsgRing_ctx_t* usb4_platform_uC_target_MsgRing_ctx, UINT32* pNum)
{
    if (NULL == pNum)
    {
        return -1;
    }

    *pNum = usb4_platform_uC_target_MsgRing_ctx->m_numMsgs;
    return 0;
}

int Usb4PlatformUcMsgRingGetEntrySize(usb4_platform_uC_target_MsgRing_ctx_t* usb4_platform_uC_target_MsgRing_ctx, UINT32* pSizeBytes)
{
    if (NULL == pSizeBytes)
    {
        return -1;
    }
    *pSizeBytes = usb4_platform_uC_target_MsgRing_ctx->m_entrySizeBytes;
    return 0;
}

int Usb4PlatformUcMsgRingPrintMsgs(usb4_platform_uC_target_MsgRing_ctx_t* usb4_platform_uC_target_MsgRing_ctx, UINT32 coreIndex)
{
    // IRQ is masked at that point
    UINT32 i;
    UINT32 n;
    // UINT32 offset = 0;

    n = usb4_platform_uC_target_MsgRing_ctx->m_numMsgs;
    for (i = 0; i < usb4_platform_uC_target_MsgRing_ctx->m_numMsgs; ++i)
    {
        Usb4Log2(USB4_LOG_CFG, Usb4PlatformUcMsgRingPrintMsgs__Params__uC_Msg, 0, coreIndex, (UINT32)usb4_platform_uC_target_MsgRing_ctx->m_pBuff + usb4_platform_uC_target_MsgRing_ctx->m_printIdx);
        // USB4_LOG_INFO("uC[%u] %s\n",coreIndex, usb4_platform_uC_target_MsgRing_ctx->m_pBuff + usb4_platform_uC_target_MsgRing_ctx->m_printIdx);
        usb4_platform_uC_target_MsgRing_ctx->m_printIdx = (usb4_platform_uC_target_MsgRing_ctx->m_printIdx + usb4_platform_uC_target_MsgRing_ctx->m_entrySizeBytes) % usb4_platform_uC_target_MsgRing_ctx->m_size_bytes;
    }
    usb4_platform_uC_target_MsgRing_ctx->m_numMsgs -= n;

    return 0;
}

int Usb4PlatformUcMsgRingPop(usb4_platform_uC_target_MsgRing_ctx_t* usb4_platform_uC_target_MsgRing_ctx, UINT8* pMsg)
{
    int result = 0;
    result = Usb4PlatformUcMsgRingPeek(usb4_platform_uC_target_MsgRing_ctx, pMsg);
    if (0 != result)
    {
        USB4_ERROR_STACK(-1);
        return -1;
    }

    usb4_platform_uC_target_MsgRing_ctx->m_printIdx = (usb4_platform_uC_target_MsgRing_ctx->m_printIdx + usb4_platform_uC_target_MsgRing_ctx->m_entrySizeBytes) % usb4_platform_uC_target_MsgRing_ctx->m_size_bytes;
    --usb4_platform_uC_target_MsgRing_ctx->m_numMsgs;

    return 0;
}

int Usb4PlatformUcMsgRingPeek(usb4_platform_uC_target_MsgRing_ctx_t* usb4_platform_uC_target_MsgRing_ctx, UINT8* pMsg)
{
    UINT8* src;
    src = usb4_platform_uC_target_MsgRing_ctx->m_pBuff + usb4_platform_uC_target_MsgRing_ctx->m_printIdx;

    while (*src != 0)
    {
        *pMsg = *src;
        ++pMsg;
        ++src;
    }

    *pMsg = 0;
    return 0;
}
