#include "program.h"

Program::Program() {
    IsProgramLoaded = FALSE;
}

void Program::loadProg(){
    firstStrPtr = new MYLIST;
    currentStrPtr = firstStrPtr;
    wxTextFile file(wxT("prog.txt"));
    wxString s;
    int i = 1;
    file.Open();
    if (file.IsOpened()) {
        for ( s = file.GetFirstLine(); !file.Eof(); s = file.GetNextLine() )  {
            currentStrPtr = addLine(i, s, currentStrPtr);
            i++;
        }
    }
    currentStrPtr->m_lineptr = NULL;
    file.Close();
    IsProgramLoaded=TRUE;
    currentStrPtr = firstStrPtr;
    currentLine = 1;
}

wxString Program::fetchOpLine() {
    if(currentStrPtr==NULL){
        return wxString(wxT("no opcode"));
    } else {
    return currentStrPtr->ProgLine;
    }
}

MYOP Program::fetchOp() {
    MYOP opcode;
    if(currentStrPtr==NULL){
        opcode.opcommand=invalid;
        return opcode;
    }
    currentLine++;
    wxString opstr = currentStrPtr->ProgLine;
    currentStrPtr = currentStrPtr->m_lineptr;



    wxString token;
    wxString rest;
    unsigned long templong;
    wxString strvalue1;
    wxString strvalue2;
    wxString strvalue3;

    //mov 1,2,3

    token = opstr.BeforeFirst(' ',&rest);
    wxPuts(token);
    wxPuts(rest);

    strvalue3 = rest.AfterLast(',');
    rest = rest.BeforeLast(',');
    strvalue2 = rest.AfterLast(',');
    rest = rest.BeforeLast(',');
    strvalue1 = rest;


    if(!strvalue1.ToULong(&templong))
        templong=0;
    opcode.val1 = (int) templong;
    if(!strvalue2.ToULong(&templong))
        templong=0;
    opcode.val2 = (int) templong;
    if(!strvalue3.ToULong(&templong))
        templong=0;
    opcode.val3 = (int) templong;

    if(token==wxString(wxT("mov"))){
        opcode.opcommand = movimm;
    }else if(token==wxString(wxT("add"))){
        opcode.opcommand = addreg;
    }else if(token==wxString(wxT("sub"))){
        opcode.opcommand = subreg;
    }else if(token==wxString(wxT("mul"))){
        opcode.opcommand = mulreg;
    }else if(token==wxString(wxT("xor"))){
        opcode.opcommand = xorreg;
    }else if(token==wxString(wxT("and"))){
        opcode.opcommand = andreg;
    }else if(token==wxString(wxT("shr"))){
        opcode.opcommand = shrreg;
    }else if(token==wxString(wxT("shl"))){
        opcode.opcommand = shlreg;
    }else{
        opcode.opcommand = invalid;
    }

    return opcode;
}

MYLIST * Program::addLine(int i, wxString u, MYLIST * currentStrPtr){
    currentStrPtr->ProgLine = u;
    currentStrPtr->linenumber = i;
    currentStrPtr->m_lineptr = new MYLIST;
    return currentStrPtr->m_lineptr;
}

wxString Program::printProgram() {
    if(IsProgramLoaded==FALSE)
        return wxString(wxT("nothing loaded"));
    wxString t;
    MYLIST * currentStrPtr =  firstStrPtr;
    do {
    t = t + currentStrPtr->ProgLine + wxT("\n");
    currentStrPtr = currentStrPtr->m_lineptr;
    }while (currentStrPtr != NULL);
    return t;
}
