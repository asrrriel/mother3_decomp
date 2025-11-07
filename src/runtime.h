#ifndef __RUNTIME_H__
#define __RUNTIME_H__

#include <stdint.h>

typedef __attribute__((mode(QI))) enum {
    MODE_NAMING,
    MODE_UNUSED,
    MODE_PLAY_FROM_NEW_GAME,
    MODE_PLAY_FROM_CONTINUE,
    MODE_PLAY_FROM_RESPAWN,
    MODE_PLAY_FROM_BATTLE_WIN,
    MODE_PLAY_FROM_MENU,
    MODE_PLAY_FROM_NEW_CHAPTER,
    MODE_BATTLE,
    MODE_FULLSCREEN_MENU,
    MODE_MAIN_MENU,
    MODE_CREDITS,
    MODE_SNDPLYR,
    MODE_HNS,
    MODE_FT_DISCLAIMER
} runtime_mode_t;

typedef struct{
    runtime_mode_t runtime_mode;
    uint8_t runtime_flags;
} runtime_t;

extern runtime_t runtime;

#endif // __RUNTIME_H__