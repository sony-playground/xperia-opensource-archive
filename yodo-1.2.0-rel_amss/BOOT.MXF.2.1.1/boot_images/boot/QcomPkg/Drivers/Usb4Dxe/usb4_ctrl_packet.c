/**---------------------------------------------------------------------------
 *   @file        usb4_ctrl_packet.cpp
 *
 *   @brief   
 *
 *   Copyright (c) 2019-2020 Qualcomm Technologies Incorporated.
 *   All Rights Reserved.
 *   Qualcomm Confidential and Proprietary
 *--------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------
 * Includes
 *--------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------
 * Macros / Types
 *--------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------
 * Static Variables
 *--------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------
 * Global Variables
 *--------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------
 * Static Functions
 *--------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------
 * Global Functions
 *--------------------------------------------------------------------------*/

// #include "comdef.h"
#include <string.h>
#include <Usb4Utils.h>
#include <Usb4Log.h>

#include "usb4_mem.h"
#include "usb4_ctrl_packet.h"
// #include <string.h>


void Usb4CtrlPacketInit(usb4_control_packet_ctx_t *control_packet_ctx)
{
  control_packet_ctx->m_CRC = 0;
  control_packet_ctx->m_packetData = 0;
  control_packet_ctx->m_packetDataLength = 0;
  control_packet_ctx->m_PDF = 0;
  control_packet_ctx->m_prefixLength = 0;
  control_packet_ctx->m_prefix = (UINT8*)(&control_packet_ctx->m_controlPacket);

  usb4_mem_memset((void*)(&control_packet_ctx->m_controlPacket), 0, sizeof(control_packet_ctx->m_controlPacket));
  control_packet_ctx->m_packetData = NULL;
  control_packet_ctx->m_packetDataLength = 0;
  control_packet_ctx->m_CRC = 0;
  control_packet_ctx->m_PDF = 0;
  control_packet_ctx->m_prefixLength = 0;
}

usb4_control_packet_t* Usb4CtrlPacketGetControlPacket(usb4_control_packet_ctx_t *control_packet_ctx)
{
  return &control_packet_ctx->m_controlPacket;
}

int Usb4CtrlPacketAssignPDF(usb4_control_packet_ctx_t *control_packet_ctx, UINT32 PDF)
{
  switch(PDF)
  {
    case 1:
      control_packet_ctx->m_prefixLength = 12;
      break;
    case 2:
      control_packet_ctx->m_prefixLength = 12;
      break;
    case 3:
      control_packet_ctx->m_prefixLength = 12;
      break;
    case 4:
      control_packet_ctx->m_prefixLength = 8;
      break;
    case 5:
      control_packet_ctx->m_prefixLength = 12;
      break;
    case 6:
      control_packet_ctx->m_prefixLength = 32;
      break;
    case 7:
      control_packet_ctx->m_prefixLength = 32;
      break;
    default:
      USB4_ASSERT_MSG(0,"Wrong PDF");
  }

  control_packet_ctx->m_PDF = PDF;
  return 0;
}

UINT32 Usb4CtrlPacketGetPDF(usb4_control_packet_ctx_t *control_packet_ctx)
{
  return control_packet_ctx->m_PDF;
}

UINT32 Usb4CtrlPacketGetCRC(usb4_control_packet_ctx_t *control_packet_ctx)
{
  return control_packet_ctx->m_CRC;
}

/** @bried swap UINT32 bytes between be and le  */
#define byteswap_UINT32(x) \
     ((((x) & 0xFF000000) >> 24) | (((x) & 0x00FF0000) >>  8) |                      \
      (((x) & 0x0000FF00) <<  8) | (((x) & 0x000000FF) << 24))

/** 
 * @brief in case #USB4_CP_LE_ENABLED is not defined, it will swap the buffer
 *        from LE to BE or vice Versa
 * @param [in/out] pBuff buffer to swap its endianess
 * @param [in] num_bytes buffer length in bytes, must be dword aligned
 * @return 0 on success, other on failure
 */
static inline int Usb4CtrlPacketswap_le32_be32_buff(UINT8* pBuff, UINT32 num_bytes)
{
#if !defined(USB4_CP_LE_ENABLED)
  UINT32 num_dwords;
  UINT32* dwords;
  UINT32 lower_addr = USB4_LOWER32(pBuff);
  if (0 != (num_bytes & 0x3))
  {
    // USB4_LOG_INFO( "Data length is not sizeof(UINT32) expect EER_LEN");
    Usb4Log(USB4_LOG_CM, DataLengthIsNotSizeofUINT32expectEERLEN__Info, 0);
  }
  USB4_ASSERT_MSG(0 == (lower_addr & 0x3), "Address is not UINT32 aligned");

  num_dwords = num_bytes >> 2;
  dwords = (UINT32*)(pBuff);
  for (UINT32 i = 0; i < num_dwords; ++i)
  {
    dwords[i] = byteswap_UINT32(dwords[i]);
  }
  return 0;

#else /* USB4_CP_LE_ENABLED */
  (void) pBuff;
  (void) num_bytes;
  return 0;
#endif /* USB4_CP_LE_ENABLED */
}

int Usb4CtrlPacketCopyPacketToBuffer(usb4_control_packet_ctx_t *control_packet_ctx, UINT8* dataBuffer, UINT32* pDataLength)
{
  UINT32* pCrc = NULL;

  USB4_ASSERT(NULL != pDataLength);
  USB4_ASSERT(control_packet_ctx->m_prefixLength >= 8); /* Sanity */
  USB4_ASSERT(control_packet_ctx->m_PDF >= 1); /* Sanity */
  USB4_ASSERT(*pDataLength >= (control_packet_ctx->m_prefixLength + control_packet_ctx->m_packetDataLength + sizeof(control_packet_ctx->m_CRC)));

  usb4_mem_memcpy(dataBuffer, control_packet_ctx->m_prefix, control_packet_ctx->m_prefixLength);
  if (control_packet_ctx->m_packetDataLength > 0)
  {
    usb4_mem_memcpy(dataBuffer+control_packet_ctx->m_prefixLength, control_packet_ctx->m_packetData, control_packet_ctx->m_packetDataLength);
  }

  Usb4CtrlPacketCalculateCRC(control_packet_ctx, dataBuffer, control_packet_ctx->m_prefixLength + control_packet_ctx->m_packetDataLength);

  // Update CRC
  pCrc = (UINT32*)(dataBuffer + control_packet_ctx->m_prefixLength +
      control_packet_ctx->m_packetDataLength);
  *pCrc = control_packet_ctx->m_CRC;

  // output the data length
  *pDataLength = control_packet_ctx->m_prefixLength + control_packet_ctx->m_packetDataLength + sizeof(control_packet_ctx->m_CRC);

  // TODO it will be more efficient if we change endianess not on a DMA buff
  //      since DMA buff is usually not cachable, however for now this will
  //      do the trick
  USB4_ASSERT(0 == Usb4CtrlPacketswap_le32_be32_buff(dataBuffer, *pDataLength));

  return 0;
}

int Usb4CtrlPacketReferenceBufferToPacket(usb4_control_packet_ctx_t *control_packet_ctx, UINT8* dataBuffer, UINT32 dataLength, UINT32 EOF_PDF)
{
  UINT32 bufferCRC;
  UINT32 length_bytes;
  USB4_ASSERT(0 == Usb4CtrlPacketAssignPDF(control_packet_ctx, EOF_PDF));

  // TODO it will be more efficient if we change endianess not on a DMA buff
  //      since DMA buff is usually not cachable, however for now this will
  //      do the trick
  USB4_ASSERT(0 == Usb4CtrlPacketswap_le32_be32_buff(dataBuffer, dataLength));

  length_bytes = MIN(control_packet_ctx->m_prefixLength, dataLength);
  usb4_mem_memcpy(control_packet_ctx->m_prefix, dataBuffer, length_bytes);


  USB4_ASSERT(dataLength >= (control_packet_ctx->m_prefixLength + sizeof(control_packet_ctx->m_CRC)));
  bufferCRC = *((UINT32*)(dataBuffer + dataLength - sizeof(control_packet_ctx->m_CRC)));
  Usb4CtrlPacketCalculateCRC(control_packet_ctx, dataBuffer, dataLength - sizeof(control_packet_ctx->m_CRC));
  //USB4_ASSERT_MSG(bufferCRC == control_packet_ctx->m_CRC, "Received packet CRC doesn't match calculated value")
  if (bufferCRC != control_packet_ctx->m_CRC)
  {
    // USB4_LOG_WARNING("Received packet CRC doesn't match calculated value\n");
    Usb4Log(USB4_LOG_CM, Usb4CtrlPacketReferenceBufferToPacketReceivedPacketCRCdoesnotMatchCalculatedValue__Warn, 0);
  }

  if (dataLength > control_packet_ctx->m_prefixLength)
  {
    control_packet_ctx->m_packetData = dataBuffer + control_packet_ctx->m_prefixLength;
    control_packet_ctx->m_packetDataLength = dataLength - control_packet_ctx->m_prefixLength - sizeof(control_packet_ctx->m_CRC);
  }
  else
  {
    control_packet_ctx->m_packetData = NULL;
    control_packet_ctx->m_packetDataLength = 0;
  }
  return 0;
}

UINT32 Usb4CtrlPacketReflect(UINT32 crc, int bitnum)
{
  /*  */
  UINT32 i, j=1, crcout=0;

  for (i=(UINT32)1<<(bitnum-1); i; i>>=1) {
    if (crc & i) crcout|=j;
    j<<= 1;
  }
  return (crcout);
}

//http://www.zorc.breitbandkatze.de/crc.html
void Usb4CtrlPacketCalculateCRC(usb4_control_packet_ctx_t *control_packet_ctx, UINT8* p, UINT32 len)
{
  const int order = 32;
  const UINT32 polynom = 0x1EDC6F41;
  const UINT32 crcinit = 0xffffffff;
  const UINT32 crcxor = 0xffffffff;
  const int refin = 1;
  const int refout = 1;
  UINT32 i, j, c, bit;
  control_packet_ctx->m_CRC = crcinit;
  UINT32 crcmask, crchighbit;

  // fast bit by bit algorithm without augmented zero bytes.
  // does not use lookup table, suited for polynom orders between 1...32.
  crcmask = ((((unsigned long)1<<(order-1))-1)<<1)|1;
  crchighbit = (unsigned long)1<<(order-1);

  for (i=0; i<len; i++) {

    c = p[(3-i%4)+(i/4)*4]; /* Reverse byte order in DWORDS */
    //c = (unsigned long)(*p++);

    if (refin) c = Usb4CtrlPacketReflect(c, 8);

    for (j=0x80; j; j>>=1) {

      bit = control_packet_ctx->m_CRC & crchighbit;
      control_packet_ctx->m_CRC<<= 1;
      if (c & j) bit^= crchighbit;
      if (bit) control_packet_ctx->m_CRC^= polynom;
    }
  }

  if (refout) control_packet_ctx->m_CRC = Usb4CtrlPacketReflect(control_packet_ctx->m_CRC, order);
  control_packet_ctx->m_CRC ^= crcxor;
  control_packet_ctx->m_CRC &= crcmask;
}

// usb4_ctrl_packet& operator= (const usb4_ctrl_packet &pckt)
usb4_control_packet_ctx_t* Usb4CtrlPacketSet(usb4_control_packet_ctx_t *control_packet_ctx, const usb4_control_packet_ctx_t *pckt)
{
  if (control_packet_ctx != pckt)
  {
    control_packet_ctx->m_CRC = pckt->m_CRC;
    usb4_mem_memcpy(control_packet_ctx->m_prefix, pckt->m_prefix, pckt->m_prefixLength);
    control_packet_ctx->m_prefixLength = pckt->m_prefixLength;
    control_packet_ctx->m_packetData = pckt->m_packetData;
    control_packet_ctx->m_packetDataLength = pckt->m_packetDataLength;
    control_packet_ctx->m_PDF = pckt->m_PDF;
  }
  return control_packet_ctx;
}

// bool operator== (usb4_ctrl_packet& lhs, usb4_ctrl_packet& rhs)
BOOLEAN Usb4CtrlPacketIsPacketSame(usb4_control_packet_ctx_t* lhs, usb4_control_packet_ctx_t* rhs)
{
  if (Usb4CtrlPacketGetPDF(lhs) != Usb4CtrlPacketGetPDF(rhs)) return FALSE;
  if (Usb4CtrlPacketGetCRC(lhs) != Usb4CtrlPacketGetCRC(rhs)) return FALSE;
  if (lhs->m_prefixLength != rhs->m_prefixLength) return FALSE;
  if (0 != memcmp(lhs->m_prefix, rhs->m_prefix, rhs->m_prefixLength))return FALSE;
  if (lhs->m_packetDataLength != rhs->m_packetDataLength) return FALSE;
  if (0 != memcmp(lhs->m_packetData, rhs->m_packetData, rhs->m_packetDataLength)) return FALSE;
  return TRUE;
}

// bool operator!=(usb4_ctrl_packet& lhs, usb4_ctrl_packet& rhs)
BOOLEAN Usb4CtrlPacketIsPacketNotSame(usb4_control_packet_ctx_t* lhs, usb4_control_packet_ctx_t* rhs)
{
  // return !(lhs == rhs);
  return !(Usb4CtrlPacketIsPacketSame(lhs, rhs));
}
