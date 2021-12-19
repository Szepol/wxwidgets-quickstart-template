/*****************************************************************//**
 * \file    MainWindowFrame.cpp
 * \brief   Code for MainWindowFrame that correspond to the main
 * interface that interacts with the user.
 * 
 * \author  Szepol
 * \date    December 2021
 * \license This project is released under MIT license.
 *********************************************************************/

#include "MainWindowFrame.h"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif


namespace RI_GUI 
{
inline wxString wxBuildInfo() 
{
    wxString build;

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

wxBEGIN_EVENT_TABLE(MainWindowFrame,wxFrame)
    EVT_CLOSE(MainWindowFrame::OnCloseWindow)
    // TODO : Lock the ratio when resizing the window
    EVT_MENU(wxID_EXIT, MainWindowFrame::OnExit)
    EVT_MENU(wxID_ABOUT, MainWindowFrame::OnAbout)
wxEND_EVENT_TABLE()

MainWindowFrame::MainWindowFrame(wxWindow* parent, wxWindowID id) :
    wxFrame(parent, id, wxTheApp->GetAppName()) 
{
    // Initialize menu bar
    InitMenu();
    SetBackgroundColour(wxColor(120, 150, 200));

    wxBoxSizer* bSizerVertical = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* bSizerHorizontal = new wxBoxSizer(wxHORIZONTAL);
    wxPanel* m_drawPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize); // Drawing panel
    wxPanel* m_sidePanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize); // Information panel
    
    // Horizontal sizer on top, contains drawing Panel and side panel
    bSizerVertical->Add(bSizerHorizontal, 1, wxEXPAND | wxALL, 5);
    bSizerHorizontal->Add(m_drawPanel, 4, wxEXPAND | wxALL, 5);
    m_drawPanel->SetBackgroundColour(wxColor(255, 255, 255));
    bSizerHorizontal->Add(m_sidePanel, 1, wxEXPAND | wxALL, 5);
    m_sidePanel->SetBackgroundColour(wxColor(0, 0, 0));


    
    SetSizer(bSizerVertical);
    Layout();
    Maximize();
    
    Show();
}

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

void MainWindowFrame::OnCloseWindow(wxCloseEvent& WXUNUSED(event)) 
{
    static bool destroyed = false;
    if (destroyed)
        return;

    this->Destroy();
    
    destroyed = true;
}
void MainWindowFrame::OnExit(wxCommandEvent& WXUNUSED(event)) 
{
    Close(true);
}

void MainWindowFrame::OnAbout(wxCommandEvent& WXUNUSED(event)) 
{
    wxMessageBox(wxT("Version : ReseauInterurbain-v0.00") + wxBuildInfo(), wxT("Information"));
}
} // namespace RI_GUI
