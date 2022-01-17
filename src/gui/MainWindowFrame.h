/*****************************************************************//**
 * \file    MainWindowFrame.h
 * \brief   Defines the MainWindowFrame that correspond to the main
 * interface that communicates with the user.
 * 
 * \author  Szepol
 * \date    December 2021
 * \license This project is released under MIT license.
 *********************************************************************/

#pragma once

#include "View.h"
#include <wx/frame.h>
#include <wx/panel.h>

namespace reseau_interurbain
{
namespace domain
{
class ControllerInput;
}
namespace gui
{
class View;
/**
 * \class MainWindowFrame
 * \brief Class of the interface where most of the input of the informations 
 * from the user to the domain is done. Is composed of the menu bar, the view and the side panel.
 * 
 */
class MainWindowFrame : public wxFrame
{
	friend class View;
public:
	MainWindowFrame(wxWindow* p_parent, wxWindowID p_id = wxID_ANY);
	~MainWindowFrame();

protected:
	void OnCloseWindow(wxCloseEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

	domain::ControllerInput* m_controller;
	View* m_view;
	wxPanel* m_sidePanel;

private:
	void InitMenu();

	wxDECLARE_EVENT_TABLE();
};
} // namespace gui
} // namespace reseau_interurbain

