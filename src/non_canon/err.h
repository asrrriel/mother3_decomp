#ifndef __ERR_H__
#define __ERR_H__

typedef enum {
    ERR_UNIMPLEMENTED,
    ERR_TEST_FAIL
} err_t;

void bugcheck(err_t err);

#endif // __ERR_H__