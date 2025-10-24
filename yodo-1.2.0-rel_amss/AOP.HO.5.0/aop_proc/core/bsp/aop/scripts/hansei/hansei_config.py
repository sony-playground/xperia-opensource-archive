#  ===========================================================================
#
#  Copyright (c) 2015-2016 Qualcomm Technologies, Inc.
#  All Rights Reserved.
#  QUALCOMM Proprietary and Confidential.
#
#  ===========================================================================


dump_file_types = [
    #
    # Core stuff, most important.
    #
    {   # The place all of the code lives
        'display_name'  : "CODERAM",
        'name'          : {'CODERAM.BIN','md_CODERAM.BIN','aop_code_0xb000000--0xb017fff.lst'},
        'ext'           : {'.BIN','.LST'},
        'basename'      : {'CODERAM', 'md_CODERAM','aop_code_0xb000000--0xb017fff'},
        'required'      : True,
        'no_load'       : False,
        'base'          : {
                            'hoya'  : 0x000000,
                            #'wildcat'  : 0x000000,
                          },
    },
    {   # The place all of the data lives
        'display_name'  : "DATARAM",
        'name'          : {'DATARAM.BIN','md_DATARAM.BIN','aop_data_0xb0e0000--0xb0e7fff.lst'},
        'ext'           : {'.BIN','.LST' },
        'basename'      : {'DATARAM','md_DATARAM', 'aop_data_0xb0e0000--0xb0e7fff'},
        'required'      : True,
        'no_load'       : False,
        'base'          : {
                              'hoya'  : 0x0E0000,
                              #'wildcat'  : 0x0E0000,
                          },
    },
    {   # The place all of the data lives
        'display_name'  : "MSGRAM0",
        'name'          : {'MSGRAM0.BIN','md_MSGRAM0.BIN','aop_msg0_0xc300000--0xc3003ff.lst'},
        'ext'           : {'.BIN','.LST'},
        'basename'      : {'MSGRAM0', 'md_MSGRAM0','aop_msg0_0xc300000--0xc3003ff'},
        'required'      : False,
        'no_load'       : False,
        'base'          : {
                              'hoya'  : 0x1300000,
                              #'wildcat'  : 0x1300000,
                          },
    },
    {   # The place all of the data lives
        'display_name'  : "MSGRAM1",
        'name'          : {'MSGRAM1.BIN','md_MSGRAM1.BIN','aop_msg1_0xc310000--0xc3103ff.lst'},
        'ext'           : {'.BIN','.LST'},
        'basename'      : {'MSGRAM1','md_MSGRAM1','aop_msg1_0xc310000--0xc3103ff'},
        'required'      : False,
        'no_load'       : False,
        'base'          : {
                              'hoya'  : 0x1310000,
                              #'wildcat'  : 0x1310000,
                          },
    },
    {   # The place all of the data lives
        'display_name'  : "MSGRAM2",
        'name'          : {'MSGRAM2.BIN','md_MSGRAM2.BIN','aop_msg2_0xc320000--0xc3203ff.lst'},
        'ext'           : {'.BIN','.LST'},
        'basename'      : {'MSGRAM2','md_MSGRAM2','aop_msg2_0xc320000--0xc3203ff'},
        'required'      : False,
        'no_load'       : False,
        'base'          : {
                              'hoya'  : 0x1320000,
                              #'wildcat'  : 0x1320000,
                          },
    },
    {   # The place all of the data lives
        'display_name'  : "MSGRAM3",
        'name'          : {'MSGRAM3.BIN','md_MSGRAM3.BIN','aop_msg3_0xc330000--0xc3303ff.lst'},
        'ext'           : {'.BIN','.LST'},
        'basename'      : {'MSGRAM3','md_MSGRAM3','aop_msg3_0xc330000--0xc3303ff'},
        'required'      : False,
        'no_load'       : False,
        'base'          : {
                              'hoya'  : 0x1330000,
                              #'wildcat'  : 0x1330000,
                          },
    },
    {   # The place all of the data lives
        'display_name'  : "MSGRAM4",
        'name'          : {'MSGRAM4.BIN','md_MSGRAM4.BIN','aop_msg4_0xc340000--0xc3403ff.lst'},
        'ext'           : {'.BIN','.LST'},
        'basename'      : {'MSGRAM4','md_MSGRAM4','aop_msg4_0xc340000--0xc3403ff'},
        'required'      : False,
        'no_load'       : False,
        'base'          : {
                              'hoya'  : 0x1340000,
                              #'wildcat'  : 0x1340000,
                          },
    },
    {   # The place all of the data lives
        'display_name'  : "MSGRAM5",
        'name'          : {'MSGRAM5.BIN','md_MSGRAM5.BIN','aop_msg5_0xc350000--0xc3503ff.lst'},
        'ext'           : {'.BIN','.LST'},
        'basename'      : {'MSGRAM5','md_MSGRAM5','aop_msg5_0xc350000--0xc3503ff'},
        'required'      : False,
        'no_load'       : False,
        'base'          : {
                              'hoya'  : 0x1350000,
                              #'wildcat'  : 0x1350000,
                          },
    },
    {   # The place all of the data lives
        'display_name'  : "MSGRAM6",
        'name'          : {'MSGRAM6.BIN','md_MSGRAM6.BIN','aop_msg6_0xc360000--0xc3603ff.lst'},
        'ext'           : {'.BIN','.LST'},
        'basename'      : {'MSGRAM6','md_MSGRAM6','aop_msg6_0xc360000--0xc3603ff'},
        'required'      : False,
        'no_load'       : False,
        'base'          : {
                              'hoya'  : 0x1360000,
                              #'wildcat'  : 0x1360000,
                          },
    },
    {   # The place all of the data lives
        'display_name'  : "MSGRAM7",
        'name'          : {'MSGRAM7.BIN','md_MSGRAM7.BIN','aop_msg7_0xc370000--0xc3703ff.lst'},
        'ext'           : {'.BIN','.LST'},
        'basename'      : {'MSGRAM7','md_MSGRAM7','aop_msg7_0xc370000--0xc3703ff'},
        'required'      : False,
        'no_load'       : False,
        'base'          : {
                              'hoya'  : 0x1370000,
                              #'wildcat'  : 0x1370000,
                          },
    },
    {   # The place all of the data lives
        'display_name'  : "MSGRAM8",
        'name'          : {'MSGRAM8.BIN','md_MSGRAM8.BIN','aop_msg8_0xc380000--0xc3803ff.lst'},
        'ext'           : {'.BIN','.LST'},
        'basename'      : {'MSGRAM8','md_MSGRAM8','md_MSGRAM0.BIN','aop_msg8_0xc380000--0xc3803ff'},
        'required'      : False,
        'no_load'       : False,
        'base'          : {
                              'hoya'  : 0x1380000,
                              #'wildcat'  : 0x1380000,
                          },
    },
    {   # The place all of the data lives
        'display_name'  : "MSGRAM9",
        'name'          : {'MSGRAM9.BIN','md_MSGRAM9.BIN','aop_msg9_0xc390000--0xc3903ff.lst'},
        'ext'           : {'.BIN','.LST'},
        'basename'      : {'MSGRAM9','md_MSGRAM9','aop_msg9_0xc390000--0xc3903ff'},
        'required'      : False,
        'no_load'       : False,
        'base'          : {
                              'hoya'  : 0x1390000,
                              #'wildcat'  : 0x1390000,
                          },
    },
    {   # The place all of the data lives
        'display_name'  : "MSGRAM10",
        'name'          : {'MSGRAM10.BIN','md_MSGRAM10.BIN','aop_msg10_0xc3a0000--0xc3a03ff.lst'},
        'ext'           : {'.BIN','.LST'},
        'basename'      : {'MSGRAM10','md_MSGRAM10','aop_msg10_0xc3a0000--0xc3a03ff'},
        'required'      : False,
        'no_load'       : False,
        'base'          : {
                              'hoya'  : 0x13A0000,
                              #'wildcat'  : 0x13A0000,
                          },
    },
    {   # The place all of the data lives
        'display_name'  : "MSGRAM11",
        'name'          : {'MSGRAM11.BIN','md_MSGRAM11.BIN','aop_msg11_0xc3b0000--0xc3b03ff.lst'},
        'ext'           : {'.BIN','.LST'},
        'basename'      : {'MSGRAM11','md_MSGRAM11','aop_msg11_0xc3b0000--0xc3b03ff'},
        'required'      : False,
        'no_load'       : False,
        'base'          : {
                              'hoya'  : 0x13B0000,
                              #'wildcat'  : 0x13B0000,
                          },
    },
    {   # The place all of the data lives
        'display_name'  : "MSGRAM12",
        'name'          : {'MSGRAM12.BIN','md_MSGRAM12.BIN','aop_msg12_0xc3c0000--0xc3c03ff.lst'},
        'ext'           : {'.BIN','.LST'},
        'basename'      : {'MSGRAM12','md_MSGRAM12','aop_msg12_0xc3c0000--0xc3c03ff'},
        'required'      : False,
        'no_load'       : False,
        'base'          : {
                              'hoya'  : 0x13C0000,
                              #'wildcat'  : 0x13C0000,
                          },
    },
    {   # The place all of the data lives
        'display_name'  : "MSGRAM13",
        'name'          : {'MSGRAM13.BIN','md_MSGRAM13.BIN','aop_msg13_0xc3d0000--0xc3d03ff.lst'},
        'ext'           : {'.BIN','.LST'},
        'basename'      : {'MSGRAM13','md_MSGRAM13','aop_msg13_0xc3d0000--0xc3d03ff'},
        'required'      : False,
        'no_load'       : False,
        'base'          : {
                              'hoya'  : 0x13D0000,
                              #'wildcat'  : 0x13D0000,
                          },
    },
    {   # The place all of the data lives
        'display_name'  : "MSGRAM14",
        'name'          : {'MSGRAM14.BIN','md_MSGRAM14.BIN','aop_msg14_0xc3e0000--0xc3e03ff.lst'},
        'ext'           : {'.BIN','.LST'},
        'basename'      : {'MSGRAM14','md_MSGRAM14','aop_msg14_0xc3e0000--0xc3e03ff'},
        'required'      : False,
        'no_load'       : False,
        'base'          : {
                              'hoya'  : 0x13E0000,
                              #'wildcat'  : 0x13E0000,
                          },
    },
	{   # The place all of the data lives
        'display_name'  : "MSGRAM15",
        'name'          : {'MSGRAM15.BIN','md_MSGRAM15.BIN','aop_msg15_0xc3f0000--0xc3f03ff.lst'},
        'ext'           : {'.BIN','.LST'},
        'basename'      : {'MSGRAM15','md_MSGRAM15','aop_msg15_0xc3f0000--0xc3f03ff'},
        'required'      : False,
        'no_load'       : False,
        'base'          : {
                              'hoya'  : 0x13F0000,
                              #'wildcat'  : 0x13F0000,
                          },
    },
    {   # The place all of the data lives
        'display_name'  : "RPMH_BINARY",
        'name'          : {'RPMH_BINARY.BIN'},
        'ext'           : {'.BIN','.LST'},
        'basename'      : {'RPMH_BINARY'},
        'required'      : False,
        'no_load'       : False,
        'base'          : {
                              'hoya'  : 0xB200000,
                              #'wildcat'  : 0xB200000,
                          },
    },
    {   # The place all of the data lives
        'display_name'  : "RPMH_MINIDUMP",
        'name'          : {'md_rpmh.BIN'},
        'ext'           : {'.BIN','.LST'},
        'basename'      : {'md_rpmh'},
        'required'      : False,
        'no_load'       : True,
        'path'          : "",
        'size'          : 0x0,
        'update'        : True,
        'base'          : {
                              'hoya'  : 0x80000000,
                              #'wildcat'  : 0x80000000,
                          },
    },

    {   # Certain system data is stored in OCIMEM
        'display_name'  : "OCIMEM",
        'name'          : {'OCIMEM.BIN','ocimem_0x14680000--0x146aafff.lst','ocimem_0x14680000--0x146bffff.lst'},
        'ext'           : {'.BIN', '.LST'},
        'basename'      : {'OCIMEM', 'ocimem_0x14680000--0x146aafff','ocimem_0x14680000--0x146bffff'},
        'no_load'       : True,
        'path'          : "",
        'base'          : {
                              'hoya'  :{ '670': 0x14680000,
                                         '24': 0x14680000,
                                         '6150': 0x14680000,
                                         '7150': 0x14680000,
                                         '845': 0x14680000,
                                         '855': 0x14680000,
										 '8250': 0x14680000,
                                         'lahaina': 0x14680000,
										 'cedros': 0x14680000,
										 'Saipan': 0x14680000,
                                         '1000': 0x14680000,
                                         '55'  : 0x14680000,
                                         'Olympic'  : 0x14680000,
                                         'waipio': 0x14680000,
                                         'fillmore': 0x14680000,
                                         'kailua': 0x14680000,
                                         },
                              #'wildcat'  :{ 'waipio': 0x14680000,
                              #           },
                          },
        'data'          : {
                              'dumptable' : {
                                                '670'   : 0x146BF000 + 0x10,
                                                '6150'   : 0x146AA000 + 0x10,
                                                '7150'   : 0x146AA000 + 0x10,
												'8250'   : 0x146BF000 + 0x10,
                                                'lahaina'   : 0x146BF000 + 0x10,
												'cedros'   : 0x146AA000 + 0x10,
												'Saipan'   : 0x146AB000 + 0x10,
                                                '855'   : 0x146BF000 + 0x10,
                                                '845'   : 0x146BF000 + 0x10,
                                                '1000'   : 0x146BF000 + 0x10,
                                                '24'   : 0x1468B000 + 0x10,
                                                '55'   : 0x1468F000 + 0x10,
                                                'Olympic'   : 0x1468F000 + 0x10,
                                                'waipio'   : 0x146AA000 + 0x10,
                                                'fillmore'   : 0x146AA000 + 0x10,  #this should be diff, as IMEM for fillmore changed? https://ipcatalog.qualcomm.com/memmap/chip/414/map/1323
                                                'kailua'   : 0x146AA000 + 0x10,
                                            },
                          },
    },
    {   # Certain system data is stored in md_SHRDIMEM
        'display_name'  : "md_SHRDIMEM",
        'name'          : {'md_SHRDIMEM.BIN'},
        'ext'           : {'.BIN', '.LST'},
        'basename'      : {'md_SHRDIMEM'},
        'no_load'       : True,
        'path'          : "",
        'base'          : {
                              'hoya'  :{ 'waipio': 0x146aa000,
                                         'fillmore': 0x146aa000,
                                         'aurora' : 0x146aa000,
                                         'kailua' : 0x146aa000,
                                         },
                              #'wildcat'  :{ 'waipio': 0x14680000,
                              #           },
                          },
        'data'          : {
                              'dumptable' : {
                                                'waipio'   : 0x146aa000 + 0x10,
                                                'fillmore' : 0x146AA000 + 0x10,
                                                'aurora'   : 0x146AA000 + 0x10,
                                                'kailua'   : 0x146AA000 + 0x10,
                                            },
                          },
    },
    {   # Heap is copied to DDR before overwritting
        'display_name'  : "md_MEMDUMP",
        'name'          : {'md_MEMDUMP.BIN'},
        'ext'           : {'.BIN', '.LST'},
        'basename'      : {'md_MEMDUMP.BIN'},
        'no_load'       : True,
        'path'          : "",
        'size'          : 0x0,
        'update'        : True,
        'base'          : {
                              'hoya'  : {  #Size      : base address
                                            0x80000000 : 0x80000000,
                                            0x10000000 : 0x80000000,
                                            0x20000000 : 0x80000000,
                                            0x2F8D000 : 0x9B9000000,
                                         },       
                          },
    },
    {   # Heap is copied to DDR before overwritting
        'display_name'  : "DDRCS0_0",
        'name'          : {'DDRCS0_0.BIN','DDRCS0.BIN','dram_cs0_0x80000000--0xffffffff.lst'},
        'ext'           : {'.BIN', '.LST'},
        'basename'      : {'DDRCS0_0', 'DDRCS0','dram_cs0_0x80000000--0xffffffff'},
        'no_load'       : True,
        'path'          : "",
        'size'          : 0x0,
        'update'        : True,
        'base'          : {
                              'hoya'  : {  #Size      : base address
                                            0x80000000 : 0x80000000,
                                            0x10000000 : 0x80000000,
                                            0x20000000 : 0x80000000,
                                         },
                              #'wildcat'  : {  #Size      : base address
                               #             0x80000000 : 0x80000000,
                                #            0x10000000 : 0x80000000,
                                 #           0x20000000 : 0x80000000,
                                  #       },
                          },
    },
    {   # Heap is copied to DDR before overwritting
        'display_name'  : "DDRCS0_1",
        'name'          : {'DDRCS0_1.BIN','dram_cs0_0x100000000--0x17fffffff.lst','dram_cs0_0x100000000--0x13fffffff.lst'},
        'ext'           : {'.BIN', '.LST'},
        'basename'      : {'DDRCS0_1', 'dram_cs0_0x100000000--0x17fffffff','dram_cs0_0x100000000--0x13fffffff'},
        'no_load'       : True,
        'path'          : "",
        'update'        : True,
        'size'          : 0x0,
        'base'          : {
                              'hoya'  : {  #Size      : base address
                                            0x40000000 : 0x100000000,
                                            0x80000000 : 0x100000000,
                                         },
                              #'wildcat'  : {  #Size      : base address
                                #            0x40000000 : 0x100000000,
                                 #           0x80000000 : 0x100000000,
                                  #       },
                          },
    },
    {   # Heap is copied to DDR before overwritting
        'display_name'  : "DDRCS1_0",
        'name'          : {'DDRCS1_0.BIN','dram_cs1_0x140000000--0x1bfffffff.lst','dram_cs1_0x180000000--0x1ffffffff.lst', 'dram_cs1_0x200000000--0x27fffffff.lst','dram_cs1_0x800000000--0x87fffffff.lst'},
        'ext'           : {'.BIN', '.LST'},
        'basename'      : {'DDRCS1_0', 'dram_cs1_0x140000000--0x1bfffffff','dram_cs1_0x180000000--0x1ffffffff', 'dram_cs1_0x200000000--0x27fffffff','dram_cs1_0x800000000--0x87fffffff'},
        'no_load'       : True,
        'path'          : "",
        'update'        : True,
        'size'          : 0x0,
        'base'          : {
                              'hoya'  : {  #Size      : base address
                                            0x80000000 : 0x800000000,
                                         },
                              #'wildcat'  : {  #Size      : base address
                               #             0x80000000 : 0x100000000,
                                #         },
                          },
    },
    {   # Heap is copied to DDR before overwritting
        'display_name'  : "DDRCS1_1",
        'name'          : {'DDRCS1_1.BIN','dram_cs1_0x1c0000000--0x1ffffffff.lst','dram_cs1_0x280000000--0x2ffffffff.lst','dram_cs1_0x880000000--0x8ffffffff.lst'},
        'ext'           : {'.BIN', '.LST'},
        'basename'      : {'DDRCS1_1', 'dram_cs1_0x1c0000000--0x1ffffffff','dram_cs1_0x280000000--0x2ffffffff','dram_cs1_0x880000000--0x8ffffffff'},
        'no_load'       : True,
        'path'          : "",
        'update'        : True,
        'size'          : 0x0,
        'base'          : {
                              'hoya'  : {  #Size      : base address
                                            0x80000000 : 0x880000000,
                                         },
                              #'wildcat'  : {  #Size      : base address
                               #             0x80000000 : 0x180000000,
                                #         },
                          },
    },
    {   # Heap is copied to DDR before overwritting
        'display_name'  : "DDRCS1_2",
        'name'          : {'DDRCS1_2.BIN','dram_cs1_0x1c0000000--0x1ffffffff.lst','dram_cs1_0x280000000--0x2ffffffff.lst','dram_cs1_0x900000000--0x97fffffff.lst'},
        'ext'           : {'.BIN', '.LST'},
        'basename'      : {'DDRCS1_2', 'dram_cs1_0x1c0000000--0x1ffffffff','dram_cs1_0x280000000--0x2ffffffff','dram_cs1_0x900000000--0x97fffffff'},
        'no_load'       : True,
        'path'          : "",
        'update'        : True,
        'size'          : 0x0,
        'base'          : {
                              'hoya'  : {  #Size      : base address
                                            0x80000000 : 0x900000000,
                                         },
                              #'wildcat'  : {  #Size      : base address
                               #             0x80000000 : 0x180000000,
                                #         },
                          },
    },
    {   # Heap is copied to DDR before overwritting
        'display_name'  : "DDRCS2_0",
        'name'          : {'DDRCS2_0.BIN','dram_cs1_0x1c0000000--0x1ffffffff.lst','dram_cs1_0x280000000--0x2ffffffff.lst'},
        'ext'           : {'.BIN', '.LST'},
        'basename'      : {'DDRCS2_0', 'dram_cs1_0x1c0000000--0x1ffffffff','dram_cs1_0x280000000--0x2ffffffff'},
        'no_load'       : True,
        'path'          : "",
        'update'        : True,
        'size'          : 0x0,
        'base'          : {
                              'hoya'  : {  #Size      : base address
                                            0x80000000 : 0x900000000,
                                         },
                              #'wildcat'  : {  #Size      : base address
                               #             0x80000000 : 0x180000000,
                                #         },
                          },
    },
    {   # Heap is copied to DDR before overwritting
        'display_name'  : "DDRCS2_1",
        'name'          : {'DDRCS2_1.BIN','dram_cs1_0x1c0000000--0x1ffffffff.lst','dram_cs1_0x280000000--0x2ffffffff.lst'},
        'ext'           : {'.BIN', '.LST'},
        'basename'      : {'DDRCS2_1', 'dram_cs1_0x1c0000000--0x1ffffffff','dram_cs1_0x280000000--0x2ffffffff'},
        'no_load'       : True,
        'path'          : "",
        'update'        : True,
        'size'          : 0x0,
        'base'          : {
                              'hoya'  : {  #Size      : base address
                                            0x80000000 : 0x980000000,
                                         },
                              #'wildcat'  : {  #Size      : base address
                               #             0x80000000 : 0x180000000,
                                #         },
                          },
    },    
    {   # Heap is copied to DDR before overwritting
        'display_name'  : "DDRCS2_2",
        'name'          : {'DDRCS2_2.BIN','dram_cs1_0x1c0000000--0x1ffffffff.lst','dram_cs1_0x280000000--0x2ffffffff.lst'},
        'ext'           : {'.BIN', '.LST'},
        'basename'      : {'DDRCS2_2', 'dram_cs1_0x1c0000000--0x1ffffffff','dram_cs1_0x280000000--0x2ffffffff'},
        'no_load'       : True,
        'path'          : "",
        'update'        : True,
        'size'          : 0x0,
        'base'          : {
                              'hoya'  : {  #Size      : base address
                                            0x80000000 : 0xa00000000,
                                         },
                              #'wildcat'  : {  #Size      : base address
                               #             0x80000000 : 0x180000000,
                                #         },
                          },
    },     
    {   # The place all of the data lives
        'display_name'  : "CMD_DB_BINARY",
        'name'          : {'CMD_DB_BINARY.BIN'},
        'ext'           : {'.BIN','.LST'},
        'basename'      : {'CMD_DB_BINARY'},
        'required'      : False,
        'no_load'       : False,
        'size'          : 0x20000,
        'base'          : {
                              'hoya'  :  0x80860000,
                              #'wildcat'  :  0x80860000,
                          },
    },
]

known_targets = {
    '55'   : 'hoya',
    '670'  : 'hoya',
    '855'  : 'hoya',
    '24'   : 'hoya',
    '1000' : 'hoya',
    '6150'  : 'hoya',
    '7150'  : 'hoya',
    '845'  : 'hoya',
	'8250'  : 'hoya',
    'lahaina'  : 'hoya',
	'cedros'  : 'hoya',
	'Saipan'  : 'hoya',
    'Olympic'  : 'hoya',
    'waipio'  : 'hoya',
    'fillmore'  : 'hoya',
	'kailua'  : 'hoya',

}

known_families = {
    'hoya'        : 'hoya',
    'wildcat'        : 'hoya',

}

default_target_family = {
    'target'        : '670',
    'family'        : 'hoya',
    'family_name'   : 'Hoya',
    'branch'        : 'AOP.HO.1.0',
}

dumptable_version_map = {
    '55'     : '1.4',
    '670'    : '1.4',
    '855'    : '1.4',
	'8250'    : '1.4',
    'lahaina'    : '1.4',
	'cedros'    : '1.4',
	'Saipan'    : '1.4',
    '24'     : '1.4',
    '1000'   : '1.4',
    '6150'    : '1.4',
    '7150'    : '1.4',
    '845'    : '1.4',
    'Olympic'    : '1.4',
    'waipio'    : '1.4',
    'fillmore'    : '1.4',
	'kailua'    : '1.4',
    'default' : '	1.4',
}

dumptable_config = {
    '1.4' :  {
                'version' : 0x200000,
                'data'    : {
                              'size'        : 0x3C,
                              'version'     : 0x0,
                              'magic'       : 0x4,
                              'magic_value' : 0x0, #need to actually figure this one out
                              'name'        : 0x8,
                              'name_size'   : 0x20,
                              'addr'        : 0x28,
                              'len'         : 0x30,
                              'reserved'    : 0x38,
                            },
                'entry'   : {
                              'size'        : 0x30,
                              'id'          : 0x0,
                              'name'        : 0x4,
                              'name_size'   : 0x20,
                              'type'        : 0x24,
                              'addr'        : 0x28,
                            },
                'table'   : {
                              'size'        : 0x30,
                              'version'     : 0x0,
                              'num_entries' : 0x4,
                              'entries'     : 0x8,
                            },
              },
}

rpmhdump_config = {
	0x11: {
					'blockdump_type': {
										'size' 			:0x1008,
										'count'			:0x0,
										'block_region'	:0x8,
										'block_size'    :0x20,
										'data'			:0x1008,
										'no_data_blocks':0x80,
										},
					'region_type'	: {
										'size'		:0x20,
										'start_addr':0x0,
										'end_addr'	:0x8,
										'data_size'	:0x10,
										'offset'	:0x18,
										},
	},
	0x12: {
					'blockdump_type': {
										'size' 			:0x1408,
										'count'			:0x0,
										'block_region'	:0x8,
										'block_size'    :0x20,
										'data'			:0x1408,
										'no_data_blocks':0xA0,
										},
					'region_type'	: {
										'size'		:0x20,
										'start_addr':0x0,
										'end_addr'	:0x8,
										'data_size'	:0x10,
										'offset'	:0x18,
										},
	},
	0x13: {
					'blockdump_type': {
										'size' 			:0x1F48,
										'count'			:0x0,
										'block_region'	:0x8,
										'block_size'    :0x20,
										'data'			:0x1F48,
										'no_data_blocks':0xFA,
										},
					'region_type'	: {
										'size'		:0x20,
										'start_addr':0x0,
										'end_addr'	:0x8,
										'data_size'	:0x10,
										'offset'	:0x18,
										},
	}

}
