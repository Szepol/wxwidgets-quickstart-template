/*****************************************************************//**
 * \file    DrawPanel.h
 * \brief   Defines the DrawPanel where all the objects 
 * rendering is done.
 * 
 * \author  Szepol
 * \date    December 2021
 * \license This project is released under MIT license.
 *********************************************************************/

#pragma once

#include <wx/frame.h>
#include <wx/panel.h>

namespace reseau_interurbain
{
// Forward declaration
namespace domain
{
class ControllerOutput;
class Model;
} // namespace domain

namespace gui
{
class DrawPanel : public wxPanel
{
public:
	DrawPanel(wxFrame* p_parent, domain::Model* p_model);
	~DrawPanel();

	void OnPaint(wxPaintEvent& event);

protected:
	domain::ControllerOutput* m_controller;

	wxDECLARE_EVENT_TABLE();
};
} // namespace gui
} // namespace reseau_interurbain

