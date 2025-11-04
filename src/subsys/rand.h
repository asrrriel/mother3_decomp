#ifndef __RAND_H__
#define __RAND_H__

#include <stdint.h>

void rand_init(uint32_t seed);
uint32_t rand_gen();


#endif // __RAND_H__