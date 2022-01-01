#include "TextFrame.h"

// menu item IDs
const int ID_FILE_EXIT = 1000;
const int ID_FILE_SAVE = 1001;
const int ID_FILE_SAVE_AS = 1002;

TextFrame::TextFrame()
    : wxFrame(NULL, -1, "wxPad")
{
    text = new wxTextCtrl(this, -1, "Type some text here!",
                          wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);

    // initialise menu
    wxMenu *menu = new wxMenu();
    menu->Append(ID_FILE_SAVE, "Save");
    menu->Append(ID_FILE_SAVE_AS, "Save As");
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

void TextFrame::OnSaveAs(wxCommandEvent &event)
{
    // show save dialog
    wxFileDialog *SaveDialog = new wxFileDialog(
        this, _("Save As"), wxEmptyString, wxEmptyString,
        _("Text files (*.txt)|*.txt|All Files (*.*)|*.*"),
        wxFD_SAVE | wxFD_OVERWRITE_PROMPT, wxDefaultPosition);

    if (SaveDialog->ShowModal() == wxID_OK)
    {
        // the user clicked "OK"
        // save the file
        std::string path = SaveDialog->GetPath();
        text->SaveFile(path);
        // set the title to reflect the file open
        SetTitle(wxString("Edit - ") << SaveDialog->GetFilename());
    }

    // clean up
    SaveDialog->Destroy();
}

BEGIN_EVENT_TABLE(TextFrame, wxFrame)
EVT_MENU(ID_FILE_EXIT, TextFrame::OnExit)
EVT_MENU(ID_FILE_SAVE_AS, TextFrame::OnSaveAs)
END_EVENT_TABLE()