#include "common.h"

extern uint8_t ramdisk_start;
extern uint8_t ramdisk_end;
#define RAMDISK_SIZE ((&ramdisk_end) - (&ramdisk_start))

/* The kernel is monolithic, therefore we do not need to
 * translate the address `buf' from the user process to
 * a physical one, which is necessary for a microkernel.
 */

/* read `len' bytes starting from `offset' of ramdisk into `buf' */
size_t ramdisk_read(void *buf, size_t offset, size_t len) {
  //printf("offset is %u and len is %u\n",offset,len);//debug
  assert(offset + len <= RAMDISK_SIZE);
  memcpy(buf, &ramdisk_start + offset, len);
  if(offset == 29019871){
    printf("debug here and last val %x and &ramdis_start+offset is %x\n",*(uint32_t*)(&ramdisk_start + offset + len-8),&ramdisk_start+offset);
    for(int k=0;k<len;k+=4)
      printf("%x ",((uint32_t*)buf)[k]);
  }
  return len;
}

/* write `len' bytes starting from `buf' into the `offset' of ramdisk */
size_t ramdisk_write(const void *buf, size_t offset, size_t len) {
  assert(offset + len <= RAMDISK_SIZE);
  memcpy(&ramdisk_start + offset, buf, len);
  return len;
}

void init_ramdisk() {
  Log("ramdisk info: start = %x, end = %x, size = %u bytes",
      &ramdisk_start, &ramdisk_end, RAMDISK_SIZE);
}

size_t get_ramdisk_size() {
  return RAMDISK_SIZE;
}
