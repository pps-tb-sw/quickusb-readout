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
#include <unistd.h> // sleep

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
  std::cout <<"* (1)  SETTING_WORDWIDE       = "<< std::bitset<16>(bitvalue) << std::hex << " = 0x" << std::setw(4) << std::setfill('0') << bitvalue << std::endl;
  
  // SETTING_DATAADDRESS
  // New Setting = 0000000111111111 = 0x01FF
  //QuickUsbWriteSetting(device, 2, 0x01FF);
  QuickUsbReadSetting(device, 2, &bitvalue);
  std::cout <<"* (2)  SETTING_DATAADDRESS    = "<< std::bitset<16>(bitvalue) << std::hex << " = 0x" << std::setw(4) << std::setfill('0') << bitvalue << std::endl;
  
  // SETTING_FIFO_CONFIG 
  //QuickUsbReadDefault(device, 3, &bitvalue);
  //std::cout <<"  DEFAULT SETTING_FIFO_CONFIG    = "<< std::bitset<16>(bitvalue) << std::hex << " = 0x" << std::setw(4) << std::setfill('0') << bitvalue << std::endl;
  // DEFAULT SETTING_FIFO_CONFIG    = 0000000000000010
  // New setting = 0000000011000010 = 0x82 
  QuickUsbWriteSetting(device, 3, 0x82 );
  QuickUsbReadSetting(device, 3, &bitvalue);
  std::cout <<"* (3)  SETTING_FIFO_CONFIG    = "<< std::bitset<16>(bitvalue) << std::hex << " = 0x" << std::setw(4) << std::setfill('0') << bitvalue << std::endl;

  // SETTING_FPGATYPE
  QuickUsbReadSetting(device, 4, &bitvalue);
  std::cout <<"* (4)  SETTING_FPGA_TYPE      = "<< std::bitset<16>(bitvalue) << std::hex << " = 0x" << std::setw(4) << std::setfill('0') << bitvalue << std::endl;
  
  // SETTING_CPUCONFIG
  //QuickUsbReadDefault(device, 5, &bitvalue);
  //std::cout <<"  DEFAULT SETTING_CPUCONFIG      = "<< std::bitset<16>(bitvalue) << std::hex << " = 0x" << std::setw(4) << std::setfill('0') << bitvalue << std::endl; 
  QuickUsbWriteSetting(device, 5, 0x8012);
  QuickUsbReadSetting(device, 5, &bitvalue);
  std::cout <<"* (5)  SETTING_CPUCONFIG      = "<< std::bitset<16>(bitvalue) << std::hex << " = 0x" << std::setw(4) << std::setfill('0') << bitvalue << std::endl;

  // SETTING_FPGATYPE
  QuickUsbReadSetting(device, 6, &bitvalue);
  std::cout <<"* (6)  SETTING_SPICONFIG      = "<< std::bitset<16>(bitvalue) << std::hex << " = 0x" << std::setw(4) << std::setfill('0') << bitvalue << std::endl;

  // SETTING_SLAVEFIFOFLAGS
  QuickUsbReadSetting(device, 7, &bitvalue);
  std::cout <<"* (7)  SETTING_SLAVEFIFOFLAGS = "<< std::bitset<16>(bitvalue) << std::hex << " = 0x" << std::setw(4) << std::setfill('0') << bitvalue << std::endl;

  // SETTING_I2CTL
  QuickUsbReadSetting(device, 8, &bitvalue);
  std::cout <<"* (8)  SETTING_I2CTL          = "<< std::bitset<16>(bitvalue) << std::hex << " = 0x" << std::setw(4) << std::setfill('0') << bitvalue << std::endl;

  // SETTING_PORTA
  QuickUsbReadSetting(device, 9, &bitvalue);
  std::cout <<"* (9)  SETTING_PORTA          = "<< std::bitset<16>(bitvalue) << std::hex << " = 0x" << std::setw(4) << std::setfill('0') << bitvalue << std::endl;

  // SETTING_PORTB
  QuickUsbReadSetting(device, 10, &bitvalue);
  std::cout <<"* (10) SETTING_PORTB          = "<< std::bitset<16>(bitvalue) << std::hex << " = 0x" << std::setw(4) << std::setfill('0') << bitvalue << std::endl;

  // SETTING_PORTC
  QuickUsbReadSetting(device, 11, &bitvalue);
  std::cout <<"* (11) SETTING_PORTC          = "<< std::bitset<16>(bitvalue) << std::hex << " = 0x" << std::setw(4) << std::setfill('0') << bitvalue << std::endl;

  // SETTING_PORTD
  QuickUsbReadSetting(device, 12, &bitvalue);
  std::cout <<"* (12) SETTING_PORTD          = "<< std::bitset<16>(bitvalue) << std::hex << " = 0x" << std::setw(4) << std::setfill('0') << bitvalue << std::endl;

  // SETTING_PORTE
  QuickUsbReadSetting(device, 13, &bitvalue);
  std::cout <<"* (13) SETTING_PORTE          = "<< std::bitset<16>(bitvalue) << std::hex << " = 0x" << std::setw(4) << std::setfill('0') << bitvalue << std::endl;

  // SETTING_PORTACCFG
  QuickUsbReadSetting(device, 14, &bitvalue);
  std::cout <<"* (14) SETTING_PORTACCFG      = "<< std::bitset<16>(bitvalue) << std::hex << " = 0x" << std::setw(4) << std::setfill('0') << bitvalue << std::endl;

  // SETTING_PINFLAGS
  QuickUsbReadSetting(device, 15, &bitvalue);
  std::cout <<"* (15) SETTING_PINFLAGS       = "<< std::bitset<16>(bitvalue) << std::hex << " = 0x" << std::setw(4) << std::setfill('0') << bitvalue << std::endl;

  // SETTING_VERSIONSPEED
  QuickUsbReadSetting(device, 17, &bitvalue);
  std::cout <<"* (17) SETTING_VERSIONSPEED   = "<< std::bitset<16>(bitvalue) << std::hex << " = 0x" << std::setw(4) << std::setfill('0') << bitvalue << std::endl;

  // SETTING_TIMEOUT_HIGH
  QuickUsbReadSetting(device, 18, &bitvalue);
  std::cout <<"* (18) SETTING_TIMEOUT_HIGH   = "<< std::bitset<16>(bitvalue) << std::hex << " = 0x" << std::setw(4) << std::setfill('0') << bitvalue << std::endl;

  // SETTING_TIMEOUT_LOW
  QuickUsbReadSetting(device, 19, &bitvalue);
  std::cout <<"* (19) SETTING_TIMEOUT_LOW    = "<< std::bitset<16>(bitvalue) << std::hex << " = 0x" << std::setw(4) << std::setfill('0') << bitvalue << std::endl;
}	

int
CheckReadback(QHANDLE device, unsigned short addr)
{        
  /////////////////////////////////////////////
  // CHECKING READBACK VALUE FOR ADDRESS addr
  /////////////////////////////////////////////
  
  unsigned short length = 2;
  unsigned char* data = new unsigned char[length]();
  if (!data) return -999;
  const unsigned char correct_value = 0x80;
  
  int result = QuickUsbReadCommand(device, addr, data, &length);
  if (result==0) {
    std::cerr << "Cannot read register 0x" << std::hex << addr << " on board " << std::dec << device << std::endl;
    return -2;
  }
  bool success = true;
  for (int i=0; i<length; i++) {
    if (data[i]!=correct_value) { success = false; }
  }
  delete [] data;

  if (!success) return -1;
  
  return 0;
}

struct Version {
  QWORD MajorVersion, MinorVersion, BuildVersion;
  void Dump() const { std::cout << "Version = " << MajorVersion <<"."<< MinorVersion <<"." << BuildVersion << std::endl; }
};

Version
GetFWVersion(QHANDLE device)
{
  QWORD major, minor, build;
  QuickUsbGetFirmwareVersion(device, &major, &minor, &build);
  
  Version out;
  out.MajorVersion = major;
  out.MinorVersion = minor;
  out.BuildVersion = build;
  return out;
}

Version
GetDriverVersion(QHANDLE device)
{
  QWORD major, minor, build;
  QuickUsbGetDriverVersion(&major, &minor, &build);
  
  Version out;
  out.MajorVersion = major;
  out.MinorVersion = minor;
  out.BuildVersion = build;
  return out;
}

Version
GetDLLVersion(QHANDLE device)
{
  QWORD major, minor, build;
  QuickUsbGetDllVersion(&major, &minor, &build);
  
  Version out;
  out.MajorVersion = major;
  out.MinorVersion = minor;
  out.BuildVersion = build;
  return out;
}

bool
CheckIDCode(QHANDLE device)
{
  /////////////////////////////////////////////
  // GET ID CODE
  /////////////////////////////////////////////
  
  unsigned char *writedata = new unsigned char[1]();
  API::GetIDCode(writedata);
  unsigned char readdata[4];
  for (unsigned short i=0; i<4; i++) { readdata[i] = 0x0; }
  int result;
  
  result = QuickUsbWriteCommand(device, 0,  writedata, 1);
  
  unsigned short length = 4;
  result = QuickUsbReadCommand(device, 1, readdata, &length);
  
  return (API::ReadGetIDCode(readdata)==2221988558);
}

void
WriteHPTDCSetup(QHANDLE device)
{
  /////////////////////////////////////////////
  // SETTING UP FPGA/HPTDC
  /////////////////////////////////////////////
  const unsigned short size1=51, size2=31;
  int result;
  unsigned long errorCode;
  
  unsigned char* writeSetup = API::SetSetupReg();
  
  unsigned char* Setup2Write1 = new unsigned char[size1];
  memcpy(Setup2Write1, writeSetup, size1);
  
  unsigned char* Setup2Write2 = new unsigned char[size2];
  memcpy(Setup2Write2, writeSetup+size1, size2);
  
  for (int i=0; i < size1 ; i++){cout << std::dec << "Setup2Write1 [" << i <<"] = 0x" << std::hex << (unsigned short)Setup2Write1[i]<<" /// " << (unsigned short)writeSetup[i]<<endl;}
  for (int i=0; i < size2 ; i++){cout << std::dec << "Setup2Write2 [" << i+size1 <<"] = 0x" << std::hex << (unsigned short)Setup2Write2[i]<<" /// " << (unsigned short)writeSetup[size1+i]<<endl;}
  
  result = QuickUsbWriteCommand(device, 0,  Setup2Write1, size1);
  QuickUsbGetLastError(&errorCode);
  cout << "result 1=" << errorCode << endl;
  
  usleep(5000);
  
  result = QuickUsbWriteCommand(device, size1,  Setup2Write2, size2);
  QuickUsbGetLastError(&errorCode);
  cout << "result 2=" << errorCode << endl;
  
  delete [] writeSetup;
  delete [] Setup2Write1;
  delete [] Setup2Write2;
  
  usleep(500);
  
} 
  
void
ReadHPTDCSetup(QHANDLE device)
{
  /////////////////////////////////////////////
  // READ BACK THE SETTINGS OF FPGA/HPTDC
  /////////////////////////////////////////////
  const unsigned short size1=50, size2=31;
  int result;
  unsigned long errorCode;
  unsigned short length;
  
  unsigned char readsetup1[size1];
  unsigned char readsetup2[size2];
  unsigned char readsetup[size1+size2];
  for (unsigned short i=0; i<size1+size2; i++) { readsetup[i] = 0x0; }
  for (unsigned short i=0; i<size1; i++) { readsetup1[i] = 0x0; }
  for (unsigned short i=0; i<size2; i++) { readsetup2[i] = 0x0; }
  
  unsigned char *writedata = API::GetSetupReg();
  cout << "header of getting setup 0x" << std::hex << (int)writedata[0]<< endl;
  result = QuickUsbWriteCommand(device, 0,  writedata, length=1);
  QuickUsbGetLastError(&errorCode);
  cout << "result 1=" << errorCode << endl;
  
  usleep(5000);
  
  // read back first part of the setup word
  length = size1;
  result = QuickUsbReadCommand(device, 1, readsetup1, &length);
  QuickUsbGetLastError(&errorCode);
  cout << "result 1=" << errorCode << endl;
  
  usleep(5000);
  
  // read back second part of the setup word
  length = size2;
  result = QuickUsbReadCommand(device, 1+size1, readsetup2, &length);
  QuickUsbGetLastError(&errorCode);
  cout << "result 2=" << errorCode << endl;
  
  for (unsigned short i=0; i<size1+size2; i++) {
    if (i<size1) readsetup[i] = readsetup1[i];
    else readsetup[i] = readsetup2[i-size1];
    cout << "readsetup[" << std::dec << i << "] = 0x" << std::hex << (unsigned short)readsetup[i] << endl;
  }
  
  API::ReadGetSetupReg(readsetup);
  
  delete [] writedata;
}

int main(int argc, char* argv[])
{
  char nameList[120];
  unsigned short length, paraddress, bitvalue, value2write, addressvalue;
  unsigned long count, errorCode, length2read = 2, length2write = 2;
  int result, ReadResult, WriteResult, ReadSettings, WriteSettings;
  QHANDLE hDev;
  
  //  Find the QuickUSB modules in the system
  result = QuickUsbFindModules(nameList, 120);

  // Check for no modules and bail if we don't find any
  if (*nameList=='\0') {
    std::cerr << "Couldn't find any QuickUSB module on this computer!" << std::endl;
    return -1;
  }
  
  // Print out the name of each module found
  char* namePtr = nameList;
  while (*namePtr!='\0') {
    printf("Found %s\n", namePtr);
    namePtr = namePtr + strlen(namePtr) + 1;
  }
  
  // Open the first device
  result = QuickUsbOpen(&hDev, nameList);
  if (result==0) {
    printf("Cannot open %s\n", nameList);
    return 1;
  }
	
  // Read all useful versions
  std::cout << "[Firmware] ";
  GetFWVersion(hDev).Dump();
  
  std::cout << "[Driver]   ";
  GetDriverVersion(hDev).Dump();
  
  std::cout << "[DLL]      ";
  GetDLLVersion(hDev).Dump();

  ConfigureQuickUSB(hDev);
  
  if (int rb_check=CheckReadback(hDev, 0x70)!=0) {
    std::cerr << "The readback check failed with status " << rb_check << std::endl;
  }

  if (!CheckIDCode(hDev)) {
    std::cerr << "The ID code was wrong!" << std::endl;
  }

  return 0;
  
//#ifdef DEBUG

  WriteHPTDCSetup(hDev);
  ReadHPTDCSetup(hDev);
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
	
//#endif
  // Close the port when you're done with it
  QuickUsbClose(hDev);
  
  return 0;
}



