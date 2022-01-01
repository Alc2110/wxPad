#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class TextFrame : public wxFrame
{
public:
    TextFrame();

private:
    wxTextCtrl *text;
};