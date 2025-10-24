/*
 * Copyright (c) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */
#ifndef FCS_ENDIAN_H_
#define FCS_ENDIAN_H_

/**
 * @defgroup endian Endian-related conversions
 * @ingroup conversions
 * @{
 * @brief Macros for endian-related conversions.
 * @file fcs_endian.h
 * @ingroup conversions
 */

#include <stdint.h>

/**
 * Takes two bytes as input and creates an uint16 as output. The storage of
 * the integer will be handled by the compiler so the function works on both
 * Little and Big Endian machines.
 * Input:  l = 0x0B
 *         h = 0x0A
 * Output: 0x0A0B
 *
 * @brief Creates a uint32 based on the input bytes.
 *
 * @param l     The least significant byte
 * @param h     The most significant byte
 */
static inline uint16_t bytes_to_uint16(uint8_t l, uint8_t h)
{
	return (uint16_t)l | ((uint16_t)h << 8);
}

/**
 * Takes four bytes as input and creates a uint32 as output. The storage of
 * the integer will be handled by the compiler so the function works on both
 * Little and Big Endian machines.
 * Input:  l  = 0x0D
 *         ml = 0x0C
 *         mh = 0x0B
 *         h  = 0x0A
 * Output: 0x0A0B0C0D
 *
 * @brief Creates a uint32 based on the input bytes
 *
 * @param l     The least significant byte
 * @param ml    The second least significant byte
 * @param mh    The second most significant byte
 * @param h     The most significant byte
 */
static inline uint32_t bytes_to_uint32(
	uint8_t l, uint8_t ml,
	uint8_t mh, uint8_t h)
{
	return (uint32_t)l | ((uint32_t)ml << 8) |
	       ((uint32_t)mh << 16) | ((uint32_t)h << 24);
}

/**
 * Takes eight bytes as input and creates a uint64 as output. The storage of
 * the integer will be handled by the compiler so the function works on both
 * Little and Big Endian machines.
 * Input:  ll  = 0x0F
 *         mll = 0x0E
 *         mlh = 0x0D
 *         lh  = 0x0C
 *         hl  = 0x0B
 *         mhl = 0x0A
 *         mhh = 0x09
 *         hh  = 0x08
 * Output: 0x08090A0B0C0D0E0F
 *
 * @brief Creates a uint64 based on the input bytes
 *
 * @param ll     The least significant byte (low word)
 * @param mll    The second least significant byte (low word)
 * @param mlh    The second most significant byte (low word)
 * @param lh     The most significant byte (low word)
 * @param hl     The least significant byte (high word)
 * @param mhl    The second least significant byte (high word)
 * @param mhh    The second most significant byte (high word)
 * @param hh     The most significant byte (high word)
 */
static inline uint64_t bytes_to_uint64(
	uint8_t ll, uint8_t mll,
	uint8_t mlh, uint8_t lh,
	uint8_t hl, uint8_t mhl,
	uint8_t mhh, uint8_t hh)
{
	return ((uint64_t)ll          | ((uint64_t)mll << 8)  |
		((uint64_t)mlh << 16) | ((uint64_t)lh << 24)  |
		((uint64_t)hl << 32)  | ((uint64_t)mhl << 40) |
		((uint64_t)mhh << 48) | ((uint64_t)hh << 56));
}

/**
 * @brief Read 16 unsigned bits from memory stored in little endian format to
 *        machine native representation
 */
static inline uint16_t read_le_u16(uint8_t *p)
{
	return bytes_to_uint16(p[0], p[1]);
}

/**
 * @brief Read 32 unsigned bits from memory stored in little endian format to
 *        machine native representation
 */
static inline uint32_t read_le_u32(uint8_t *p)
{
	return bytes_to_uint32(p[0], p[1], p[2], p[3]);
}

/**
 * @brief Read 64 unsigned bits from memory stored in little endian format to
 *        machine native representation
 */
static inline uint64_t read_le_u64(uint8_t *p)
{
	return bytes_to_uint64(p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7]);
}

/**
 * @brief Read 16 unsigned bits from memory stored in big endian format to
 *        machine native representation
 */
static inline uint16_t read_be_u16(uint8_t *p)
{
	return bytes_to_uint16(p[1], p[0]);
}

/**
 * @brief Read 32 unsigned bits from memory stored in big endian format to
 *        machine native representation
 */
static inline uint32_t read_be_u32(uint8_t *p)
{
	return bytes_to_uint32(p[3], p[2], p[1], p[0]);
}

/**
 * @brief Read 64 unsigned bits from memory stored in big endian format to
 *        machine native representation
 */
static inline uint64_t read_be_u64(uint8_t *p)
{
	return bytes_to_uint64(p[7], p[6], p[5], p[4], p[3], p[2], p[1], p[0]);
}

/**
 * @brief Write 16 unsigned bits to memory in little endian format from machine
 *        native representation
 */
static inline void write_le_u16(uint_fast16_t d, uint8_t *p)
{
	p[0] = d & 0xFF;
	p[1] = (d >> 8) & 0xFF;
}

/**
 * @brief Write 32 unsigned bits to memory in little endian format from machine
 *        native representation
 */
static inline void write_le_u32(uint_fast32_t d, uint8_t *p)
{
	p[0] = d & 0xFF;
	p[1] = (d >> 8) & 0xFF;
	p[2] = (d >> 16) & 0xFF;
	p[3] = (d >> 24) & 0xFF;
}

/**
 * @brief Write 64 unsigned bits to memory in little endian format from machine
 *        native representation
 */
static inline void write_le_u64(uint_fast64_t d, uint8_t *p)
{
	p[0] = d & 0xFF;
	p[1] = (d >> 8) & 0xFF;
	p[2] = (d >> 16) & 0xFF;
	p[3] = (d >> 24) & 0xFF;
	p[4] = (d >> 32) & 0xFF;
	p[5] = (d >> 40) & 0xFF;
	p[6] = (d >> 48) & 0xFF;
	p[7] = (d >> 56) & 0xFF;
}

/**
 * @brief Write 16 unsigned bits to memory in big endian format from machine
 *        native representation
 */
static inline void write_be_u16(uint_fast16_t d, uint8_t *p)
{
	p[1] = d & 0xFF;
	p[0] = (d >> 8) & 0xFF;
}

/**
 * @brief Write 32 unsigned bits to memory in big endian format from machine
 *        native representation
 */
static inline void write_be_u32(uint_fast32_t d, uint8_t *p)
{
	p[3] = d & 0xFF;
	p[2] = (d >> 8) & 0xFF;
	p[1] = (d >> 16) & 0xFF;
	p[0] = (d >> 24) & 0xFF;
}

/**
 * @brief Write 64 unsigned bits to memory in big endian format from machine
 *        native representation
 */
static inline void write_be_u64(uint_fast64_t d, uint8_t *p)
{
	p[7] = d & 0xFF;
	p[6] = (d >> 8) & 0xFF;
	p[5] = (d >> 16) & 0xFF;
	p[4] = (d >> 24) & 0xFF;
	p[3] = (d >> 32) & 0xFF;
	p[2] = (d >> 40) & 0xFF;
	p[1] = (d >> 48) & 0xFF;
	p[0] = (d >> 56) & 0xFF;
}
/** @}*/
#endif /* FCS_ENDIAN_H_ */

