#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class TextFrame : public wxFrame
{
public:
    TextFrame();

    void OnExit(wxCommandEvent &event);

private:
    wxTextCtrl *text;
    DECLARE_EVENT_TABLE();
};