# Library name and version
LIB_NAME = mathutils
VERSION = 1.0.0
SONAME = lib$(LIB_NAME).so.$(VERSION)

# Directories
SRC_DIR = src
INCLUDE_DIR = include
TEST_DIR = tests
EXAMPLE_DIR = examples
BUILD_DIR = build
LIB_DIR = $(BUILD_DIR)/lib
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

# Source files
LIB_SRCS = $(wildcard $(SRC_DIR)/*.c)
TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)
EXAMPLE_SRCS = $(wildcard $(EXAMPLE_DIR)/*.c)

# Object files
LIB_OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(LIB_SRCS))
TEST_OBJS = $(patsubst $(TEST_DIR)/%.c,$(OBJ_DIR)/%.o,$(TEST_SRCS))
EXAMPLE_OBJS = $(patsubst $(EXAMPLE_DIR)/%.c,$(OBJ_DIR)/%.o,$(EXAMPLE_SRCS))

# Output files
STATIC_LIB = $(LIB_DIR)/lib$(LIB_NAME).a
SHARED_LIB = $(LIB_DIR)/lib$(LIB_NAME).so
TEST_BIN = $(BIN_DIR)/test_suite
EXAMPLE_BINS = $(patsubst $(EXAMPLE_DIR)/%.c,$(BIN_DIR)/%,$(EXAMPLE_SRCS))

# Compiler flags
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g -fPIC -I$(INCLUDE_DIR)
LDFLAGS = -lm

# Default target
all: directories static shared 

# Create build directories
directories:
	mkdir -p $(OBJ_DIR) $(LIB_DIR) $(BIN_DIR)

# Build static library
static: directories $(LIB_OBJS)
	ar rcs $(STATIC_LIB) $(LIB_OBJS)

# Build shared library
shared: directories $(LIB_OBJS)
	$(CC) -shared -Wl,-soname,$(SONAME) -o $(SHARED_LIB) $(LIB_OBJS) $(LDFLAGS)

# Compile library sources
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile test sources
$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Build tests
tests: directories static $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $(TEST_BIN) $(TEST_OBJS) $(STATIC_LIB) $(LDFLAGS)

# Compile example sources
$(OBJ_DIR)/%.o: $(EXAMPLE_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Build examples
examples: directories static $(EXAMPLE_BINS)

$(BIN_DIR)/%: $(OBJ_DIR)/%.o
	$(CC) $(CFLAGS) -o $@ $< $(STATIC_LIB) $(LDFLAGS)

# Clean up
clean:
	rm -rf $(BUILD_DIR)

# Install the library
install: shared static
	mkdir -p $(DESTDIR)/usr/local/lib
	mkdir -p $(DESTDIR)/usr/local/include/$(LIB_NAME)
	cp $(SHARED_LIB) $(DESTDIR)/usr/local/lib/
	cp $(STATIC_LIB) $(DESTDIR)/usr/local/lib/
	cp -r $(INCLUDE_DIR)/$(LIB_NAME)/* $(DESTDIR)/usr/local/include/$(LIB_NAME)/
	ln -sf $(DESTDIR)/usr/local/lib/$(SHARED_LIB) $(DESTDIR)/usr/local/lib/lib$(LIB_NAME).so

# Run tests
run-tests: tests
	LD_LIBRARY_PATH=$(LIB_DIR):$(LD_LIBRARY_PATH) $(TEST_BIN)

.PHONY: all directories static shared tests examples clean install run-tests