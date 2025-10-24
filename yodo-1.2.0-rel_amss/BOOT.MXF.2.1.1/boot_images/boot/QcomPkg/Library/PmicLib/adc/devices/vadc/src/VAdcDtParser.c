/*============================================================================
  FILE:         VAdcDtParser.c

  OVERVIEW:     Implementation of a parser for device tree configation node

  DEPENDENCIES: None

                Copyright (c) 2020-2022 Qualcomm Technologies, Inc.
                All Rights Reserved.
                Qualcomm Technologies Proprietary and Confidential.

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/adc/devices/vadc/src/VAdcDtParser.c#1 $
============================================================================*/

#include "DALSys.h"
#include "CoreVerify.h"

#include "libfdt.h"
#include "DTBExtnLib.h"

#include "VAdcBsp.h"
#include <stdio.h>
#include "boot_logger.h"

#define LOG_LINE_BUF_SIZE       40
#define VADC_CHANNEL_NAME_LEN   40

#define DTB_NODE_BUF_SIZE 0x80

#define ERR_MSG_NODE_ITEM(v,x) \
   if (v) { \
            vadc_read_dt_err_helper(x); \
            return v; } 

#define ERR_MSG(x) vadc_read_dt_err_helper(x)

#define STR_CFG_COMPARE(x,y) (x[0] == y[0] && x[1] == y[1] && x[2] == y[2] && x[3] == y[3])

// Hardcode table size for speed
#define MAX_INT_TABLE_IDX     10

#define ERROR_SIZE_OVERFLOW   -100

#define GET_OPTIONAL_PROP(ret_val, lval, rval, noval) \
   if(ret_val) { \
      if (ret_val != -FDT_ERR_NOTFOUND) { \
         return ret_val; \
      } \
      lval = noval; \
   } \
   else { \
      lval = rval; \
   }

// Helper function for error checking
char vadcdt_last_err_msg[LOG_LINE_BUF_SIZE];

static void vadc_read_dt_err_helper(char *msg)
{
   // Save the last error in log buffer
   snprintf(vadcdt_last_err_msg, LOG_LINE_BUF_SIZE, "ADC_ERROR: %s", msg);
   // Only enable the error message print out when debugging
   //LogMsg(vadcdt_last_err_msg); 
   //DEBUG((EFI_D_ERROR,"%s",vadcdt_last_err_msg));
}

AdcIntTableType g_all_int_tables[MAX_INT_TABLE_IDX];        

int vadc_read_dt_channel_cfg(void *fdt_handle, char *node, VAdcChannelConfigType *pChCfg)
{
   int ret_value;
   uint32_t value;
   uint32_t buf[2];
   char dt_buf[5];
   fdt_node_handle hNode;
   DALResult status;
   
   fdt_get_node_handle(&hNode, fdt_handle, node);

   ret_value = fdt_get_uint32_prop(&hNode, "hw-channel", &value);
   ERR_MSG_NODE_ITEM (ret_value, "hw-channel");
   pChCfg->uAdcHardwareChannel = value;

   ret_value = fdt_get_uint32_prop(&hNode, "settling-delay-uS", &value);
   ERR_MSG_NODE_ITEM (ret_value, "settling-delay-uS");
   if (value < 100) {
      pChCfg->eSettlingDelay = VADC_SETTLING_DELAY_0_US;
   }
   else if (value < 200) {
      pChCfg->eSettlingDelay = VADC_SETTLING_DELAY_100_US;
   }
   else if (value < 300) {
      pChCfg->eSettlingDelay = VADC_SETTLING_DELAY_200_US;
   }
   else if (value < 400) {
      pChCfg->eSettlingDelay = VADC_SETTLING_DELAY_300_US;
   }
   else if (value < 500) {
      pChCfg->eSettlingDelay = VADC_SETTLING_DELAY_400_US;
   }
   else if (value < 600) {
      pChCfg->eSettlingDelay = VADC_SETTLING_DELAY_500_US;
   }
   else if (value < 700) {
      pChCfg->eSettlingDelay = VADC_SETTLING_DELAY_600_US;
   }
   else if (value < 800) {
      pChCfg->eSettlingDelay = VADC_SETTLING_DELAY_700_US;
   }
   else if (value < 900) {
      pChCfg->eSettlingDelay = VADC_SETTLING_DELAY_800_US;
   }
   else if (value < 1000) {
      pChCfg->eSettlingDelay = VADC_SETTLING_DELAY_900_US;
   }
   else if (value < 2000) {
      pChCfg->eSettlingDelay = VADC_SETTLING_DELAY_1_MS;
   }
   else if (value < 4000) {
      pChCfg->eSettlingDelay = VADC_SETTLING_DELAY_2_MS;
   }
   else if (value < 6000) {
      pChCfg->eSettlingDelay = VADC_SETTLING_DELAY_4_MS;
   }
   else if (value < 8000) {
      pChCfg->eSettlingDelay = VADC_SETTLING_DELAY_6_MS;
   }
   else if (value < 10000) {
      pChCfg->eSettlingDelay = VADC_SETTLING_DELAY_8_MS;
   }
   else if (value < 1600) {
      pChCfg->eSettlingDelay = VADC_SETTLING_DELAY_10_MS;
   }
   else if (value < 3200) {
      pChCfg->eSettlingDelay = VADC_SETTLING_DELAY_16_MS;
   }
   else if (value < 6400) {
      pChCfg->eSettlingDelay = VADC_SETTLING_DELAY_32_MS;
   }
   else if (value < 12800) {
      pChCfg->eSettlingDelay = VADC_SETTLING_DELAY_64_MS;
   }
   else {
      pChCfg->eSettlingDelay = VADC_SETTLING_DELAY_128_MS;
   }

   ret_value = fdt_get_uint32_prop(&hNode, "average-sample", &value);
   ERR_MSG_NODE_ITEM (ret_value, "average-sample");
   switch (value) {
      case 1:
         pChCfg->eAverageMode = VADC_AVERAGE_1_SAMPLE;
         break;
      case 2:
         pChCfg->eAverageMode = VADC_AVERAGE_2_SAMPLES;
         break;
      case 4:
         pChCfg->eAverageMode = VADC_AVERAGE_4_SAMPLES;
         break;
      case 8:
         pChCfg->eAverageMode = VADC_AVERAGE_8_SAMPLES;
         break;
      case 16:
         pChCfg->eAverageMode = VADC_AVERAGE_16_SAMPLES;
         break;
      default:
         pChCfg->eAverageMode = VADC_AVERAGE_1_SAMPLE;
         break;
   }

   ret_value = fdt_get_uint32_prop(&hNode, "decimation-ratio", &value);
   ERR_MSG_NODE_ITEM (ret_value, "decimation-ratio");
   if (value < 512) {
      pChCfg->eDecimationRatio = VADC_DECIMATION_RATIO_256;
   }
   else if (value < 1024) {
      pChCfg->eDecimationRatio = VADC_DECIMATION_RATIO_512;
   }
   else {
      pChCfg->eDecimationRatio = VADC_DECIMATION_RATIO_1024;
   }

   ret_value = fdt_get_string_prop_list(&hNode, "cal-method", dt_buf, sizeof(dt_buf));
   ERR_MSG_NODE_ITEM (ret_value, "cal-method");
   // abs or raio
   {
      const char abs_str[] = "abs ";
      const char raio_str[] = "raio";
      if (STR_CFG_COMPARE(abs_str, dt_buf)) {
         pChCfg->eCalMethod = VADC_CAL_METHOD_ABSOLUTE;
      } 
      else if (STR_CFG_COMPARE(raio_str, dt_buf)) {
         pChCfg->eCalMethod = VADC_CAL_METHOD_RATIOMETRIC;
      } 
      else {
         pChCfg->eCalMethod = VADC_CAL_METHOD_NO_CAL;
      }
   }

   ret_value = fdt_get_uint32_prop_list(&hNode, "scaling-factor", buf, 2 * sizeof (uint32_t));
   ERR_MSG_NODE_ITEM (ret_value, "scaling-factor");
   pChCfg->scalingFactor.uNumerator = buf[0];
   pChCfg->scalingFactor.uDenominator = buf[1];

   ret_value = fdt_get_string_prop_list(&hNode, "scaling-method", dt_buf, sizeof(dt_buf));
   ERR_MSG_NODE_ITEM (ret_value, "scaling-method");
   {
      const char xtuV_str[] = "xtuV";
      const char xtmV_str[] = "xtmV";
      const char xtr_str[] = "xtr ";
      const char res_str[] = "res ";
      if (STR_CFG_COMPARE(xtmV_str, dt_buf)) {
         pChCfg->eScalingMethod = VADC_SCALE_INTERPOLATE_FROM_MILLIVOLTS;
      } 
      else if (STR_CFG_COMPARE(xtr_str, dt_buf)) {
         pChCfg->eScalingMethod = VADC_SCALE_THERMISTOR;
      } 
      else if (STR_CFG_COMPARE(res_str, dt_buf)) {
         pChCfg->eScalingMethod = VADC_SCALE_RESISTOR_DIVIDER;
      } 
      else if (STR_CFG_COMPARE(xtuV_str, dt_buf)) {
         pChCfg->eScalingMethod = VADC_SCALE_INTERPOLATE_FROM_MICROVOLTS;
      } 
      else {
         pChCfg->eScalingMethod = VADC_SCALE_TO_MILLIVOLTS;
      }
   }

   ret_value = fdt_get_uint32_prop(&hNode, "offset-factor", &value);
   ERR_MSG_NODE_ITEM (ret_value, "offset-factor");
   pChCfg->nOffset = (int32)value;

   ret_value = fdt_get_uint32_prop(&hNode, "pull-up-res", &value);
   ERR_MSG_NODE_ITEM (ret_value, "pull-up-res");
   pChCfg->uPullUp = value;

   ret_value = fdt_get_uint32_prop(&hNode, "adc-sid", &value);
   ERR_MSG_NODE_ITEM (ret_value, "adc-sid");
   pChCfg->uSlaveId = value;

   // Read the translation table
   {
      uint32_t size;

      pChCfg->pIntTable = NULL;

      ret_value = fdt_get_prop_size(&hNode, "int-table", &size);
      if(size != 0 && ret_value == 0) {
         char *ptr;
         fdt_node_handle hlocal;

         status = DALSYS_Malloc(size, (VOID**)&ptr);
         CORE_VERIFY(status==DAL_SUCCESS);

         ret_value = fdt_get_string_prop_list(&hNode, "int-table", ptr, size);
         ERR_MSG_NODE_ITEM (ret_value, "int-table (prop-list)");

         // Read in the REG value and use it for reference
         fdt_get_node_handle(&hlocal, fdt_handle, ptr);

         ret_value = fdt_get_uint32_prop(&hlocal, "reg", &value);
         ERR_MSG_NODE_ITEM (ret_value, "int-table (reg)");

         pChCfg->pIntTable = &g_all_int_tables[value];
         status = DALSYS_Free(ptr);
         CORE_VERIFY(status==DAL_SUCCESS);
      }
   }

   return ret_value;
}

int vadc_read_dt_int_table(void *fdt_handle, char *node)
{
   uint32_t size;
   void *ptr = NULL;
   uint32_t *walk;
   uint32_t i, j;
   uint32_t idx;
   AdcMapPtInt32toInt32Type *ptb;
   fdt_node_handle hNode;
   int ret_value;
   DALResult status;

   fdt_get_node_handle(&hNode, fdt_handle, node);

   ret_value = fdt_get_uint32_prop(&hNode, "reg", &idx);
   ERR_MSG_NODE_ITEM (ret_value, "int-table (reg)");

   if (idx >= MAX_INT_TABLE_IDX) {
      ERR_MSG("Translation table index out of range");
      return -1;
   }

   ret_value = fdt_get_prop_size(&hNode, "table", &size);
   ERR_MSG_NODE_ITEM (ret_value, "int-table (table)");

   status = DALSYS_Malloc(size, (VOID**)&ptr);
   CORE_VERIFY(status==DAL_SUCCESS);

   ret_value = fdt_get_uint32_prop_list(&hNode, "table", ptr, size);
   if (ret_value) {
      ERR_MSG("Err get table prop list");
      return ret_value;
   }
   
   size /= 8;        // Each entry is 2 DWORDS

   status = DALSYS_Malloc((sizeof (AdcMapPtInt32toInt32Type) * size), (VOID**)&ptb);
   CORE_VERIFY(status==DAL_SUCCESS);

   walk = (uint32_t *)ptr;
   i = 0, j = 0;
   while (i < size) {
      ptb[i].x = walk[j++]; 
      ptb[i].y = walk[j++];
      i++;
   }

   // Save the parsed table
   g_all_int_tables[idx].pTable = ptb;
   g_all_int_tables[idx].uLength = size;

   status = DALSYS_Free(ptr);
   CORE_VERIFY(status==DAL_SUCCESS);
   return 0;
}

int vadc_read_gpio_table(void *fdt_handle, char *node, VAdcGpioChannelMappingType *pGpioMap)
{
   fdt_node_handle hNode;
   int ret_value;

   fdt_get_node_handle(&hNode, fdt_handle, node);

   /* Remove the use of Channel listing migration to SID based GPIO config */
   pGpioMap->uNumChannels = 0;

   ret_value = fdt_get_uint32_prop(&hNode, "gpio-num", &pGpioMap->eGpio);
   ERR_MSG_NODE_ITEM (ret_value, "gpio (eGpio)");

   ret_value = fdt_get_uint32_prop(&hNode, "pmic-sid", &pGpioMap->uPmicId);
   ERR_MSG_NODE_ITEM (ret_value, "gpio (psid)");

   return 0;
}

int vadc_read_dt_device_root(const char *node, VAdcBspType *pBsp)
{
   int ret_value;
   uint32_t value;
   fdt_node_handle hNode;
   DALResult status;
   char node_buf[DTB_NODE_BUF_SIZE];
   void *fdt_handle = NULL;

   strlcpy(node_buf, node, DTB_NODE_BUF_SIZE);
   fdt_get_node_handle(&hNode, fdt_handle, node_buf);

   ret_value = fdt_get_boolean_prop(&hNode, "use-interrupt", &value);
   ERR_MSG_NODE_ITEM (ret_value, "use-interrupt");
   pBsp->bUsesInterrupts = value;

   ret_value = fdt_get_uint32_prop(&hNode, "fullscale-code", &value);
   ERR_MSG_NODE_ITEM (ret_value, "fullscale-code");
   pBsp->uFullScale_code = value;

   ret_value = fdt_get_uint32_prop(&hNode, "fullscale-uV", &value);
   ERR_MSG_NODE_ITEM (ret_value, "fullscale-uV");
   pBsp->uFullScale_uV = value;

   ret_value = fdt_get_uint32_prop(&hNode, "fullratiometric-code", &value);
   ERR_MSG_NODE_ITEM (ret_value, "fullratiometric-code");
   pBsp->uFullRatiometric_code = value;

   ret_value = fdt_get_uint32_prop(&hNode, "read-timeout-uS", &value);
   ERR_MSG_NODE_ITEM (ret_value, "read-timeout-uS");
   pBsp->uReadTimeout_us = value;

   ret_value = fdt_get_uint32_prop(&hNode, "ldo-settling-uS", &value);
   ERR_MSG_NODE_ITEM (ret_value, "ldo-settling-uS");
   pBsp->uLDOSettlingTime_us = value;

   ret_value = fdt_get_uint32_prop(&hNode, "slave-id", &value);
   ERR_MSG_NODE_ITEM (ret_value, "slave-id");
   pBsp->uSlaveId = value;

   ret_value = fdt_get_uint32_prop(&hNode, "peripheral-id", &value);
   ERR_MSG_NODE_ITEM (ret_value, "peripheral-id");
   pBsp->uPeripheralId = value;

   ret_value = fdt_get_uint32_prop(&hNode, "master-id", &value);
   ERR_MSG_NODE_ITEM (ret_value, "master-id");
   pBsp->uMasterID = value;

   ret_value = fdt_get_uint32_prop(&hNode, "pmic-device", &value);
   ERR_MSG_NODE_ITEM (ret_value, "pmic-device");
   pBsp->ucPmicDevice = value;

   ret_value = fdt_get_uint32_prop(&hNode, "bus-id", &value);
   /* Make this optional in future */
   ERR_MSG_NODE_ITEM (ret_value, "bus-id");
   pBsp->uBusId = value;

   // Get the GPIO mapping table
   {
      int ret_value, i;
      uint32_t count, size;
      uint32_t *ptr=NULL;
      char *walk;
      VAdcGpioChannelMappingType *pGpioMap;
      char node_gpio[DTB_NODE_BUF_SIZE];

      snprintf(node_gpio, DTB_NODE_BUF_SIZE, "%s/gpio-map", node);
      fdt_get_node_handle(&hNode, fdt_handle, node_gpio);

      ret_value = fdt_get_count_of_subnodes(&hNode, &count);
      ERR_MSG_NODE_ITEM (ret_value, "get_count_subnode");

      if (count > 40) {
         return ERROR_SIZE_OVERFLOW;
      }

      if (count == 0) {
         pBsp->paGpioChannelMappings = NULL;
         pBsp->uNumGpioChannelMappings = 0;
      }
      else {
         status = DALSYS_Malloc(count * sizeof(uint32_t), (VOID**)&ptr);
         CORE_VERIFY(status==DAL_SUCCESS);

         status = DALSYS_Malloc(count * sizeof (VAdcGpioChannelMappingType), (VOID**)&pGpioMap);
         CORE_VERIFY(status==DAL_SUCCESS);

         pBsp->paGpioChannelMappings = pGpioMap;
         pBsp->uNumGpioChannelMappings = count;

         ret_value = fdt_get_size_of_subnode_names(&hNode, ptr, count);
         if (ret_value) {
            status = DALSYS_Free(ptr);
            CORE_VERIFY(status==DAL_SUCCESS);
            ERR_MSG_NODE_ITEM (ret_value, "get_size_subnode_name");
         }

         for (i=0,size=0; i<count; i++)
            size += ptr[i];

         status = DALSYS_Free(ptr);
         CORE_VERIFY(status==DAL_SUCCESS);

         status = DALSYS_Malloc(size, (VOID**)&ptr);
         CORE_VERIFY(status==DAL_SUCCESS);
         walk = (char *)ptr;

         ret_value = fdt_get_subnode_names(&hNode, ptr, size);
         if (ret_value) {
            status = DALSYS_Free(ptr);
            CORE_VERIFY(status==DAL_SUCCESS);
            ERR_MSG_NODE_ITEM (ret_value, "get_subnode_name");
         }
         
         for (i=0; i<count; i++) {
            // Read the channel configuration subnode
            snprintf(node_buf, DTB_NODE_BUF_SIZE, "%s/%s", node_gpio, walk);
            vadc_read_gpio_table(fdt_handle, node_buf, &pBsp->paGpioChannelMappings[i]);
            
            // Next node
            walk += strlen(walk) + 1;
         }

         if (ptr) {
            status = DALSYS_Free(ptr);
            CORE_VERIFY(status==DAL_SUCCESS);
         }
      }
   }

   // Get the int-table
   {
      int ret_value, i;
      uint32_t count, size;
      uint32_t *ptr=NULL;
      char *walk;
      char node_therm[DTB_NODE_BUF_SIZE];

      snprintf(node_therm, DTB_NODE_BUF_SIZE, "%s/therm_table", node);
      fdt_get_node_handle(&hNode, fdt_handle, node_therm);

      ret_value = fdt_get_count_of_subnodes(&hNode, &count);
      ERR_MSG_NODE_ITEM (ret_value, "get_count_subnode");

      if (count > 10) {
         return ERROR_SIZE_OVERFLOW;
      }

      status = DALSYS_Malloc(count * sizeof(uint32_t), (VOID**)&ptr);
      CORE_VERIFY(status==DAL_SUCCESS);

      ret_value = fdt_get_size_of_subnode_names(&hNode, ptr, count);
      if (ret_value) {
         status = DALSYS_Free(ptr);
         CORE_VERIFY(status==DAL_SUCCESS);
         ERR_MSG_NODE_ITEM (ret_value, "get_size_subnode_name");
      }

      for (i=0,size=0; i<count; i++)
         size += ptr[i];

      status = DALSYS_Free(ptr);
      CORE_VERIFY(status==DAL_SUCCESS);

      status = DALSYS_Malloc(size, (VOID**)&ptr);
      CORE_VERIFY(status==DAL_SUCCESS);
      walk = (char *)ptr;

      ret_value = fdt_get_subnode_names(&hNode, ptr, size);
      if (ret_value) {
         status = DALSYS_Free(ptr);
         CORE_VERIFY(status==DAL_SUCCESS);
         ERR_MSG_NODE_ITEM (ret_value, "get_subnode_name");
      }
      
      for (i=0; i<count; i++) {
         // Read the channel configuration subnode
         snprintf(node_buf, DTB_NODE_BUF_SIZE, "%s/%s", node_therm, walk);
         vadc_read_dt_int_table(fdt_handle, node_buf);
         
         // Next node
         walk += strlen(walk) + 1;
      }

      if (ptr) { 
         status = DALSYS_Free(ptr);
         CORE_VERIFY(status==DAL_SUCCESS);
      }
   }

   // Get the channel config table
   {
      int ret_value, i;
      uint32_t count, size;
      uint32_t *ptr=NULL;
      char *walk;
      VAdcChannelConfigType *pChCfg;
      char node_ch_cfg[DTB_NODE_BUF_SIZE];

      snprintf(node_ch_cfg, DTB_NODE_BUF_SIZE, "%s/vadc_ch_cfg", node);
      fdt_get_node_handle(&hNode, fdt_handle, node_ch_cfg);

      ret_value = fdt_get_count_of_subnodes(&hNode, &count);
      ERR_MSG_NODE_ITEM (ret_value, "get_count_subnode");

      if (count > 100) {
         return ERROR_SIZE_OVERFLOW;
      }

      status = DALSYS_Malloc(count * sizeof(uint32_t), (VOID**)&ptr);
      CORE_VERIFY(status==DAL_SUCCESS);

      status = DALSYS_Malloc(count * sizeof (VAdcChannelConfigType), (VOID**)&pChCfg);
      CORE_VERIFY(status==DAL_SUCCESS);

      status = DALSYS_Malloc(sizeof(uint32_t), (VOID**)&pBsp->puNumChannels);
      CORE_VERIFY(status==DAL_SUCCESS);

      pBsp->paChannels = pChCfg;
      *(pBsp->puNumChannels) = count;

      ret_value = fdt_get_size_of_subnode_names(&hNode, ptr, count);
      if (ret_value) {
         status = DALSYS_Free(ptr);
         CORE_VERIFY(status==DAL_SUCCESS);
         ERR_MSG_NODE_ITEM (ret_value, "get_size_subnode_name");
      }

      for (i=0,size=0; i<count; i++)
         size += ptr[i];

      if (ptr) { 
         status = DALSYS_Free(ptr);
         CORE_VERIFY(status==DAL_SUCCESS);
      }

      status = DALSYS_Malloc(size, (VOID**)&ptr);
      CORE_VERIFY(status==DAL_SUCCESS);
      walk = (char *)ptr;

      // Reuse the subnote name buffer in pChCfg data structure
      // to reduce allocation buffer requirement
      ret_value = fdt_get_subnode_names(&hNode, ptr, size);
      if (ret_value) {
         status = DALSYS_Free(ptr);
         CORE_VERIFY(status==DAL_SUCCESS);
         ERR_MSG_NODE_ITEM (ret_value, "get_subnode_name");
      }
      
      for (i=0; i<count; i++) {
         int walk_len = strlen(walk) + 1;
         // Read the channel configuration subnode
         
         status = DALSYS_Malloc(walk_len, (VOID**)&pChCfg[i].pszName);
         CORE_VERIFY(status==DAL_SUCCESS);
         
         strlcpy(pChCfg[i].pszName, walk, walk_len);

         snprintf(node_buf, DTB_NODE_BUF_SIZE, "%s/%s", node_ch_cfg, walk);
         vadc_read_dt_channel_cfg(fdt_handle, node_buf, &pChCfg[i]);
         
         // Next node
         walk += walk_len;
      }

      if (ptr) { 
         status = DALSYS_Free(ptr);
         CORE_VERIFY(status==DAL_SUCCESS);
      }
   }

   return 0;
}
