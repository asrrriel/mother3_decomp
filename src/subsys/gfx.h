#ifndef __GFX_H__
#define __GFX_H__

#include <stdint.h>

typedef struct {
    uint16_t bldalpha;
    uint16_t bldy;
    uint16_t dispcnt;
    uint16_t bg0cnt;
    uint16_t bg1cnt;
    uint16_t bg2cnt;
    uint16_t bg3cnt;
} gfx_regs_t;

extern gfx_regs_t glob_gfx_regs;
extern char glob_gfx_staging[0x2B00]; //TODO: make this gigantic struct

void init_gfx_regs(gfx_regs_t* regs);
void clear_gfx_staging(void* staging);
#endif // __GFX_H__