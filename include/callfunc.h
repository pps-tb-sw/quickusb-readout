
#include <string>
 
unsigned short  * GetControlReg(void);


unsigned short  * SetControlReg (int control);


//auxiliar


std::string readheader (std::string);


unsigned short int bintohex(const char* );


unsigned short int * GetSixteenBits(int, const int);
