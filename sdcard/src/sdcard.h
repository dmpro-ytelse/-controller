#include <stdint.h>

#include "diskio.h"


/* Definitions for MMC/SDC command */
#define CMD0      (0)         /**< GO_IDLE_STATE */
#define CMD1      (1)         /**< SEND_OP_COND */
#define ACMD41    (41 | 0x80) /**< SEND_OP_COND (SDC) */
#define CMD8      (8)         /**< SEND_IF_COND */
#define CMD9      (9)         /**< SEND_CSD */
#define CMD10     (10)        /**< SEND_CID */
#define CMD12     (12)        /**< STOP_TRANSMISSION */
#define ACMD13    (13 | 0x80) /**< SD_STATUS (SDC) */
#define CMD16     (16)        /**< SET_BLOCKLEN */
#define CMD17     (17)        /**< READ_SINGLE_BLOCK */
#define CMD18     (18)        /**< READ_MULTIPLE_BLOCK */
#define CMD23     (23)        /**< SET_BLOCK_COUNT */
#define ACMD23    (23 | 0x80) /**< SET_WR_BLK_ERASE_COUNT (SDC) */
#define CMD24     (24)        /**< WRITE_BLOCK */
#define CMD25     (25)        /**< WRITE_MULTIPLE_BLOCK */
#define CMD41     (41)        /**< SEND_OP_COND (ACMD) */
#define CMD55     (55)        /**< APP_CMD */
#define CMD58     (58)        /**< READ_OCR */

/* definitions for sdcard on controller */
#define SD_HI_SPI_FREQ     12000000

#define SD_LO_SPI_FREQ     100000
#define SD_USART           USART0
#define SD_CMUCLOCK        cmuClock_USART0
#define SD_LOC             USART_ROUTE_LOCATION_LOC1
#define SD_GPIOPORT     gpioPortE
#define SD_MISOPIN      14
#define SD_MOSIPIN      15
#define SD_CLKPIN       13
#define SD_CSPIN        12

void SD_disk_initialize(void);
static uint8_t WaitReady(void);
uint8_t SD_XferSpi(uint8_t data);
void SD_SpiClkSlow(void);
void SD_SpiClkFast(void);
void SD_PowerOn(void);
void SD_PowerOff(void);
int SD_BlockRx(uint8_t *buff, uint32_t btr);
int SD_BlockTx(const uint8_t *buff, uint8_t token);
void SD_TimeOutSet(uint32_t msec);
uint8_t SD_SendCmd(uint8_t cmd, DWORD arg);
int SD_Select(void);
void SD_Deselect(void);
DSTATUS SD_disk_status(BYTE);
int SD_TimeOutElapsed(void);


DWORD get_fattime(void);