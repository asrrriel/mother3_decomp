SRC_DIR = src
OBJ_DIR = obj

C_SRC = $(shell find $(SRC_DIR) -name "*.c")
C_OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(C_SRC))

CC = gcc
CFLAGS = -Wall -g -I$(SRC_DIR)

$(shell mkdir -p $(OBJ_DIR))

all: m3tool

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

m3tool: $(C_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf $(OBJ_DIR)/*.o $(GEN_DIR)/*.c m3tool

run: m3tool
	@if [ -z "$(ARGS)" ]; then \
		echo "Usage: make run ARGS='<args>'"; \
		exit 1; \
	fi
	./m3tool $(ARGS)

# Phony targets
.PHONY: all clean
