#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class TextFrame : public wxFrame
{
public:
    TextFrame();

private:
    wxTextCtrl *text_area;
    std::string current_file_path;

    void save_as();

    void OnExit(wxCommandEvent &event);
    void OnSave(wxCommandEvent &event);
    void OnSaveAs(wxCommandEvent &event);
    void OnOpen(wxCommandEvent &event);
    void OnPaste(wxCommandEvent &event);
    void OnReplace(wxCommandEvent &event);
    void OnSelectAll(wxCommandEvent &event);
    void OnFormatFont(wxCommandEvent &event);
    void OnClose(wxCloseEvent &event);

    DECLARE_EVENT_TABLE();
};