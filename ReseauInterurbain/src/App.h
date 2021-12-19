/*****************************************************************//**
 * \file    App.h
 * \brief   Defines Application class, acts as the entry point
 * for the application
 * 
 * \author  Szepol
 * \date    December 2021
 * \license This project is released under MIT license.
 *********************************************************************/

#pragma once

#include <wx/app.h>

class App : public wxApp 
{
public:
    virtual bool OnInit() wxOVERRIDE;
    virtual int OnExit() wxOVERRIDE { return 0; };


};
