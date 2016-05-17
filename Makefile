CPP  = g++
CC   = gcc
EXT_LIB = xpedaq/quickusb-2.15.2/
APIOBJ  = APIUSB.o
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
	${RM} $(LINKOBJ) $(BIN) *.o

$(BIN): Console.cpp $(APIOBJ)
	$(CPP) $^ -o "console.exe" $(CXXINCS) $(LFLAGS)

readout.exe: readout.cpp PlatformIndependentTimer.o $(LINKOBJ)
	$(CPP) $^ -o "readout.exe" $(CXXINCS) $(LFLAGS)

%.o: %.cpp %.h
	@echo "Building $<..."
	$(CPP) -c $(CXXFLAGS) $< -o $@
