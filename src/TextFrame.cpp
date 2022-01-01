#include <wx/fontdlg.h>
#include "TextFrame.h"

// menu item IDs
const int ID_FILE_EXIT = 1000;
const int ID_FILE_SAVE = 1001;
const int ID_FILE_SAVE_AS = 1002;
const int ID_FILE_OPEN = 1003;
const int ID_FORMAT_FONT = 2000;

TextFrame::TextFrame()
    : wxFrame(NULL, -1, "wxPad")
{
    // set up main text area
    text_area = new wxTextCtrl(this, -1, "Type some text here!",
                               wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);

    // set up menus
    wxMenuBar *menu_bar = new wxMenuBar();
    // initialise file menu
    wxMenu *file_menu = new wxMenu();
    file_menu->Append(ID_FILE_OPEN, "Open");
    file_menu->Append(ID_FILE_SAVE, "Save");
    file_menu->Append(ID_FILE_SAVE_AS, "Save As");
    file_menu->Append(ID_FILE_EXIT, "Exit");
    menu_bar->Append(file_menu, "File");
    // initialise edit menu
    wxMenu *format_menu = new wxMenu();
    format_menu->Append(ID_FORMAT_FONT, "Font");
    menu_bar->Append(format_menu, "Format");
    // set up menu bar
    SetMenuBar(menu_bar);
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

void TextFrame::OnFormatFont(wxCommandEvent &event)
{
    // show font dialog
    wxFontDialog *font_dialog = new wxFontDialog(this);

    if (font_dialog->ShowModal() == wxID_OK)
    {
        // the user clicked "OK"
        // set the main text area font
        const wxFontData font_data = font_dialog->GetFontData();
        const wxFont chosen_font = font_data.GetChosenFont();
        text_area->SetFont(chosen_font);
    }

    // clean up
    font_dialog->Destroy();
}

BEGIN_EVENT_TABLE(TextFrame, wxFrame)
EVT_MENU(ID_FILE_EXIT, TextFrame::OnExit)
EVT_MENU(ID_FILE_SAVE_AS, TextFrame::OnSaveAs)
EVT_MENU(ID_FILE_OPEN, TextFrame::OnOpen)
EVT_MENU(ID_FORMAT_FONT, TextFrame::OnFormatFont)
END_EVENT_TABLE()