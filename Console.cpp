/*=============================================================================
 Title        : Console.cpp
 Description  : QuickUSB Console App for CT-PPS
 Authors      : CT-PPS DAQ Team
=============================================================================*/

#include <iostream>
#include <iomanip> 
#include <sstream>
#include <fstream>
#include <algorithm>
#include <string>
#include <cstring>
#include <bitset>
#include <stdlib.h>
#include <stdio.h>

#include "QuickUSB.h"
#include "APIUSB.h"

using namespace std;

void
ConfigureQuickUSB(QHANDLE device)
{
  ////////////////////////////////////////
  // QUICK USB SETTINGS 
  ////////////////////////////////////////
  
  unsigned short bitvalue;
  
  // SETTING_WORDWIDE   
  QuickUsbWriteSetting(device, 1, 0); // This sets it to 8 bits
  QuickUsbReadSetting(device, 1, &bitvalue);
  std::cout <<"* NEW SETTING_WORDWIDE   = "<< std::bitset<8>(bitvalue) << std::endl;
  
  // SETTING_DATAADDRESS 
  // New Setting = 0000000111111111 = 0x01FF
  //QuickUsbWriteSetting(device, 2, 0x01FF);
  //QuickUsbReadSetting(device, 2, &bitvalue);
  //std::cout <<"* NEW SETTING_DATAADDRESS    = "<< std::bitset<16>(bitvalue) << std::endl;
  
  // SETTING_FIFO_CONFIG 
  //QuickUsbReadDefault(device, 3, &bitvalue);
  //std::cout <<"  DEFAULT SETTING_FIFO_CONFIG    = "<< std::bitset<16>(bitvalue) << std::endl;
  // DEFAULT SETTING_FIFO_CONFIG    = 0000000000000010
  // New setting = 0000000011000010 = 0x82 
  QuickUsbWriteSetting(device, 3, 0x82 );
  QuickUsbReadSetting(device, 3, &bitvalue);
  std::cout <<"* NEW SETTING_FIFO_CONFIG = "<< std::bitset<16>(bitvalue) << std::endl;
  
  // SETTING_CPUCONFIG
  //QuickUsbReadDefault(device, 5, &bitvalue);
  //std::cout <<"  DEFAULT SETTING_CPUCONFIG      = "<< std::bitset<16>(bitvalue) << std::endl; 
  QuickUsbWriteSetting(device, 5, 0x8012);
  QuickUsbReadSetting(device, 5, &bitvalue);
  std::cout <<"* NEW SETTING_CPUCONFIG  = "<< std::bitset<16>(bitvalue) << std::endl;
}	

int
CheckReadback(QHANDLE device, unsigned short addr)
{        
  /////////////////////////////////////////////
  // CHECKING READBACK VALUE FOR ADDRESS addr
  /////////////////////////////////////////////
  
  unsigned short length = 2;
  unsigned char* data = new unsigned char[length];
  
  int result = QuickUsbReadCommand(device, addr, data, &length);
  if (!result) {
    std::cerr << "Cannot read register 0x" << std::hex << addr << " on board " << std::dec << device << std::endl;
    return 1;
  }
  for (int i=0; i<length; i++) {
    cout << "data " << i << " = 0x"<< hex << (int)data[i] << endl;
  }
  
  delete [] data;
  return 0;
}

struct Version {
  QWORD MajorVersion, MinorVersion, BuildVersion;
};

Version
GetFWVersion(QHANDLE device)
{
  // Get Firmware Version 
  QWORD major, minor, build;
  QuickUsbGetFirmwareVersion(device, &major, &minor, &build);
  cout << "==============================" << endl;
  cout << "=                            =" << endl;
  cout << "= Firmware Version = " << major <<"."<< minor <<"." << build << "  =" << endl;
  
  Version out;
  out.MajorVersion = major;
  out.MinorVersion = minor;
  out.BuildVersion = build;
  return out;
}

Version
GetDriverVersion(QHANDLE device)
{
  // Get Driver Version 
  QWORD major, minor, build;
  QuickUsbGetDriverVersion(&major, &minor, &build);
  cout << "= Driver Version   = " << major <<"."<< minor <<"." << build << "  =" << endl;
  
  Version out;
  out.MajorVersion = major;
  out.MinorVersion = minor;
  out.BuildVersion = build;
  return out;
}

Version
GetDLLVersion(QHANDLE device)
{
  // Get dll version 
  QWORD major, minor, build;
  QuickUsbGetDllVersion(&major, &minor, &build);
  cout << "= DLL Version      = " << major <<"."<< minor <<"." << build << "  =" << endl;
  cout << "=                            =" << endl;
  cout << "==============================" << endl;
  cout << "" << endl;
  
  Version out;
  out.MajorVersion = major;
  out.MinorVersion = minor;
  out.BuildVersion = build;
  return out;
}

void
ReadIDCode(QHANDLE device)
{
  /////////////////////////////////////////////
  // GET ID CODE
  /////////////////////////////////////////////
  
  unsigned char *writedata = API::GetIDCode();
  unsigned char readdata[4];
  int result;
  
  cout << "header of write data " << setbase(16) << (int)writedata[0]<< endl;

  result = QuickUsbWriteCommand(device, 0,  writedata, 1);
  
  unsigned short length = 4;
  result = QuickUsbReadCommand(device, 1, readdata, &length);
  
  API::ReadGetIDCode(readdata);
}

int main(int argc, char* argv[])
{
  char *namePtr;
  char nameList[120];
  unsigned char data2read[20], data2write[20];
  unsigned short length, paraddress, bitvalue, value2write, addressvalue;
  unsigned long count, len, errorCode, length2read = 2, length2write = 2;
  int result, ReadResult, WriteResult, ReadSettings, WriteSettings;
  QHANDLE hDev;
  
  //  Find the QuickUSB modules in the system
  len = 512;
  result = QuickUsbFindModules(nameList, len);
  
  // Check for no modules and bail if we don't find any
  if (*nameList == '\0') {
    std::cerr << "Couldn't find any QuickUSB module on this computer!" << std::endl;
    return -1;
  }
  
  // Print out the name of each module found
  namePtr = nameList;
  while (*namePtr != '\0') {
    printf("Found %s\n", namePtr);
    namePtr = namePtr + strlen(namePtr) + 1;
  }
  
  // Open the first device
  result = QuickUsbOpen(&hDev, nameList);
  if (!result) {
    printf("Cannot open %s\n", nameList);
    return 1;
  }
	
/*
  GetFWVersion(hDev);
  GetDriverVersion(hDev);
  GetDLLVersion(hDev);
*/

  ConfigureQuickUSB(hDev);
  
  CheckReadback(hDev, 0x70);
  
  ReadIDCode(hDev);
  
//#ifdef DEBUG
  /////////////////////////////////////////////
  // SETTING UP FPGA/HPTDC
  /////////////////////////////////////////////
  const unsigned short size1=51, size2=31;
  unsigned char * writeSetup = API::SetSetupReg();
  unsigned char * Setup2Write1=(unsigned char *)malloc(size1);
  unsigned char * Setup2Write2=(unsigned char *)malloc(size2);
  //for (int i=0; i < 51 ; i++){cout << "writeSetup [" << i <<"] = " << (unsigned int)writeSetup[i]<<endl;}
  
  //std::copy(writeSetup, writeSetup+51, Setup2Write);
  //cout << sizeof(writeSetup) << " -- " << sizeof(unsigned char) << endl;
  memcpy(Setup2Write1, writeSetup, size1);
  memcpy(Setup2Write2, writeSetup+size1, size2);
  for (int i=0; i < size1 ; i++){cout << std::dec << "Setup2Write1 [" << i <<"] = " << std::hex << (unsigned short)Setup2Write1[i]<<" /// " << (unsigned short)writeSetup[i]<<endl;}
  for (int i=0; i < size2 ; i++){cout << std::dec << "Setup2Write2 [" << i+size1 <<"] = " << std::hex << (unsigned short)Setup2Write2[i]<<" /// " << (unsigned short)writeSetup[size1+i]<<endl;}
  result = QuickUsbWriteCommand(hDev, 0,  Setup2Write1, size1);
  QuickUsbGetLastError(&errorCode);
  cout << "result 1=" << errorCode << endl;
  result = QuickUsbWriteCommand(hDev, size1,  Setup2Write2, size2);
  QuickUsbGetLastError(&errorCode);
  cout << "result 2=" << errorCode << endl;
  
  /////////////////////////////////////////////
  // READ BACK THE SETTINGS OF FPGA/HPTDC
  /////////////////////////////////////////////
  
  unsigned char readsetup1[size1-1];
  unsigned char readsetup2[size2];
  unsigned char readsetup[size1-1+size2];

  unsigned char *writedata = API::GetSetupReg();
  cout << "header of getting setup " << setbase(16) << (int)writedata[0]<< endl;
  length =1;
  result = QuickUsbWriteCommand(hDev, 0,  writedata, length);
  QuickUsbGetLastError(&errorCode);
  cout << "result 1=" << errorCode << endl;
  
  length=size1-1;
  result = QuickUsbReadCommand(hDev, 1, readsetup1, &length);
  QuickUsbGetLastError(&errorCode);
  cout << "result 1=" << errorCode << endl;
  length=size2;
  result = QuickUsbReadCommand(hDev, size1, readsetup2, &length);
  QuickUsbGetLastError(&errorCode);
  cout << "result 2=" << errorCode << endl;
  for (int i=0; i < 81 ; i++){
    if (i<size1-1) readsetup[i] = readsetup1[i];
    else readsetup[i] = readsetup2[i-(size1-1)];
    cout << "readsetup[" << std::dec << i << "] = " << hex <<(unsigned short)readsetup[i] << endl;
  }
  
  API::ReadGetSetupReg(readsetup);
  /*		
		unsigned char * writeControl;
		writeControl=SetControlReg();
		length =6;
		result = QuickUsbWriteCommand(hDev, 0,  writeControl, length);
	
		
		
		unsigned char readControl[5];
		writedata=GetControlReg();
		cout << "header of getting Control " << setbase(16) << (int)writedata[0]<< endl;
		length =1;
		result = QuickUsbWriteCommand(hDev, 0,  writedata, length);
		length=5;
		result = QuickUsbReadCommand(hDev, 1, readControl, &length);
		cout << "Control 1 " << setbase(16) << (int)readControl[0] << endl;
		cout << "Control 2 " << setbase(16) << (int)readControl[1] << endl;
		cout << "Control 3 " << setbase(16) << (int)readControl[2] << endl;
		cout << "Control 4 " << setbase(16) << (int)readControl[3] << endl;
		cout << "Control 5 " << setbase(16) << (int)readControl[4] << endl;
		ReadGetControlReg(readControl);
*/
		
/*		unsigned char readStat[8];
	writedata=GetStatReg();
	cout << "header of getting Stat " << setbase(16) << (int)writedata[0]<< endl;
	length =1;
	result = QuickUsbWriteCommand(hDev, 0,  writedata, length);
	length=8;
	result = QuickUsbReadCommand(hDev, 1, readStat, &length);
	cout << "Stat 1 " << setbase(16) << (int)readStat[0] << endl;
	cout << "Stat 2 " << setbase(16) << (int)readStat[1] << endl;
	cout << "Stat 3 " << setbase(16) << (int)readStat[2] << endl;
	cout << "Stat 4 " << setbase(16) << (int)readStat[3] << endl;
	cout << "Stat 5 " << setbase(16) << (int)readStat[4] << endl;
	cout << "Stat 6 " << setbase(16) << (int)readStat[5] << endl;
	cout << "Stat 7 " << setbase(16) << (int)readStat[6] << endl;
	cout << "Stat 8 " << setbase(16) << (int)readStat[7] << endl;
	ReadGetStatReg(readStat);
*/
 
	
	
// Read the Command register at address 0
//	unsigned char *datacontrol;
//	datacontrol=SetControlReg();
	
/*	
  	if (argv[0]){
		data = SetControlReg (100);
		cout << " Word 0 = " << hex <<  data[0] << endl;
		cout << " Word 1 = " << hex <<  data[1] << endl;
		cout << " Word 2 = " << hex <<  data[2] << endl;
		cout << " Word 3 = " << hex <<  data[3] << endl;
		result = QuickUsbWriteCommand(hDev, 0, (unsigned char *) data, length);
	}
	
	if (argv[1]){
		data=GetControlReg();
		length =1;
		result = QuickUsbWriteCommand(hDev, 0, (unsigned char *) data, length);
		length=3;
		result = QuickUsbReadCommand(hDev, 1, (unsigned char *) data, &length);
		cout << "****************" << endl;
		cout << " Read data[0] = " << data[0] << endl;
		cout << " Read data[1] = " << data[1] << endl;
		cout << " Read data[2] = " << data[2] << endl;
		cout << " Read data[3] = " << data[3] << endl;
		cout << "****************" << endl;
	}
*/
/*
//	QuickUsbGetLastError(&errorCode);
//	std::cout << "Error Code  = " << errorCode << std::endl;
	if (result == FALSE) {
		printf("Cannot read %s command register\n", nameList);
		return 1;
	}
   //printf("ReadCommand address 0 = %04X\n");
	
*/	
	free(writeSetup);
	
//#endif
	// Close the port when you're done with it
	QuickUsbClose(hDev);

	
	return 0;
}



