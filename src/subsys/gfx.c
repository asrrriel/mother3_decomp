#include "gfx.h"
#include <stdint.h>
#include <util/lowlevel.h>

gfx_regs_t glob_gfx_regs;
char glob_gfx_staging[0x2B00]; //TODO: make this gigantic struct

//original address: $080013d0
void init_gfx_regs(gfx_regs_t* regs){
    //TODO: full implementation of the gfx regs
    regs->dispcnt = 0;
    //regs->bldalpha = 0; the original doesnt initialize these (????)
    //regs->bldy = 0;
    for(int i = 0; i < 4;i++){
        (&regs->bg0cnt)[i] = 0;
    }
}

void clear_gfx_staging(void* staging){
  *(uint16_t *)(staging + 0x2c46) = 0;
  *(uint16_t *)(staging + 0x2c44) = *(uint16_t*)(staging + 0x2c46);
  *(uint16_t *)(staging + 0x2c42) = *(uint16_t*)(staging + 0x2c44);
  *(uint16_t *)(staging + 0x2c40) = *(uint16_t*)(staging + 0x2c42);
  do_dma_clear(staging,0x800);
  do_dma_clear(staging + 0x800,0x800);
  do_dma_clear(staging + 0x1000,0x800);
  do_dma_clear(staging + 0x1800,0x800);
  do_dma_clear(staging + 0x2700,0x400);
  *(uint16_t *)(staging + 0x2c48) = 0;
  *(uint16_t *)(staging + 0x2c4a) = 0;
  *(uint8_t *)((int)staging + 0x2c4c) = 0;
  *(uint8_t *)((int)staging + 0x2c4d) = 0;
  *(uint8_t *)((int)staging + 0x2c4e) = 0;
  *(uint16_t *)((int)staging + 0x2700) =
       (uint16_t)*(uint8_t *)((int)staging + 0x2c4d) << 5 | (uint16_t)*(uint8_t *)((int)staging + 0x2c4c) |
       (uint16_t)*(uint8_t *)((int)staging + 0x2c4e) << 10;
}