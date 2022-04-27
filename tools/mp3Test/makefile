
#
# sudo apt install libmpg123-dev libao-dev
#

APP:=mp3Test

SRC_CC := $(notdir $(wildcard ./src/*.cc))
OBJ    := $(SRC_CC:%.cc=bin/%.o)

CFLAGS := -Wall -O3 -pthread -MMD
CFLAGS += -I src/ 
LDFLAGS := -pthread
LDLIBS := -lstdc++ -ldl -lmpg123 -lao

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
debug: CFLAGS += -Og -ggdb
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
