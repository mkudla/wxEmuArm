#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include "wxemuarm.h"

Armcore::Armcore() {
    fMzeroregisters(&reg[0]);
    regcount =  16;
    regwidth = 32;
    interactivemode = 1;
}

void Armcore::OnStep(MYOP operation) {
		switch(operation.opcommand) {
		case movimm:
            fMmovimm(operation.val1, operation.val2);
            break;
		case movreg:
            fMmovreg(operation.val1, operation.val2);
            break;
		case shlreg:
            fMshlreg(operation.val1, operation.val2, operation.val3);
            break;
		case shrreg:
            fMshrreg(operation.val1, operation.val2, operation.val3);
            break;
		case addreg:
            fMaddreg(operation.val1, operation.val2, operation.val3);
            break;
   		case subreg:
            fMsubreg(operation.val1, operation.val2, operation.val3);
            break;
		case xorreg:
            fMxorreg(operation.val1, operation.val2, operation.val3);
            break;
		case andreg:
            fMandreg(operation.val1, operation.val2, operation.val3);
            break;
		case mulreg:
            fMmulreg(operation.val1, operation.val2, operation.val3);
            break;
		default:
            break;
		}

}
void Armcore::OnStep(COMMAND command, int val1, int val2, int val3) {
		switch(command) {
		case movimm:
            fMmovimm(val1, val2);
            break;
		case movreg:
            fMmovreg(val1, val2);
            break;
		case shlreg:
            fMshlreg(val1, val2, val3);
            break;
		case shrreg:
            fMshrreg(val1, val2, val3);
            break;
		case addreg:
            fMaddreg(val1, val2, val3);
            break;
   		case subreg:
            fMsubreg(val1, val2, val3);
            break;
		case xorreg:
            fMxorreg(val1, val2, val3);
            break;
		case andreg:
            fMandreg(val1, val2, val3);
            break;
		case mulreg:
            fMmulreg(val1, val2, val3);
            break;
		default:
            break;
		}
}

void Armcore::OnInit() {
//here is just testing
OnStep(movimm, 1,122,0);
}

wxString Armcore::OnRegStatus() {
    char dispstr[33];
    wxString strRegisters;
    wxString strRegister;
    for(int i = 0; i<16; i++){
    fMprintbin(reg[i], &dispstr[0]);
    strRegister.Printf("reg %i\t%s", i, dispstr);
    strRegisters = strRegisters + strRegister;
    fMprinthexvl(reg[i], 32, &dispstr[0]);
    strRegister.Printf("\t%s\t%i\n", dispstr, reg[i]);
    strRegisters = strRegisters + strRegister;
    }
    return strRegisters;
}


// prints 32 bit register passed as unsigned integer
char * Armcore::fMprintbin(unsigned int binval, char *dispstr) {
	unsigned int index = 0x80000000u;
	char displaystring[] = "00000000000000000000000000000000";
	displaystring[33] = '\0';
	for (int ii=31;ii>=0;ii--) {
		if((index & binval) >0 ) {
			displaystring[31-ii] = '1';
		}
		index = index >> 1;
	}
	strcpy(dispstr, displaystring);
	return dispstr;
}


char * Armcore::fMprinthexvl(unsigned int binval, unsigned int length, char *dispstr) {

	char displaystring[length/4];
	for (unsigned int iter = 0; iter < (length/4); iter+=4) {
		displaystring[iter] = '0';
	}
    displaystring[8] = '\0'; //9 !!
// code here

	unsigned int mask = 0x0000000Fu;
	for (int iter2 = 7; iter2 >= 0;iter2-- ) {
		unsigned int result = binval & mask;
		switch (result) {
			case 0:
				displaystring[iter2] = '0';
				break;
			case 1:
				displaystring[iter2] = '1';
				break;
			case 2:
				displaystring[iter2] = '2';
				break;
			case 3:
				displaystring[iter2] = '3';
				break;
			case 4:
				displaystring[iter2] = '4';
				break;
			case 5:
				displaystring[iter2] = '5';
				break;
			case 6:
				displaystring[iter2] = '6';
				break;
			case 7:
				displaystring[iter2] = '7';
				break;
			case 8:
				displaystring[iter2] = '8';
				break;
			case 9:
				displaystring[iter2] = '9';
				break;
			case 10:
				displaystring[iter2] = 'A';
				break;
			case 11:
				displaystring[iter2] = 'B';
				break;
			case 12:
				displaystring[iter2] = 'C';
				break;
			case 13:
				displaystring[iter2] = 'D';
				break;
			case 14:
				displaystring[iter2] = 'E';
				break;
			case 15:
				displaystring[iter2] = 'F';
				break;
		}
		binval = binval >> 4;
	}
	strcpy(dispstr, displaystring);
	return dispstr;
}


void Armcore::fMzeroregisters(unsigned int *registerarm) {
	for(int i=0; i<16; i++) {
	registerarm[i] = 0;
	}
}

void Armcore::fMmovimm(int registernumber1, int movvalue) {
	reg[registernumber1] = movvalue;
}
void Armcore::fMmovreg(int registernumber1, int registernumber2) {
	reg[registernumber2] = reg[registernumber1];
}
void Armcore::fMshrreg(int registernumber1, int movvalue, int registernumber2) {
	reg[registernumber2] = reg[registernumber1] >> movvalue;
}
void Armcore::fMshlreg(int registernumber1, int movvalue, int registernumber2) {
	reg[registernumber2] = reg[registernumber1] << movvalue;
}
void Armcore::fMaddreg(int registernumber1,int registernumber2, int registernumber3) {
	reg[registernumber3] = reg[registernumber1] + reg[registernumber2];
}
void Armcore::fMsubreg(int registernumber1,int registernumber2, int registernumber3) {
	reg[registernumber3] = reg[registernumber1] - reg[registernumber2];
}
void Armcore::fMmulreg(int registernumber1,int registernumber2, int registernumber3) {
	reg[registernumber3] = reg[registernumber1] * reg[registernumber2];
}
void Armcore::fMxorreg(int registernumber1,int registernumber2, int registernumber3) {
	reg[registernumber3] = reg[registernumber1] ^ reg[registernumber2];
}
void Armcore::fMandreg(int registernumber1,int registernumber2, int registernumber3) {
	reg[registernumber3] = reg[registernumber1] & reg[registernumber2];
}
