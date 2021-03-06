#include "common.h"
#include <amdev.h>
#include "fs.h"

size_t serial_write(const void *buf, size_t offset, size_t len) {
  // _yield();
  for(int i=0;i<len;i++) _putc(((char*)buf)[i]);
  return len;
}

#define NAME(key) \
  [_KEY_##key] = #key,

static const char *keyname[256] __attribute__((used)) = {
  [_KEY_NONE] = "NONE",
  _KEYS(NAME)
};

extern void switch_pcb(int i);
size_t events_read(void *buf, size_t offset, size_t len) {
    // _yield();
    int key = read_key();
    int down = 0;
    if (key & 0x8000) {
      key ^= 0x8000;
		  switch_pcb(key);
      down = 1;
    }
    if (key != _KEY_NONE) {
      return snprintf(buf,len,"%s %s\n",down ? "kd" : "ku" ,keyname[key]);
    }
    else return snprintf(buf,len,"t %u\n",uptime());
}

static char dispinfo[128] __attribute__((used)) = {};

size_t dispinfo_read(void *buf, size_t offset, size_t len) {
  int tail = strlen(dispinfo);
  if(offset >= tail) return 0;
  int ret = len < tail - offset ? len : tail - offset;
  memcpy(buf,dispinfo+offset,ret);
  return ret;
}

size_t fb_write(const void *buf, size_t offset, size_t len) {
  // _yield();
  int width  = screen_width();
  offset/=4;
  int x = offset % width;
  int y = offset / width;
  draw_rect((uint32_t*)buf,x,y,len/4,1);
  return len;
}

size_t fbsync_write(const void *buf, size_t offset, size_t len) {
  draw_sync();
  return len;
}

void init_device() {
  Log("Initializing devices...");
  _ioe_init();

  // TODO: print the string to array `dispinfo` with the format
  // described in the Navy-apps convention
  sprintf(dispinfo,"WIDTH:%d\nHEIGHT:%d\n\0",screen_width(),screen_height());
}
