#ifndef __RUNTIME_H__
#define __RUNTIME_H__

#include <stdint.h>

typedef struct{
    uint8_t runtime_mode;
    uint8_t runtime_flags;
} runtime_t;

extern runtime_t runtime;

#endif // __RUNTIME_H__