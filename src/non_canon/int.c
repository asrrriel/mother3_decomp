#include "int.h"
#include "gba_interrupt.h"
#include "gba_video.h"
#include <gba.h>
#include <stdint.h>
#include <non_canon/err.h>

void __int_vblank(){
    //bugcheck(ERR_TEST_FAIL);
    return; //TODO
}

void install_ivt1(){
    REG_IME       = 0;
    REG_IE       &= 0xfff8;
    REG_DISPSTAT &= 0xffc7;

    irqSet(IRQ_VBLANK, __int_vblank);
    irqEnable(IRQ_VBLANK);

    REG_IME = 1;
}