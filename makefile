
APP:=BlockSimulatedKingdom

SRC_CC := $(wildcard ./src/*.cc)
SRC := $(notdir $(SRC_CC:%.cc=%))
OBJ := $(SRC:%=bin/%.o)

#sudo apt install libx11-dev libepoxy-dev

PKGS := epoxy x11

CFLAGS := -Wall -O3 -pthread -std=c++14 -MMD
CFLAGS += $(shell pkg-config --cflags $(PKGS))
CFLAGS += -I /usr/include 

LDFLAGS := -pthread -std=c++14
LDFLAGS += $(shell pkg-config --libs $(PKGS))

LDLIBS := -lstdc++ -lGLU -lGL -lXext

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
	@rm -f bin/*
	@rm -f $(APP)

-include $(OBJ:.o=.d)		
