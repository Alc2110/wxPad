#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class TextFrame : public wxFrame
{
public:
    TextFrame();

    void OnExit(wxCommandEvent &event);
    void OnSaveAs(wxCommandEvent &event);

private:
    wxTextCtrl *text_area;
    DECLARE_EVENT_TABLE();
};