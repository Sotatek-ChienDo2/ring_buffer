.PHONY: all clean mk_objs mk_static install test coverage

LIB_NAME := ring_buffer-master

CUR_DIR := .
BIN_DIR := $(CUR_DIR)/bin
INC_DIR := $(CUR_DIR)/inc
OBJ_DIR := $(CUR_DIR)/objs
SRC_DIR := $(CUR_DIR)/src
LIB_DIR := $(CUR_DIR)/libs

# LIB_SHARED := $(LIB_DIR)/shared
LIB_STATIC := $(LIB_DIR)/static

INC_FLAGS := -I $(INC_DIR) -I /usr/include/gtest
CFLAGS := -Wall -g --coverage
LDFLAGS := --coverage

CC := g++

mk_objs:
	mkdir -p $(OBJ_DIR) $(BIN_DIR) $(LIB_DIR) $(LIB_STATIC)
	$(CC) -c $(CUR_DIR)/main.c -o $(OBJ_DIR)/main.o $(INC_FLAGS) $(CFLAGS)
	$(CC) -c $(SRC_DIR)/ring_buffer.c -o $(OBJ_DIR)/ring_buffer.o $(INC_FLAGS) $(CFLAGS)

mk_static:
	ar rcs $(LIB_STATIC)/lib$(LIB_NAME).a $(OBJ_DIR)/ring_buffer.o

install:
	cp -f $(LIB_STATIC)/lib$(LIB_NAME).a /usr/lib

all: mk_objs mk_static 
	$(CC)   $(OBJ_DIR)/main.o  -L$(LIB_STATIC) -l$(LIB_NAME) -o $(BIN_DIR)/use_static_lib -lgtest -lgtest_main -lpthread $(LDFLAGS)
clean:
	rm -rf $(OBJ_DIR)/*
	rm -rf $(LIB_STATIC)/lib$(LIB_NAME).a
	rm -rf $(BIN_DIR)/use_static_lib
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(LIB_DIR) $(LIB_STATIC)
	rm -rf $(CUR_DIR)/*.gcda $(CUR_DIR)/*.gcno $(CUR_DIR)/*.info $(CUR_DIR)/coverage

test: all
	$(BIN_DIR)/use_static_lib

coverage: test
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory coverage