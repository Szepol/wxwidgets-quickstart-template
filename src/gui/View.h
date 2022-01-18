/*****************************************************************//**
 * \file    View.h
 * \brief   Defines the View that correspond to main panel that
 * draws the objects from the domain to user
 * 
 * \author  Szepol
 * \date    December 2021
 * \license This project is released under MIT license.
 *********************************************************************/

#pragma once

#include "MainWindowFrame.h"
#include <wx/panel.h>

namespace reseau_interurbain
{
namespace domain
{
class ControllerOutput;
class Model;
} // namespace domain
namespace gui
{
class MainWindowFrame;
/**
 * \class View
 * \brief Class of the drawing panel wheres the domain's objects are visually represented
 * contains functionalities of inputs like zoom and translation of the view.
 */
class View : public wxPanel
{
public:
	View(wxFrame* p_parent, domain::Model* p_model);
	~View();

protected:
	void OnZoom(wxMouseEvent& event);
	void UpdateMouse(wxMouseEvent& event);
	void OnRightMouse(wxMouseEvent& event);
	void OnPaint(wxPaintEvent& event);
	void OnEraseBackground(wxEraseEvent& event);

private:
	wxPoint m_point;
	domain::ControllerOutput* m_controller;

	wxDECLARE_EVENT_TABLE();
};
} // namespace gui
} // namespace reseau_interurbain
