/*****************************************************************//**
 * \file    MainWindowFrame.cpp
 * \brief   Code for MainWindowFrame that correspond to the main
 * interface that communicates with the user.
 * 
 * \author  Szepol
 * \date    December 2021
 * \license This project is released under MIT license.
 *********************************************************************/

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "MainWindowFrame.h"
#include "../domain/controller/ControllerInput.h"
#include "../domain/controller/Model.h"
#include "../App.h"
#include <format>

#include "wx/event.h"

namespace reseau_interurbain
{
namespace gui
{
inline wxString wxBuildInfo()
{
    wxString build;
    build << APPLICATION_NAME << "-" << VERSION;
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
    // TODO : Lock the ratio when resizing the window
    EVT_MENU(wxID_EXIT, MainWindowFrame::OnExit)
    EVT_MENU(wxID_ABOUT, MainWindowFrame::OnAbout)
wxEND_EVENT_TABLE()

/**
 * \brief MainWindowFrame constructor, initialize the main window frame by creating the menu bar.
 * view panel and side panel.
 * 
 * \param wxWindow* p_parent pointer to parent window
 * \param wxWindowID p_id window id of the frame
 */
MainWindowFrame::MainWindowFrame(wxWindow* p_parent, wxWindowID p_id) 
    : wxFrame(p_parent, p_id, wxTheApp->GetAppName())
{
    // We need to share same model object with both the ControllerInput and ControllerOutput
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
    m_sidePanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize); // Information panel

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
/**
 * \brief MainWindowFrame destructor
 * 
 */
MainWindowFrame::~MainWindowFrame()
{
    delete m_controller;
}
/**
 * \brief OnCloseWindow handles the X button event to close the window.
 * 
 * \param wxCloseEvent& WXUNUSED 
 */
void MainWindowFrame::OnCloseWindow(wxCloseEvent& WXUNUSED(event))
{
    static bool destroyed = false;
    if (destroyed)
        return;

    this->Destroy();

    destroyed = true;
}
/**
 * \brief OnExit handles the exit event in the menu bar.
 * 
 * \param wxCommandEvent& WXUNUSED
 */
void MainWindowFrame::OnExit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}
/**
 * \brief OnAbout handles the about event in the menu bar.
 * 
 * \param wxCommandEvent& WXUNUSED
 */
void MainWindowFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox(wxBuildInfo(), wxT("Information"));
}
/**
 * \brief InitMenu initialize the menu bar
 *
 */
void MainWindowFrame::InitMenu()
{
    wxMenu* fileMenu = new wxMenu();
    wxMenu* editMenu = new wxMenu();
    wxMenu* helpMenu = new wxMenu();
    wxMenuBar* mainMenuBar = new wxMenuBar();

    fileMenu->Append(wxID_EXIT, wxT("&Quitter\tAlt-Q"), wxT("Quitter l'application Reseau Interurbain"));
    helpMenu->Append(wxID_ABOUT, wxT("&Version"), wxT("En savoir plus sur la version de l'application Reseau Interurbain"));

    mainMenuBar->Append(fileMenu, wxT("&Fichier"));
    mainMenuBar->Append(editMenu, wxT("&Edit"));
    mainMenuBar->Append(helpMenu, wxT("Aide"));

    SetMenuBar(mainMenuBar);
}
} // namespace gui
} // namespace reseau_interurbain

