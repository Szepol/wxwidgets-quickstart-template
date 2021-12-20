/*****************************************************************//**
 * \file    MainWindowFrame.h
 * \brief   Defines the MainWindowFrame that correspond to the main
 * interface that interacts with the user.
 * 
 * \author  Szepol
 * \date    December 2021
 * \license This project is released under MIT license.
 *********************************************************************/

#pragma once

#include <wx/frame.h>
#include <wx/panel.h>
#include "DrawPanel.h"

namespace reseau_interurbain
{
// We use a forward declaration for the controller, this is a design choice to prevent unneeded headers link
namespace domain
{
class ControllerInput;
}
namespace gui
{
class MainWindowFrame : public wxFrame
{
public:
	MainWindowFrame(wxWindow* parent, wxWindowID id = wxID_ANY);
	~MainWindowFrame();

	void OnCloseWindow(wxCloseEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

protected:
	domain::ControllerInput* m_controller;
	DrawPanel* m_drawPanel;
	wxPanel* m_sidePanel;

private:
	void InitMenu();

	wxDECLARE_EVENT_TABLE();
};
} // namespace gui
} // namespace reseau_interurbain

