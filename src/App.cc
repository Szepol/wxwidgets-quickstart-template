// Copyright 2022 Szepol
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this softwareand associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright noticeand this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <App.h>

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <gui/MainWindowFrame.h>

namespace reseau_interurbain {
wxIMPLEMENT_APP(App);
bool App::OnInit() {
    if (!wxApp::OnInit())
        return false;

    wxTheApp->SetAppName(APPLICATION_NAME);
    wxTheApp->SetAppDisplayName(APPLICATION_NAME);
    wxTheApp->SetVendorName(APPLICATION_NAME);

    ::wxInitAllImageHandlers();

    gui::MainWindowFrame* Frame = new gui::MainWindowFrame(NULL);
    Frame->SetMinSize(wxSize(MINIMUM_SIZE_WIDTH, MINIMUM_SIZE_HEIGHT));
    SetTopWindow(Frame);

    return true;
}
}  // namespace reseau_interurbain

