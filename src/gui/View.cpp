/*****************************************************************//**
 * \file    View.cpp
 * \brief   Code for the View that correspond to main panel that
 * draws the objects from the domain to user
 * 
 * \author  Szepol
 * \date    December 2021
 * \license This project is released under MIT license.
 *********************************************************************/

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <gui/View.h>
#include <domain/controller/ControllerOutput.h>
#include <domain/controller/ControllerInput.h>
#include <domain/controller/Model.h>
#include <wx/dcbuffer.h>

namespace reseau_interurbain
{
namespace gui
{
wxBEGIN_EVENT_TABLE(View, wxPanel)
EVT_RIGHT_DOWN(View::OnRightMouse)
EVT_MOUSEWHEEL(View::OnZoom)
EVT_MOTION(View::UpdateMouse)
EVT_PAINT(View::OnPaint)
EVT_ERASE_BACKGROUND(View::OnEraseBackground)
wxEND_EVENT_TABLE()
/**
 * \brief View constructor, initializes the panel.
 * 
 * \param wxFrame* p_parent pointer to the parent
 * \param domain::Model p_model pointer to the model object
 */
View::View(wxFrame* p_parent, domain::Model* p_model) :
	wxPanel(p_parent), m_controller(new domain::ControllerOutput(this, p_model)), m_point(wxPoint(0,0))
{
	SetDoubleBuffered(true);
}
/**
 * \brief View destructor.
 * 
 */
View::~View()
{
	delete m_controller;
}
/**
 * \brief Handle the mousewheel event and scales the affinematrix of the model accordingly
 * 
 * \param wxMouseEvent& event used to get the mouse position and wheel rotation axis
 */
void View::OnZoom(wxMouseEvent& event)
{
	((MainWindowFrame*)GetParent())->m_controller->Zoom(event.GetWheelRotation(), ScreenToClient(wxGetMousePosition()).x, ScreenToClient(wxGetMousePosition()).y);
	Update();
	Refresh();
}
/**
 * \brief Handles the mouse motion event
 * 
 * \param wxMouseEvent& event used to assess what state the mouse is in and calculate the delta of the motion if needed.
 */
void View::UpdateMouse(wxMouseEvent& event)
{
	if (event.Dragging() && event.RightIsDown())
	{
		((MainWindowFrame*)GetParent())->m_controller->Move(m_point.x - ScreenToClient(wxGetMousePosition()).x, m_point.y - ScreenToClient(wxGetMousePosition()).y);
		m_point.x = ScreenToClient(wxGetMousePosition()).x;
		m_point.y = ScreenToClient(wxGetMousePosition()).y;
		Update();
		Refresh();
	}
}
/**
 * \brief Saves the position of the mouse on right click, used to calculate the delta during motion
 * 
 * \param wxMouseEvent& WXUNUSED event; no method used.
 */
void View::OnRightMouse(wxMouseEvent& WXUNUSED(event))
{
	m_point.x = ScreenToClient(wxGetMousePosition()).x;
	m_point.y = ScreenToClient(wxGetMousePosition()).y;
}
/**
 * \brief Pains the paint drawing context or buffered paint drawing context.
 * 
 * \param wxPaintEvent& WXUNUSED event; no method used.
 */
void View::OnPaint(wxPaintEvent& WXUNUSED(event))
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
/**
 * \brief Removes the erase background because it just draws over, less demanding according to the wiki.
 * 
 * \param  wxEraseEvent& WXUNUSED event; no method used.
 */
void View::OnEraseBackground(wxEraseEvent& WXUNUSED(event))
{

}
#if wxUSE_GRAPHICS_CONTEXT
void View::UseGraphicRenderer(wxGraphicsRenderer* renderer)
{
	m_controller->UseGraphicRenderer(renderer);
}
#endif // wxUSE_GRAPHICS_CONTEXT
} // namespace gui
} // namespace reseau_interurbain

