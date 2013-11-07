

#include "autogen_init.h"
#include "em_gpio.h"
#include "em_usart.h"
#include "em_cmu.h"
#include "ff.h"
#include "sdcard.h"



static uint32_t timeOut, xfersPrMsec;

/* fat thing */
static FATFS Fatfs;
FIL fh;

int main(void)
{
  FRESULT res;
  int write_num;
  /* Initialize chip */
  
  SD_disk_initialize();
  res = f_mount(&Fatfs, 0, 1);
  
  if (res != FR_OK) {
      while (1); /* should return some error code */
  }
  
  res = f_open(&fh, "test", FA_WRITE);
  
  write_num = f_puts("this is a fine text\n", &fh);
  
  if (write_num == -1) {
    while(1);
  }
  
  return 0;
  
}

DWORD get_fattime(){
  return (28 << 25) | (2 << 21) | (1 << 16);
}

static uint8_t WaitReady(void)
{
  uint8_t res;
  uint32_t retryCount;

  /* Wait for ready in timeout of 500ms */
  retryCount = 500 * xfersPrMsec;
  do
    res = SD_XferSpi(0xff);
  while ((res != 0xFF) && --retryCount);

  return res;
}

void SD_disk_initialize(void) {
  
  USART_InitSync_TypeDef init = USART_INITSYNC_DEFAULT;
  
  /* Enabling clock to USART 0 */
  CMU_ClockEnable(SD_CMUCLOCK, true);
  CMU_ClockEnable(cmuClock_GPIO, true);
  
  /* Initialize USART in SPI master mode. */
  xfersPrMsec   = SD_LO_SPI_FREQ / 8000;
  init.baudrate = SD_LO_SPI_FREQ;
  init.msbf     = true;
  USART_InitSync(SD_USART, &init);
  
    /* Enabling pins and setting location, SPI CS not enable */
  SD_USART->ROUTE = USART_ROUTE_TXPEN | USART_ROUTE_RXPEN |
                    USART_ROUTE_CLKPEN | SD_LOC;


  GPIO_PinModeSet(SD_GPIOPORT, SD_MOSIPIN, gpioModePushPull, 0);
  GPIO_PinModeSet(SD_GPIOPORT, SD_MISOPIN, gpioModePushPull, 1);
  GPIO_PinModeSet(SD_GPIOPORT, SD_CSPIN, gpioModePushPull, 1);
  GPIO_PinModeSet(SD_GPIOPORT, SD_CLKPIN, gpioModePushPull, 0);

}

void SD_SpiClkSlow(void)
{
  USART_BaudrateSyncSet(SD_USART, 0, SD_LO_SPI_FREQ);
  xfersPrMsec = SD_LO_SPI_FREQ / 8000;
}

uint8_t SD_XferSpi(uint8_t data)
{
  if ( timeOut )
    timeOut--;

  return USART_SpiTransfer(SD_USART, data);
}

int SD_Select(void)
{
  GPIO->P[ SD_GPIOPORT ].DOUTCLR = 1 << SD_CSPIN; /* CS pin low. */
  if (WaitReady() != 0xFF)
  {
    SD_Deselect();
    return 0;
  }
  return 1;
}

void SD_Deselect(void)
{
  GPIO->P[ SD_GPIOPORT ].DOUTSET = 1 << SD_CSPIN; /* CS pin high */
  SD_XferSpi(0xff);
}

void SD_PowerOn(void)
{
  /* Enable SPI clock */
  CMU_ClockEnable(SD_CMUCLOCK, true);
}

void SD_PowerOff(void)
{
  SD_Select();
  SD_Deselect();
  CMU_ClockEnable(SD_CMUCLOCK, false);
}

uint8_t SD_SendCmd(uint8_t cmd, DWORD arg)
{
  uint8_t  n, res;
  uint32_t retryCount;

  if (cmd & 0x80)
  { /* ACMD<n> is the command sequense of CMD55-CMD<n> */
    cmd &= 0x7F;
    res  = SD_SendCmd(CMD55, 0);
    if (res > 1) return res;
  }

  /* Select the card and wait for ready */
  SD_Deselect();
  if (!SD_Select())
    return 0xFF;

  /* Send command packet */
  SD_XferSpi(0x40 | cmd);            /* Start + Command index */
  SD_XferSpi((uint8_t)(arg >> 24));  /* Argument[31..24] */
  SD_XferSpi((uint8_t)(arg >> 16));  /* Argument[23..16] */
  SD_XferSpi((uint8_t)(arg >> 8));   /* Argument[15..8] */
  SD_XferSpi((uint8_t) arg);         /* Argument[7..0] */
  n = 0x01;                               /* Dummy CRC + Stop */
  if (cmd == CMD0)
    n = 0x95;                             /* Valid CRC for CMD0(0) */
  if (cmd == CMD8)
    n = 0x87;                             /* Valid CRC for CMD8(0x1AA) */
  SD_XferSpi(n);

  /* Receive command response */
  if (cmd == CMD12)
    SD_XferSpi(0xff);                /* Skip a stuff byte when stop reading */
  retryCount = 10;                        /* Wait for a valid response in timeout of 10 attempts */
  do
    res = SD_XferSpi(0xff);
  while ((res & 0x80) && --retryCount);

  return res;             /* Return with the response value */
}

void SD_TimeOutSet(uint32_t msec)
{
  timeOut = xfersPrMsec * msec;
}

int SD_TimeOutElapsed(void)
{
  return timeOut == 0;
}



/**************************************************************************//**
 * @brief Set SPI clock to maximum frequency.
 *****************************************************************************/
void SD_SpiClkFast(void)
{
  USART_BaudrateSyncSet(SD_USART, 0, SD_HI_SPI_FREQ);
  xfersPrMsec = SD_HI_SPI_FREQ / 8000;
}

int SD_BlockRx(uint8_t *buff, uint32_t btr)
{
  uint8_t token;
  uint32_t retryCount, framectrl, ctrl;
  uint16_t *buff_16 = (uint16_t *) buff;

  /* Wait for data packet in timeout of 100ms */
  retryCount = 100 * xfersPrMsec;
  do
    token = SD_XferSpi(0xff);
  while ((token == 0xFF) && --retryCount);

  if (token != 0xFE)
    /* Invalid data token */
    return 0;

  /* Save old configuration. */
  framectrl = SD_USART->FRAME;
  ctrl      = SD_USART->CTRL;

  /* Set up frames to 16 bit on each frame. This will increase the
   * data rate and make the maximum use of the buffers available. */
  SD_USART->FRAME = (SD_USART->FRAME & (~_USART_FRAME_DATABITS_MASK))
                         | USART_FRAME_DATABITS_SIXTEEN;
  SD_USART->CTRL |= USART_CTRL_BYTESWAP;

  /* Clear send and receive buffer */
  SD_USART->CMD = USART_CMD_CLEARRX | USART_CMD_CLEARTX;

  if ( timeOut >= btr + 2 )
    timeOut -= btr + 2;
  else
    timeOut = 0;

  /* Pipelining - The USART has two buffers of 16 bit in both
   * directions. Make sure that at least one is in the pipe at all
   * times to maximize throughput. */
  SD_USART->TXDOUBLE = 0xffff;
  do
  {
    SD_USART->TXDOUBLE = 0xffff;

    while (!(SD_USART->STATUS & USART_STATUS_RXDATAV));
    *buff_16++ = (uint16_t) SD_USART->RXDOUBLE;

    btr -= 2;
  } while (btr);

  /* Next two bytes is the CRC which we discard. */
  while (!(SD_USART->STATUS & USART_STATUS_RXDATAV));
  SD_USART->RXDOUBLE;

  /* Restore old settings. */
  SD_USART->FRAME = framectrl;
  SD_USART->CTRL  = ctrl;

  return 1;     /* Return with success */
}

#if __READONLY == 0
int SD_BlockTx(const uint8_t *buff, uint8_t token)
{
  uint8_t resp;
  uint32_t bc = 512;

  if (WaitReady() != 0xFF)
    return 0;

  SD_XferSpi(token);         /* Xmit a token */
  if (token != 0xFD)
  {                               /* Not StopTran token */
    do
    {
      /* Xmit the 512 byte data block to the MMC */
      SD_XferSpi(*buff++);
      SD_XferSpi(*buff++);
      SD_XferSpi(*buff++);
      SD_XferSpi(*buff++);
      bc -= 4;
    } while (bc);

    SD_XferSpi(0xFF);        /* CRC (Dummy) */
    SD_XferSpi(0xFF);
    resp = SD_XferSpi(0xff); /* Receive a data response */
    if ((resp & 0x1F) != 0x05)    /* If not accepted, return with error */
      return 0;
  }
  return 1;
}
#endif  /* _READONLY */

