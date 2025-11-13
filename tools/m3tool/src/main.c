#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <endian.h>

#include <stdlib.h>
#include <string.h>
#include <structs.h>

bool check_rom(FILE* f){
    //read rom header
    romhdr_t hdr;
    fread(&hdr, sizeof(romhdr_t), 1, f);

    //check if its a valid rom
    if(hdr.reserved2 != 0 ||
        hdr.mandatory_val != ROMHDR_FIXED){
        return false;
    }

    //TODO: complement check

    //check if its mother 3
    if(strncmp(hdr.title, "MOTHER3",7) != 0 ||
        strncmp(hdr.game_code, "A3UJ",4) != 0 ||
        strncmp(hdr.maker_code, "01",2) != 0){
        return false;
    }

    //get ROM size
    fseek(f, 0, SEEK_END);
    uint32_t size = ftell(f);

    //must be a 32meg cart
    if (size != 33554432){
        return false;
    }

    //check for layout clues
    char m3_gbson[8];
    char mother3[7];
    fseek(f, 0xCDB8A8, SEEK_SET);
    fread(m3_gbson, 1, 8, f);
    fseek(f, 0x66570, SEEK_SET);
    fread(mother3, 1, 7, f);

    if(strncmp(m3_gbson, "M3 GBSON",8) != 0 ||
        strncmp(mother3, "mother3",7) != 0) {
        return false;
    }

    return true;
}


void print_enemy_order(FILE* f){
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
}

void print_enemy_data(FILE* f){
    fseek(f,ENEMY_DATA_OFF,SEEK_SET);
    enemy_t enemies[ENEMY_DATA_ENTRIES];

    fread(enemies,sizeof(enemy_t),ENEMY_DATA_ENTRIES,f);

    printf("Enemy data:\n");
    for (size_t i = 0; i < 0xBE /*Let's try to not show garbage data*/; i++){
        enemy_t entry = enemies[i];

        printf("==%2zx===\n  ID:            0x%x\n",i,entry.enemy_id);
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
}

void print_music_order(FILE* f){
    fseek(f,MUSIC_ORDER_OFF,SEEK_SET);
    music_t musics[MUSIC_ORDER_ENTRIES];

    fread(musics,sizeof(music_t),MUSIC_ORDER_ENTRIES,f);

    for (size_t i = 0; i < MUSIC_ORDER_ENTRIES; i++){
        music_t entry = musics[i];

        printf("==%2zx===\n",i);
        printf("  Song ptr:                 0x%x\n",entry.song_ptr);
        printf("  Music player num:         %u\n",entry.music_player_num);
        printf("  Required chapter:         0x%x\n",entry.required_chapter);
        printf("  Duration(unit?):          0x%x\n",entry.duration);
    }

}

int main(int argc, char** argv){
    printf("=====M3TOOL vDevelopment====\n");
    if(argc < 2){
        printf("Usage: %s <rom>", argv[0]);
    }

    FILE* f = fopen(argv[1],"rb");

    if(!check_rom(f)){
        printf("Error: This doesn't seem to be an english v1.3 mother 3 ROM\n");
        fclose(f);
        exit(1);
    }

    //print_enemy_order(f);
    //print_enemy_data(f);
    print_music_order(f);


    fclose(f);
}