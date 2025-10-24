#ifndef HAL_MDP_VDCM_H
#define HAL_MDP_VDCM_H
/*=============================================================================
  Copyright (c) 2020 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
=============================================================================*/

#define VDCM_FLAT_QP_LUT_SIZE     8
#define VDCM_MAX_QP_LUT_SIZE      8
#define VDCM_TAR_DEL_LUT_SIZE     16
#define VDCM_LBDA_BRATE_LUT_SIZE  16
#define VDCM_LBDA_BF_LUT_SIZE     16
#define VDCM_LBDA_BRATE_REG_SIZE  64
#define VDCM_LBDA_BF_REG_SIZE     64
#define VDCM_MAX(x, y)            (((x) > (y)) ? (x) : (y))
#define VDCM_MIN(x, y)            (((x) < (y)) ? (x) : (y))
#define VDCM_CEIL(x, y)           (((x) + (y) - 1) / (y))

/**
 * VDC-M video traffic mode
 * @VDCM_TRAFFIC_SYNC_PULSES:       Non-burst mode with sync pulses.
 * @VDCM_TRAFFIC_SYNC_START_EVENTS: Non-burst mode with sync start events.
 * @VDCM_TRAFFIC_BURST_MODE:        Burst mode using sync start events.
 */
typedef enum
{
  VDCM_TRAFFIC_SYNC_PULSES = 0,
  VDCM_TRAFFIC_SYNC_START_EVENTS,
  VDCM_TRAFFIC_BURST_MODE,
  VDCM_TRAFFIC_MAX,
} VDCMTrafficMode;

/* VDC-M profile that can be supported */
typedef enum {
  RGB444_8BPC_8BPP,
  RGB444_8BPC_6BPP,
  RGB444_10BPC_10BPP,
  RGB444_10BPC_8BPP,
  RGB444_10BPC_7BPP,
  RGB444_10BPC_6BPP,
  YUV422_8BPC_6BPP,
  YUV422_8BPC_5BPP,
  YUV422_8BPC_4_75BPP,
  YUV422_10BPC_8BPP,
  YUV422_10BPC_6BPP,
  YUV422_10BPC_5_5BPP,
  YUV422_10BPC_5PP,
  VDCM_PROFILE_MAX_INDEX
} VDCMProfileIndex;

/* Color space */
typedef enum {
   RGB,
   YUV,
} VDCMColorSpace;

/* Chroma Format */
typedef enum {
   RGB444,
   YUV422,
} VDCMChroma;

/* VDC-M Profile Parameter */
typedef struct
{
   uint32         uMajor;
   uint32         uMinor;
   uint32         uVersionRelease;         /* version release*/
   VDCMChroma     uChroma;
   VDCMColorSpace uColorSpace;
   uint32         uBPC;                    /* source bpc */
   float          fBPP;                    /* target bpp */
} VDCMConfigType;

const VDCMConfigType gVDCMProfile_table[] =
{
   { 1, 1, 0, RGB444, RGB, 8, 8.0},   /*   RGB444_8BPC_8BPP      */
   { 1, 1, 0, RGB444, RGB, 8, 6.0},   /*   RGB444_8BPC_6BPP      */
   { 1, 1, 0, RGB444, RGB, 10, 10.0}, /*   RGB444_10BPC_10BPP    */
   { 1, 1, 0, RGB444, RGB, 10, 8.0},  /*   RGB444_10BPC_8BPP     */
   { 1, 1, 0, RGB444, RGB, 10, 7.0},  /*   RGB444_10BPC_7BPP     */
   { 1, 1, 0, RGB444, RGB, 10, 6.0},  /*   RGB444_10BPC_6BPP     */
   { 1, 1, 0, YUV422, YUV, 8, 6.0},   /*   YUV422_8BPC_6BPP      */
   { 1, 1, 0, YUV422, YUV, 8, 5.0},   /*   YUV422_8BPC_5BPP      */
   { 1, 1, 0, YUV422, YUV, 8, 4.75},  /*   YUV422_8BPC_4_75BPP   */
   { 1, 1, 0, YUV422, YUV, 10, 8.0},  /*   YUV422_10BPC_8BPP     */
   { 1, 1, 0, YUV422, YUV, 10, 6.0},  /*   YUV422_10BPC_6BPP     */
   { 1, 1, 0, YUV422, YUV, 10, 5.5},  /*   YUV422_10BPC_5_5BPP   */
   { 1, 1, 0, YUV422, YUV, 10, 5.0},  /*   YUV422_10BPC_5PP      */
}; 

/* VDC-M core profile that can be supported */
typedef enum {
   VDCM_V1_1_ENC_1HS_2SS_10BIT,   /* can only be used at vdcm_0 */
   VDCM_CORE_PROFILE_MAX_INDEX,
} VDCMCoreIndex;

/* VDC-M Core Profile parameters*/
typedef struct
{
   uint32 rtl_max_bpc;
   uint32 rtl_nb_hs_enc;
   uint32 rtl_nb_ss_enc;
   uint32 rtl_output_data_width;
   uint32 rtl_native_420_enable;
   uint32 rtl_native_422_enable;
   uint32 rtl_max_pixels_per_line;
   uint32 rtl_max_pixels_per_hs_line;
   uint32 rtl_max_pixels_per_frame;
   uint32 rtl_max_pixels_per_slice;
   uint32 rtl_max_max_se;
   uint32 rtl_ram_read_latency;
   uint32 rtl_input_demux_enable;
   uint32 rtl_ob_addr_width;
   uint32 rtl_max_contect_per_ob;
} VDCMCoreConfigType;

const VDCMCoreConfigType gVDCMCoreConfig_table[] =
{
   {10, 1, 2, 64, 0, 1, 5120, 5120, 5120, 5120, 128, 1, 0, 10, 32},
};

const uint8 vdcm_ssm_max_se_size[VDCM_PROFILE_MAX_INDEX] =
{
	128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128
};

const uint8 vdcm_rc_target_rate_extra_fbls[VDCM_PROFILE_MAX_INDEX] =
{
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
};

const uint8 vdcm_mppf_bpc_r_y[VDCM_PROFILE_MAX_INDEX] =
{
	2, 1, 3, 2, 2, 1, 3, 2, 2, 4, 3, 2, 2
};

const uint8 vdcm_mppf_bpc_g_cb[VDCM_PROFILE_MAX_INDEX] =
{
	2, 2, 3, 2, 2, 2, 2, 2, 1, 3, 2, 2, 2
};

const uint8 vdcm_mppf_bpc_b_cr[VDCM_PROFILE_MAX_INDEX] =
{
	2, 1, 3, 2, 2, 1, 2, 2, 1, 3, 2, 2, 2
};

const uint8 vdcm_mppf_bpc_y[VDCM_PROFILE_MAX_INDEX] =
{
	2, 2, 3, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0
};

const uint8 vdcm_mppf_bpc_co[VDCM_PROFILE_MAX_INDEX] =
{
	2, 1, 3, 2, 2, 1, 0, 0, 0, 0, 0, 0, 0
};

const uint8 vdcm_mppf_bpc_cg[VDCM_PROFILE_MAX_INDEX] =
{
	2, 1, 3, 2, 2, 1, 0, 0, 0, 0, 0, 0, 0
};

const uint8 vdcm_flat_qp_vf_fbls[VDCM_PROFILE_MAX_INDEX] =
{
	20, 24, 24, 24, 24, 24, 24, 24, 24, 8, 20, 18, 24
};

const uint8 vdcm_flat_qp_vf_nfbls[VDCM_PROFILE_MAX_INDEX] =
{
	24, 28, 28, 28, 28, 28, 28, 28, 28, 16, 24, 20, 28
};

const uint8 vdcm_flat_qp_sf_fbls[VDCM_PROFILE_MAX_INDEX] =
{
	24, 28, 28, 28, 28, 28, 28, 28, 28, 16, 24, 20, 28
};

const uint8 vdcm_flat_qp_sf_nfbls[VDCM_PROFILE_MAX_INDEX] =
{
	28, 40, 32, 28, 32, 28, 36, 36, 36, 16, 24, 24, 28
};

const uint16 vdcm_flat_qp_lut_table[VDCM_PROFILE_MAX_INDEX][VDCM_FLAT_QP_LUT_SIZE] =
{
	{20, 20, 24, 24, 28, 32, 36, 40},
	{24, 24, 28, 32, 36, 40, 40, 40},
	{24, 24, 28, 32, 32, 36, 36, 36},
	{20, 24, 28, 28, 32, 36, 40, 44},
	{20, 24, 28, 32, 32, 36, 36, 40},
	{24, 28, 32, 32, 36, 40, 40, 40},
	{24, 28, 32, 34, 36, 38, 40, 40},
	{24, 28, 32, 36, 40, 42, 44, 44},
	{24, 28, 32, 36, 40, 42, 44, 44},
	{0, 8, 10, 12, 14, 16, 18, 20},
	{12, 16, 20, 20, 20, 24, 24, 28},
	{16, 18, 20, 22, 24, 26, 28, 28},
	{20, 22, 24, 26, 28, 28, 32, 32},
};

const uint16 vdcm_max_qp_lut_table[VDCM_PROFILE_MAX_INDEX][VDCM_MAX_QP_LUT_SIZE] =
{
	{28, 28, 32, 32, 36, 42, 42, 48},
	{32, 32, 36, 40, 44, 48, 48, 52},
	{32, 32, 36, 36, 36, 40, 44, 48},
	{24, 28, 32, 32, 36, 40, 44, 48},
	{28, 28, 32, 32, 36, 42, 42, 48},
	{28, 32, 36, 40, 44, 44, 46, 52},
	{32, 32, 36, 40, 40, 44, 48, 48},
	{32, 32, 36, 40, 44, 48, 50, 52},
	{32, 32, 36, 40, 44, 48, 50, 52},
	{8, 12, 12, 16, 20, 24, 28, 28},
	{18, 20, 22, 24, 28, 30, 32, 40},
	{18, 20, 22, 24, 28, 30, 32, 40},
	{20, 20, 24, 24, 28, 28, 32, 36},
};

const uint16 vdcm_tar_del_lut_table[VDCM_PROFILE_MAX_INDEX][VDCM_TAR_DEL_LUT_SIZE] =
{
	{128, 117, 107, 96, 85, 75, 64, 53, 43, 32, 24, 11, 0, 0, 0, 0},
	{96, 88, 80, 72, 64, 56, 48, 40, 32, 24, 16, 8, 0, 0, 0, 0},
	{160, 147, 133, 120, 107, 93, 80, 67, 53, 40, 27, 13, 0, 0, 0, 0},
	{128, 117, 107, 96, 85, 75, 64, 53, 43, 32, 21, 11, 0, 0, 0, 0},
	{112, 103, 93, 84, 75, 95, 56, 47, 37, 28, 19, 9, 0, 0, 0, 0},
	{96, 88, 80, 72, 64, 56, 48, 40, 32, 24, 16, 8, 0, 0, 0, 0},
	{96, 88, 80, 72, 64, 56, 48, 40, 32, 24, 16, 8, 0, 0, 0, 0},
	{80, 73, 67, 60, 53, 47, 40, 33, 27, 20, 13, 7, 0, 0, 0, 0},
	{76, 70, 63, 57, 51, 44, 38, 32, 25, 19, 13, 6, 0, 0, 0, 0},
	{128, 117, 107, 96, 85, 75, 64, 53, 43, 32, 21, 11, 0, 0, 0, 0},
	{96, 88, 80, 72, 64, 56, 48, 40, 32, 24, 16, 8, 0, 0, 0, 0},
	{88, 81, 73, 66, 59, 51, 44, 37, 29, 22, 15, 7, 0, 0, 0, 0},
	{80, 73, 67, 60, 53, 47, 40, 33, 27, 20, 13, 7, 0, 0, 0, 0},
};

const uint16 vdcm_lbda_brate_lut_table[VDCM_PROFILE_MAX_INDEX][VDCM_LBDA_BRATE_LUT_SIZE] =
{
	{4, 6, 10, 16, 25, 40, 64, 102, 161, 256, 406, 645, 1024, 1625, 2580, 4095},
	{8, 12, 18, 28, 42, 64, 97, 147, 223, 338, 512, 776, 1176, 1782, 2702, 4095},
	{16, 23, 34, 48, 70, 102, 147, 213, 308, 446, 645, 933, 1351, 1955, 2829, 4095},
	{8, 12, 18, 28, 42, 64, 97, 147, 223, 338, 512, 776, 1176, 1782, 2702, 4095},
	{32, 44, 61, 84, 117, 161, 223, 308, 425, 588, 813, 1123, 1552, 2144, 2963, 4095},
	{64, 84, 111, 147, 194, 256, 338, 446, 588, 776, 1024, 1351, 1782, 2352, 3103, 4095},
	{1, 2, 3, 5, 9, 16, 28, 48, 84, 147, 256, 446, 776, 1351, 2352, 4095},
	{4, 6, 10, 16, 25, 40, 64, 102, 161, 256, 406, 645, 1024, 1625, 2580, 4095},
	{4, 6, 10, 16, 25, 40, 64, 102, 161, 256, 406, 645, 1024, 1625, 2580, 4095},
	{1, 2, 3, 5, 9, 16, 28, 48, 84, 147, 256, 446, 776, 1351, 2352, 4095},
	{1, 2, 3, 5, 9, 16, 28, 48, 84, 147, 256, 446, 776, 1351, 2352, 4095},
	{1, 2, 3, 5, 9, 16, 28, 48, 84, 147, 256, 446, 776, 1351, 2352, 4095},
	{1, 2, 3, 5, 9, 16, 28, 48, 84, 147, 256, 446, 776, 1351, 2352, 4095},
};

const uint16 vdcm_lbda_bf_lut_table[VDCM_PROFILE_MAX_INDEX][VDCM_LBDA_BF_LUT_SIZE] =
{
	{1, 1, 2, 3, 4, 6, 9, 13, 19, 28, 40, 58, 84, 122, 176, 255},
	{1, 1, 2, 3, 4, 6, 9, 13, 19, 28, 40, 58, 84, 122, 176, 255},
	{1, 1, 2, 3, 4, 6, 9, 13, 19, 28, 40, 58, 84, 122, 176, 255},
	{1, 1, 2, 3, 4, 6, 9, 13, 19, 28, 40, 58, 84, 122, 176, 255},
	{4, 5, 7, 9, 12, 16, 21, 28, 37, 48, 64, 84, 111, 146, 193, 255},
	{1, 1, 1, 2, 3, 4, 6, 9, 14, 21, 32, 48, 73, 111, 168, 255},
	{1, 1, 1, 1, 2, 3, 4, 6, 10, 16, 25, 40, 64, 101, 161, 255},
	{1, 1, 1, 1, 2, 3, 4, 6, 10, 16, 25, 40, 64, 101, 161, 255},
	{1, 1, 1, 1, 2, 3, 4, 6, 10, 16, 25, 40, 64, 101, 161, 255},
	{1, 1, 1, 1, 2, 3, 4, 6, 10, 16, 25, 40, 64, 101, 161, 255},
	{1, 1, 1, 1, 2, 3, 4, 6, 10, 16, 25, 40, 64, 101, 161, 255},
	{1, 1, 1, 1, 2, 3, 4, 6, 10, 16, 25, 40, 64, 101, 161, 255},
	{1, 1, 1, 1, 2, 3, 4, 6, 10, 16, 25, 40, 64, 101, 161, 255},
};

uint16 vdcm_lbda_brate_lut_interp_table[VDCM_LBDA_BRATE_REG_SIZE];
uint16 vdcm_lbda_bf_lut_interp_table[VDCM_LBDA_BF_REG_SIZE];


/*************************************************************************/

typedef struct
{
  uint32 version_major;
  uint32 version_minor;
  uint32 version_release;
  uint32 bits_per_component;
  uint32 bits_per_pixel;
  uint32 chroma_format;
  uint32 source_color_space;
  uint32 picture_height; 
  uint32 picture_width;
  uint32 slice_height;
  uint32 slice_width;
  uint32 bpc_pps_flag;
  uint32 bpp_codec;
  uint32 chroma_pps_flag;
  uint32 colorspace_pps_flag;
  
  /* VDC-M Lookup Parameters */
  uint32 ssm_max_se_size;
  uint32 rc_target_rate_extra_fbls;
  uint32 mppf_bits_per_comp;
  uint32 flatness_qp_very_flat_fbls;
  uint32 flatness_qp_very_flat_nfbls;
  uint32 flatness_qp_somewhat_flat_fbls;
  uint32 flatness_qp_somewhat_flat_nfbls;
  const uint16 *flatness_qp_lut;
  const uint16 *max_qp_lut;
  const uint16 *target_rate_delta_lut;
  const uint16 *lbda_brate_lut;
  const uint16 *lbda_bf_lut;
  uint16 *lbda_brate_lut_interp;
  uint16 *lbda_bf_lut_interp;

  /* VDC-M Config Parameters */
  uint32 vdcm_config_index;
  uint32 core_config_index;
  const VDCMConfigType          *pConfig; 
  const VDCMCoreConfigType      *pCoreConfig;    /* base on core_config_index */
  uint32 num_of_active_ss;
  uint32 num_of_active_hs;
  uint32 frame_width;
  uint32 frame_height;
  uint32 video_mode;
  uint32 panel_split;

  /* VDC-M Fixed Parameters */
  uint32 pps_identifier; 
  uint32 slice_num_px_threshold;
  uint32 max_pipeline_latency;
  uint32 min_pipeline_latency;
  uint32 ob_data_width;
  uint32 out_buf_full_thresh;
  uint32 out_buf_uf_margin;
  uint32 out_buf_of_margin_tc_10;
  uint32 out_buf_of_margin_ob;
  uint32 output_data_width;
  uint32 ob0_ram_depth;
  uint32 ob1_ram_depth;

  /* VDC-M Core Algorithm Calculated Parameters */
  uint32 chunk_size;
  uint32 chunk_size_bits;
  uint32 slice_num_px;
  uint32 avg_block_bits;
  uint32 per_chunk_pad_bits;
  uint32 total_padding_bits;
  uint32 rc_stuffing_bits;
  uint64 slice_num_bits;
  uint32 slice_num_bits_upper_byte;
  uint32 slice_num_bits_lower_dword;
  uint32 chunk_adj_bits;
  uint32 rc_buffer_init_size_temp;
  uint32 init_tx_delay_temp;
  uint32 rc_buffer_init_size;
  uint32 rc_init_tx_delay;
  uint32 rc_init_tx_delay_px_times;
  uint32 rc_buffer_max_size;
  uint32 rc_target_rate_scale_temp_a;
  uint32 rc_target_rate_scale_temp_b;
  uint32 rc_target_rate_scale;
  uint32 rc_target_rate_threshold;
  uint32 chroma_samples;
  uint32 block_max_bits;
  uint32 rc_lambda_bitrate_scale;
  uint32 rc_buffer_fullness_scale;
  uint32 rc_fullness_offset_threshold;
  uint32 ramp_blocks;
  uint32 ramp_bits;
  uint32 rc_fullness_offset_slope;
  uint32 num_extra_mux_bits_init;
  uint32 extra_crop_bits;
  uint32 num_extra_mux_bits;
  uint32 mppf_bits_comp_0;
  uint32 mppf_bits_comp_1;
  uint32 mppf_bits_comp_2;
  uint32 min_block_bits;
 
  /* VDC-M Core Calculated Parameters */
  uint32 min_ssm_delay;;
  uint32 max_ssm_delay;
  uint32 input_ssm_out_latency;
  uint32 input_ssm_out_latency_min;
  uint32 obuf_latency;
  uint32 base_hs_latency ;
  uint32 base_hs_latency_min;
  uint32 base_hs_latency_pixels;
  uint32 base_hs_latency_pixels_min;
  uint32 base_initial_lines;
  uint32 base_top_up;
  uint32 output_rate;
  uint32 output_rate_ratio_100;
  uint32 burst_accum_pixels;
  uint32 ss_initial_lines;
  uint32 burst_initial_lines;
  uint32 initial_lines;
  uint32 obuf_base;
  uint32 obuf_extra_ss0;
  uint32 obuf_extra_ss1;
  uint32 obuf_extra_burst;
  uint32 obuf_ss0;
  uint32 obuf_ss1;
  uint32 obuf_margin_words;
  uint32 ob0_max_addr;
  uint32 ob1_max_addr;
  uint32 slice_width_orig;
  uint32 r2b0_max_addr;
  uint32 r2b1_max_addr;
} VDCM_DesciptorType;

#endif /* HAL_MDP_VDCM_H */
