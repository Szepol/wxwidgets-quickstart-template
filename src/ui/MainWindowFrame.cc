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

#include <wx/graphics.h>
#include <wx/event.h>

namespace wxwidgets_quickstart_template {
namespace ui {
inline wxString wxBuildInfo() {
    wxString build;
    wxString version;
    version << "v" << APPLICATION_VERSION_MAJOR << "."
        << APPLICATION_VERSION_MINOR;
    build << APPLICATION_NAME << " " << version;
#if defined (__WXMSW__)
    build << wxT("-Windows");
#elif defined(__UNIX__)
    build << wxT("-Linux");
#endif

#if wxUSE_UNICODE
    build << wxT("-Unicode build");
#else
    build << wxT("-AINSI build");
#endif

    return build;
}
wxBEGIN_EVENT_TABLE(MainWindowFrame, wxFrame)
    EVT_CLOSE(MainWindowFrame::OnCloseWindow)
    // TODO(Szepol): Lock the ratio when resizing the window
    EVT_MENU(wxID_EXIT, MainWindowFrame::OnExit)
    EVT_MENU(wxID_ABOUT, MainWindowFrame::OnAbout)
wxEND_EVENT_TABLE()


MainWindowFrame::MainWindowFrame(wxWindow* p_parent, wxWindowID p_id)
      : wxFrame(p_parent, p_id, wxTheApp->GetAppName()) {
    // Initialize menu bar
    InitMenu();
    SetBackgroundColour(wxColor(120, 150, 200));

    wxBoxSizer* bSizerVertical = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* bSizerHorizontal = new wxBoxSizer(wxHORIZONTAL);

    // Horizontal sizer on top, contains drawing Panel and side panel
    bSizerVertical->Add(bSizerHorizontal, 1, wxEXPAND | wxALL, 5);

    SetSizer(bSizerVertical);
    Layout();
    Maximize();
    Show();
}

void MainWindowFrame::OnCloseWindow(wxCloseEvent& WXUNUSED(event)) {
    static bool destroyed = false;
    if (destroyed)
        return;
    this->Destroy();
    destroyed = true;
}

void MainWindowFrame::OnExit(wxCommandEvent& WXUNUSED(event)) {
    Close(true);
}

void MainWindowFrame::OnAbout(wxCommandEvent& WXUNUSED(event)) {
    wxMessageBox(wxBuildInfo(), wxT("Information"));
}

void MainWindowFrame::InitMenu() {
    wxMenu* fileMenu = new wxMenu();
    wxMenu* editMenu = new wxMenu();
    wxMenu* helpMenu = new wxMenu();
    wxMenuBar* mainMenuBar = new wxMenuBar();
    wxString version;
    version << "Learn more about " << APPLICATION_NAME;
    fileMenu->Append(wxID_EXIT, wxT("&Exit"));
    helpMenu->Append(wxID_ABOUT, wxT("&Version"), version);

    mainMenuBar->Append(fileMenu, wxT("&File"));
    mainMenuBar->Append(editMenu, wxT("&Edit"));
    mainMenuBar->Append(helpMenu, wxT("Help"));

    SetMenuBar(mainMenuBar);
}
}  // namespace ui
}  // namespace wxwidgets_quickstart_template

