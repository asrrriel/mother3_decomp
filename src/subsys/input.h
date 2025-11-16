#ifndef __INPUT_H__
#define __INPUT_H__

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint16_t pressed;
    uint16_t down;
    uint16_t timer;
    uint16_t mystery;
    uint16_t held;
    uint16_t saved_down;
    uint16_t since_last_inp_change;
    bool     is_anything_down;
} input_state_t;

extern input_state_t glob_inp_state;

void inp_init(input_state_t* state, uint16_t mystery);
void inp_update(input_state_t* state);

#endif // __INPUT_H__