/*****************************************************************//**
 * \file    DrawPanel.cpp
 * \brief   Code for the DrawPanel where all the objects
 * rendering is done.
 * 
 * \author  Szepol
 * \date    December 2021
 * \license This project is released under MIT license.
 *********************************************************************/

#include "DrawPanel.h"
#include "../domain/controller/ControllerOutput.h"
#include "../domain/controller/Model.h"
#include "wx/dcbuffer.h"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

namespace reseau_interurbain
{
namespace gui
{
wxBEGIN_EVENT_TABLE(DrawPanel, wxPanel)
EVT_PAINT(DrawPanel::OnPaint)
wxEND_EVENT_TABLE()

DrawPanel::DrawPanel(wxFrame* p_parent, domain::Model* p_model)
	: wxPanel(p_parent), m_controller(new domain::ControllerOutput(this, p_model))
{

}

DrawPanel::~DrawPanel()
{
	delete m_controller;
}
void DrawPanel::OnPaint(wxPaintEvent& WXUNUSED(event))
{
	if (m_controller->IsUsingBuffer())
	{
		wxBufferedPaintDC bpdc(this);
		m_controller->DrawComponent(bpdc);
	}
	else
	{
		wxPaintDC pdc(this);
		m_controller->DrawComponent(pdc);
	}
}
} // namespace gui
} // namespace reseau_interurbain

