
/*****************************************************************//**
 * \file    PlaneGraphics.cpp
 * \brief   Code of the plane graphics where the controller
 * communicates with the renderer
 * 
 * \author  Szepol
 * \date    December 2021
 * \license This project is released under MIT license.
 *********************************************************************/

#include "PlaneGraphics.h"

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

namespace RI_DOMAIN 
{
PlaneGraphics::PlaneGraphics(wxPanel* parent) : m_parent(parent)
{
}
// TODO : Render all the items in the controller
void PlaneGraphics::DrawComponent(wxDC& pdc)
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

}
} // namespace RI_DOMAIN
