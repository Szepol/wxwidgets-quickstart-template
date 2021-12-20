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
#include "../domain/controller/PlaneGraphics.h"
#include "wx/dcbuffer.h"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

namespace RI_GUI
{

wxBEGIN_EVENT_TABLE(DrawPanel, wxPanel)
	EVT_PAINT(DrawPanel::OnPaint)
wxEND_EVENT_TABLE()

DrawPanel::DrawPanel(wxFrame* parent)
	: wxPanel(parent), planeGraphics(new RI_DOMAIN::PlaneGraphics(this))
{

}

DrawPanel::~DrawPanel()
{
	delete planeGraphics;
}
void DrawPanel::OnPaint(wxPaintEvent& WXUNUSED(event))
{
	if (planeGraphics->IsUsingBuffer())
	{
		wxBufferedPaintDC bpdc(this);
		planeGraphics->DrawComponent(bpdc);
	}
	else 
	{
		wxPaintDC pdc(this);
		planeGraphics->DrawComponent(pdc);
	}
}
} // namespace RI_GUI
