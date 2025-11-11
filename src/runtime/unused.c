#include <runtime/runtime.h>
#include <non_canon/err.h>

void rt_mode_unused(){
    bugcheck(ERR_UNIMPLEMENTED);
};