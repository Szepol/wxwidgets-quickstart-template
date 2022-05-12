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

#include <gui/MainWindowFrame.h>
#include <domain/controller/ControllerInput.h>
#include <domain/controller/Model.h>
#include <Version.h>

#include <wx/graphics.h>
#include <wx/event.h>

namespace reseau_interurbain {
namespace gui {
inline wxString wxBuildInfo() {
    wxString build;
    wxString version;
    version << "v" << ReseauInterurbain_VERSION_MAJOR << "."
        << ReseauInterurbain_VERSION_MINOR;
    // build << APPLICATION_NAME << " " << version;
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
#if wxUSE_DC_TRANSFORM_MATRIX
    domain::Model* t_model = new domain::Model(new wxAffineMatrix2D());
#else
    domain::Model* t_model = new domain::Model();
#endif
    m_controller = new domain::ControllerInput(t_model);

    // Initialize menu bar
    InitMenu();
    SetBackgroundColour(wxColor(120, 150, 200));

    wxBoxSizer* bSizerVertical = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* bSizerHorizontal = new wxBoxSizer(wxHORIZONTAL);
    m_view = new View(this, t_model);
    m_sidePanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);

#if wxUSE_GRAPHICS_CONTEXT
    m_view->UseGraphicRenderer(wxGraphicsRenderer::GetDefaultRenderer());
#if wxUSE_CAIRO
    m_view->UseGraphicRenderer(wxGraphicsRenderer::GetCairoRenderer());
#endif  // wxUSE_CAIRO
#ifdef __WXMSW__
#if wxUSE_GRAPHICS_DIRECT2D
    m_view->UseGraphicRenderer(wxGraphicsRenderer::GetDirect2DRenderer());
#endif
#if wxUSE_GRAPHICS_GDIPLUS
    m_view->UseGraphicRenderer(wxGraphicsRenderer::GetGDIPlusRenderer());
#endif
#endif  // __WXMSW__
#endif  // wxUSE_GRAPHICS_CONTEXT

    // Horizontal sizer on top, contains drawing Panel and side panel
    bSizerVertical->Add(bSizerHorizontal, 1, wxEXPAND | wxALL, 5);
    bSizerHorizontal->Add(m_view, 4, wxEXPAND | wxALL, 5);
    bSizerHorizontal->Add(m_sidePanel, 1, wxEXPAND | wxALL, 5);

    // Sets background color
    m_view->SetBackgroundColour(wxColor(255, 255, 255));
    m_sidePanel->SetBackgroundColour(wxColor(0, 0, 0));

    SetSizer(bSizerVertical);
    Layout();
    Maximize();
    Show();
}
MainWindowFrame::~MainWindowFrame() {
    delete m_controller;
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
    version << "En savoir plus sur la version"
        << " de l'application Reseau Interurbain";
    fileMenu->Append(wxID_EXIT, wxT("&Quitter    Alt-Q"),
        wxT("Quitter l'application Reseau Interurbain"));
    helpMenu->Append(wxID_ABOUT, wxT("&Version"),
        version);

    mainMenuBar->Append(fileMenu, wxT("&Fichier"));
    mainMenuBar->Append(editMenu, wxT("&Edit"));
    mainMenuBar->Append(helpMenu, wxT("Aide"));

    SetMenuBar(mainMenuBar);
}
}  // namespace gui
}  // namespace reseau_interurbain

