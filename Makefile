CC     := $(DEVKITARM)/bin/arm-none-eabi-gcc
OBJCPY := $(DEVKITARM)/bin/arm-none-eabi-objcopy
LD     := $(DEVKITARM)/bin/arm-none-eabi-ld
AS     := $(DEVKITARM)/bin/arm-none-eabi-as
GBAFIX := $(DEVKITPRO)/tools/bin/gbafix

CFLAGS  := -g -Wall -O2 -mcpu=arm7tdmi -mtune=arm7tdmi -specs=gba.specs -ffreestanding -I$(DEVKITPRO)/libgba/include -Isrc
LDFLAGS := -L$(DEVKITPRO)/libgba/lib -L$(DEVKITARM)/lib/gcc/arm-none-eabi/15.1.0/ -lgba -lgcc

SRC_DIR = src
OBJ_DIR = obj

C_SRC = $(shell find $(SRC_DIR) -name "*.c")
C_OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(C_SRC))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

rom: dirs gen/romhdr.o $(C_OBJ)
	$(LD) -T link.ld -o rom.elf gen/romhdr.o $(shell find obj/ -name "*.o") $(LDFLAGS)
	$(OBJCPY) -O binary rom.elf rom.gba
	$(GBAFIX) rom.gba

dirs:
	mkdir -p obj 
	mkdir -p gen 

gen/romhdr.o:
	$(OBJCPY) -I binary -O elf32-littlearm -B arm assets/romhdr.bin gen/romhdr.o --rename-section .data=.hdr