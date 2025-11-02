#include "gba_dma.h"
#include "gba_input.h"
#include "gba_interrupt.h"
#include "gba_sio.h"
#include "gba_sound.h"
#include "gba_systemcalls.h"
#include "gba_video.h"
#include <gba.h>
#include "regs.h"
#include "runtime.h"
#include <err/err.h>
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
	//TODO: mystery table
}


void do_soft_reset() {
	plant_reset_magic();
	REG_SOUNDCNT_X = 0;
	REG_IME = 0;
	SoftReset(0);
}

void main_loop();

void main() {
	//set up registers
	REG_WAITCNT  = 0x45b4;
	REG_IE   	 = 0x2000;
	REG_RCNT 	 = 0x0000;
	REG_SIOCNT   = 0x2000;

	clear_ram();
	clear_special_mem();
	check_reset();
	setup_runtime();

	if ((REG_KEYINPUT & 0x3ff) == 0xf){
		runtime.runtime_flags |= 2;
	}

	//TODO: rest of initialization

	main_loop();

	do_soft_reset();
}

void main_loop(){
	do {
		switch(runtime.runtime_mode){
			case 0x0:
				bugcheck(ERR_UNIMPLEMENTED);
			case 0x1:
				bugcheck(ERR_UNIMPLEMENTED);
			case 0x2 ... 0x7:
				bugcheck(ERR_UNIMPLEMENTED);
			case 0x8:
				bugcheck(ERR_UNIMPLEMENTED);
			case 0x9:
				bugcheck(ERR_UNIMPLEMENTED);
			case 0xa:
				bugcheck(ERR_UNIMPLEMENTED);
			case 0xb:
				bugcheck(ERR_UNIMPLEMENTED);
			case 0xc:
				bugcheck(ERR_UNIMPLEMENTED);
			case 0xd:
				bugcheck(ERR_UNIMPLEMENTED);
			case 0xe:
				bugcheck(ERR_UNIMPLEMENTED);
			default:
				break;
		}
		//TODO:interrupt stuff
	} while(true);
}