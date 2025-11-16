#include <runtime/runtime.h>
#include <non_canon/err.h>

//original addr: $08000920
void rt_mode_unused(){
    bugcheck(ERR_UNIMPLEMENTED);
};