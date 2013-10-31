#include "diskio.h"
int main(void);

DSTATUS SD_disk_initialize(BYTE);
DSTATUS SD_disk_status(BYTE);
int SD_disk_read(BYTE*, DWORD, UINT);
int SD_disk_write(BYTE*, DWORD, UINT);
DRESULT SD_disk_ioctl(BYTE, void *);

DWORD get_fattime(void);