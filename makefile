
APP:=game

SRC_CC := $(wildcard ./src/*.cc)
SRC := $(notdir $(SRC_CC:%.cc=%))
OBJ := $(SRC:%=bin/%.o)

CFLAGS := -Wall -MMD -pthread -std=c++14
LDFLAGS := -pthread -std=c++14
LDLIBS := -lstdc++


.PHONY: all clean debug

all: bin/$(APP)

bin/%.o: src/%.cc
	@mkdir -p bin/
	@echo compiling 
	@$(CXX) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

bin/$(APP): $(OBJ)
	@mkdir -p bin/
	@$(CXX) -o $@ $(LDFLAGS) $(LDLIBS) $(OBJ) 

clean:
	rm -f bin/*
