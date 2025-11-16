#include "input.h"
#include "gba_input.h"
#include <stdint.h>

input_state_t glob_inp_state;

//original addr: $08001630
void inp_init(input_state_t* state, uint16_t mystery){
    state->is_anything_down                &= 0xfe;
    state->pressed               = 0;
    state->down                  = 0;
    state->timer                 = 0;
    state->mystery               = mystery;
    state->held                  = 0;
    state->saved_down            = 0;
    state->since_last_inp_change = 0; 
}

//original addr: $0800164c
void inp_update(input_state_t* state){
    uint16_t inp  = ~REG_KEYINPUT & 0x3ff;

    state->is_anything_down = true;
    if(inp == 0){
        state->timer = 0;
        state->is_anything_down = false;
        state->since_last_inp_change = 0;
    } else if (state->timer == 0){
        state->timer = 20;
    } else {
        if (state->timer-- == 0){
            state->timer = 6;
        } else {
            state->is_anything_down = false;
        }
    }

    if (state->is_anything_down){
        uint16_t timer = 0;
        if (state->down == state->saved_down){
            timer = state->since_last_inp_change;
        } else {
            timer = 0;
        }
        state->since_last_inp_change = timer;
        state->saved_down            = state->down;
    }

    uint16_t pressed = inp & ~state->down;
    state->pressed = pressed;
    state->down    = inp;

    if (state->is_anything_down){
        state->held = pressed | state->held;
    } else {
        state->pressed = pressed | state->held;
        state->held = 0;
    }
}