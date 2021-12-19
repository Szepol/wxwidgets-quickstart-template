/*****************************************************************//**
 * \file    App.cpp
 * \brief   Code for the Application class, acts as the entry point
 * for the application
 * 
 * \author  Szepol
 * \date    December 2021
 * \license This project is released under MIT license.
 *********************************************************************/

#include "App.h"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "gui/MainWindowFrame.h"

#define APPLICATION_NAME L"Reseau Interurbain"
#define MINIMUM_SIZE_HEIGHT 720
#define MINIMUM_SIZE_WIDTH 1280

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    wxTheApp->SetAppName(APPLICATION_NAME);
    wxTheApp->SetAppDisplayName(APPLICATION_NAME);
    wxTheApp->SetVendorName(APPLICATION_NAME);

    ::wxInitAllImageHandlers();

    RI_GUI::MainWindowFrame* Frame = new RI_GUI::MainWindowFrame(NULL);
    Frame->SetMinSize(wxSize(MINIMUM_SIZE_WIDTH, MINIMUM_SIZE_HEIGHT));
    SetTopWindow(Frame);

    return true;
}
