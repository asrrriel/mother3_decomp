#include <gba.h>
#include <regs.h>
#include <runtime/runtime.h>
#include <subsys/rand.h>
#include <non_canon/err.h>
#include <non_canon/int.h>
#include <stdint.h>
#include <util/lowlevel.h>

runtime_t runtime;
const char reset_check_str[8] = "M3 GBSON";

void clear_ram(){
	do_dma_clear((void*)0x2000000,0x40000); // EWRAM
	do_dma_clear((void*)0x3000008,0x7d98);  // IWRAM
}

void clear_special_mem(){
	do_swi_clear((void*)0x6000000,0x18000); // VRAM
	do_swi_clear((void*)0x5000000,0x400);	// Palette RAM
	do_swi_clear((void*)0x7000000,0x400);   // OAM
}

//reset awareness, for returning to title screen
void check_reset(){
	char* iwram = (char*)0x3000000;

	for(int i = 0; i < 8; i++){
		if(iwram[i] != reset_check_str[i]){
			runtime.runtime_flags &=  0xfe;
			return;
		}
	}
	runtime.runtime_flags |= 1;
}

void plant_reset_magic(){
	char* iwram = (char*)0x3000000;

	for(int i = 0; i < 8; i++){
		iwram[i] = reset_check_str[i];
	}
}

void setup_runtime() {
	runtime.runtime_mode = 0xd;
	runtime.runtime_flags &= 0xfd;
	rand_init(4357);
}


void do_soft_reset() {
	plant_reset_magic();
	REG_SOUNDCNT_X = 0;
	REG_IME = 0;
	SoftReset(0);
}

void main() {
	//set up registers
	REG_WAITCNT  = 0x45b4;
	REG_IE   	 = 0x2000;
	REG_RCNT 	 = 0x0000;
	REG_SIOCNT   = 0x2000;

	clear_ram();
	clear_special_mem();
	check_reset();

	irqInit(); //libGBA wants this to be here for some reason, maybe it wants cleared RAM :P

	install_ivt1();
	setup_runtime();

	if ((REG_KEYINPUT & 0x3ff) == 0xf){
		runtime.runtime_flags |= 2;
	}

	//TODO: rest of initialization

	runtime_dispatch();

	do_soft_reset();
}
