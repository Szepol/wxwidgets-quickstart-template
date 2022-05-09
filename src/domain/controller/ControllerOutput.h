/*****************************************************************//**
 * \file    ControllerOutput.h
 * \brief   Communicates with the model inside the domain to draw the
 * objects in the canvas
 * \author  Szepol
 * \date    December 2021
 * \license This project is released under MIT license.
 *********************************************************************/

#pragma once

#include <wx/graphics.h>
#include <wx/panel.h>
#include <domain/controller/Model.h>

namespace reseau_interurbain
{
namespace domain
{
class ControllerOutput
{
public:
	ControllerOutput(wxPanel* parent, Model* p_model);
	~ControllerOutput() {};

#if wxUSE_GRAPHICS_CONTEXT
	void UseGraphicRenderer(wxGraphicsRenderer* renderer);
#endif // wxUSE_GRAPHICS_CONTEXT

	bool IsUsingBuffer() { return m_useBuffer; };
	void EnableAntiAliasing(bool use = true) { m_useAntiAliasing = use; m_parent->Refresh(); }
	void EnableBuffer(bool use = true) { m_useBuffer = use; m_parent->Refresh(); }
	void DrawComponent(wxDC& dc);
protected:
	void DrawGrid(wxDC& dc);

	Model* m_model;
	bool m_useBuffer;
	bool m_useAntiAliasing;
	bool m_useAffineMatrix;
	wxPanel* m_parent;
	wxGraphicsRenderer* m_renderer;
};
} // namespace domain
} // namespace reseau_interurbain

