
#
# sudo apt install libx11-dev libepoxy-dev libunittest++-dev
#

APP:=BlockSimulatedKingdom

SRC_CC := $(wildcard ./src/*.cc)
SRC := $(notdir $(SRC_CC:%.cc=%))
OBJ := $(SRC:%=bin/%.o)

CFLAGS := -Wall -O3 -pthread -std=c++17 -MMD
CFLAGS += -I /usr/include
LDFLAGS := -pthread
LDLIBS := -lstdc++ -lGLESv2 -lglfw -lpng

# Phony targets
.PHONY: all clean debug

#
# Bulid app
#
all: $(APP)
	@echo Done making $(APP)

#
# Debug the app
#
debug: CFLAGS += -g3
debug: all

#
# Compile
#
bin/%.o: src/%.cc
	@mkdir -p bin/
	@echo compiling $<
	@$(CXX) -c $(CFLAGS) $(CPPFLAGS) -o $@ $< 

#
# Link
#
$(APP): $(OBJ)		
	@echo linking $@
	@$(CXX) -o $@ $(OBJ) $(LDFLAGS) $(LDLIBS)

#
# Clean
#
clean:
	@echo cleaning
	rm -f bin/*
	rm -f $(APP)

-include $(OBJ:.o=.d)		
