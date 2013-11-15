/***************************************************************************//**
 * @file    iec60335_class_b_flash_test.c
 * @brief   c based test for internal FLASH
 *          POST and BIST internal FLASH test for all compiler
 * @author  Energy Micro AS
 * @version 1.0.0
 *******************************************************************************
 * @section License
 * <b>(C) Copyright 2010 Energy Micro AS, http://www.energymicro.com</b>
 *******************************************************************************
 *
 * This source code is the property of Energy Micro AS. The source and compiled
 * code may only be used on Energy Micro "EFM32" microcontrollers.
 *
 * This copyright notice may not be removed from the source code nor changed.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Energy Micro AS has no
 * obligation to support this Software. Energy Micro AS is providing the
 * Software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Energy Micro AS will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 ******************************************************************************/
#include "em_device.h"
#include "iec60335_class_b.h"

/*! @addtogroup IEC60335_FLASH_TEST
 * @{
 */

/*! @cond RealView */
#if     (defined (__CC_ARM))
/*------------------RealView Compiler -----------------*/
FlashCRC_t const IEC60335_Flash_CRC_REF __attribute__ ((at(FLASH_CRC_ADDR))) = ENTRY_FLASH_CRC;
/* FlashCRC_t const IEC60335_Flash_CRC_REF = ENTRY_FLASH_CRC; */
/*! @endcond */

#elif   (defined (__ICCARM__))
/*! @cond ICC */
/*------------------ ICC Compiler -------------------*/
#pragma section = "_CRC_area"
const FlashCRC_t IEC60335_Flash_CRC_REF @ "_CRC_area" = ENTRY_FLASH_CRC;
/*! @endcond */

#elif   (defined (__GNUC__))
/*! @cond GCC */
/*------------------ GNU Compiler ---------------------*/
const FlashCRC_t IEC60335_Flash_CRC_REF __attribute__ ((section("_CRC_area"))) = ENTRY_FLASH_CRC;
/*! @endcond */
#else
#error "iec60355_class_b_flash_test.c: undefined compiler"
#endif


/*! @cond StaticCRCTable */
#if (dynamic_CRC_table == 0)
/* ========================================================================
 * Table of CRC-32's of all single-byte values (made by make_crc_table)
 */

/* const table for CRC32 byte references */
static const uint32_t crc_table[256] = {
  0x00000000L, 0x77073096L, 0xee0e612cL, 0x990951baL, 0x076dc419L,
  0x706af48fL, 0xe963a535L, 0x9e6495a3L, 0x0edb8832L, 0x79dcb8a4L,
  0xe0d5e91eL, 0x97d2d988L, 0x09b64c2bL, 0x7eb17cbdL, 0xe7b82d07L,
  0x90bf1d91L, 0x1db71064L, 0x6ab020f2L, 0xf3b97148L, 0x84be41deL,
  0x1adad47dL, 0x6ddde4ebL, 0xf4d4b551L, 0x83d385c7L, 0x136c9856L,
  0x646ba8c0L, 0xfd62f97aL, 0x8a65c9ecL, 0x14015c4fL, 0x63066cd9L,
  0xfa0f3d63L, 0x8d080df5L, 0x3b6e20c8L, 0x4c69105eL, 0xd56041e4L,
  0xa2677172L, 0x3c03e4d1L, 0x4b04d447L, 0xd20d85fdL, 0xa50ab56bL,
  0x35b5a8faL, 0x42b2986cL, 0xdbbbc9d6L, 0xacbcf940L, 0x32d86ce3L,
  0x45df5c75L, 0xdcd60dcfL, 0xabd13d59L, 0x26d930acL, 0x51de003aL,
  0xc8d75180L, 0xbfd06116L, 0x21b4f4b5L, 0x56b3c423L, 0xcfba9599L,
  0xb8bda50fL, 0x2802b89eL, 0x5f058808L, 0xc60cd9b2L, 0xb10be924L,
  0x2f6f7c87L, 0x58684c11L, 0xc1611dabL, 0xb6662d3dL, 0x76dc4190L,
  0x01db7106L, 0x98d220bcL, 0xefd5102aL, 0x71b18589L, 0x06b6b51fL,
  0x9fbfe4a5L, 0xe8b8d433L, 0x7807c9a2L, 0x0f00f934L, 0x9609a88eL,
  0xe10e9818L, 0x7f6a0dbbL, 0x086d3d2dL, 0x91646c97L, 0xe6635c01L,
  0x6b6b51f4L, 0x1c6c6162L, 0x856530d8L, 0xf262004eL, 0x6c0695edL,
  0x1b01a57bL, 0x8208f4c1L, 0xf50fc457L, 0x65b0d9c6L, 0x12b7e950L,
  0x8bbeb8eaL, 0xfcb9887cL, 0x62dd1ddfL, 0x15da2d49L, 0x8cd37cf3L,
  0xfbd44c65L, 0x4db26158L, 0x3ab551ceL, 0xa3bc0074L, 0xd4bb30e2L,
  0x4adfa541L, 0x3dd895d7L, 0xa4d1c46dL, 0xd3d6f4fbL, 0x4369e96aL,
  0x346ed9fcL, 0xad678846L, 0xda60b8d0L, 0x44042d73L, 0x33031de5L,
  0xaa0a4c5fL, 0xdd0d7cc9L, 0x5005713cL, 0x270241aaL, 0xbe0b1010L,
  0xc90c2086L, 0x5768b525L, 0x206f85b3L, 0xb966d409L, 0xce61e49fL,
  0x5edef90eL, 0x29d9c998L, 0xb0d09822L, 0xc7d7a8b4L, 0x59b33d17L,
  0x2eb40d81L, 0xb7bd5c3bL, 0xc0ba6cadL, 0xedb88320L, 0x9abfb3b6L,
  0x03b6e20cL, 0x74b1d29aL, 0xead54739L, 0x9dd277afL, 0x04db2615L,
  0x73dc1683L, 0xe3630b12L, 0x94643b84L, 0x0d6d6a3eL, 0x7a6a5aa8L,
  0xe40ecf0bL, 0x9309ff9dL, 0x0a00ae27L, 0x7d079eb1L, 0xf00f9344L,
  0x8708a3d2L, 0x1e01f268L, 0x6906c2feL, 0xf762575dL, 0x806567cbL,
  0x196c3671L, 0x6e6b06e7L, 0xfed41b76L, 0x89d32be0L, 0x10da7a5aL,
  0x67dd4accL, 0xf9b9df6fL, 0x8ebeeff9L, 0x17b7be43L, 0x60b08ed5L,
  0xd6d6a3e8L, 0xa1d1937eL, 0x38d8c2c4L, 0x4fdff252L, 0xd1bb67f1L,
  0xa6bc5767L, 0x3fb506ddL, 0x48b2364bL, 0xd80d2bdaL, 0xaf0a1b4cL,
  0x36034af6L, 0x41047a60L, 0xdf60efc3L, 0xa867df55L, 0x316e8eefL,
  0x4669be79L, 0xcb61b38cL, 0xbc66831aL, 0x256fd2a0L, 0x5268e236L,
  0xcc0c7795L, 0xbb0b4703L, 0x220216b9L, 0x5505262fL, 0xc5ba3bbeL,
  0xb2bd0b28L, 0x2bb45a92L, 0x5cb36a04L, 0xc2d7ffa7L, 0xb5d0cf31L,
  0x2cd99e8bL, 0x5bdeae1dL, 0x9b64c2b0L, 0xec63f226L, 0x756aa39cL,
  0x026d930aL, 0x9c0906a9L, 0xeb0e363fL, 0x72076785L, 0x05005713L,
  0x95bf4a82L, 0xe2b87a14L, 0x7bb12baeL, 0x0cb61b38L, 0x92d28e9bL,
  0xe5d5be0dL, 0x7cdcefb7L, 0x0bdbdf21L, 0x86d3d2d4L, 0xf1d4e242L,
  0x68ddb3f8L, 0x1fda836eL, 0x81be16cdL, 0xf6b9265bL, 0x6fb077e1L,
  0x18b74777L, 0x88085ae6L, 0xff0f6a70L, 0x66063bcaL, 0x11010b5cL,
  0x8f659effL, 0xf862ae69L, 0x616bffd3L, 0x166ccf45L, 0xa00ae278L,
  0xd70dd2eeL, 0x4e048354L, 0x3903b3c2L, 0xa7672661L, 0xd06016f7L,
  0x4969474dL, 0x3e6e77dbL, 0xaed16a4aL, 0xd9d65adcL, 0x40df0b66L,
  0x37d83bf0L, 0xa9bcae53L, 0xdebb9ec5L, 0x47b2cf7fL, 0x30b5ffe9L,
  0xbdbdf21cL, 0xcabac28aL, 0x53b39330L, 0x24b4a3a6L, 0xbad03605L,
  0xcdd70693L, 0x54de5729L, 0x23d967bfL, 0xb3667a2eL, 0xc4614ab8L,
  0x5d681b02L, 0x2a6f2b94L, 0xb40bbe37L, 0xc30c8ea1L, 0x5a05df1bL,
  0x2d02ef8dL
};
/*! @endcond */
#else
/*! @cond DynamicCRCTable */
static int32_t  crc_table_empty = 1;
static uint32_t crc_table[256];
static void make_crc_table(void);
/*
 *  Generate a table for a byte-wise 32-bit CRC calculation on the polynomial:
 *  x^32+x^26+x^23+x^22+x^16+x^12+x^11+x^10+x^8+x^7+x^5+x^4+x^2+x+1.
 *
 *  Polynomials over GF(2) are represented in binary, one bit per coefficient,
 *  with the lowest powers in the most significant bit.  Then adding polynomials
 *  is just exclusive-or, and multiplying a polynomial by x is a right shift by
 *  one.  If we call the above polynomial p, and represent a byte as the
 *  polynomial q, also with the lowest power in the most significant bit (so the
 *  byte 0xb1 is the polynomial x^7+x^3+x+1), then the CRC is (q*x^32) mod p,
 *  where a mod b means the remainder after dividing a by b.
 *
 *  This calculation is done using the shift-register method of multiplying and
 *  taking the remainder.  The register is initialized to zero, and for each
 *  incoming bit, x^32 is added mod p to the register if the bit is a one (where
 *  x^32 mod p is p+x^32 = x^26+...+1), and the register is multiplied mod p by
 *  x (which is shifting right by one and adding x^32 mod p if the bit shifted
 *  out is a one).  We start with the highest power (least significant bit) of
 *  q and repeat for all eight bits of q.
 *
 *  The table is simply the CRC of all possible eight bit values.  This is all
 *  the information needed to generate CRC's on data a byte at a time for all
 *  combinations of CRC register values and incoming bytes.
 */
static void make_crc_table(void)
{
  uint32_t             c;
  int                  n, k;
  uint32_t             poly; /* polynomial exclusive-or pattern */
  /* terms of polynomial defining this crc (except x^32): */
  static const uint8_t p[] = { 0, 1, 2, 4, 5, 7, 8, 10, 11, 12, 16, 22, 23, 26 };

  /* make exclusive-or pattern from polynomial (0xedb88320L) */
  poly = 0L;
  for (n = 0; n < sizeof(p) / sizeof(uint8_t); n++)
  {
    poly |= 1L << (31 - p[n]);
  }

  for (n = 0; n < 256; n++)
  {
    c = (uint32_t) n;
    for (k = 0; k < 8; k++)
    {
      c = c & 1 ? poly ^ (c >> 1) : c >> 1;
    }
    crc_table[n] = c;
  }
  crc_table_empty = 0;
}
#endif
/*! @endcond */

/* ========================================================================= */
#define DO1(src)    crc = crc_table[((uint32_t) crc ^ (*src++)) & 0xff] ^ (crc >> 8);
#define DO2(src)    DO1(src); DO1(src);
#define DO4(src)    DO2(src); DO2(src);
#define DO8(src)    DO4(src); DO4(src);

/* ========================================================================= */
uint32_t crc32(uint32_t crc, uint8_t ** const pp_src, uint32_t len)
{
  uint8_t * src = (*pp_src);
#if (dynamic_CRC_table == 1)
  if (crc_table_empty)
    make_crc_table();
#endif
  crc = crc ^ 0xffffffffL;
  while (len > 7)
  {
    DO8(src);
    len -= 8;
  }
  if (len) do
    {
      DO1(src);
    } while (--len);

  *pp_src = src;
  return(crc ^ 0xffffffffL);
}

testResult_t IEC60335_ClassB_FLASHtest_POST(void)
{
  FlashCRC_t   TestCRC;
  uint32_t     TestAddr = (uint32_t)__STEXT;
  testResult_t Result = IEC60335_testFailed;

  /* Do the POST signature generation according to the various flash sizes */
  /* check the complete Flash memory */
  TestCRC.CRC32Val = crc32(0, (uint8_t ** )&TestAddr, FLASHSIZE - (int32_t) __STEXT);
  TestCRC.Status   = FLASH_CRC_Done;

  /* check status flag and CRC value */
  if (IEC60335_Flash_CRC_REF.Status == FLASH_CRC_Valid)
  {
    if (TestCRC.CRC32Val == IEC60335_Flash_CRC_REF.CRC32Val)
    {
      Result = IEC60335_testPassed;
    }
  }

  return(Result);
}

testResult_t IEC60335_ClassB_FLASHtest_BIST(uint8_t StartMode)
{
  testResult_t      Result = IEC60335_testFailed;
  /*                                 CRC32Val,MemLenght,NextAddress,BlockSize,Status; */
  static FlashCRC_t bistFlashCRC = { 0, FLASH_SIZE, 0, CRC_block_size, FLASH_CRC_Restart };

  if (StartMode >= FLASH_CRC_Restart)
  {
    bistFlashCRC.Status = FLASH_CRC_Restart;
    Result              = IEC60335_testInProgress;
  }
  if (StartMode == FLASH_CRC_Missing)
  {
    return(Result);
  }
  /* consecutive addressing based on the struct content */

  /* check parts of the Flash memory */
  /* determine restart condition of FlashTest */
  if (bistFlashCRC.NextAddress <= (uint32_t) __STEXT)
  {
    bistFlashCRC.Status = FLASH_CRC_Restart;
  }
  /* determine failure condition of FlashTest */
  if (bistFlashCRC.NextAddress > FLASHSIZE)
  {
    bistFlashCRC.Status = FLASH_CRC_Restart;
  }
  if (bistFlashCRC.Status == FLASH_CRC_Restart)
  {
    bistFlashCRC.CRC32Val    = 0;
    bistFlashCRC.NextAddress = (uint32_t) __STEXT;
    bistFlashCRC.BlockSize   = CRC_block_size;
  }

  /* determine next length exceeding FlasSize */
  if ((bistFlashCRC.NextAddress + bistFlashCRC.BlockSize) > FLASHSIZE)
  {
    bistFlashCRC.BlockSize = FLASHSIZE - bistFlashCRC.NextAddress;
  }
  /* calculate next part */
  bistFlashCRC.CRC32Val = crc32(bistFlashCRC.CRC32Val, (uint8_t ** )&bistFlashCRC.NextAddress, bistFlashCRC.BlockSize);

  bistFlashCRC.Status   = FLASH_CRC_InProg;
  if (bistFlashCRC.NextAddress == FLASHSIZE)
  {
    bistFlashCRC.Status = FLASH_CRC_Done;
  }

  /* state when memory block is processed completely */
  if (bistFlashCRC.Status == FLASH_CRC_Done)
  {
    if (bistFlashCRC.CRC32Val == IEC60335_Flash_CRC_REF.CRC32Val)
    {
      Result = IEC60335_testPassed;
    }
  }
  if (bistFlashCRC.Status == FLASH_CRC_InProg)
  {
    Result = IEC60335_testInProgress;
  }

  /* return value if the part or all is done */
  return(Result);
}

/*!
 * @}
 */

/************************************** EOF *********************************/