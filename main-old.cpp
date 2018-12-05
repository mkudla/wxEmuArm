#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include "main.h"

int main(int argc, char *argv[]){

Armcore * core0 =  new Armcore;
Program * prog1 = new Program;
prog1->loadProg();
wxPuts(prog1->printProgram());

MYOP currentop;

core0->OnStep(prog1->fetchOp());
// DEBUG wxPrintf("operation %d v1 %i v2 %i v3 %i \n", currentop.opcommand,currentop.val1,currentop.val2,currentop.val3);
core0->OnRegStatus();



return 0;
}
