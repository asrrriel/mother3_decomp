#include "input.h"

input_state_t glob_inp_state;

void inp_init(input_state_t* state, uint16_t mystery){
    state->flags                &= 0xfe;
    state->pressed               = 0;
    state->down                  = 0;
    state->timer                 = 0;
    state->mystery               = mystery;
    state->held                  = 0;
    state->saved_down            = 0;
    state->since_last_inp_change = 0; 
}