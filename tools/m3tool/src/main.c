#include <stdio.h>
#include <stdint.h>
#include <endian.h>

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
    uint8_t  reserved[7];
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

int main(int argc, char** argv){
    printf("=====M3TOOL vDevelopment====\n");
    if(argc < 2){
        printf("Usage: %s <rom>", argv[0]);
    }

    FILE* f = fopen(argv[1],"rb");

    romhdr_t hdr;

    fread(&hdr, sizeof(romhdr_t), 1, f);

    printf("ROM title: \"%s\"\n",hdr.title);
    printf("ROM game code: \"%.*s\"\n",4,hdr.game_code);
    printf("ROM maker code: \"%.*s\"\n",2,hdr.maker_code);
    printf("ROM unit code: 0x%x\n",hdr.unit_code);
    printf("ROM device type: 0x%x\n\n",hdr.device_type);

    fseek(f, 0, SEEK_END);
    uint32_t size = ftell(f);
    printf("ROM size: %uM\n",size / 1000000);

    fseek(f,ENEMY_ORDER_OFF,SEEK_SET);
    uint16_t enemy_order[ENEMY_ORDER_ENTRIES];

    fread(enemy_order,2,ENEMY_ORDER_ENTRIES,f);

    printf("Battle memory enemy order:\n");
    for (size_t i = 0; i < ENEMY_ORDER_ENTRIES; i++){
        uint16_t entry = le16toh(enemy_order[i]);

        if(entry == 0xffff) //end signal
            break;

        printf("  %zu: 0x%x\n",i,entry);

    }

    fseek(f,ENEMY_DATA_OFF,SEEK_SET);
    enemy_t enemies[ENEMY_DATA_ENTRIES];

    fread(enemies,sizeof(enemy_t),ENEMY_DATA_ENTRIES,f);

    
    printf("Enemy data:\n");
    for (size_t i = 0; i < 0xBE /*Let's try to not show garbage data*/; i++){
        enemy_t entry = enemies[i];

        printf("==%2zx===\n  ID: 0x%x\n",i,entry.enemy_id);
        printf("  Background:               0x%x\n",entry.background);
        printf("  Transition music:         0x%x\n",entry.transition_music);
        printf("  Battle music:             0x%x\n",entry.battle_music);
        printf("  Win music:                0x%x\n",entry.win_music);
        printf("  Level:                    0x%x\n",entry.level);
        printf("  HP:                       0x%x\n",entry.hp);
        printf("  PP:                       0x%x\n",entry.pp);
        printf("  Offense:                  0x%x\n",entry.offense);
        printf("  Defense:                  0x%x\n",entry.defense);
        printf("  IQ:                       0x%x\n",entry.iq);
        printf("  Speed:                    0x%x\n",entry.speed);
        printf("  Kindness:                 0x%x\n",entry.kindness);
        printf("  Offense(suprise attack):  0x%x\n",entry.suprise_offense);
        printf("  Defense(suprise attack):  0x%x\n",entry.suprise_defense);
        printf("  IQ(suprise attack):       0x%x\n",entry.suprise_iq);
        printf("  Speed(suprise attack):    0x%x\n",entry.suprise_speed);
        printf("  Kindness(suprise attack): 0x%x\n",entry.suprise_kindness);
        printf("  Dropped experience:       0x%x\n",entry.drop_exp);
        printf("  Dropped money:            0x%x\n",entry.drop_money);
        printf("  Defeat animation:         0x%x\n",entry.defeat_animation);
        printf("  Defeat anim(last enemy):  0x%x\n",entry.last_defeat_anim);


    }

    fclose(f);
}