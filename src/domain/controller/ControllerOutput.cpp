// Copyright 2022 Szepol
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this softwareand associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright noticeand this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <domain/controller/ControllerOutput.h>
#include <wx/dcbuffer.h>
#include <wx/dcgraph.h>
#include <wx/graphics.h>
#if wxUSE_SVG
#include <wx/dcsvg.h>
#endif
#if wxUSE_POSTSCRIPT
#include <wx/dcps.h>
#endif


namespace reseau_interurbain {
namespace domain {
ControllerOutput::ControllerOutput(wxPanel* parent, Model* p_model)
    : m_parent(parent), m_model(p_model) {
#if wxUSE_DC_TRANSFORM_MATRIX
    m_useAffineMatrix = true;
#endif
#if wxUSE_GRAPHICS_CONTEXT
    m_renderer = NULL;
    m_useAntiAliasing = true;
#endif
    m_useBuffer = true;
}
// TODO(Szepol): Render all the items in the controller
void ControllerOutput::DrawComponent(wxDC* pdc) {
    if (m_parent == NULL)
        return;

#if wxUSE_GRAPHICS_CONTEXT
    wxGCDC gdc;

    if (m_renderer) {
        wxGraphicsContext* context;
        if (auto paintdc = wxDynamicCast(pdc, wxPaintDC)) {
            context = m_renderer->CreateContext(*paintdc);
        } else if (auto memdc = wxDynamicCast(pdc, wxMemoryDC)) {
            context = m_renderer->CreateContext(*memdc);
#if wxUSE_METAFILE && defined(wxMETAFILE_IS_ENH)
        } else if (auto metadc = wxDynamicCast(&pdc, wxEnhMetaFileDC)) {
            context = m_renderer->CreateContext(*metadc);
#endif
        } else {
            wxFAIL_MSG("Unknown wxDC kind");
            return;
        }

        context->SetAntialiasMode(m_useAntiAliasing ?
            wxANTIALIAS_DEFAULT : wxANTIALIAS_NONE);

        gdc.SetBackground(m_parent->GetBackgroundColour());
        gdc.SetGraphicsContext(context);
    }

    wxDC* dc = m_renderer ? gdc.GetImpl()->GetOwner() : pdc;
#else
    wxDC& dc = pdc;
#endif
    if (m_useAffineMatrix)
        dc->SetTransformMatrix(*(m_model->GetAffineMatrix()));
    DrawGrid(dc);
}
void ControllerOutput::DrawGrid(wxDC* dc) {
#if wxUSE_GRAPHICS_CONTEXT
    if (m_renderer) {
        wxGCDC& gdc = (wxGCDC&)*dc;
        wxGraphicsContext* gc = gdc.GetGraphicsContext();
        wxGraphicsPath pth;
    }
#endif
    wxPoint2DDouble origin = wxPoint(0, 0);
    int width;
    int height;
    dc->GetSize(&width, &height);
    wxPoint2DDouble limit = wxPoint(width, height);
    if (m_useAffineMatrix) {
        wxAffineMatrix2D* mtx = m_model->GetAffineMatrix();
        wxMatrix2D* ref_mtx = new wxMatrix2D();
        // Inverse affine matrix
        mtx->Invert();
        // Get the matrix
        mtx->Get(ref_mtx, nullptr);
        // If the scale is too big we disable the zooming to prevent
        // frame rate dropping really low when scaling is too high
        if (ref_mtx->m_11 > 1.5f || ref_mtx->m_22 > 1.5f) {
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
    origin.m_x = floor(origin.m_x / 50) * 50;
    origin.m_y = floor(origin.m_y / 50) * 50;
    for (int x = origin.m_x; x <= floor(limit.m_x); x += 50) {
        for (int y = origin.m_y; y <= floor(limit.m_y); y += 50) {
            wxBrush brush = dc->GetBrush();
            brush.SetColour(wxColor(211, 211, 211));
            dc->SetPen(*wxGREY_PEN);
            dc->SetBrush(brush);
            dc->DrawRectangle(x, y, 50, 50);
        }
    }
}
#if wxUSE_GRAPHICS_CONTEXT
void ControllerOutput::UseGraphicRenderer(wxGraphicsRenderer* renderer) {
    m_renderer = renderer;
    m_parent->Refresh();
}
#endif  // wxUSE_GRAPHICS_CONTEXT
}  // namespace domain
}  // namespace reseau_interurbain

