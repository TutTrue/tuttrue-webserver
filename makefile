# Compiler and flags
CC = gcc
CFLAGS = -Wall -g -I$(INCLUDE_DIR)

# Directories
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = build
BIN_DIR = bin
LIB_DIR = lib
UTILS_DIR = $(SRC_DIR)/utils

# Library and binary
LIBRARY = $(LIB_DIR)/libTutTrueWebServer.a
TARGET = $(BIN_DIR)/main

# Source and object files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(UTILS_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES:$(UTILS_DIR)/%.c=$(OBJ_DIR)/%.o))
MAIN_SRC = main.c
MAIN_OBJ = $(OBJ_DIR)/main.o

# Default target
all: $(LIBRARY) $(TARGET)
	@echo "Build complete. Running program:"
	@$(TARGET)

# Build static library
$(LIBRARY): $(OBJ_FILES)
	@mkdir -p $(LIB_DIR)
	ar rcs $@ $^
	@echo "Static library created: $@"

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled: $<"

$(OBJ_DIR)/%.o: $(UTILS_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled: $<"

# Compile main.c to object file
$(MAIN_OBJ): $(MAIN_SRC)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled: $<"

# Link the main program with the static library
$(TARGET): $(MAIN_OBJ) $(LIBRARY)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $< -L$(LIB_DIR) -lTutTrueWebServer -o $@
	@echo "Executable created: $@"

# Clean build artifacts and binaries
clean:
	@rm -rf $(OBJ_DIR)/*.o $(LIBRARY) $(TARGET)
	@echo "Cleaned build artifacts and binaries."

# Phony targets
.PHONY: all clean
