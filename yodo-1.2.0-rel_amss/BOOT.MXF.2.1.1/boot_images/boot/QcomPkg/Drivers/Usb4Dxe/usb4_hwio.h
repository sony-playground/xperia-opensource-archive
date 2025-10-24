#ifndef __USB4_HWIO_H__
#define __USB4_HWIO_H__
/*
===========================================================================
*/
/*
    ===========================================================================

    Copyright (c) 2020 Qualcomm Technologies Incorporated.
    All Rights Reserved.
    Qualcomm Confidential and Proprietary

    Export of this technology or software is regulated by the U.S. Government.
    Diversion contrary to U.S. law prohibited.

    All ideas, data and information contained in or disclosed by
    this document are confidential and proprietary information of
    Qualcomm Technologies, Inc. and all rights therein are expressly reserved.
    By accepting this material the recipient agrees that this material
    and the information contained therein are held in confidence and in
    trust and will not be used, copied, reproduced in whole or in part,
    nor its contents revealed in any manner to others without the express
    written permission of Qualcomm Technologies, Inc.

    ===========================================================================

    $Header: //components/rel/core.boot/6.1.1/QcomPkg/Drivers/Usb4Dxe/usb4_hwio.h#1 $
    $DateTime: 2022/08/18 10:15:46 $
    $Author: pwbldsvc $

    ===========================================================================
*/

#define out_dword_usb(addr, val)  \
  out_dword(addr, val);           \
  Usb4Log2(USB4_LOG_REG, Usb4Reg_Addr_Val, 0, (uint32)addr, (uint32)val)
  
#define out_dword_masked_ns_usb(io, mask, val, current_reg_content)  \
  out_dword_masked_ns(io, mask, val, current_reg_content);           \
  Usb4Log2(USB4_LOG_REG, Usb4Reg_Addr_Val, 0, (uint32)io, ((current_reg_content & (uint32)(~(mask))) | \
                 ((uint32)((val) & (mask)))))

#if 0 // TODO: AC porting
#define USB4_HWIO_POR(hwiosym) __usb4hwio_por(hwiosym)
#define USB4_HWIO_MAXn(hwiosym) __usb4hwio_maxn(hwiosym)
#define USB4_HWIO_MAXr(hwiosym) __usb4hwio_maxr(hwiosym)
#define USB4_HWIO_2FMSK(io, f1, f2) __usb4hwio_2fmsk(io, f1, f2)
#endif // TODO: AC porting

/**
* @brief Takes a numerical value and will shift and mask the
*        field value from the numberical value
* @code UFS_HWIO_FVAL_FROM_RVAL(REG, FLD_BIT8, 0x300) -> 0x1
*/
#define USB4_HWIO_FVAL_FROM_RVAL(io, field, rval) __usb4_hwio_fval_from_rval(io, field, rval)


#if 0 // TODO: AC porting
#define __usb4hwio_por(hwiosym) HWIO_##hwiosym##_POR
#define __usb4hwio_maxr(hwiosym) HWIO_##hwiosym##_MAXr
#define __usb4hwio_maxn(hwiosym) HWIO_##hwiosym##_MAXn
#endif // TODO: AC porting

#define __usb4hwio_2fmsk(io, f1, f2) (HWIO_FMSK(io, f1) | HWIO_FMSK(io, f2))

#define __usb4_hwio_fval_from_rval(io, field, rval) \
	((rval & HWIO_FMSK(io, field)) >> HWIO_SHFT(io, field))

#if 0 // TODO: AC porting
#if !defined(HWIO_OUTXF2) && defined(HWIO_OUTX2F)
    #define HWIO_OUTXF2 HWIO_OUTX2F
#endif /* HWIO_OUTXF2 && HWIO_OUTX2F */

#if !defined(HWIO_OUTXF3) && defined(HWIO_OUTX3F)
    #define HWIO_OUTXF3 HWIO_OUTX3F
#endif /* HWIO_OUTXF3 && HWIO_OUTX3F */
#endif // TODO: AC porting

#endif /* __USB4_HWIO_H__ */

