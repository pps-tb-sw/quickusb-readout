#include "stdafx.h"
#include "windows.h"
#include "QuickUSB.h"
#include <iostream>
#include <stdio.h>
#include <bitset>
#include <stdlib.h>
#include <conio.h> 

using namespace std;

int main(int argc, char* argv[])
{

	printf("Read and Write Data test!\n");

	// Global Variables
	char nameList[120];
	char *namePtr;
	int result;


	//  Find the QuickUSB modules in the system
	unsigned long len = 512;
	result = QuickUsbFindModules(nameList, len);

	// Check for no modules and bail if we don't find any
	if (*nameList == '\0') {
		printf("Couldn't find any modules\n");
      		return 0;
	}

	// Print out the name of each module found
	char *namePtr;
	namePtr = nameList;
	while (*namePtr != '\0') {
		printf("Found %s\n", namePtr);
		namePtr = namePtr + strlen(namePtr) + 1;
	}

	// Open the first device
	QHANDLE hDev;
	result = QuickUsbOpen(&hDev, nameList);
	if (result == FALSE) {
		printf("Cannot open %s\n", nameList);
		return 1;
	}

   	// Read some data
	unsigned char data2read[2];
	unsigned long errorCode, length2read = 2;

	ReadResult = QuickUsbReadData(hDev, data2read, &length2read);
	std::cout << "ReadResult = " << ReadResult << std::endl; 
	if (ReadResult == FALSE) {
		QuickUsbGetLastError(&errorCode);
		printf("Cannot read data from %s\n", nameList);
		std::cout << "Error Code  = " << errorCode << std::endl;
		//return 1;
	}

	// Close the port when you're done with it
	QuickUsbClose(hDev);

	printf("DONE");
	return 0;
}