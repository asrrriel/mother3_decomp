#include <runtime/runtime.h>
#include <non_canon/err.h>

//original addr: $080007cc
void rt_mode_ft_disclaimer(){
    bugcheck(ERR_UNIMPLEMENTED);
};