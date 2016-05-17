#include <bitset>
#include <cstdlib>
#include <stdio.h>
#include <callfunc.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>		
#include <cstdlib>
#include <bitset>
using namespace std;




//Setting control register
unsigned short *SetControlReg (int control)
{

  const int nwords = 4;		//total number of words including header 

  unsigned short *ret = new unsigned short[nwords];	//number of words including header


  std::string headerstr = readheader ("SetControlReg");	//getting header from .dat file
  cout << headerstr.c_str() << endl;
  unsigned short header = bintohex (headerstr.c_str ());
 cout << "header is " << hex << (int) header << endl;

  ret = GetSixteenBits (control, nwords);
  ret[0] = header;
  return ret;
}





//Getting HPTDC control register
unsigned short *
GetControlReg (void)
{

  const int nbytes = 1;		//total number of bytes including header 

  unsigned short *ret = new unsigned short[nbytes];	//number of bytes including header

  std::string headerstr = readheader ("GetControlReg");	//getting header from .dat file
  unsigned short header = bintohex (headerstr.c_str ());

  ret[0] = header;
  ret[1]=0;
  ret[2]=0;
  ret[3]=0;
  return ret;

}







// AUXILIAR FUNCTIONS

std::string readheader (string header = "")
{
  std::ifstream inputFile ("data.dat");
  std::string line;

  std::string result = "0";

  while (std::getline (inputFile, line))
    {


      std::string col1, col2;
      std::istringstream ss (line);
      ss >> col1 >> col2;
      if (col1 == header)
	result = col2;

    }

  return result;
}

unsigned short
bintohex (const char *digits)
{
  unsigned short res = 0;
  while (*digits)
    res = (res << 1) | (*digits++ - '0');
  return res;
}



unsigned short *
GetSixteenBits (int parameter, const int nwords)
{


  unsigned short *ret = new unsigned short[nwords];	//number of words including header

  const int wordsafterheader = nwords - 1;

  int factor = 65535;		// mask lowest 16 bits in decimal
  for (int i = 0; i < wordsafterheader; i++)
    {

      int nEventspart = parameter & factor;	// mask next 16 bits
      
      unsigned short nEventspartfinal = nEventspart >> 16 * i;	// rightshift by 14 bits
      

      ret[wordsafterheader - i] = nEventspartfinal;

      factor *= 65536;



    }


  ret[0] = 0;			//filling the header with 0 for now

  return ret;

}
