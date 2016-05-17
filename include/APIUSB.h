#include <string>
 

unsigned char  * SetControlReg (void);
unsigned char  *SetSetupReg   (void); 


unsigned char  *GetSetupReg    (void);
unsigned char  * GetControlReg(void);
unsigned char  *GetStatReg  (void);
unsigned char  *GetIDCode   (void);
unsigned char  *GetICR      (void);

unsigned char  *Start  (void);
unsigned char  *Stop   (void);
unsigned char  *GeneralReset      (void);  

void  ReadGetSetupReg    (unsigned char *);
void  ReadGetControlReg(unsigned char *);
void  ReadGetIDCode(unsigned char *);
void  ReadGetStatReg  (unsigned char *);
void ReadGetICR      (unsigned char *);
//auxiliar


std::string readheader (std::string);

unsigned short setupregister (std::string);
unsigned long controlregister (std::string);
unsigned char  bintohex(const char* );


unsigned char  * GetSixteenBits(int, const int);
