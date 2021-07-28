
#
# sudo apt install libx11-dev libepoxy-dev libunittest++-dev
#

APP:=fontCreator

SRC_CC := $(notdir $(wildcard ./src/*.cc))
OBJ    := $(SRC_CC:%.cc=bin/%.o)

CFLAGS := -Wall -O3 -pthread -MMD
CFLAGS += -I src/ -I /usr/include/freetype2
LDFLAGS := -pthread
LDLIBS := -lstdc++ -lpng -ldl -lfreetype

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
# Compile C++
#
bin/%.o: src/%.cc
	@mkdir -p bin/
	@echo compiling $<
	@$(CXX) -c $(CFLAGS) -std=c++17 $(CPPFLAGS) -o $@ $<
	 
#
# Compile C
#
bin/%.o: src/%.c
	@mkdir -p bin/
	@echo compiling $<
	@$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $< 
	
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
