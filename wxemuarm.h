#ifndef WXEMUARM_H_INCLUDED
#define WXEMUARM_H_INCLUDED
#include "myop.h"

class Armcore {
    public:
    Armcore();
    void OnInit();
    void OnStep(COMMAND command, int val1, int val2, int val3);
    void OnStep(MYOP operation);
    wxString OnRegStatus();

    private:
    int interactivemode;
    unsigned int reg[16]; // create register bank 16 x 32 bit
    unsigned int regcount;
    unsigned int regwidth;

    void fMmovimm(int registernumber1, int movvalue);
    void fMmovreg(int registernumber1, int registernumber2);
    void fMshrreg(int registernumber1, int movvalue, int registernumber2);
    void fMshlreg(int registernumber1, int movvalue, int registernumber2);
    void fMaddreg(int registernumber1,int registernumber2, int registernumber3);
    void fMsubreg(int registernumber1,int registernumber2, int registernumber3);
    void fMmulreg(int registernumber1,int registernumber2, int registernumber3);
    void fMxorreg(int registernumber1,int registernumber2, int registernumber3);
    void fMandreg(int registernumber1,int registernumber2, int registernumber3);
    char * fMprintbin(unsigned int binval, char *);
    char * fMprinthexvl(unsigned int binval, unsigned int length, char *dispstr);
    void fMzeroregisters(unsigned int *);
};


#endif // WXEMUARM_H_INCLUDED
