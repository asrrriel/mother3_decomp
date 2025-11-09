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

    fclose(f);
}