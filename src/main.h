#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "TextFrame.h"

class App : public wxApp
{
public:
    virtual bool OnInit();

private:
    TextFrame *textFrame;
};

DECLARE_APP(App);