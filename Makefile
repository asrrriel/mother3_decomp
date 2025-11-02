CC     := arm-none-eabi-gcc
OBJCPY := arm-none-eabi-objcopy
LD     := arm-none-eabi-ld
AS     := arm-none-eabi-as

CFLAGS  := -g -Wall -O2 -mcpu=arm7tdmi -mtune=arm7tdmi -specs=gba.specs -ffreestanding -I$(DEVKITPRO)/libgba/include -Isrc
LDFLAGS := -L$(DEVKITPRO)/libgba/lib -lgba

SRC_DIR = src
OBJ_DIR = obj

C_SRC = $(shell find $(SRC_DIR) -name "*.c")
C_OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(C_SRC))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

rom: dirs obj/romhdr.o $(C_OBJ)
	$(LD) -T link.ld -o rom.elf $(shell find obj/ -name "*.o") $(LDFLAGS)
	$(OBJCPY) -O binary rom.elf rom.gba

dirs:
	mkdir -p obj 
	mkdir -p gen 

obj/romhdr.o:
	$(OBJCPY) -I binary -O elf32-littlearm -B arm assets/romhdr.bin obj/romhdr.o --rename-section .data=.hdr