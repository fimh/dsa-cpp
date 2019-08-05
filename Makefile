CXX		  := clang++
CXX_FLAGS := -Wall -Wextra -std=c++11 -g # change to c++11 accroding to google's c++ style guide

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib

LIBRARIES	:=
EXECUTABLE	:= main


all: $(BIN)/$(EXECUTABLE)

run: clean all
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*

# create output directory if needed
# for details, refer to https://stackoverflow.com/a/45048948
$(shell mkdir -p $(BIN))