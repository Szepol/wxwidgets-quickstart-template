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

#define APPLICATION_NAME L"Reseau Interurbain"
#define MINIMUM_SIZE_HEIGHT 720
#define MINIMUM_SIZE_WIDTH 1280

namespace reseau_interurbain
{
class App : public wxApp
{
public:
    virtual bool OnInit() wxOVERRIDE;
    virtual int OnExit() wxOVERRIDE { return 0; };

};
} // namespace reseau_interurbain

