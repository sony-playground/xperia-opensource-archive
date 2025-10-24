/**********************************************************************
 * spinor_sfdp.c
 *
 * Serial Flash Discoverable Parameters
 *
 * Copyright (c) 2020,2022 Qualcomm Technologies Inc.
 * All Rights Reserved.
 * Qualcomm Confidential and Proprietary
 *
 **********************************************************************/
/*======================================================================

                        EDIT HISTORY FOR MODULE

when        who  what, where, why
----------  ---  -------------------------------------------------------
2022-04-13  sc   Remove unused variable.
2022-02-01  sa   Removed unused code.
2020-07-23  wek  Use the same error codes on all SPI-NOR dirver files.
2020-04-08  wek  Create.

======================================================================*/
#include <string.h>
#include "spinor_core.h"
#include "spinor_utils.h"
#include "spinor_init_config.h"
#include "spinor_sfdp.h"
#include "spinor_spial.h"

#define MAX_3BYTE_ADDRESS      0x00FFFFFF
#define READ_SDR_4B_111_INST   0x13
#define READ_SDR_4B_111_INST_F 0x0C
#define READ_SDR_4B_114_INST   0x6C
#define READ_SDR_4B_144_INST   0xEC
#define PROG_SDR_4B_111_INST   0x12
#define PROG_SDR_4B_114_INST   0x34
#define PROG_SDR_4B_144_INST   0x3E

#define READ_DDR_4B_111_INST   0x0E
#define READ_DDR_4B_122_INST   0xBE
#define READ_DDR_4B_122_INST_F 0xBC
#define READ_DDR_4B_144_INST   0xEE

#define SFDP_HEADER_SIGNATURE 0x50444653
#define SFDP_HEADER_MAJOR_REV    1
#define SFDP_HEADER_MINOR_REV_A  5 /* JESD216A = 5*/

#define SFDP_BASIC_PARAM_MAJOR_REV    1
#define SFDP_BASIC_PARAM_MINOR_REV    5 /* JESD216A = 5, JESD216B = 6*/
#define SFDP_BASIC_PARAM_LSB  0x00
#define SFDP_BASIC_PARAM_MSB  0xFF
#define SFDP_4BYTE_INST_LSB  0x84
#define SFDP_4BYTE_INST_MSB  0xFF

#define MANUFACTURER_ID_MACRONIX  0xC2
#define MANUFACTURER_ID_MICRON    0x20
#define MANUFACTURER_ID_SPANSION  0x01
#define MANUFACTURER_ID_WINBOND   0xEF


struct spinor_sfdp_header
{
  uint32 signature; /* SFDP or 0x50444653 */
  uint8  minor_rev;
  uint8  major_rev;
  uint8  num_param_headers;
  uint8  access_protocol;

} __attribute__((__packed__));

/* SFDP Parameter Header */
struct spinor_sfdp_param_header
{
  uint8  param_id_lsb;
  uint8  minor_rev;
  uint8  major_rev;
  uint8  table_length;
  uint32 table_pointer:24;
  uint32 param_id_msb:8;
} __attribute__((__packed__));

/* SFDP Basic Parameters */
struct spinor_sfdp_basic_param
{
  /* DWORD 1 */
  uint32 blk_erase_size:2; /* Block/Sector Erase Sizes */
  uint32 write_granularity:1;
  uint32 volatile_block_protect:1; /* Volatile Status Register Block Protect bits */
  uint32 write_enable_instruction:1; /* Write Enable Instruction Select for Writing to Volatile Status Register */
  uint32 reserved1_1:3;
  uint32 erase_instr_4k:8; /* 4 Kilobyte Erase Instruction */
  uint32 read_112_support:1; /* Supports (1-1-2) Fast Read */
  uint32 address_bytes_sup:2; /*Address bytes mode, 3 byte or 4 byte */
  uint32 dtr_support:1;
  uint32 read_122_support:1; /* Supports (1-2-2) Fast Read */
  uint32 read_144_support:1; /* Supports (1-4-4) Fast Read */
  uint32 read_114_support:1; /* Supports (1-1-4) Fast Read */
  uint32 reserved1_2:9;
  /* DWORD 2 */
  uint32 density; /* Density in bits. */
  /* DWORD 3 */
  uint32 read_144_dummy_cycles:5;
  uint32 read_144_mode_clocks:3;
  uint32 read_144_instruction:8;
  uint32 read_114_dummy_cycles:5;
  uint32 read_114_mode_clocks:3;
  uint32 read_114_instruction:8;
  /* DWORD 4 */
  uint32 read_112_dummy_cycles:5;
  uint32 read_112_mode_clocks:3;
  uint32 read_112_instruction:8;
  uint32 read_122_dummy_cycles:5;
  uint32 read_122_mode_clocks:3;
  uint32 read_122_instruction:8;
  /* DWORD 5 */
  uint32 read_222_support:1;
  uint32 reserved5_1:3;
  uint32 read_444_support:1;
  uint32 reserved5_2:27;
  /* DWORD 6 */
  uint32 reserved6_1:16;
  uint32 read_222_dummy_cycles:5;
  uint32 read_222_mode_clocks:3;
  uint32 read_222_instruction:8;
  /* DWORD 7 */
  uint32 reserved7_1:16;
  uint32 read_444_dummy_cycles:5;
  uint32 read_444_mode_clocks:3;
  uint32 read_444_instruction:8;
  /* DWORD 8 */
  uint32 erase_type1_size:8; /* Size in bytes, this field specifies N for size as 2^N */
  uint32 erase_type1_inst:8;
  uint32 erase_type2_size:8;
  uint32 erase_type2_inst:8;
  /* DWORD 9 */
  uint32 erase_type3_size:8;
  uint32 erase_type3_inst:8;
  uint32 erase_type4_size:8;
  uint32 erase_type4_inst:8;
  /* DWORD 10 */
  uint32 erase_time_multiplier:4;
  uint32 erase_type1_time:7;
  uint32 erase_type2_time:7;
  uint32 erase_type3_time:7;
  uint32 erase_type4_time:7;
  /* DWORD 11 */
  uint32 program_multiplier:4; /* Multiplier from typical time to max time for Page or byte program */
  uint32 page_size:4;
  uint32 page_prog_time:6; /* Page Program Typical time */
  uint32 byte_prog_time_first:5; /* Byte Program Typical time, first byte */
  uint32 byte_prog_time_additional:5; /* Byte Program Typical time, additional byte */
  uint32 erase_time:7; /* Chip Erase, Typical time */
  uint32 reserved11_1:1;
  /* DWORD 12 */
  uint32 prohibit_op_prog:4; /* Prohibited Operations During Program Suspend */
  uint32 prohibit_op_erase:4; /* Prohibited Operations During Erase Suspend */
  uint32 reserved12_1:1;
  uint32 prog_resume_suspend_interval:4; /* Program Resume to Suspend Interval */
  uint32 suspend_prog_lat_count:5; /* Suspend in-progress program max latency count */
  uint32 suspend_prog_lat_units:2; /* Suspend in-progress program max latency unit */
  uint32 erase_res2susp_interval:4; /* Erase Resume to Suspend Interval */
  uint32 suspend_erase_lat_count:5; /* Suspend in-progress erase max latency count */
  uint32 suspend_erase_lat_units:2; /* Suspend in-progress erase max latency count */
  uint32 susp_res_suppport:1; /* Suspend / Resume supported */
  /* DWORD 13 */
  uint32 prog_resume_inst:8; /* Program Resume Instruction */
  uint32 prog_suspend_inst:8; /* Program Suspend Instruction */
  uint32 resume_inst:8; /* Resume Instruction */
  uint32 suspend_inst:8; /* Suspend Instruction */
  /* DWORD 14 */
  uint32 reserved14_1:2;
  uint32 status_polling:6; /* Status Register Polling Device Busy */
  uint32 exit_pwr_delay_count:5; /* Exit Deep Powerdown to next operation delay count */
  uint32 exit_pwr_delay_units:2; /* Exit Deep Powerdown to next operation delay unit */
  uint32 exit_pwr_inst:8; /* Exit Deep Powerdown Instruction */
  uint32 enter_pwr_inst:8; /* Enter Deep Powerdown Instruction */
  uint32 deep_pwr_support:1; /* Deep Powerdown Supported */
  /* DWORD 15 */
  uint32 disable_444_seq:4; /* 4-4-4 mode disable sequences */
  uint32 enable_444_seq:5; /* 4-4-4 mode enable sequences */
  uint32 support_044:1; /* 0-4-4 mode supported */
  uint32 exit_044_method:6; /* 0-4-4 Mode Exit Method */
  uint32 entry_044_method:4; /* 0-4-4 Mode Entry Method */
  uint32 quad_en_r:3; /* Quad Enable Requirements (QER) */
  uint32 reset_disable:1; /* HOLD or RESET Disable */
  uint32 reserved15_1:8;
  /* DWORD 16 */
  uint32 volatile_register_1:7; /* Volatile or Non-Volatile Register and Write Enable Instruction for Status Register 1 */
  uint32 reserved16_1:1;
  uint32 srr_seq_sup:6; /* Soft Reset and Rescue Sequence Support */
  uint32 exit_4b_addr:10; /* Exit 4-Byte Addressing */
  uint32 enter_4b_addr:8; /* Enter 4-Byte Addressing */
  /* DWORD 17 */
  uint32 read_188_dummy_cycles:5; /* (1-8-8) Fast Read Number of Wait states (dummy clocks) needed before valid output */
  uint32 read_188_mode_clocks:3; /* (1-8-8) Fast Read Number of Mode Clocks */
  uint32 read_188_instruction:8; /* (1-8-8) Fast Read Instruction */
  uint32 read_118_dummy_cycles:5; /* (1-1-8) Fast Read Number of Wait states (dummy clocks) needed before valid output */
  uint32 read_118_mode_clocks:3; /* (1-1-8) Fast Read Number of Mode Clocks */
  uint32 read_118_instruction:8; /* (1-1-8) Fast Read Instruction */
  /* DWORD 18 */
  uint32 reserved18_1:18;
  uint32 var_output_strength:5; /* Variable Output Driver Strength */
  uint32 spi_reset:1; /* JEDEC SPI Protocol Reset(In-Band Reset) */
  uint32 dsw_str_mode:2; /* Data StrobeWaveforms in STR Mode */
  uint32 ds_sup_str_mode:1; /* Data Strobe support for QPI STR mode (4S-4S-4S) */
  uint32 ds_sup_dtr_mode:1; /* Data Strobe support for QPI DTR mode (4S-4D-4D) */
  uint32 reserved18_2:1;
  uint32 octal_dtr_ext:2; /* Octal DTR (8D-8D-8D) Command and Command Extension */
  uint32 byte_order_888_mode:1; /* Byte Orderin 8D-8D-8Dmode */
  /* DWORD 19 */
  uint32 dis_888_seq:4; /* 8s-8s-8smode disable sequences */
  uint32 en_888_seq:5; /* 8s-8s-8smode enable sequences */
  uint32 sup_088:1; /* 0-8-8 mode supported */
  uint32 exit_088_method:6; /* 0-8-8Mode Exit Method */
  uint32 entry_088_method:4; /* 0-8-8Mode Entry Method */
  uint32 octal_en_req:3; /* OctalEnable Requirements */
  uint32 reserved19_1:9;
  /* DWORD 20 */
  uint32 mhz_444s_ndt:4; /*Maximum operation speed of device in 4S-4S-4S mode when not utilizing Data Strobe */
  uint32 mhz_444s_dt:4; /* Maximum operation speed of device in 4S-4S-4S mode when utilizing Data Strobe */
  uint32 mhz_444d_ndt:4; /*Maximum operation speed of device in 4S-4D-4D mode when not utilizing Data Strobe */
  uint32 mhz_444d_dt:4; /* Maximum operation speed of device in 4S-4D-4D mode when utilizing Data Strobe */
  uint32 mhz_888s_ndt:4; /*Maximum operation speed of device in 8S-8S-8S mode when not utilizing Data Strobe */
  uint32 mhz_888s_dt:4; /* Maximum operation speed of device in 8S-8S-8S mode when utilizing Data Strobe */
  uint32 mhz_888d_ndt:4; /*Maximum operation speed of device in 8S-8D-8D mode when not utilizing Data Strobe */
  uint32 mhz_888d_dt:4; /* Maximum operation speed of device in 8S-8D-8D mode when utilizing Data Strobe */
} __attribute__((__packed__));

/* 4-byte Address Instruction Table */
struct spinor_sfdp_4byte_inst
{
  /* DWORD 1 */
  uint32 read_111_support:1; /* Support for (1-1-1) READ Command, Instruction=13h */
  uint32 fread_111_support:1;/* Support for (1-1-1) FAST_READ Command, Instruction=0Ch */
  uint32 read_112_support:1; /* Support for (1-1-2) FAST_READ Command, Instruction=3Ch */
  uint32 read_122_support:1; /* Support for (1-2-2) FAST_READ Command, Instruction=BCh */
  uint32 read_114_support:1; /* Support for (1-1-4) FAST_READ Command, Instruction=6Ch */
  uint32 read_144_support:1; /* Support for (1-4-4) FAST_READ Command, Instruction=ECh */
  uint32 prog_111_support:1; /* Support for (1-1-1) Page Program Command, Instruction=12h */
  uint32 prog_114_support:1; /* Support for (1-1-4) Page Program Command, Instruction=34h */
  uint32 prog_144_support:1; /* Support for (1-4-4) Page Program Command, Instruction=3Eh */
  uint32 erase_1_support:1; /* Support for Erase Command –Type 1 size, Instruction lookup in next Dword */
  uint32 erase_2_support:1; /* Support for Erase Command –Type 2 size, Instruction lookup in next Dword */
  uint32 erase_3_support:1; /* Support for Erase Command –Type 3 size, Instruction lookup in next Dword */
  uint32 erase_4_support:1; /* Support for Erase Command –Type 4 size, Instruction lookup in next Dword */
  uint32 read_ddr_111_support:1; /* Support for (1-1-1) DTR_Read Command, Instruction=0Eh */
  uint32 read_ddr_122_support:1; /* Support for (1-2-2) DTR_Read Command, Instruction=BEh */
  uint32 read_ddr_144_support:1; /* Support for (1-4-4) DTR_Read Command, Instruction=EEh */
  uint32 vol_read_lock_support:1; /* Support for volatile individual sector lock Read command, Instruction=E0h */
  uint32 vol_write_lock_support:1; /* Support for volatile individual sector lock Write command, Instruction=E1h */
  uint32 nvol_read_lock_support:1;/*Support for non-volatile individual sector lock read command, Instruction=E2h*/
  uint32 nvol_write_lock_support:1; /* Support for non-volatile individual sector lock write command, Instruction=E3h */
  uint32 read_118_support:1;     /* Support for (1-1-8) FAST_READ Command, Instruction=7Ch */
  uint32 read_188_support:1;     /* Support for (1-8-8) FAST_READ Command, Instruction=CCh */
  uint32 read_ddr_188_support:1; /* Support for (1-8-8) DTR_Read Command, Instruction=FDh */
  uint32 prog_118_support:1;      /* Support for (1-1-8) Page Program Command, Instruction=84h */
  uint32 prog_188_support:1;      /* Support for (1-8-8) Page Program Command, Instruction=8Eh */
  uint32 reserved1:7;
  /* DWORD 2, erase command, same as basic flash parameter table DWORD 8 and 9 */
  uint32 erase_1_inst:8; /* Instruction for Erase Type 1 , typical 0x21 */
  uint32 erase_2_inst:8; /* Instruction for Erase Type 2 , typical 0x5C */
  uint32 erase_3_inst:8; /* Instruction for Erase Type 3 , typical 0xDC */
  uint32 erase_4_inst:8; /* Instruction for Erase Type 4 , typical 0xDC */
} __attribute__((__packed__));


/**********************************************************
 * Read the Parameters using SFDP
 *
 * @param device_id [IN/OUT]
 *   spinor Device ID
 *
 * @param device_id_len [IN]
 *   Number of bytes to read
 *
 * @return int [OUT]
 *   Result of the operation.
 *
 **********************************************************/
SPINOR_STATUS spinor_read_sfdp(spinor_config_data *config, uint8 manufacturer)
{
  struct spinor_sfdp_header header_data;
  struct spinor_sfdp_param_header paramh_data;
  struct spinor_sfdp_basic_param bparam_data;
  struct spinor_sfdp_4byte_inst inst4b_data;
  spinor_drv_info *spinord = &spinor_dev;
  struct spinor_sfdp_header *header;
  struct spinor_sfdp_param_header *paramh;
  struct spinor_sfdp_basic_param *bparam;
  struct spinor_sfdp_4byte_inst *inst4b;
  uint32 offset, count;
  uint32 page_size;
  SPINOR_STATUS status;
  SPINOR_STATUS ret_status = SPINOR_DEVICE_FAIL;
  spinor_config_data *config_data;
  uint32 basic_param_offset = 0, basic_param_size;
  uint32 inst_4byte_offset = 0, inst_4byte_size;
  uint64 density_in_bytes;
  uint8 addr_bytes;

  /* Sanity check the structures. if compiler sizes are wrong the Compiler will
   * only keep the code inside this IF, and remove the rest. */
  if(sizeof(struct spinor_sfdp_header) != 8 ||
     sizeof(struct spinor_sfdp_param_header) != 8 ||
     sizeof(struct spinor_sfdp_basic_param) != (20*4) ||
     sizeof(struct spinor_sfdp_4byte_inst) != (2*4))
  {
    spinor_log (&spinor_dev.debug_log, 0x2E0);
    return ret_status;
  }

  header = &header_data;
  paramh = &paramh_data;
  bparam = &bparam_data;
  inst4b = &inst4b_data;

  memset(header, 0, sizeof(struct spinor_sfdp_header));
  memset(paramh, 0, sizeof(struct spinor_sfdp_param_header));
  memset(bparam, 0, sizeof(struct spinor_sfdp_basic_param));
  memset(inst4b, 0, sizeof(struct spinor_sfdp_4byte_inst));

  /* Basic device config to read SFDP. */
  config_data = spinor_dev.config_data;
  memset(config_data, 0, sizeof(spinor_config_data));
  config_data->magic_number = 0xFACEECAF;
  config_data->addr_bytes = 3;
  config_data->read_mode = READ_SDR_1_1_1_MODE;
  config_data->freq_khz = 50000; /* SFDP compliant parts must support reading
                                    at 50MHz*/
  config_data->dma_enable = 0;

  /* Read the SFDP header and validate it */
  /* Command | data addr | data buffer | length | opcode */
  status = spial_transfer(qspi_read_sfdp_mode, 0, (uint8*)header,
                          sizeof(struct spinor_sfdp_header), READ_SFDP_CMD);
  if (status != SPINOR_DEVICE_DONE)
  {
    spinor_log (&spinor_dev.debug_log, 0x2E1);
    ret_status = status;
    goto spinor_core_sfdp_end;
  }

  /* Header was read, validate it. */
  if (header->signature != SFDP_HEADER_SIGNATURE ||
      (header->major_rev < SFDP_HEADER_MAJOR_REV &&
       header->minor_rev < SFDP_HEADER_MINOR_REV_A))
  {
    spinor_log (&spinor_dev.debug_log, 0x2E2);
    goto spinor_core_sfdp_end;
  }

  /* Valid header, read until we find the basic parameter table. */
  for (count = 0; count <= header->num_param_headers; count++)
  {
    offset = sizeof(struct spinor_sfdp_header) + count * sizeof(struct spinor_sfdp_param_header);
    status = spial_transfer(qspi_read_sfdp_mode, offset, (uint8*)paramh,
                        sizeof(struct spinor_sfdp_param_header), READ_SFDP_CMD);
    if (status != SPINOR_DEVICE_DONE)
    {
      spinor_log (&spinor_dev.debug_log, 0x2E3);
      ret_status = status;
      goto spinor_core_sfdp_end;
    }

    /* Check for valid header version */
    if (paramh->major_rev != SFDP_BASIC_PARAM_MAJOR_REV &&
	paramh->minor_rev < SFDP_BASIC_PARAM_MINOR_REV)
    {
      continue;
    }

    /* Look for the Basic parameter Table offset. */
    if (paramh->param_id_lsb == SFDP_BASIC_PARAM_LSB &&
	paramh->param_id_msb == SFDP_BASIC_PARAM_MSB)
    {
      basic_param_offset = paramh->table_pointer;
      basic_param_size = paramh->table_length * sizeof(uint32);
    }

    /* Look for 4-byte Address Instruction Parameter Header. */
    if (paramh->param_id_lsb == SFDP_4BYTE_INST_LSB &&
	paramh->param_id_msb == SFDP_4BYTE_INST_MSB)
    {
      inst_4byte_offset = paramh->table_pointer;
      inst_4byte_size = paramh->table_length * sizeof(uint32);
    }
  }
  /* Check if we found a valid basic parameter header. */
  if (basic_param_offset == 0)
  {
    spinor_log (&spinor_dev.debug_log, 0x2E4);
    goto spinor_core_sfdp_end;
  }

  /* Compute the number of bytes of read for the table */
  if (basic_param_size > sizeof(struct spinor_sfdp_basic_param))
    basic_param_size = sizeof(struct spinor_sfdp_basic_param);

  /* Read the basic parameter table. */
  status = spial_transfer(qspi_read_sfdp_mode, basic_param_offset,
        (uint8*)bparam, basic_param_size, READ_SFDP_CMD);
  if (status != SPINOR_DEVICE_DONE)
  {
    spinor_log (&spinor_dev.debug_log, 0x2E5);
    ret_status = status;
    goto spinor_core_sfdp_end;
  }

  if ((bparam->density & 0x80000000))
    density_in_bytes = (1 << bparam->density & 0x7FFFFFFF) / 8;
  else
    density_in_bytes = (bparam->density / 8) + 1;

   /* possible values are
      0b00 3 byte addressing only
      0b01 3 byte or 4 byte addressing
      0b10 4 byte addressing only
      0b11 Reserved.*/
  if (bparam->address_bytes_sup == 0 ||
      (bparam->address_bytes_sup == 0b01 && density_in_bytes <= MAX_3BYTE_ADDRESS))
    addr_bytes = 3;
  else if (bparam->address_bytes_sup == 0b01 || bparam->address_bytes_sup == 0b10)
    addr_bytes = 4;
  else
  {
    spinor_log (&spinor_dev.debug_log, 0x2E5);
    goto spinor_core_sfdp_end;
  }

  /* 4 byte address mode enabled, read the 4 byte SFDP table. */
  if (addr_bytes == 4)
  {
    uint8 read_mode, read_inst, read_dummy_c;
    uint8 prog_mode, prog_inst;
    uint8 erase_4k_index = 0xFF, erase_bulk_index = 0xFF, prev_shift = 0;
    uint8 erase_inst[4];
    uint8 erase_shift_size[4];
    int i;
    /* Check if we found a valid 4 byte address instruction table. */
    if (inst_4byte_offset == 0)
    {
      spinor_log (&spinor_dev.debug_log, 0x2E6);
      goto spinor_core_sfdp_end;
    }
    if (inst_4byte_size > sizeof(struct spinor_sfdp_4byte_inst))
      inst_4byte_size = sizeof(struct spinor_sfdp_4byte_inst);

    /* Read the 4-byte address instruction table. */
    status = spial_transfer(qspi_read_sfdp_mode, inst_4byte_offset,
			    (uint8*)inst4b, inst_4byte_size, READ_SFDP_CMD);
    if (status != SPINOR_DEVICE_DONE)
    {
      spinor_log (&spinor_dev.debug_log, 0x2E7);
      ret_status = status;
      goto spinor_core_sfdp_end;
    }

    /* Setup the Read Mode and instruction*/
    if (inst4b->read_144_support == 1)
    {
      read_mode = READ_SDR_1_4_4_MODE;
      read_inst = READ_SDR_4B_144_INST;
      read_dummy_c = bparam->read_144_dummy_cycles + bparam->read_144_mode_clocks;
    }
    else if (inst4b->read_114_support == 1)
    {
      read_mode = READ_SDR_1_1_4_MODE;
      read_inst = READ_SDR_4B_114_INST;
      read_dummy_c = bparam->read_114_dummy_cycles + bparam->read_114_mode_clocks;
    }
    else if (inst4b->fread_111_support == 1)
    {
      read_mode = READ_SDR_1_1_1_MODE;
      read_inst = READ_SDR_4B_111_INST_F;
      read_dummy_c = 0;
    }
    else if (inst4b->read_111_support == 1)
    {
      read_mode = READ_SDR_1_1_1_MODE;
      read_inst = READ_SDR_4B_111_INST;
      read_dummy_c = 0;
    }
    else if (inst4b->read_ddr_111_support == 1)
    {
      read_mode = READ_DDR_1_1_1_MODE;
      read_inst = READ_DDR_4B_111_INST;
      read_dummy_c = 0;
    }
    else if (inst4b->read_ddr_122_support == 1)
    {
      read_mode = READ_DDR_1_2_2_MODE;
      read_inst = READ_DDR_4B_122_INST;
      read_dummy_c = bparam->read_122_dummy_cycles + bparam->read_122_mode_clocks;
    }
    else if (inst4b->read_122_support == 1)
    {
      read_mode = READ_DDR_1_2_2_MODE;
      read_inst = READ_DDR_4B_122_INST_F;
      read_dummy_c = bparam->read_122_dummy_cycles + bparam->read_122_mode_clocks;
    }
    else if (inst4b->read_ddr_144_support == 1)
    {
      read_mode = READ_DDR_1_4_4_MODE;
      read_inst = READ_DDR_4B_144_INST;
      read_dummy_c = bparam->read_144_dummy_cycles + bparam->read_144_mode_clocks;
    }
    else if (inst4b->read_118_support == 1)
    {
      /* Octal SPI support isn't available. Reverting to READ_DDR_1_4_4_MODE */
      read_mode = READ_DDR_1_4_4_MODE;
      read_inst = READ_DDR_4B_144_INST;
      read_dummy_c = bparam->read_144_dummy_cycles + bparam->read_144_mode_clocks;
    }
    else if (inst4b->read_ddr_188_support == 1)
    {
      /* Octal SPI support isn't available. Reverting to READ_DDR_1_4_4_MODE */
      read_mode = READ_DDR_1_4_4_MODE;
      read_inst = READ_DDR_4B_144_INST;
      read_dummy_c = bparam->read_144_dummy_cycles + bparam->read_144_mode_clocks;
    }
    else if (inst4b->read_188_support == 1)
    {
     /* Octal SPI support isn't available. Reverting to READ_DDR_1_4_4_MODE */
      read_mode = READ_DDR_1_4_4_MODE;
      read_inst = READ_DDR_4B_144_INST;
      read_dummy_c = bparam->read_144_dummy_cycles + bparam->read_144_mode_clocks;
    }
    else
    {
      spinor_log (&spinor_dev.debug_log, 0x2E8);
      goto spinor_core_sfdp_end;
    }

    /* Setup the Program/Write Mode and instruction*/
    if (inst4b->prog_144_support == 1)
    {
      prog_mode = WRITE_SDR_1_4_4_MODE;
      prog_inst = PROG_SDR_4B_144_INST;
    }
    else if (inst4b->prog_114_support == 1)
    {
      prog_mode = WRITE_SDR_1_1_4_MODE;
      prog_inst = PROG_SDR_4B_114_INST;
    }
    else if (inst4b->prog_111_support == 1)
    {
      prog_mode = WRITE_SDR_1_1_1_MODE;
      prog_inst = PROG_SDR_4B_111_INST;
    }
    else if (inst4b->prog_118_support == 1)
    {
      /* Octal SPI support isn't available. Reverting to WRITE_SDR_1_4_4_MODE */
      prog_mode = WRITE_SDR_1_4_4_MODE;
      prog_inst = PROG_SDR_4B_144_INST;
    }
    else if (inst4b->prog_188_support == 1)
    {
      /* Octal SPI support isn't available. Reverting to WRITE_SDR_1_4_4_MODE */
      prog_mode = WRITE_SDR_1_4_4_MODE;
      prog_inst = PROG_SDR_4B_144_INST;
    }
    else
    {
      spinor_log (&spinor_dev.debug_log, 0x2E9);
      goto spinor_core_sfdp_end;
    }

    memset (erase_shift_size, 0, sizeof(erase_shift_size));
    memset (erase_inst, 0, sizeof(erase_inst));
    if (inst4b->erase_1_support == 1)
    {
      erase_inst[0] = inst4b->erase_1_inst;
      erase_shift_size[0] = bparam->erase_type1_size;
    }
    if (inst4b->erase_2_support == 1)
    {
      erase_inst[1] = inst4b->erase_2_inst;
      erase_shift_size[1] = bparam->erase_type2_size;
    }
    if (inst4b->erase_3_support == 1)
    {
      erase_inst[2] = inst4b->erase_3_inst;
      erase_shift_size[2] = bparam->erase_type3_size;
    }
    if (inst4b->erase_4_support == 1)
    {
      erase_inst[3] = inst4b->erase_4_inst;
      erase_shift_size[3] = bparam->erase_type4_size;
    }
    /* Search for the 4k and bulk erase erase operations. */
    for (i = 0; i < 4; i++)
    {
      if (erase_shift_size[i] == 0x0C) /* 1 << 0x0C = 4096 */
	erase_4k_index = i;

      if (prev_shift < erase_shift_size[i])
      {
	prev_shift = erase_shift_size[i];
	erase_bulk_index = i;
      }
    }

    config->read_mode = read_mode;
    config->read_sdr_opcode = read_inst;
    config->read_sdr_wait_state = read_dummy_c;
    config->write_mode = prog_mode;
    config->write_sdr_opcode = prog_inst;
    if (erase_4k_index >= 4)
    {
      /* We didn't find a valid 4K erase command, required by software. */
      spinor_log (&spinor_dev.debug_log, 0x2EA);
      goto spinor_core_sfdp_end;
    }
    config->erase_4kb_opcode = erase_inst[erase_4k_index];
    /* Bulk erase must be at least 4K in We didn't find a valid Bulk erase command */
    if (erase_bulk_index >= 4 || erase_shift_size[erase_bulk_index] < 0xC)
    {
      spinor_log (&spinor_dev.debug_log, 0x2EB);
      goto spinor_core_sfdp_end;
    }
    config->bulk_erase_size_in_4KB = (1 << (erase_shift_size[erase_bulk_index] - 0xC));
    config->bulk_erase_opcode = erase_inst[erase_bulk_index];

    /* Sort this statements to give priority to a different switch mode */
    if (bparam->enter_4b_addr & 0b01000000) /* Always in 4 byte mode */
      spinord->addr_mode_4byte = ADDR_4BYTE_MODE_7;
    else if (bparam->enter_4b_addr & 0b00000001) /* Issue B7 instruction */
      spinord->addr_mode_4byte = ADDR_4BYTE_MODE_1;
    else if (bparam->enter_4b_addr & 0b00100000) /* Dedicated 4Byte ADDR Instructions. */
      spinord->addr_mode_4byte = ADDR_4BYTE_MODE_6;
    else if (bparam->enter_4b_addr & 0b00000010) /* instruction 06 then B7 */
      spinord->addr_mode_4byte = ADDR_4BYTE_MODE_2;
    else if (bparam->enter_4b_addr & 0b00000100) /* */
      spinord->addr_mode_4byte = ADDR_4BYTE_MODE_3;
    else if (bparam->enter_4b_addr & 0b00001000)
      spinord->addr_mode_4byte = ADDR_4BYTE_MODE_4;
    else if (bparam->enter_4b_addr & 0b00010000)
      spinord->addr_mode_4byte = ADDR_4BYTE_MODE_5;
    else
      spinord->addr_mode_4byte = ADDR_4BYTE_MODE_MAX; /* 4 byte address not supported? odd*/

  }
  else /* 3 byte address mode */
  {

    spinord->addr_mode_4byte = ADDR_4BYTE_NOT_SUPPORTED;
    /* We don't fully support or have tested 3 byte addressing,
     * Return error since we don't support this part. */
    spinor_log (&spinor_dev.debug_log, 0x2ED);
    goto spinor_core_sfdp_end;
  }

  if (bparam->page_size > 0x0C) /* Code assumes page size is less than 4k */
  {
    spinor_log (&spinor_dev.debug_log, 0x2EE);
    goto spinor_core_sfdp_end;
  }
  page_size = 1 << bparam->page_size;

  config->addr_bytes = addr_bytes;
  config->quad_enable_mode = bparam->quad_en_r;
  config->read_max_transfer_in_pages = density_in_bytes / page_size;
  config->density_in_blocks = density_in_bytes / 4096;
  config->block_size_in_bytes = 4096;
  config->pages_per_block = 4096 / page_size;
  config->page_size_in_bytes = page_size;

  /* The error bitmask for erase and program could be retrieved from the
   * device by getting the SCCR table in SFDP. SCCR is defined in JESD216C
   * or later. */
  switch (manufacturer)
  {
  case MANUFACTURER_ID_MACRONIX:
    config->erase_err_bmsk       = 0x40;
    config->erase_err_status_reg = 0x2B;
    config->write_err_bmsk       = 0x20;
    config->write_err_status_reg = 0x2B;
    break;
  case MANUFACTURER_ID_MICRON:
    config->erase_err_bmsk       = 0x7E;
    config->erase_err_status_reg = 0x70;
    config->write_err_bmsk       = 0x7E;
    config->write_err_status_reg = 0x70;
    break;
  case MANUFACTURER_ID_SPANSION:
    config->erase_err_bmsk       = 0x60;
    config->erase_err_status_reg = 0x05;
    config->write_err_bmsk       = 0x60;
    config->write_err_status_reg = 0x05;
    break;
  case MANUFACTURER_ID_WINBOND:
    config->erase_err_bmsk       = 0;
    config->erase_err_status_reg = 0;
    config->write_err_bmsk       = 0;
    config->write_err_status_reg = 0;
    break;
  default:
    spinor_log (&spinor_dev.debug_log, 0x2EF);
    goto spinor_core_sfdp_end;
    break;
  }

  config->dma_enable = TRUE;
  config->erase_status_polling_ms = 5; /* not part related */
  config->write_status_polling_usec = 100; /* not part related */
  config->spinor_client_ref_count = 0;/* not part related */
  config->reserved_1 = 0;
  config->reserved_3 = 0;

  ret_status = SPINOR_DEVICE_DONE;

spinor_core_sfdp_end:
  return ret_status;
}
