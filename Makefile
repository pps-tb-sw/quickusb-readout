CPP  = g++
CC   = gcc
EXT_LIB = xpedaq/quickusb-2.15.2/
API_OBJ = obj/APIUSB.o
CXXINCS =  -Iinclude -I$(EXT_LIB)
BIN  = console.exe
OBJ_DIR = obj/
CXXFLAGS = $(CXXINCS)  
CFLAGS = $(CXXINCS) 
LFLAGS := -L$(EXT_LIB)/linux/lib/x86_64/ -lquickusb -Wl,-R$(EXT_LIB)/linux/lib/x86_64/
RM = rm -f

.PHONY: all clean

all: console.exe

clean:
	${RM} $(BIN) *.o

$(BIN): Console.cpp $(API_OBJ)
	$(CPP) $^ -o $@ $(CXXINCS) $(LFLAGS)

readout.exe: readout.cpp obj/PlatformIndependentTimer.o
	$(CPP) $^ -o $@ $(CXXINCS) $(LFLAGS)

$(OBJ_DIR)%.o: src/%.cpp include/%.h
	@echo "Building $<..."
	$(CPP) -c $(CXXFLAGS) $< -o $@
