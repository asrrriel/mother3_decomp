#ifndef __INPUT_H__
#define __INPUT_H__

#include <stdint.h>

typedef struct {
    uint16_t pressed;
    uint16_t down;
    uint16_t timer;
    uint16_t mystery;
    uint16_t held;
    uint16_t saved_down;
    uint16_t since_last_inp_change;
    uint8_t  flags;
} input_state_t;

extern input_state_t glob_inp_state;

void inp_init(input_state_t* state, uint16_t mystery);

#endif // __INPUT_H__