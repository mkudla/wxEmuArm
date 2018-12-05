/*
Copyright (c) 2015-2018 Marek Kudla.

MIT License

windowed ARM1-like cpu sandbox program
*/
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include "main.h"

class MyApp: public wxApp   //substitutes for main()
{
public:
    virtual bool OnInit();  // This executes on the initialization of the class
};

class MyFrame: public wxFrame   // This is the UI class
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);     // This is constructor
    wxFrame *m_this;
    wxStaticText *m_text;
    wxStaticText *m_progline;
    Program *m_prog;
    Armcore *m_core;
    wxTextCtrl    *m_textbox;

private:
    // here go the functions to handle events
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnRun(wxCommandEvent& event);
    void OnEdit(wxCommandEvent& event);
    void OnStep(wxCommandEvent& event);
    void OnOpen(wxCommandEvent& event);
    wxDECLARE_EVENT_TABLE();    // and here is apparently this macro that declares the event table
};

enum
{
    // Here we need to declare the events, using enum (yes, they are just numbers, but using IDs makes it for better code)
    TEXT_INSTR = wxID_HIGHEST + 1,
    ID_Hello = 1,
    ID_Step = 2,
    ID_Run = 3,
    ID_Edit = 4,
    ID_Open = 5,

};

// This is the event table that binds events (from menu or button) with their methods in MyFrame
wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(ID_Hello,   MyFrame::OnHello)
    EVT_MENU(wxID_EXIT,  MyFrame::OnExit)
    EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
    EVT_BUTTON(wxID_EXIT, MyFrame::OnExit)
    EVT_BUTTON(ID_Step, MyFrame::OnStep)
    EVT_BUTTON(ID_Run, MyFrame::OnRun)
    EVT_BUTTON(ID_Edit, MyFrame::OnEdit)
    EVT_BUTTON(ID_Open, MyFrame::OnOpen)
wxEND_EVENT_TABLE()
wxIMPLEMENT_APP(MyApp);     // And this macro takes the MyApp method and actually implements the program

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxFrame(NULL, wxID_ANY, title, pos, size)         // here is the implementation of the MyFrame class
{
    // Here we start implementing the menu
    wxMenu *menuFile = new wxMenu;  // menu File
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H", "Help string shown in status bar for this menu item"); // item of the menu File
    menuFile->AppendSeparator();    // same as above, but separator
    menuFile->Append(wxID_EXIT);    // same as above, see we append it to the menuFile
    wxMenu *menuHelp = new wxMenu;  //  Creating new menu, menuHelp
    menuHelp->Append(wxID_ABOUT);   // appending and item to menuHelp
    wxMenuBar *menuBar = new wxMenuBar;     // making a new menu bar, we will bind our menus to it
    menuBar->Append( menuFile, "&File" );   // appending File menu
    menuBar->Append( menuHelp, "&Help" );   // appending Help menu
    SetMenuBar( menuBar );  // setting our menuBar as the main menu bar. Hurray, the job is done
    CreateStatusBar();  // creating the status bar (useful for hints and status of the program)
    SetStatusText( "simple cpu emulator" );   // setting status bar text

    // Ok, now buttons
    wxPanel *panel = new wxPanel(this, wxID_ANY);   // First we need to create panel, why I do not know yet.
    wxButton *buttonQuit = new wxButton(panel, wxID_EXIT, wxT("Quit"), wxPoint(10, 20));    // first button, bound with the wx's wxID_EXIT event
    wxButton *buttonRun = new wxButton(panel, ID_Run, wxT("Run"), wxPoint(10, 50));     // second button, bound with our custom ID_Run
    wxButton *buttonEdit = new wxButton(panel, ID_Edit, wxT("Edit"), wxPoint(10, 80));  // see that all buttons were manually positioned using absolute coordinates, this is enough for our purposes
    wxButton *buttonOpenProgram = new wxButton(panel, ID_Open, wxT("Open"), wxPoint(10, 110));
    wxButton *buttonStep = new wxButton(panel, ID_Step, wxT("Step"), wxPoint(10, 140));







    // Static text
    //UI needs to be modified here: !!!
    Armcore * core0 = new Armcore;
    Program * prog1 = new Program;
    m_core = core0;
    m_prog = prog1;

    m_this = this;

    wxString reglabel = wxT("--------REGISTERS---------------");
    wxStaticText *st = new wxStaticText(panel, wxID_ANY, reglabel, wxPoint(100, 20), wxDefaultSize, wxALIGN_LEFT);


    wxString  text = m_core->OnRegStatus();
    wxStaticText *registerText = new wxStaticText(panel, wxID_ANY, text, wxPoint(100, 40), wxDefaultSize, wxALIGN_LEFT);
    m_text = registerText;

    wxString noprog = wxT("no program");
    wxStaticText *progText = new wxStaticText(panel, wxID_ANY, noprog, wxPoint(100, 400), wxDefaultSize, wxALIGN_LEFT);
    m_progline = progText;
         //m_textbox = new wxTextCtrl( this, TEXT_INSTR, wxT("input"), wxPoint(100,350), wxDefaultSize, wxTE_PROCESS_ENTER, wxDefaultValidator, wxTextCtrlNameStr);
}

bool MyApp::OnInit()
{
        // new init:


    MyFrame *frame = new MyFrame( "Hello World", wxPoint(50, 50), wxSize(600, 500) );   // on init of the app we create our frame MyFrame with all its goodies
    frame->Show( true );    // we show the frame to the user




    return true;    // done
}


void MyFrame::OnExit(wxCommandEvent& event)
{
    Close( true );
}
void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox( "This is emulator of simple cpu",
                  "WinEmu", wxOK | wxICON_INFORMATION );
}
void MyFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("simple cpu emulator");
}
void MyFrame::OnStep(wxCommandEvent& event)
{
    //wxString  text = wxT("00000000000000000000000000000000");
    //m_text->SetLabel(text);
    /* updating control is simple
        you just need a public pointer in the same class and put the address of the control in the class init.
    */
    //core0->OnStep(prog1->fetchOp());
    //m_text->SetLabel(core0->OnRegStatus());
    wxString currentProgramLine = m_prog->fetchOpLine();
    m_progline->SetLabel(currentProgramLine);
    m_core->OnStep(m_prog->fetchOp());
    m_text->SetLabel(m_core->OnRegStatus());
    /*
    m_core->OnStep(m_prog->fetchOp());
    m_progline->SetLabel();
    m_text->SetLabel(m_core->OnRegStatus());
    */
}
void MyFrame::OnRun(wxCommandEvent& event)
{
    wxLogMessage("Run Button - uninplemented");
}
void MyFrame::OnEdit(wxCommandEvent& event)
{
    wxLogMessage("Edit Button - uninplemented");
    //prog1->loadProg();
    //wxPuts(prog1->printProgram());
}
void MyFrame::OnOpen(wxCommandEvent& event)
{
    wxLogMessage("prog.txt loaded");
    m_prog->loadProg();
}
