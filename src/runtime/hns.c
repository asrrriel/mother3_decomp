#include "gba_interrupt.h"
#include <runtime/runtime.h>
#include <non_canon/err.h>
#include <stdint.h>
#include <subsys/subsys.h>
#include <subsys/assets.h>
#include <util/lowlevel.h>


extern char health_gfx;
uint32_t press_any_button_graphic;

//original addr: $0805a568
void hns_load_graphics(){
    void* loaded;

    loaded = index_asset_tbl(&health_gfx, 0);
    lz777_uncomp_vram(loaded,(void*)0x6008000);
    loaded = index_asset_tbl(&health_gfx, 2);
    lz777_uncomp_vram(loaded,(void*)0x6000000);
    loaded = index_asset_tbl(&health_gfx, 3);
    lz777_uncomp_vram(loaded,(void*)0x6010000);

    press_any_button_graphic = (uint32_t)index_asset_tbl(&health_gfx, 4);

    void* palette_data = index_asset_tbl(&health_gfx, 1);

}

//original addr: $0805a2f4
void hns_main(){
    hns_load_graphics();
    //TODO: whatever the hell those mystery flags do
    while(1); //temporary
}

//original addr: $0805a2dc
void hns_body(){
    //TODO: implement load_hns_jmptbl
    init_subsystems();
    //I refuse to implement $0805a378 because it looks useless
    hns_main();
}

//original addr: $080007b0
void rt_mode_hns(){
    //TODO: implement clear_sound
    hns_body();
    //TODO: implement mystery sound op($080037d8)
    runtime.mode = MODE_FT_DISCLAIMER;

}