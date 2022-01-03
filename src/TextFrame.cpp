#include <wx/fontdlg.h>
#include <wx/clipbrd.h>
#include <wx/fdrepdlg.h>
#include "TextFrame.h"

// menu item IDs
const int ID_FILE_EXIT = 1000;
const int ID_FILE_SAVE = 1001;
const int ID_FILE_SAVE_AS = 1002;
const int ID_FILE_OPEN = 1003;
const int ID_EDIT_PASTE = 2000;
const int ID_EDIT_REPLACE = 2001;
const int ID_EDIT_SELECT_ALL = 2002;
const int ID_FORMAT_FONT = 3000;

TextFrame::TextFrame()
    : wxFrame(NULL, -1, "wxPad")
{
    // set up main text area
    // by setting the parent, responsibilty of managing the object is passed to wxWidgets itself
    text_area = new wxTextCtrl(this, -1, "Type some text here!",
                               wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);

    current_file_path = "";

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
    wxMenu *edit_menu = new wxMenu();
    edit_menu->Append(ID_EDIT_PASTE, "Paste");
    edit_menu->Append(ID_EDIT_REPLACE, "Replace");
    edit_menu->Append(ID_EDIT_SELECT_ALL, "Select All");
    menu_bar->Append(edit_menu, "Edit");
    // initialise format menu
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

void TextFrame::OnSave(wxCommandEvent &event)
{
    if (current_file_path.empty())
    {
        save_as();
    }
    else
    {
        text_area->SaveFile(current_file_path);
    }
}

void TextFrame::OnSaveAs(wxCommandEvent &event)
{
    save_as();
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

void TextFrame::OnPaste(wxCommandEvent &event)
{
    if (wxTheClipboard->Open())
    {
        // get the clipboard data
        wxTextDataObject clipboard_data;
        wxTheClipboard->GetData(clipboard_data);

        // append the text to the main text area
        text_area->AppendText(clipboard_data.GetText());
    }
}

void TextFrame::OnReplace(wxCommandEvent &event)
{
    wxFindReplaceData *find_replace_data = new wxFindReplaceData();
    wxFindReplaceDialog *find_replace_dialog = new wxFindReplaceDialog(this, new wxFindReplaceData(), wxT("Find and Replace"), wxFR_REPLACEDIALOG);
    find_replace_dialog->Show(true);

    return;
}

void TextFrame::OnSelectAll(wxCommandEvent &event)
{
    text_area->SetSelection(-1, -1);
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

void TextFrame::save_as()
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
        current_file_path = path;
        // set the title to reflect the file open
        SetTitle(wxString("Edit - ") << save_dialog->GetFilename());
    }

    // clean up
    save_dialog->Destroy();
}

BEGIN_EVENT_TABLE(TextFrame, wxFrame)
EVT_MENU(ID_FILE_EXIT, TextFrame::OnExit)
EVT_MENU(ID_FILE_SAVE, TextFrame::OnSave)
EVT_MENU(ID_FILE_SAVE_AS, TextFrame::OnSaveAs)
EVT_MENU(ID_FILE_OPEN, TextFrame::OnOpen)
EVT_MENU(ID_EDIT_PASTE, TextFrame::OnPaste)
EVT_MENU(ID_EDIT_REPLACE, TextFrame::OnReplace)
EVT_MENU(ID_EDIT_SELECT_ALL, TextFrame::OnSelectAll)
EVT_MENU(ID_FORMAT_FONT, TextFrame::OnFormatFont)
END_EVENT_TABLE()