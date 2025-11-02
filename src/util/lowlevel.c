#include "lowlevel.h"
#include "gba_systemcalls.h"
#include <gba.h>
#include <stdint.h>

void do_dma_clear(void* addr, uint32_t size){
	DMA3COPY(0, addr, 0x5000000 | size >> 2);
	while(REG_DMA3CNT & 0x80000000);
}

void do_swi_clear(void* addr, uint32_t size){
	if ((size & 0x1f) == 0 && ((uint32_t)addr & 3) == 0) {
		CpuFastSet(0, addr, size >> 2 |  0x1000000);
	} else {
		CpuSet(0, addr, size >> 2);
	}
}