#ifndef MYOP_H_INCLUDED
#define MYOP_H_INCLUDED

enum COMMAND {movimm,movreg,shlreg,shrreg,addreg,mulreg,subreg,xorreg,andreg, invalid};

struct MYOP {
    COMMAND opcommand;
    unsigned int val1, val2, val3;
};

#endif // MYOP_H_INCLUDED
