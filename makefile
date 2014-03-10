SOURCE_EXT=cpp
OBJ_EXT=o
HEAD_EXT=h

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

MODULES   := engine 
SRC_DIR   := $(addprefix $(SRC_PATH)/,$(MODULES))
SRC_DIR   += $(SRC_PATH)
BUILD_DIR := $(addprefix $(OBJ_PATH)/,$(MODULES))

SRC       := $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.cpp))
OBJ       := $(patsubst $(SRC_PATH)/%.cpp,$(OBJ_PATH)/%.o,$(SRC))
INCLUDES  := $(addprefix -I,$(SRC_DIR))
.PHONY: clean cleanall run test debug

vpath %.cpp $(SRC_DIR)


all: checkdirs $(DEFAULT_DEBUG) $(EXECUTABLE) 

debug: CFLAGS += $(DFLAGS)
debug: $(EXECUTABLE)


$(EXECUTABLE): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $@

$(BUILD_DIR)/%.$(OBJ_EXT): %.$(SOURCE_EXT) 
	$(CC) $(CFLAGS) $< -o $@


cleanall: clean
	rm -f $(EXECUTABLE)

proper: clean cleanall

re: proper all

redo: proper debug

checkdirs: $(BUILD_DIR)

$(BUILD_DIR):
	mkdir -p $@
clean:
	rm -rf $(BUILD_DIR)

run:
	cd $(BIN_PATH) && ./$(EXECUTABLE_NAME)

test:
	cd $(BIN_PATH) && gdb -tui $(EXECUTABLE_NAME)
