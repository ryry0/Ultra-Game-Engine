SOURCE_EXT=cpp
OBJ_EXT=o
HEAD_EXT=h
OBJ_HEAD_EXT=gch
BIN_PATH=bin
SRC_PATH=src
OBJ_PATH=obj
INC_PATH=inc
CC=g++
CFLAGS=-c -I$(INC_PATH) -std=c++11
LDFLAGS= -lSDL2 -lSDL2_image -lSDL2_ttf -lGL
DFLAGS=-DDEBUG -ggdb -g3 -Wall
DEFAULT_DEBUG=debug

EXECUTABLE_NAME=Game.x
EXECUTABLE=$(addprefix $(BIN_PATH)/,$(EXECUTABLE_NAME))

SOURCE_NAMES=$(shell ls $(SRC_PATH))
SOURCES=$(addprefix $(SRC_PATH)/,$(SOURCE_NAMES))
OBJECT_NAMES=$(SOURCE_NAMES:.$(SOURCE_EXT)=.$(OBJ_EXT))
OBJECTS=$(addprefix $(OBJ_PATH)/,$(OBJECT_NAMES))

.PHONY: clean cleanall run test debug

all: $(DEFAULT_DEBUG) $(SOURCES) $(EXECUTABLE) 

debug: CFLAGS += $(DFLAGS)
debug: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

$(OBJ_PATH)/%.$(OBJ_EXT): $(SRC_PATH)/%.$(SOURCE_EXT) $(wildcard $(INC_PATH)/*.$(HEAD_EXT))
	$(CC) $(CFLAGS) $< -o $@


cleanall: clean
	rm -f $(EXECUTABLE)

proper: clean cleanall

re: proper all

redo: proper debug

clean:
	rm -f $(wildcard $(OBJ_PATH)/*.$(OBJ_EXT)) 

run:
	cd $(BIN_PATH) && ./$(EXECUTABLE_NAME)

test:
	cd $(BIN_PATH) && gdb -tui $(EXECUTABLE_NAME)
