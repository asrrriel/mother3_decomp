#include "subsys.h"
#include "gfx.h"
#include "subsys/input.h"

//original addr: $0805a520
void init_subsystems(){
    //TODO: implement mystery variables here

    init_gfx_regs(&glob_gfx_regs);
    clear_gfx_staging(&glob_gfx_staging);
    inp_init(&glob_inp_state, 2);
}