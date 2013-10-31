#include "autogen_init.h"
#include "em_gpio.h"
#include "ff.h"
#include "sdcard.h"

#define SD_MISOPIN      14
#define SD_MOSIPIN      15
#define SD_CLKPIN       13
#define SD_CSPIN        12

DSTATUS Stat = STA_NOINIT;

int main(void)
{
  /* Initialize chip */
  eADesigner_Init();
  
  while(1){
    break;
  }
  return 0;
  
}

DWORD get_fattime(){
  return (28 << 25) | (2 << 21) | (1 << 16);
}

DSTATUS SD_disk_initialize(BYTE pdrv) {
  GPIO_PinModeSet(gpioPortE, SD_MOSIPIN, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortE, SD_MISOPIN, gpioModePushPull, 1);
  GPIO_PinModeSet(gpioPortE, SD_CSPIN, gpioModePushPull, 1);
  GPIO_PinModeSet(gpioPortE, SD_CLKPIN, gpioModePushPull, 0);
  return 0;
}

DSTATUS SD_disk_status(BYTE pdrv) {
  if (pdrv) return STA_NOINIT;
  return Stat;
}

int SD_disk_read(BYTE* buff, DWORD sector, UINT count){
  return 0;
}

int SD_disk_write(BYTE* buff, DWORD sector, UINT count){
  return 0;
}

DRESULT SD_disk_iotcl(BYTE cmd, void *buff){
  return 0;
}