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

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <ui/MainWindowFrame.h>

#define MINIMUM_SIZE_HEIGHT 720
#define MINIMUM_SIZE_WIDTH 1280

class App : public wxApp {
 public:
#if wxCHECK_VERSION(3, 1, 0)
    virtual bool OnInit() wxOVERRIDE;
    virtual int OnExit() wxOVERRIDE { return 0; }
#else
    bool OnInit() override;
    int OnExit() override { return 0; }
#endif  // wxCHECK_VERSION
};

wxIMPLEMENT_APP(App);

bool App::OnInit() {
    if (!wxApp::OnInit())
        return false;

    wxTheApp->SetAppName(APPLICATION_NAME);
    wxTheApp->SetAppDisplayName(APPLICATION_NAME);
    wxTheApp->SetVendorName(APPLICATION_NAME);

    ::wxInitAllImageHandlers();

    wxwidgets_quickstart_template::ui::MainWindowFrame* Frame =
        new wxwidgets_quickstart_template::ui::MainWindowFrame(NULL);
    Frame->SetMinSize(wxSize(MINIMUM_SIZE_WIDTH, MINIMUM_SIZE_HEIGHT));
    SetTopWindow(Frame);

    return true;
}
