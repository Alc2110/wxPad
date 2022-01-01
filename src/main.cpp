#include "main.h"

IMPLEMENT_APP(App)

bool App::OnInit()
{
    textFrame = new TextFrame();
    textFrame->Show(true);

    return true;
}