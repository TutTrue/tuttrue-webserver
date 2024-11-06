CC = gcc
CFLAGS = -Wall -g -I$(INCLUDE_DIR)

# Directories
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = build
BIN_DIR = bin
LIB_DIR = lib

# Library and source files
LIBRARY = $(LIB_DIR)/libTutTrueWebServer.a
OBJ_FILES = $(OBJ_DIR)/create_server.o $(OBJ_DIR)/handle_request.o $(OBJ_DIR)/parse_request.o $(OBJ_DIR)/route.o $(OBJ_DIR)/tlisten.o $(OBJ_DIR)/get_status_text.o
MAIN_SRC = main.c
MAIN_OBJ = $(OBJ_DIR)/main.o

# Default target to build the library and the main program
all: $(LIBRARY) $(BIN_DIR)/main
	  @$(BIN_DIR)/main

# Build the static library
$(LIBRARY): $(OBJ_FILES)
	ar rcs $@ $^

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile main.c to object file
$(MAIN_OBJ): $(MAIN_SRC)
	$(CC) $(CFLAGS) -c $(MAIN_SRC) -o $(MAIN_OBJ)

# Link the main program with the static library
$(BIN_DIR)/main: $(MAIN_OBJ) $(LIBRARY)
	$(CC) $(CFLAGS) $(MAIN_OBJ) -L$(LIB_DIR) -lTutTrueWebServer -o $(BIN_DIR)/main

# Clean the build and binary files
clean:
	rm -rf $(OBJ_DIR)/*.o $(LIBRARY) $(BIN_DIR)/main

.PHONY: all clean

