/*****************************************************************//**
 * \file    ControllerOutput.cpp
 * \brief   Code for the ControllerOutput handling all most of the
 * outputs to the view object.
 * 
 * \author  Szepol
 * \date    December 2021
 * \license This project is released under MIT license.
 *********************************************************************/

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "ControllerOutput.h"

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
/**
 * \brief .
 * 
 * \param parent
 * \param p_model
 */
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
/**
 * \brief .
 * 
 * \param dc
 */
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
	wxPoint2DDouble origin = wxPoint(0, 0);
	int width;
	int height;
	dc.GetSize(&width, &height);
	wxPoint2DDouble limit = wxPoint(width, height);
	if (m_useAffineMatrix)
	{
		wxAffineMatrix2D* mtx = m_model->GetAffineMatrix();
		wxMatrix2D* ref_mtx = new wxMatrix2D();
		// Inverse affine matrix
		mtx->Invert();
		// Get the matrix
		mtx->Get(ref_mtx, nullptr);
		// If the scale is too big we disable the zooming to prevent
		// frame rate dropping really low when scaling is too high
		if (ref_mtx->m_11 > 1.5f || ref_mtx->m_22 > 1.5f)
		{
			ref_mtx->m_11 = 1.5f;
			ref_mtx->m_22 = 1.5f;
			m_model->EnableZoomOut(false);
		}
		// Find the logical position by transforming 
		// the point with the inverse matrix
		limit = mtx->TransformPoint(limit);
		origin = mtx->TransformPoint(origin);
		// Reverse affine matrix
		mtx->Invert();
	}
	// Draw the grid
	for (int x = floor(origin.m_x /50) * 50; x <= floor(limit.m_x); x += 50)
	{
		for (int y = floor(origin.m_y / 50) * 50; y <= floor(limit.m_y); y += 50)
		{
			wxBrush brush = dc.GetBrush();
			brush.SetColour(wxColor(211, 211, 211));
			dc.SetPen(*wxGREY_PEN);
			dc.SetBrush(brush);
			dc.DrawRectangle(x, y, 50, 50);
		}
	}
}
} // namespace domain
} // namespace reseau_interurbain

