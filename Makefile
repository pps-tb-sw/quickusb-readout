# Project: QuickUSB Console Demo
# Makefile created by Dev-C++ 4.9.9.2

CPP  = g++.exe
CC   = gcc.exe
WINDRES = windres.exe
LINKOBJ  = APIUSB.o
LIBS =  -L"C:/Dev-Cpp/lib" -L"C:/Projects/Bitwise/QuickUSB/Library/Software/QuickUsbMingw" libquickusb.a  
INCS =  -I"C:/Dev-Cpp/include" 
CXXINCS =  -I"C:/Dev-Cpp/lib/gcc/mingw32/3.4.2/include" -I"include" -I"C:/Dev-Cpp/include/c++/3.4.2/backward"  -I"C:/Dev-Cpp/include/c++/3.4.2/mingw32"  -I"C:/Dev-Cpp/include/c++/3.4.2"  -I"C:/Dev-Cpp/include" 
BIN  = console.exe
CXXFLAGS = $(CXXINCS)  
CFLAGS = $(INCS) --add-stdcall-alias  
LFLAGS := C:\Windows\System32\QuickUSB.dll -lws2_32
RM = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before console.exe all-after


clean: clean-custom
	${RM} $(LINKOBJ) $(BIN)

$(BIN): Console.cpp $(LINKOBJ)
	$(CPP) $^ -o "console.exe" $(LIBS) $(CXXINCS) $(LFLAGS)

readout.exe: readout.cpp PlatformIndependentTimer.o $(LINKOBJ)
	$(CPP) $^ -o "readout.exe" $(LIBS) $(CXXINCS) $(LFLAGS)

#PlatformIndependentTimer.o: PlatformIndependentTimer.cpp
#	$(CPP) -c PlatformIndependentTimer.cpp -o PlatformIndependentTimer.o $(CXXFLAGS)