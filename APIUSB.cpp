#include <bitset>
#include <cstdlib>
#include <stdio.h>
#include <APIUSB.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>		
#include <cstdlib>
#include <bitset>
#include <iostream>
#include <iomanip> 
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

//#define ABS_PATH "C:\\Users\\Lara\\Desktop\\DAQ\\SetSettings\\"
#define ABS_PATH "C:\\QuickUSB-Marco-16May\\"


//Setting control register
unsigned char *SetControlReg (void)
{

  const int nwords = 6;		//total number of words including header 

  unsigned char *ret = new unsigned char[nwords];	//number of words including header


  std::string headerstr = readheader ("SetControlReg");	//getting header from .dat file
  unsigned char header = bintohex (headerstr.c_str ());
//////////////////////////////////////////////////////////////////////
cout << " enters setting control register " << endl;

  unsigned long control_parity=controlregister("control_parity");
  unsigned long pll_reset=controlregister("pll_reset");
  unsigned long dll_reset=controlregister("dll_reset");
  unsigned long enable_channel=controlregister("enable_channel");
  unsigned long global_reset=controlregister("global_reset");
  unsigned long enable_pattern=controlregister("enable_pattern");

  ret[0] = header;
  for (int index=1; index < nwords; index++){
  ret[index]=0;
  }	


  
  
  cout << " control parity is "  << hex << (int)control_parity << endl;
  ////////////// RET 1 /////////////////
  ret[1]= (control_parity << 7) | (pll_reset << 6) | (dll_reset << 5) ;
  ret[1] = ((enable_channel & 0xF8000000) >> 27) | ret[1] ;
  cout << "ret 1 is "  << hex << (int) ret[1] << endl;
  
  ////////////// RET 2 /////////////////
  ret[2]=(enable_channel & 0x7F80000) >> 19 ;
  
   ////////////// RET 3 /////////////////
   ret[3]= (enable_channel & 0x7F800) >> 11;
   
   
   ////////////// RET 4 /////////////////
   ret[4]= (enable_channel & 0x7F8) >> 3;
   
   ////////////// RET 5 /////////////////
   ret[5]= (enable_channel & 0x7) << 5;
   ret[5]= (global_reset << 4) | ret[5];
   ret[5]= enable_pattern | ret[5];
   
   
   
   
  
  
  return ret;
}





//Getting HPTDC control register
unsigned char *
GetControlReg (void)
{

  const int nwords = 6;		//total number of bytes including header 

  unsigned char *ret = new unsigned char[nwords];	//number of bytes including header

  std::string headerstr = readheader ("GetControlReg");	//getting header from .dat file
  unsigned char header = bintohex (headerstr.c_str ());

  ret[0] = header;
  for (int index=1; index < nwords; index++){
  ret[index]=0;
  }
  
  
  
  
 
  return ret;

}

void ReadGetControlReg (unsigned char * input)
{

  const int nwords = 5;		//total number of bytes without header

  unsigned char *ret = new unsigned char[nwords];	//number of bytes including header

  ret=input;

ofstream outFile("ReadGetControlReg.txt");


unsigned short control_parity= (ret[4] & 128) >> 7;
unsigned short pll_reset= (ret[4] & 64) >> 6;
unsigned short dll_reset= (ret[4] & 32) >> 5;
unsigned long enable_channel=((ret[4] & 31) << 27) | ((ret[3] & 255) << 19) | ((ret[2] & 255) << 11) | ((ret[1] & 255) << 3)| ((ret[0] & 224) >> 5);
unsigned short global_reset =((ret[0] & 16) >> 4);
unsigned short enable_pattern= ((ret[0]) & 15);

outFile << "control_parity  "<< setbase(10)<< control_parity   << endl;
outFile << "pll_reset  "<< setbase(10)<< pll_reset  << endl;
outFile << "dll_reset  "<< setbase(10)<< dll_reset  << endl;
outFile << "enable_channel  "<< setbase(10)<< enable_channel   << endl;
outFile << "global_reset  "<< setbase(10)<< global_reset   << endl;
outFile << "enable_pattern  "<< setbase(10)<< enable_pattern   << endl;


}


unsigned char * SetSetupReg  (void)
{
	
const int nwords=82; // number of 8 bits words + header
//unsigned char *ret =new unsigned char [nwords];
unsigned char *ret = (unsigned char *)malloc(nwords);
std::string headerstr = readheader ("SetSetupReg");
unsigned char header = bintohex (headerstr.c_str ());
std::cout << "---> " << headerstr << " / " << (unsigned short)header << std::endl;
//////////////////////////////////////////////////////////////////////

  ret[0] = header;
  for (int index=1; index < nwords; index++){
  ret[index]=0;
  }	

unsigned short TDC_ID=setupregister("TDC_ID");
unsigned short reject_count_offset=setupregister("reject_count_offset");
unsigned short search_window =setupregister("search_window");
unsigned short match_window =setupregister("match_window");
unsigned short fixed_pattern= setupregister("fixed_pattern");
unsigned short enable_fixed_pattern= setupregister("enable_fixed_pattern");
unsigned short trigger_count_offset = setupregister("trigger_count_offset");
unsigned short coarse_count_offset= setupregister("coarse_count_offset");
unsigned short rc_adjust =setupregister("rc_adjust");
unsigned short pll_control= setupregister("pll_control");
unsigned short roll_over= setupregister("roll_over") ;
unsigned short enable_pair =setupregister("enable_pair");
unsigned short enable_matching =setupregister("enable_matching");
unsigned short setup_parity =setupregister("setup_parity");
unsigned short enable_ttl_serial =setupregister("enable_ttl_serial");
unsigned short enable_ttl_hit =setupregister("enable_ttl_hit");
unsigned short enable_ttl_clock= setupregister("enable_ttl_clock");
unsigned short enable_ttl_reset= setupregister("enable_ttl_reset");
unsigned short enable_ttl_control =setupregister("enable_ttl_control");
unsigned short dll_mode =setupregister("dll_mode");
unsigned short mode_rc =setupregister("mode_rc");
unsigned short mode_rc_compression =setupregister("mode_rc_compression");
unsigned short enable_trailing =setupregister("enable_trailing");
unsigned short enable_leading =setupregister("enable_leading");
unsigned short enable_relative =setupregister("enable_relative");

 ////////////////////////////////// RET 1 ////////////
 ret[1] = (setup_parity << 6)  | ret[1];
 ret[1] = (enable_ttl_hit << 5)  | ret[1];
 ret[1] = (enable_ttl_clock << 4)  | ret[1];
 ret[1] = (enable_ttl_reset << 3)  | ret[1];
 ret[1] = (enable_ttl_control << 2)  | ret[1];
 ret[1] = (enable_ttl_serial << 1)  | ret[1]; 
 ret[1] = (enable_pair << 0)  | ret[1]; 
   
  // outFile << "ret 1 "<< hex << std::bitset<8>(ret[1]) << endl; // ret 1 OK &  
 
 ////////////////////////////////// RET 2 ////////////
 
 ret[2] =(enable_matching << 7) | ret[2];
 ret[2] = ((roll_over & 4064 ) >> 5) | ret[2];
 

 
////////////////////////////////// RET 3 ////////////

ret[3]=((roll_over & 31) << 3) | ret[3];
ret[3]= ret[3] | 3;



////////////////////////////////// RET 4 ////////////

ret[4]=64;
 
 ////////////////////////////////// RET 5 ////////////

ret[5]=0;

////////////////////////////////// RET 6 ////////////

ret[6]=((pll_control & 192) >> 6) | ret[6];
 

  
 ////////////////////////////////// RET 7////////////

ret[7]=((pll_control & 63) << 2) | ret[7];
ret[7] = dll_mode | ret[7];



 ////////////////////////////////// RET 8////////////

ret[8]=(mode_rc << 7);
ret[8]= (mode_rc_compression << 6) | ret[8];
ret[8]=(enable_leading << 5) | ret[8];
ret[8]= (enable_trailing << 4) | ret[8];



///////////////////////////////////RET 9 & 10

ret[9]=16;
ret[10]=0;

///////////////////////////////////RET 11 ////////////

ret[11]=(rc_adjust & 4064) >> 5;


///////////////////////////////////RET 12 ////////////

ret[12]=(rc_adjust & 31) << 3;





///////////////////////////////////RET 24 ////////////

ret[25] =(coarse_count_offset & 3584) >> 9;

///////////////////////////////////RET 25 ////////////

ret[26] =(coarse_count_offset & 510) >> 1;

///////////////////////////////////RET 26 ////////////

ret[27] =(coarse_count_offset & 1) << 7;

//outFile << "ret 1 "<< hex << std::bitset<8>(ret[24]) << std::bitset<8>(ret[25])<< std::bitset<8>(ret[26])<< endl; // ret 1 OK &  

///////////////////////////////////RET 62 ////////////
ret[62]=112;

///////////////////////////////////RET 63 ////////////
ret[63] =(ret[63] | 64);
ret[63] =((trigger_count_offset & 4032) >> 6) | ret[63];


///////////////////////////////////RET 64 ////////////

ret[64] =(trigger_count_offset & 63) << 2;

///////////////////////////////////RET 66 ////////////

ret[66] =41 | (enable_relative <<4);

///////////////////////////////////RET 67 ////////////

ret[67] =16; //(right now, fixed patter is set to 0)

///////////////////////////////////RET 71 ////////////

ret[71] =(match_window & 3840) >> 8 ; 

///////////////////////////////////RET 72////////////

ret[72] =(match_window & 255) ;



///////////////////////////////////RET 71 ////////////

ret[73] =(search_window & 4080) >> 4 ; 

///////////////////////////////////RET 74////////////

ret[74] =(search_window & 15) << 4 ;
ret[74] =((reject_count_offset & 3840) >> 8) | ret[74];

///////////////////////////////////RET 75////////////

ret[75] =(reject_count_offset & 255)  ;

///////////////////////////////////RET 76////////////

ret[76] =224 | TDC_ID  ;

///////////////////////////////////RET 77////////////

ret[77] =25  ;

///////////////////////////////////RET 78////////////
ret[78] =128  ;

///////////////////////////////////RET 79////////////
ret[79] =1  ;

///////////////////////////////////RET 80////////////
ret[80] =255 ;

///////////////////////////////////RET 81////////////
ret[81] =222 ;

 return ret;

}  


unsigned char * GetSetupReg   (void){
	
const int nwords=1;

unsigned char *ret =new unsigned char [nwords];

std::string headerstr = readheader ("GetSetupReg");

unsigned char header = bintohex (headerstr.c_str ());



  ret[0] = header;

  return ret;

}

void ReadGetSetupReg   (unsigned char * input){
	
const int nwords=81;

unsigned char *ret =new unsigned char [nwords];
ret=input;

std::ofstream outFile("ReadGetSetupReg.txt");



unsigned short setup_parity= (ret[80] & 64) >> 6;
unsigned short enable_ttl_hit= (ret[80] & 32) >> 5;
unsigned short enable_ttl_clock = (ret[80] & 16 ) >> 4;
unsigned short enable_ttl_reset = (ret[80] & 8) >> 3;
unsigned short enable_ttl_control =(ret[80] & 4) >> 2 ;
unsigned short enable_ttl_serial =(ret[80] & 2) >> 1;
unsigned short enable_pair=(ret[80] & 1);


outFile << "setup_parity  "<< setbase(10)<< setup_parity   << endl;
outFile << "enable_ttl_hit  "<< setbase(10)<< enable_ttl_hit   << endl;
outFile << "enable_ttl_clock  "<< setbase(10)<< enable_ttl_clock << endl;
outFile << "enable_ttl_reset  "<< setbase(10)<< enable_ttl_reset << endl;
outFile << "enable_ttl_control  "<< setbase(10)<< enable_ttl_control << endl;
outFile << "enable_ttl_serial  "<< setbase(10)<< enable_ttl_serial << endl;
outFile << "enable_pair  "<< setbase(10)<< enable_pair << endl;


unsigned short enable_matching = (ret[79] & 128  ) >> 7;
unsigned short roll_over= ((ret[79] & 127) << 5 ) | ((ret[78] & 248) >> 3);
unsigned short pll_control= ((ret[75] & 3) << 6) |  ((ret[74] & 252) >> 2) ;
unsigned short dll_mode =(ret[74] & 3);

outFile << "enable_matching  "<< setbase(10)<< enable_matching << endl;
outFile << "roll_over  "<< setbase(10)<< roll_over  << endl;
outFile << "pll_control  "<< setbase(10)<< pll_control << endl;
outFile << "dll_mode  "<< setbase(10)<< dll_mode<< endl;

unsigned short mode_rc= (ret[73] & 128) >> 7;
unsigned short mode_rc_compression= (ret[73] & 64) >> 6;
unsigned short enable_leading= (ret[73] & 32) >> 5;
unsigned short enable_trailing= (ret[73] & 16) >> 4;

outFile << "mode_rc  "<< setbase(10)<< mode_rc << endl;
outFile << "mode_rc_compression  "<< setbase(10)<< mode_rc_compression  << endl;
outFile << "enable_leading "<< setbase(10)<< enable_leading << endl;
outFile << "enable_trailing  "<< setbase(10)<< enable_trailing<< endl;

unsigned short rc_adjust= ((ret[70] & 127) <<5 ) | ((ret[69] & 240) >> 3);

outFile << "rc_adjust "<< setbase(10)<< rc_adjust << endl;




unsigned short coarse_count_offset=((ret[56] & 7) << 9) | ((ret[55] & 255) << 1) | ((ret[53] & 128) >> 7);
outFile << "coarse_count_offset "<< setbase(10)<< coarse_count_offset << endl;

unsigned short trigger_count_offset=((ret[18] & 63) << 6) | ((ret[17] & 252)>> 2);
outFile << "trigger_count_offset "<< setbase(10)<< trigger_count_offset << endl;

unsigned short enable_relative=((ret[15] & 16) >> 4) ;
outFile << "enable_relative "<< setbase(10)<< enable_relative << endl;


unsigned short match_window=((ret[10] & 15) << 8) | (ret[9] & 255) ;
outFile << "match_window "<< setbase(10)<< match_window << endl;


unsigned short search_window=( (ret[8] & 255) << 4) | ((ret[7] & 240) >>4) ;
outFile << "search_window "<< setbase(10)<< search_window << endl;

unsigned short reject_count_offset=((ret[7] & 15) << 8) | (ret[6] & 255) ;
outFile << "reject_count_offset "<< setbase(10)<< reject_count_offset << endl;



unsigned short prueba =(ret[5] & 15);
outFile << "TDC_ID  "<< setbase(10)<< prueba << endl;




}


unsigned char * GetStatReg  (void){
	
	const int nwords=1;

unsigned char *ret =new unsigned char [nwords];

std::string headerstr = readheader ("GetStatReg");
unsigned char header = bintohex (headerstr.c_str ());

  ret[0] = header;
  return ret;
}

 void ReadGetStatReg  (unsigned char *input){
	
const int nwords=8;

unsigned char *ret =new unsigned char [nwords];

  ret=input;

std::ofstream outFile("ReadGetStatReg.txt");



unsigned short dll_lock= (ret[7] & 32) >>5;
unsigned short trigger_fifo_empty=(ret[7] & 16) >> 4;
unsigned short trigger_fifo_full=(ret[7] & 8) >> 3;
unsigned short trigger_fifo_occupancy=((ret[7] & 3) << 2) | ((ret[6] & 192) >> 6) ;
unsigned short group0_1l_occupancy=((ret[6] & 63) << 2) |  ((ret[5] & 192 ) >> 6);
unsigned short group1_1l_occupancy=((ret[5] & 63) << 2) |  ((ret[4] & 192 ) >> 6);
unsigned short group2_1l_occupancy=((ret[4] & 63) << 2) |  ((ret[3] & 192 ) >> 6);
unsigned short group3_1l_occupancy=((ret[3] & 63) << 2) |  ((ret[2] & 192 ) >> 6);
unsigned short readout_fifo_empty=((ret[2] & 32) >> 5);
unsigned short readout_fifo_full=((ret[2] & 16) >> 4);
unsigned short readout_fifo_occupancy=((ret[2] & 15) << 4) | ((ret[1] & 240) >> 4);
unsigned short have_token =((ret[1] & 8) >> 3);
unsigned short jtag_instruction_error=((ret[1] & 4) >> 2);
unsigned short control_parity_error=((ret[1] & 2) >> 1);
unsigned short setup_parity_error=(ret[1] & 1);
unsigned short readout_state_error	=((ret[0] & 128) >> 7);
unsigned short readout_fifo_parity_error=((ret[0] & 64) >> 6);
unsigned short trigger_matching_state_error	=((ret[0] & 32) >> 5);
unsigned short trigger_fifo_parity_error=((ret[0] & 16) >> 4);	
unsigned short l1_buffer_parity_error =((ret[0] & 8) >> 3);
unsigned short channel_select_error=((ret[0] & 4) >> 2);
unsigned short coarse_error=((ret[0] & 2) >> 1);
unsigned short vernier_error=((ret[0] & 1) );

outFile  <<   "dll_lock  "<<  setbase(10) <<  dll_lock   <<  endl;
outFile <<  "trigger_fifo_empty "<<  setbase(10) << trigger_fifo_empty <<  endl;
outFile <<  "trigger_fifo_full "<<  setbase(10) << trigger_fifo_full <<  endl;
outFile <<  "trigger_fifo_occupancy "<<  setbase(10) << trigger_fifo_occupancy <<  endl;
outFile <<  "group0_1l_occupancy "<<  setbase(10) << group0_1l_occupancy <<  endl;
outFile <<  "group1_1l_occupancy "<<  setbase(10) << group1_1l_occupancy <<  endl;
outFile <<  "group2_1l_occupancy "<<  setbase(10) << group2_1l_occupancy <<  endl;
outFile <<  "group3_1l_occupancy "<<  setbase(10) << group3_1l_occupancy <<  endl;
outFile <<  "readout_fifo_empty "<<  setbase(10) << readout_fifo_empty <<  endl;
outFile <<  "readout_fifo_full "<<  setbase(10) << readout_fifo_full <<  endl;
outFile <<  "readout_fifo_occupancy "<<  setbase(10) <<  readout_fifo_occupancy <<  endl;
outFile <<  "have_token "<<   setbase(10) << have_token <<  endl;
outFile <<  "jtag_instruction_error "<<  setbase(10) << jtag_instruction_error <<  endl;
outFile <<  "control_parity_error "<<  setbase(10) << control_parity_error <<  endl;
outFile <<  "setup_parity_error "<<  setbase(10) << setup_parity_error <<  endl;
outFile <<  "readout_state_error "	 <<  setbase(10) << readout_state_error <<  endl;
outFile <<  "readout_fifo_parity_error "<<  setbase(10) << readout_fifo_parity_error <<  endl;
outFile <<  "trigger_matching_state_error "<<  setbase(10) << trigger_matching_state_error <<  endl;
outFile <<  "trigger_fifo_parity_error "<<  setbase(10) << 	trigger_fifo_parity_error <<  endl;
outFile <<  "l1_buffer_parity_error "<<  setbase(10) << l1_buffer_parity_error <<  endl;
outFile <<  "channel_select_error "<<  setbase(10) << channel_select_error <<  endl;
outFile <<  "coarse_error "<<  setbase(10) << coarse_error <<  endl;
outFile <<  "vernier_error "<<  setbase(10) << vernier_error <<  endl;

}


unsigned char * GetIDCode   (void){

	const int nwords=1;

unsigned char *ret =new unsigned char [nwords];

std::string headerstr = readheader ("GetIDCode");
unsigned char header = bintohex (headerstr.c_str ());

  ret[0] = header;
  return ret;
	
}   


void ReadGetIDCode   ( unsigned char * input){



const int nwords=4;

unsigned char *ret =new unsigned char [nwords];

ret= input;



unsigned long id_code= ((ret[3] & 255) << 24) | ((ret[2] & 255) << 16) | ((ret[1] & 255) << 8)| ((ret[0] & 255) );

ofstream outFile("ReadGetIDCode.txt");

outFile << setbase(10) << "id_code "<< id_code<< endl; // put on file
cout << setbase(10) << "id_code "<< id_code << endl; // outFile in the screen
	
}  


unsigned char *GetICR (void){
	
	const int nwords=1;

unsigned char *ret =new unsigned char [nwords];

std::string headerstr = readheader ("GetStatReg");
unsigned char header = bintohex (headerstr.c_str ());

  ret[0] = header;
  return ret;	
}         


void ReadGetICR (unsigned char * input){
	
	const int nwords=94;

unsigned char *ret =new unsigned char [nwords];

ret= input;

ofstream outFile("ReadGetICR.txt");
cout << "entra aqui"<< endl;

outFile << "========== GROUP 0 ========== "<< endl;

unsigned short load_hit_data= (ret[93] & 16) >> 4;
unsigned short select_error_detected = (ret[93] & 8) >> 3;
unsigned short channel= (ret[93] & 7) ;
unsigned short second_edge_type= (ret[92] & 128) >> 7;
unsigned short second_coarse_2_parity = ((ret[92] & 64) >> 6);
unsigned short second_coarse_2= ((ret[92] & 63) << 9) | ((ret[91] & 255) << 1) | ((ret[90] & 128) >> 7);
unsigned short second_coarse_1_parity=(ret[90] & 64 ) >> 6;
unsigned short second_coarse_1= ((ret[90] & 63) << 9) | ((ret[89] & 255) << 1) | ((ret[88] & 128) >> 7);
unsigned long  second_vernier = ((ret[88] & 127) << 25) | ((ret[87] & 255) << 17)  |  ((ret[86] & 255) << 9)  | ((ret[85] & 255) << 1)| ((ret[84] & 128) >> 7);
unsigned short first_edge_type = (ret[84] & 64) >> 6;
unsigned short first_coarse_2_parity= (ret[84] & 32) >> 5;
unsigned short first_coarse_2 = ((ret[84] & 31) << 10) | ((ret[83] & 255) << 2)| ((ret[82] & 192) >> 6) ;
unsigned short first_coarse_parity =((ret[82] & 32) >> 5);
unsigned short first_coarse_1 = ((ret[82] & 31) << 10) | ((ret[81] & 255) << 2) | ((ret[80] & 192) >> 6) ;
unsigned long first_vernier = ((ret[80] & 63) << 26 )  | ((ret[79] & 255) << 18 ) | ((ret[78] & 255) << 10 )| ((ret[77] & 255) << 2 ) | ((ret[76] & 192) >> 6 );

outFile << ""<< endl;
outFile << setbase(10) <<   "load_hit_data   "<< load_hit_data<< endl; // put on file
outFile << setbase(10) <<   "select_error_detected   "<< select_error_detected<< endl; // put on file
outFile << setbase(10) <<   "channel   "<< channel << endl; // put on file
outFile << setbase(10) <<   "load_hit_data  "<<  load_hit_data<< endl; 
outFile << setbase(10) <<   "select_error_detected   "<< select_error_detected<< endl; 
outFile << setbase(10) <<   "channel  "<<  channel<< endl; 
outFile << setbase(10) <<   "second_edge_type  "<<  second_edge_type<< endl; 
outFile << setbase(10) <<   "second_coarse_2  "<<  second_coarse_2<< endl; 
outFile << setbase(10) <<   "second_coarse_1  "<< second_coarse_1<< endl; 
outFile << setbase(10) <<   "second_vernier   "<<  second_vernier<< endl; 
outFile << setbase(10) <<   "first_edge_type   "<<  first_edge_type<< endl; 
outFile << setbase(10) <<   "first_coarse_2_parity  "<<  first_coarse_2_parity<< endl; 
outFile << setbase(10) <<   "first_coarse_2   "<< first_coarse_2<< endl; 
outFile << setbase(10) <<   "first_coarse_parity   "<< first_coarse_parity<< endl; 
outFile << setbase(10) <<   "first_coarse_1   "<<  first_coarse_1 << endl; 
outFile << setbase(10) <<   "first_vernier   "<< first_vernier<< endl; 



outFile << "========== GROUP 1 ========== "<< endl;

load_hit_data= ((ret[76]) & 32 ) >> 5;
select_error_detected= ((ret[76]) & 16) >> 4;
channel = (( ret[76]) & 14) >> 1 ;
second_edge_type =(( ret[76]) & 1) ;
second_coarse_2_parity = ((ret[75]) & 128) >> 7;
second_coarse_2 = ((ret[75]) & 127) << 8 | (ret[74] & 255);
second_coarse_1_parity  = ((ret[74]) & 128) >> 7;
second_coarse_1 = ((ret[73]) & 127) << 8 | (ret[72] & 255);
second_vernier = ((ret[71] & 255) << 24) | ((ret[70] & 255) << 16) | ((ret[69] & 255) << 8)| (ret[68] & 255);
first_edge_type = (ret[67] & 128) >> 7;
first_coarse_2_parity = (ret[67] & 64) >> 6;
first_coarse_2 = ((ret[67] & 63) <<9 ) | ((ret[66] & 255) <<1 ) | ((ret[65] & 128) >> 7 );
first_coarse_parity = ((ret[65] & 64) >> 6 );
first_coarse_1 = ((ret[65] & 63) <<9 ) | ((ret[64] & 255) <<1 ) | ((ret[63] & 128) >> 7 );
first_vernier = ((ret[63] & 127) << 25) | ((ret[62] & 255) << 17) |((ret[61] & 255) << 9) | ((ret[60] & 255) << 1) |  ((ret[59] & 128) >> 7) ;

outFile << ""<< endl;
outFile << setbase(10) <<   "load_hit_data   "<< load_hit_data<< endl; // put on file
outFile << setbase(10) <<   "select_error_detected   "<< select_error_detected<< endl; // put on file
outFile << setbase(10) <<   "channel   "<< channel << endl; // put on file
outFile << setbase(10) <<   "load_hit_data  "<<  load_hit_data<< endl; 
outFile << setbase(10) <<   "select_error_detected   "<< select_error_detected<< endl; 
outFile << setbase(10) <<   "channel  "<<  channel<< endl; 
outFile << setbase(10) <<   "second_edge_type  "<<  second_edge_type<< endl; 
outFile << setbase(10) <<   "second_coarse_2  "<<  second_coarse_2<< endl; 
outFile << setbase(10) <<   "second_coarse_1  "<< second_coarse_1<< endl; 
outFile << setbase(10) <<   "second_vernier   "<<  second_vernier<< endl; 
outFile << setbase(10) <<   "first_edge_type   "<<  first_edge_type<< endl; 
outFile << setbase(10) <<   "first_coarse_2_parity  "<<  first_coarse_2_parity<< endl; 
outFile << setbase(10) <<   "first_coarse_2   "<< first_coarse_2<< endl; 
outFile << setbase(10) <<   "first_coarse_parity   "<< first_coarse_parity<< endl; 
outFile << setbase(10) <<   "first_coarse_1   "<<  first_coarse_1 << endl; 
outFile << setbase(10) <<   "first_vernier   "<< first_vernier<< endl; 

outFile << "========== GROUP 2 ========== "<< endl;

load_hit_data = (ret[59] & 64) >> 6;
select_error_detected = (ret[59] & 32) >> 6;
channel= (ret[59] & 28) >> 2;
second_edge_type =(ret[59] & 2) >> 1;
second_coarse_2_parity = (ret[59] & 1) ;
second_coarse_2= ((ret[58] & 255) << 7) | ((ret[57] & 254) >> 1);
second_coarse_1_parity = (ret[57] & 1);
second_coarse_1 = ((ret[56] & 255) << 7) | ((ret[55] & 254) >> 1);
second_vernier = ((ret[55] & 1) << 31) | ((ret[54] & 255 ) << 23)| ((ret[53] & 255 ) << 15)| ((ret[52] & 255 ) << 7)| ((ret[51] & 254 ) >> 1);
first_edge_type = (ret[51] & 1);
first_coarse_2_parity= (ret[50] & 128) >> 7;
first_coarse_2= ((ret[50] & 127) << 8 ) | (ret[49] & 255) ;
first_coarse_parity = (ret[48] & 128) >> 7;
first_coarse_2= ((ret[48] & 127) << 8 ) | (ret[47] & 255) ;
first_vernier= ((ret[46] & 255) << 24 )   | ((ret[45] & 255) << 16 )| ((ret[44] & 255) << 8 )| ((ret[43] & 255) );


outFile << ""<< endl;
outFile << setbase(10) <<   "load_hit_data   "<< load_hit_data<< endl; // put on file
outFile << setbase(10) <<   "select_error_detected   "<< select_error_detected<< endl; // put on file
outFile << setbase(10) <<   "channel   "<< channel << endl; // put on file
outFile << setbase(10) <<   "load_hit_data  "<<  load_hit_data<< endl; 
outFile << setbase(10) <<   "select_error_detected   "<< select_error_detected<< endl; 
outFile << setbase(10) <<   "channel  "<<  channel<< endl; 
outFile << setbase(10) <<   "second_edge_type  "<<  second_edge_type<< endl; 
outFile << setbase(10) <<   "second_coarse_2  "<<  second_coarse_2<< endl; 
outFile << setbase(10) <<   "second_coarse_1  "<< second_coarse_1<< endl; 
outFile << setbase(10) <<   "second_vernier   "<<  second_vernier<< endl; 
outFile << setbase(10) <<   "first_edge_type   "<<  first_edge_type<< endl; 
outFile << setbase(10) <<   "first_coarse_2_parity  "<<  first_coarse_2_parity<< endl; 
outFile << setbase(10) <<   "first_coarse_2   "<< first_coarse_2<< endl; 
outFile << setbase(10) <<   "first_coarse_parity   "<< first_coarse_parity<< endl; 
outFile << setbase(10) <<   "first_coarse_1   "<<  first_coarse_1 << endl; 
outFile << setbase(10) <<   "first_vernier   "<< first_vernier<< endl; 


outFile << "========== GROUP 3 ========== "<< endl;

load_hit_data = (ret[42] & 128) >> 7;
select_error_detected = (ret[42] & 64) >> 6;
channel= (ret[42] & 56) >> 3;
second_edge_type = (ret[42] & 4) >> 2 ;
second_coarse_2_parity = (ret[42] & 2) >> 1;
second_coarse_2= ((ret[42] & 1) << 14) |  ((ret[41] & 255) << 6) |((ret[40] & 252) >> 2);
second_coarse_1_parity = (ret[40] & 2) >> 1;
second_coarse_1=((ret[40] & 1) << 14) | ((ret[39] & 255) << 6) | (( ret[38] & 252) >> 2);
second_vernier = ((ret[38] & 3) << 30) | ((ret[37] & 255) << 22)| ((ret[36] & 255) << 14) | ((ret[35] & 255) << 6)| ((ret[34] & 252) >> 2);
first_edge_type = (ret[34] & 2) >> 1;
first_coarse_2_parity=(ret[34] & 1);
first_coarse_2= ((ret[33] & 255) << 7) |  ((ret[32] & 254) >> 1);
first_coarse_parity = (ret[32] & 1) ;
first_coarse_1= ((ret[31] & 255) << 7) | ((ret[30] & 254) >> 1);
first_vernier = ((ret[30] & 1) << 31) | ((ret[29] & 255) << 23)| ((ret[28] & 255) << 15)| ((ret[27] & 255) << 7)| ((ret[26] & 254) >> 1);


outFile <<   ""<< endl;
outFile << setbase(10) <<   "load_hit_data   "<< load_hit_data<< endl; // put on file
outFile << setbase(10) <<   "select_error_detected   "<< select_error_detected<< endl; // put on file
outFile << setbase(10) <<   "channel   "<< channel << endl; // put on file
outFile << setbase(10) <<   "load_hit_data  "<<  load_hit_data<< endl; 
outFile << setbase(10) <<   "select_error_detected   "<< select_error_detected<< endl; 
outFile << setbase(10) <<   "channel  "<<  channel<< endl; 
outFile << setbase(10) <<   "second_edge_type  "<<  second_edge_type<< endl; 
outFile << setbase(10) <<   "second_coarse_2  "<<  second_coarse_2<< endl; 
outFile << setbase(10) <<   "second_coarse_1  "<< second_coarse_1<< endl; 
outFile << setbase(10) <<   "second_vernier   "<<  second_vernier<< endl; 
outFile << setbase(10) <<   "first_edge_type   "<<  first_edge_type<< endl; 
outFile << setbase(10) <<   "first_coarse_2_parity  "<<  first_coarse_2_parity<< endl; 
outFile << setbase(10) <<   "first_coarse_2   "<< first_coarse_2<< endl; 
outFile << setbase(10) <<   "first_coarse_parity   "<< first_coarse_parity<< endl; 
outFile << setbase(10) <<   "first_coarse_1   "<<  first_coarse_1 << endl; 
outFile << setbase(10) <<   "first_vernier   "<< first_vernier<< endl; 


outFile << ""<< endl;
outFile << ""<< endl;
outFile << "========== GROUP 0 ========== "<< endl;

unsigned short group0_1l_ready = ret[26] & 1 ;
unsigned short group0_1l_empty = (ret[25] & 128) >> 7;
unsigned short parity = (ret[25] & 64) >> 6;
unsigned short separator= (ret[25] & 32) >> 5;
unsigned short overflow_stop= (ret[25] & 16) >> 4;
unsigned short overflow_start= (ret[25] & 8) >> 3;
unsigned short error =(ret[25] & 4) >> 2;
channel=((ret[25] & 3) << 1) | ((ret[24] & 128) >>7);
unsigned short edge_type = (ret[24] & 1);
unsigned short edge_coarse_time = ((ret[23] & 255) << 4) | ((ret[22] & 240) >> 4) ;
unsigned short edge_fine_time = ((ret[22] & 15 ) << 4 ) |  ((ret[21] & 240 ) >> 4 );
unsigned short wait_end = ((ret[21] & 4 ) >> 2 );
unsigned short waiting_for_separator = ((ret[21] & 2 ) >> 1 );
unsigned short active = (ret[21] & 1 ) ;
unsigned short write_occupancy = (ret[20] & 128) >> 7;
unsigned short idle = (ret[20] & 64) >> 6;

outFile << ""<< endl;

outFile << setbase(10) <<   "group0_1l_ready   "<< group0_1l_ready<< endl;
outFile << setbase(10) <<   "group0_1l_empty   "<<  group0_1l_empty<< endl;
outFile << setbase(10) <<   "parity   "<<  parity<< endl;
outFile << setbase(10) <<   "separator  "<<  separator<< endl;
outFile << setbase(10) <<   "overflow_stop  "<<  overflow_stop<< endl;
outFile << setbase(10) <<   "overflow_start  "<< overflow_start<< endl;
outFile << setbase(10) <<   "error   "<< error<< endl;
outFile << setbase(10) <<   "channel  "<< channel<< endl;
outFile << setbase(10) <<   "edge_type   "<<  edge_type<< endl;
outFile << setbase(10) <<   "edge_coarse_time   "<<  edge_coarse_time<< endl;
outFile << setbase(10) <<   "edge_fine_time   "<< edge_fine_time<< endl;
outFile << setbase(10) <<   "wait_end   "<<  wait_end<< endl;
outFile << setbase(10) <<   "waiting_for_separator   "<<  waiting_for_separator<< endl;
outFile << setbase(10) <<   "active   "<<  active<< endl;
outFile << setbase(10) <<   "write_occupancy   "<<  write_occupancy<< endl;
outFile << setbase(10) <<   "idle   "<<  idle<< endl;

outFile << "========== GROUP 1 ========== "<< endl;
outFile << ""<< endl;

unsigned short group1_1l_ready = (ret[20] & 32) >> 5;
unsigned short group1_1l_empty = (ret[20] & 16) >> 4;
parity = (ret[20] & 8) >> 3;
separator =  (ret[20] & 4) >> 2;
overflow_stop =(ret[20] & 2) >> 1;
overflow_start = (ret[20] & 1) ;
error = ((ret[19] & 128) >> 7);
channel = ((ret[19] & 112) >> 4);
edge_type= (ret[18] & 32) >> 5;
edge_coarse_time =((ret[18] & 31) << 7) |  ((ret[17] & 254) >> 1);
edge_fine_time = ((ret[17] & 1) << 7) | ((ret[16] & 254 ) >> 1 ); 
wait_end=(ret[15] & 128)>> 7;
waiting_for_separator= (ret[15] & 64) >> 6 ;
active = (ret[15] &  32 )>> 5;
write_occupancy = (ret[15] & 16 ) >> 4;
idle = (ret[15] & 8 ) >> 3;  

 

outFile << setbase(10) <<   "group1_1l_ready   "<< group1_1l_ready<< endl;
outFile << setbase(10) <<   "group1_1l_empty   "<<  group1_1l_empty<< endl;
outFile << setbase(10) <<   "parity   "<<  parity<< endl;
outFile << setbase(10) <<   "separator  "<<  separator<< endl;
outFile << setbase(10) <<   "overflow_stop  "<<  overflow_stop<< endl;
outFile << setbase(10) <<   "overflow_start  "<< overflow_start<< endl;
outFile << setbase(10) <<   "error   "<< error<< endl;
outFile << setbase(10) <<   "channel  "<< channel<< endl;
outFile << setbase(10) <<   "edge_type   "<<  edge_type<< endl;
outFile << setbase(10) <<   "edge_coarse_time   "<<  edge_coarse_time<< endl;
outFile << setbase(10) <<   "edge_fine_time   "<< edge_fine_time<< endl;
outFile << setbase(10) <<   "wait_end   "<<  wait_end<< endl;
outFile << setbase(10) <<   "waiting_for_separator   "<<  waiting_for_separator<< endl;
outFile << setbase(10) <<   "active   "<<  active<< endl;
outFile << setbase(10) <<   "write_occupancy   "<<  write_occupancy<< endl;
outFile << setbase(10) <<   "idle   "<<  idle<< endl;

outFile << "========== GROUP 2 ========== "<< endl;
outFile << ""<< endl;

unsigned short group2_1l_ready = (ret[15] & 4) >> 2 ;
unsigned short group2_1l_empty = (ret[15] & 2) >> 1 ;
parity = (ret[15] & 1);
separator = (ret[14] & 128) >> 7;
overflow_stop = (ret[14] & 64 )>> 6; 
overflow_start= (ret[14] & 32 )>> 5; 
error= (ret[14] & 16 )>> 4;
channel = (ret[14] & 14) >> 1;
edge_type = (ret[13] & 4) >> 2;
edge_coarse_time = ((ret[13] & 3) << 10 ) |  ((ret[12] & 255) << 2 ) |  ((ret[11] & 192) >> 6 );
edge_fine_time = ((ret[11] & 63) << 2) | ((ret[10] & 192) >> 6);
wait_end = (ret[10] & 16 ) >> 4;
waiting_for_separator = (ret[10] & 8 ) >> 3;
active = (ret[10] & 4 ) >> 2;
write_occupancy = (ret[10] & 2 ) >> 1;
idle = (ret[10] & 1 );

outFile << setbase(10) <<   "group2_1l_ready   "<< group2_1l_ready<< endl;
outFile << setbase(10) <<   "group2_1l_empty   "<<  group2_1l_empty<< endl;
outFile << setbase(10) <<   "parity   "<<  parity<< endl;
outFile << setbase(10) <<   "separator  "<<  separator<< endl;
outFile << setbase(10) <<   "overflow_stop  "<<  overflow_stop<< endl;
outFile << setbase(10) <<   "overflow_start  "<< overflow_start<< endl;
outFile << setbase(10) <<   "error   "<< error<< endl;
outFile << setbase(10) <<   "channel  "<< channel<< endl;
outFile << setbase(10) <<   "edge_type   "<<  edge_type<< endl;
outFile << setbase(10) <<   "edge_coarse_time   "<<  edge_coarse_time<< endl;
outFile << setbase(10) <<   "edge_fine_time   "<< edge_fine_time<< endl;
outFile << setbase(10) <<   "wait_end   "<<  wait_end<< endl;
outFile << setbase(10) <<   "waiting_for_separator   "<<  waiting_for_separator<< endl;
outFile << setbase(10) <<   "active   "<<  active<< endl;
outFile << setbase(10) <<   "write_occupancy   "<<  write_occupancy<< endl;
outFile << setbase(10) <<   "idle   "<<  idle<< endl;

outFile << "========== GROUP 3 ========== "<< endl;
outFile << ""<< endl;


unsigned short group3_1l_ready = (ret[9] & 128) >> 7 ;
unsigned short group3_1l_empty = (ret[9] & 64) >> 6 ;
parity =  (ret[9] & 32) >> 5 ;
separator=  (ret[9] & 16) >> 4 ;
overflow_stop =  (ret[9] & 8) >> 3 ;
overflow_start =  (ret[9] & 4) >> 2 ;
error =  (ret[9] & 2) >> 1 ;
channel = ((ret[9] & 1) << 2 ) | ((ret[8])& 192) >> 6;
edge_type = (ret[7] & 128) >> 7 ;
edge_coarse_time = ((ret[7] & 127) << 5 |  (ret[6] & 248) >> 3 )  ;
edge_fine_time =((ret[6] & 7) << 5 )  |  ((ret[5] & 248) >> 3 ) ;
wait_end = (ret[5] & 2) >> 1;
waiting_for_separator = (ret[5] & 1);
active = (ret[4] & 128) >> 7;
write_occupancy = (ret[4] & 64) >> 6;
idle = (ret[4] & 32) >> 5;

outFile << setbase(10) <<   "group3_1l_ready   "<< group3_1l_ready<< endl;
outFile << setbase(10) <<   "group3_1l_empty   "<<  group3_1l_empty<< endl;
outFile << setbase(10) <<   "parity   "<<  parity<< endl;
outFile << setbase(10) <<   "separator  "<<  separator<< endl;
outFile << setbase(10) <<   "overflow_stop  "<<  overflow_stop<< endl;
outFile << setbase(10) <<   "overflow_start  "<< overflow_start<< endl;
outFile << setbase(10) <<   "error   "<< error<< endl;
outFile << setbase(10) <<   "channel  "<< channel<< endl;
outFile << setbase(10) <<   "edge_type   "<<  edge_type<< endl;
outFile << setbase(10) <<   "edge_coarse_time   "<<  edge_coarse_time<< endl;
outFile << setbase(10) <<   "edge_fine_time   "<<edge_fine_time<< endl;
outFile << setbase(10) <<   "wait_end   "<<  wait_end<< endl;
outFile << setbase(10) <<   "waiting_for_separator   "<<  waiting_for_separator<< endl;
outFile << setbase(10) <<   "active   "<<  active<< endl;
outFile << setbase(10) <<   "write_occupancy   "<<  write_occupancy<< endl;
outFile << setbase(10) <<   "idle   "<<  idle<< endl;


outFile  << endl;
outFile  << endl;
outFile << "======================== "<< endl;
unsigned short trigger_ready = (ret[4] & 16) >> 4 ; 
parity = (ret[4] & 8) >> 3 ; 
unsigned short trigger_lost = (ret[4] & 4) >> 2 ; 
separator  = (ret[4] & 2) >> 1 ; 
unsigned short event_id = ((ret[4] & 1) << 11 ) | ((ret[3] & 255) << 3 ) | ((ret[2] & 224) >> 5 );
unsigned short bunch_id = ((ret[2] & 31) << 7 ) | ((ret[1] & 254) >> 1 );
unsigned short matching = (ret[1]) & 1 ;
unsigned short occupancy = (ret[0] & 128) >> 7;
separator = (ret[0] & 64) >> 6;
unsigned short lost_trailer= (ret[0] & 32) >> 5;
unsigned short trailer = (ret[0] & 16) >>4;
error = (ret[0] & 8) >> 3;
unsigned short lost_header = (ret[0] & 4) >> 2;
unsigned short header = (ret[0] & 2) >> 1;
idle= (ret[0] & 1);



outFile << setbase(10) <<   "trigger_ready  "<<   trigger_ready<< endl;
outFile << "- trigger data - "<< endl; 
outFile << setbase(10) <<   "parity  "<<   parity<< endl;
outFile << setbase(10) <<   "trigger_lost  "<<  trigger_lost<< endl;
outFile << setbase(10) <<   "separator   "<<   separator   << endl;
outFile << setbase(10) <<   "event_id  "<<   event_id << endl;
outFile << setbase(10) <<   "bunch_id  "<<   bunch_id << endl;

outFile << "- common_matching_state - "<< endl; 
outFile << setbase(10) <<   "matching  "<<   matching<< endl;
outFile << setbase(10) <<   "occupancy  "<<  occupancy<< endl;
outFile << setbase(10) <<   "separator  "<<  separator<< endl;
outFile << setbase(10) <<   "lost_trailer "<<   lost_trailer<< endl;
outFile << setbase(10) <<   "trailer  "<<   trailer<< endl;
outFile << setbase(10) <<   "error  "<<  error<< endl;
outFile << setbase(10) <<   "lost_header  "<<   lost_header<< endl;
outFile << setbase(10) <<   "header  "<<  header<< endl;
outFile << setbase(10) <<   "idle "<<   idle<< endl;

}  


unsigned char * Start(void){
	
	const int nwords=1;

unsigned char *ret =new unsigned char [nwords];

ret[0]=1;
return ret;

}


unsigned char * Stop(void){
	
const int nwords=1;

unsigned char *ret =new unsigned char [nwords];

ret[0]=0;
return ret;

}


unsigned char * GeneralReset(void){
	
const int nwords=1;

unsigned char *ret =new unsigned char [nwords];

ret[0]=1;
return ret;

}
///////////////////////////////////////////////////////////////////////////////////////////////


// AUXILIAR FUNCTIONS

std::string readheader (string header = "")
{
  const std::string path = std::string(ABS_PATH)+"data.dat";
  std::ifstream inputFile (path.c_str());
  std::string line;
  std::string result = "0";

  while (std::getline (inputFile, line))
    {


      std::string col1, col2;
      std::istringstream ss (line);
      ss >> col1 >> col2;
      if (col1 == header) { result = col2; break; }
    }

  return result;
}


// AUXILIAR FUNCTIONS

unsigned short setupregister (string header = "")
{
  const std::string path = std::string(ABS_PATH)+"HPTDCSetup.dat";
  std::ifstream inputFile (path.c_str());
  std::string line;

  unsigned short result = 0;
  
  while (std::getline (inputFile, line))
    {


      std::string col1;
	  unsigned short col2;
      std::istringstream ss (line);
      ss >> col1 >> col2;
	  
      if (col1 == header) { result = col2; break; }

    }
	
	

  return result;
}


unsigned long controlregister (string header = "")
{
	const std::string path = std::string(ABS_PATH)+"HPTDCControl.dat";
    std::ifstream inputFile (path.c_str());
    std::string line;

  unsigned long result = 0;
  
  while (std::getline (inputFile, line))
    {


      std::string col1;
	  unsigned long col2;
      std::istringstream ss (line);
      ss >> col1 >> col2;
	  
      if (col1 == header) { result = col2; break; }

    }
	
	

  return result;
}

unsigned char
bintohex (const char *digits)
{
  unsigned char res = 0;
  while (*digits)
    res = (res << 1) | (*digits++ - '0');
  return res;
}



unsigned char *
GetSixteenBits (int parameter, const int nwords)
{


  unsigned char *ret = new unsigned char[nwords];	//number of words including header

  const int wordsafterheader = nwords - 1;

  int factor = 65535;		// mask lowest 16 bits in decimal
  for (int i = 0; i < wordsafterheader; i++)
    {

      int nEventspart = parameter & factor;	// mask next 16 bits
      
      unsigned char nEventspartfinal = nEventspart >> 16 * i;	// rightshift by 14 bits
      

      ret[wordsafterheader - i] = nEventspartfinal;

      factor *= 65536;



    }


  ret[0] = 0;			//filling the header with 0 for now

  return ret;

}
