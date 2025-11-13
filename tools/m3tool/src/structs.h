#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include <stdint.h>

#define ROMHDR_FIXED        0x96

typedef struct {
    uint32_t entry_instr;
    uint8_t  nintendo_logo[0x9c];
    char     title[0xC];
    char     game_code[4];
    char     maker_code[2];
    uint8_t  mandatory_val;
    uint8_t  unit_code;
    uint8_t  device_type;
    uint8_t  reserved[8];
    uint8_t  complement;
    uint8_t  reserved2;
} romhdr_t;

#define ENEMY_ORDER_OFF     0xC6B64
#define ENEMY_ORDER_ENTRIES 0xFF

#define ENEMY_DATA_OFF   	0xD0D28
#define ENEMY_DATA_ENTRIES  0x100

typedef struct {
    uint32_t enemy_id;
    uint32_t smell_type;
    uint16_t overworld_sound;
    uint16_t background;
    uint16_t transition_music;
    uint16_t battle_music;
    uint16_t win_music;
    uint16_t level;
    uint32_t hp;
    uint32_t pp;
    uint8_t  offense;
    uint8_t  defense;
    uint8_t  iq;
    uint8_t  speed;
    uint32_t kindness;
    uint8_t  suprise_offense;
    uint8_t  suprise_defense;
    uint8_t  suprise_iq;
    uint8_t  suprise_speed;
    uint32_t suprise_kindness;
    uint8_t  wakness_table[0x28];
    uint8_t  action_table[0x10];
    uint16_t attack_sound;
    uint8_t  encounter_text;
    uint8_t  defeat_text;
    uint32_t defeat_animation;
    uint32_t battle_spr_height;
    uint8_t  memory_spr_height_front;
    uint8_t  memory_spr_height_back;
    uint8_t  battle_spr_height_front;
    uint8_t  battle_spr_height_back;
    uint8_t  memory_can_turn;
    uint8_t  battle_can_turn;
    uint16_t last_defeat_anim;
    uint8_t  drop_tbl[0xC];
    uint32_t drop_exp;
    uint32_t drop_money;
    uint32_t smell_weakness;
} enemy_t;

#define MUSIC_ORDER_OFF   	0xECD40
#define MUSIC_ORDER_ENTRIES 0x100

typedef struct {
    uint16_t song_ptr;
    uint16_t music_player_num;
    uint32_t required_chapter;
    uint32_t duration;
} music_t;

#endif // __STRUCTS_H__