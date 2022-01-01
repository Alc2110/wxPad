#include "TextFrame.h"

// menu item IDs
const int ID_FILE_EXIT = 1000;

TextFrame::TextFrame()
    : wxFrame(NULL, -1, "wxPad")
{
    text = new wxTextCtrl(this, -1, "Type some text here!",
                          wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);

    // initialise menu
    wxMenu *menu = new wxMenu();
    menu->Append(ID_FILE_EXIT, "Exit");

    // add menu to menubar
    wxMenuBar *menu_bar = new wxMenuBar();
    SetMenuBar(menu_bar);
    menu_bar->Append(menu, "File");
}

void TextFrame::OnExit(wxCommandEvent &event)
{
    Destroy();
}

BEGIN_EVENT_TABLE(TextFrame, wxFrame)
EVT_MENU(ID_FILE_EXIT, TextFrame::OnExit)
END_EVENT_TABLE()