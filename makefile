#file: Makefile

BIN_DIR = ./bin
INC_DIR = ./include
SRC_DIR = ./src
OBJ_DIR = ./obj

CC = g++ -std=c++11

ROOT_INC = $(ROOTSYS)/include
ROOTCFLAGS := $(shell root-config --cflags)
ROOTLIBS := $(shell root-config --libs)

LFLAGS = -L/usr/lib \
		-Wl,--no-as-needed $(ROOTLIBS) 

CFLAGS = -ggdb -fPIC -DLINUX -Wall -funsigned-char \
		-I$(INC_DIR) -I$(ROOT_INC) -I$(ROOTCFLAGS)

all: $(BIN_DIR) $(OBJ_DIR) reformatting

reformatting: 		main.o MakeDAQFile.o MakeCAENFile.o MakeDIPFile.o utils.o
					g++ $(CFLAGS) $(OBJ_DIR)/main.o \
					$(OBJ_DIR)/utils.o \
					$(OBJ_DIR)/MakeDAQFile.o \
					$(OBJ_DIR)/MakeCAENFile.o \
					$(OBJ_DIR)/MakeDIPFile.o \
        			-o $(BIN_DIR)/reformatting \
        			$(LFLAGS) \
        		 	-l curses

main.o:
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.cc -o $(OBJ_DIR)/main.o
utils.o:
	$(CC) $(CFLAGS) -c $(SRC_DIR)/utils.cc -o $(OBJ_DIR)/utils.o
MakeDAQFile.o:
	$(CC) $(CFLAGS) -c $(SRC_DIR)/MakeDAQFile.cc -o $(OBJ_DIR)/MakeDAQFile.o
MakeCAENFile.o:
	$(CC) $(CFLAGS) -c $(SRC_DIR)/MakeCAENFile.cc -o $(OBJ_DIR)/MakeCAENFile.o
MakeDIPFile.o:
	$(CC) $(CFLAGS) -c $(SRC_DIR)/MakeDIPFile.cc -o $(OBJ_DIR)/MakeDIPFile.o

$(BIN_DIR):
	mkdir -p $(BIN_DIR)/

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)/
	
clean:
	rm -rf $(BIN_DIR)/
	rm -rf $(OBJ_DIR)/

remove:
	rm -rf $(BIN_DIR)/
	rm -rf $(OBJ_DIR)/
	
