#include "TextFrame.h"

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