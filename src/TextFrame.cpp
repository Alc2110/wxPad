#include "TextFrame.h"

// menu item IDs
const int ID_FILE_EXIT = 1000;
const int ID_FILE_SAVE = 1001;
const int ID_FILE_SAVE_AS = 1002;
const int ID_FILE_OPEN = 1003;

TextFrame::TextFrame()
    : wxFrame(NULL, -1, "wxPad")
{
    text_area = new wxTextCtrl(this, -1, "Type some text here!",
                               wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);

    // initialise menu
    wxMenu *menu = new wxMenu();
    menu->Append(ID_FILE_OPEN, "Open");
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
    wxFileDialog *save_dialog = new wxFileDialog(
        this, _("Save As"), wxEmptyString, wxEmptyString,
        _("Text files (*.txt)|*.txt|All Files (*.*)|*.*"),
        wxFD_SAVE | wxFD_OVERWRITE_PROMPT, wxDefaultPosition);

    if (save_dialog->ShowModal() == wxID_OK)
    {
        // the user clicked "OK"
        // save the file
        std::string path = save_dialog->GetPath();
        text_area->SaveFile(path);
        // set the title to reflect the file open
        SetTitle(wxString("Edit - ") << save_dialog->GetFilename());
    }

    // clean up
    save_dialog->Destroy();
}

void TextFrame::OnOpen(wxCommandEvent &event)
{
    // show open file dialog
    wxFileDialog *open_dialog = new wxFileDialog(
        this, _("Open File"), wxEmptyString, wxEmptyString,
        _("Text files (*.txt)|*.txt|All Files (*.*)|*.*"),
        wxFD_OPEN, wxDefaultPosition);

    if (open_dialog->ShowModal() == wxID_OK)
    {
        // the user clicked "OK"
        // open the file
        std::string path = open_dialog->GetPath();
        text_area->LoadFile(path);
        // set the title to reflect the file open
        SetTitle(wxString("Edit - ") << open_dialog->GetFilename());
    }

    // clean up
    open_dialog->Destroy();
}

BEGIN_EVENT_TABLE(TextFrame, wxFrame)
EVT_MENU(ID_FILE_EXIT, TextFrame::OnExit)
EVT_MENU(ID_FILE_SAVE_AS, TextFrame::OnSaveAs)
EVT_MENU(ID_FILE_OPEN, TextFrame::OnOpen)
END_EVENT_TABLE()