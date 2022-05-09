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

#include <domain/controller/ControllerInput.h>
#include <wx/affinematrix2d.h>

namespace reseau_interurbain {
namespace domain {
ControllerInput::ControllerInput(Model* p_model) : m_model(p_model) {
}
ControllerInput::~ControllerInput() {
    delete m_model;
}
void ControllerInput::Zoom(const int p_direction, int p_x, int p_y) {
    if (p_direction > 0 && !m_model->IsZoomOutEnabled())
        return;
    wxAffineMatrix2D* mtx = m_model->GetAffineMatrix();
    wxPoint2DDouble point = wxPoint2DDouble(wxDouble(p_x), wxDouble(p_y));
    mtx->Invert();
    point = mtx->TransformPoint(point);
    mtx->Invert();
    OutputDebugStringA(("x :" + std::to_string(point.m_x) + "\n").c_str());
    OutputDebugStringA(("y :" + std::to_string(point.m_y) + "\n").c_str());
    if (p_direction > 0) {
        mtx->Translate(point.m_x, point.m_y);
        mtx->Scale(0.91, 0.91);
        mtx->Translate(-point.m_x, -point.m_y);
    } else {
        if (!m_model->IsZoomOutEnabled())
            m_model->EnableZoomOut(true);
        mtx->Translate(point.m_x, point.m_y);
        mtx->Scale(1.09, 1.09);
        mtx->Translate(-point.m_x, -point.m_y);
    }
}
void ControllerInput::Move(int p_dx, int p_dy) {
    wxAffineMatrix2D* mtx = m_model->GetAffineMatrix();
    wxMatrix2D* temp_mtx = new wxMatrix2D();
    mtx->Invert();
    mtx->Get(temp_mtx, nullptr);
    mtx->Invert();
    mtx->Translate(-p_dx * temp_mtx->m_11, -p_dy * temp_mtx->m_22);
}
}  // namespace domain
}  // namespace reseau_interurbain

