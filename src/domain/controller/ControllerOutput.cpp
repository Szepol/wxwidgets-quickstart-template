/*****************************************************************//**
 * \file    ControllerOutput.cpp
 * \brief   
 * 
 * \author  Szepol
 * \date    December 2021
 * \license This project is released under MIT license.
 *********************************************************************/

#include "ControllerOutput.h"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "wx/dcbuffer.h"
#include "wx/dcgraph.h"
#include "wx/graphics.h"
#if wxUSE_SVG
#include "wx/dcsvg.h"
#endif
#if wxUSE_POSTSCRIPT
#include "wx/dcps.h"
#endif

namespace reseau_interurbain
{
namespace domain
{
ControllerOutput::ControllerOutput(wxPanel* parent, Model* p_model) : m_parent(parent), m_model(p_model)
{
#if wxUSE_DC_TRANSFORM_MATRIX
	m_useAffineMatrix = true;
#endif
}
// TODO : Render all the items in the controller
void ControllerOutput::DrawComponent(wxDC& pdc)
{
	if (m_parent == NULL)
		return;

#if wxUSE_GRAPHICS_CONTEXT
	wxGCDC gdc;

	if (m_renderer)
	{
		wxGraphicsContext* context;
		if (wxPaintDC* paintdc = wxDynamicCast(&pdc, wxPaintDC))
			context = m_renderer->CreateContext(*paintdc);
		else if (wxMemoryDC* memdc = wxDynamicCast(&pdc, wxMemoryDC))
			context = m_renderer->CreateContext(*memdc);
#if wxUSE_METAFILE && defined(wxMETAFILE_IS_ENH)
		else if (wxEnhMetaFileDC* metadc = wxDynamicCast(&pdc, wxEnhMetaFileDC))
			context = m_renderer->CreateContext(*metadc);
#endif
		else {
			wxFAIL_MSG("Unknown wxDC kind");
			return;
		}

		context->SetAntialiasMode(m_useAntiAliasing ? wxANTIALIAS_DEFAULT : wxANTIALIAS_NONE);

		gdc.SetBackground(m_parent->GetBackgroundColour());
		gdc.SetGraphicsContext(context);
	}

	wxDC& dc = m_renderer ? static_cast<wxDC&>(gdc) : pdc;
#else
	wxDC& dc = pdc;
#endif 

	if (m_useAffineMatrix)
		dc.SetTransformMatrix(*(m_model->GetAffineMatrix()));

	DrawGrid(dc);
}

void ControllerOutput::DrawGrid(wxDC& dc)
{
#if wxUSE_GRAPHICS_CONTEXT
	if (m_renderer)
	{
		wxGCDC& gdc = (wxGCDC&)dc;
		wxGraphicsContext* gc = gdc.GetGraphicsContext();
		wxGraphicsPath pth;
	}
#endif
	dc.DrawText(wxT("TEST"), wxPoint(50, 50));
}
} // namespace domain
} // namespace reseau_interurbain

