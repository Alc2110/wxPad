#include "TextFrame.h"

TextFrame::TextFrame()
    : wxFrame(NULL, -1, "wxPad")
{
    text = new wxTextCtrl(this, -1, "Type some text here!",
                          wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
}