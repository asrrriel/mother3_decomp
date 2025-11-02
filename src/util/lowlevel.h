#ifndef __LOWLEVEL_H__
#define __LOWLEVEL_H__

#include <stdint.h>

void do_dma_clear(void* addr, uint32_t size);
void do_swi_clear(void* addr, uint32_t size);

#endif // __LOWLEVEL_H__