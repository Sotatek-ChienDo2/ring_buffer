.PHONY: all clean mk_objs mk_static install

LIB_NAME := Test_1

CUR_DIR := .
BIN_DIR := $(CUR_DIR)/bin
INC_DIR := $(CUR_DIR)/inc
OBJ_DIR := $(CUR_DIR)/objs
SRC_DIR := $(CUR_DIR)/src
LIB_DIR := $(CUR_DIR)/libs

# LIB_SHARED := $(LIB_DIR)/shared
LIB_STATIC := $(LIB_DIR)/static

INC_FLAGS := -I $(INC_DIR)

CC := gcc

mk_objs:
	$(CC) -c $(CUR_DIR)/main.c -o $(OBJ_DIR)/main.o $(INC_FLAGS)
	$(CC) -c $(SRC_DIR)/ring_buffer.c -o $(OBJ_DIR)/ring_buffer.o $(INC_FLAGS)

mk_static:
	ar rcs $(LIB_STATIC)/lib$(LIB_NAME).a $(OBJ_DIR)/ring_buffer.o

install:
	cp -f $(LIB_STATIC)/lib$(LIB_NAME).a /usr/lib

all: mk_objs mk_static 
	$(CC)   $(OBJ_DIR)/main.o  -L$(LIB_STATIC) -l$(LIB_NAME) -o $(BIN_DIR)/use_static_lib
clean:
	rm -rf $(OBJ_DIR)/*
	rm -rf $(LIB_STATIC)/lib$(LIB_NAME).a
	rm -rf $(BIN_DIR)/use_static_lib