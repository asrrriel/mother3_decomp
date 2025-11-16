#include "assets.h"

//original address: $08126318
void* index_asset_tbl(void* tbl, uint32_t idx){
    //TODO: investigate that weird ass logic
    return tbl + ((uint32_t*)tbl)[idx+1];
}