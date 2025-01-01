SRC_DIR = src
BUILD_DIR = bin
CC = gcc
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_NAME = PLAY

# Paths
INCLUDE_PATHS = -I/opt/homebrew/include 
LIBRARY_PATHS = -L/opt/homebrew/lib 

# Compiler and Linker Flags
COMPILER_FLAGS = -std=c99 -Wall -ggdb3 -O0 -arch arm64 $(INCLUDE_PATHS)
LINKER_FLAGS = -lm -lSDL2 -lSDL2_image -lSDL2_ttf $(LIBRARY_PATHS)

# Build Commands
all:
	mkdir -p $(BUILD_DIR)
	$(CC) $(COMPILER_FLAGS) $(SRC_FILES) -o $(BUILD_DIR)/$(OBJ_NAME) $(LINKER_FLAGS)

# Clean Command
clean:
	rm -f $(BUILD_DIR)/$(OBJ_NAME)
