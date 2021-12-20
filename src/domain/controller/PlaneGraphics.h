/*****************************************************************//**
 * \file    PlaneGraphics.h
 * \brief   Defines plane graphics where the controller
 * communicates with the renderer
 * \author  Szepol
 * \date    December 2021
 * \license This project is released under MIT license.
 *********************************************************************/

#pragma once

#include <wx/graphics.h>
#include <wx/panel.h>

namespace RI_DOMAIN 
{

class PlaneGraphics
{
public:
	PlaneGraphics(wxPanel *parent);
	~PlaneGraphics() {};

	bool IsUsingBuffer() { return m_useBuffer; };
	void EnableAntiAliasing(bool use = true) { m_useAntiAliasing = use; m_parent->Refresh(); }
	void EnableBuffer(bool use = true) { m_useBuffer = use; m_parent->Refresh(); }
	void DrawComponent(wxDC& dc);
protected:

	bool m_useBuffer;
	bool m_useAntiAliasing;
	wxPanel* m_parent;
	wxGraphicsRenderer* m_renderer;
};
}
