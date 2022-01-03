#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class TextFrame : public wxFrame
{
public:
    TextFrame();

    void OnExit(wxCommandEvent &event);
    void OnSaveAs(wxCommandEvent &event);
    void OnOpen(wxCommandEvent &event);
    void OnPaste(wxCommandEvent &event);
    void OnReplace(wxCommandEvent &event);
    void OnSelectAll(wxCommandEvent &event);
    void OnFormatFont(wxCommandEvent &event);

private:
    wxTextCtrl *text_area;
    DECLARE_EVENT_TABLE();
};