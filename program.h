#ifndef PROGRAM_H_INCLUDED
#define PROGRAM_H_INCLUDED

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <wx/textfile.h>
#include "myop.h"
#include "wxemuarm.h"

struct MYLIST {
    MYLIST * m_lineptr;
    int linenumber;
    unsigned int opCode;
    wxString ProgLine;
};


class Program {
public:
Program();
MYOP fetchOp();
void fetchIP();
void loadProg();
wxString printProgram();
wxString fetchOpLine();

private:
bool IsProgramLoaded;
int currentLine;
MYLIST * firstStrPtr;
MYLIST * currentStrPtr;
MYLIST * addLine(int i, wxString u, MYLIST * currentStrPtr);




};

#endif // PROGRAM_H_INCLUDED
