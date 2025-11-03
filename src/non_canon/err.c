#include "err.h"
#include "gba_interrupt.h"
#include <gba.h>
#include <stdint.h>
void bugcheck(err_t err) {

    //switch to bitmap mode
	REG_DISPCNT = 0x0403;

    //fill the screen with blue
    unsigned short* vram = (unsigned short*)VRAM;

    for(uint32_t i = 0; i < 160*240; i++){
        vram[i]= 0x7800;
    }

    //draw a red X
    for(uint32_t i = 0; i < 30; i++){
        vram[(10+i)+(10+i)*240]= 0x001F;
        vram[(40-i)+(10+i)*240]= 0x001F;
    }

    // draw as many lines as the error code
    for(uint32_t i = 0; i < err; i++){
        for(uint32_t j = 0; j < 10; j++){
            vram[(50+(i*5))+(15+j)*240]= 0x001F;
        }
    }
    //die
    REG_IME = 0;
    while (1);

}