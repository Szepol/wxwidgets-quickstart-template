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

#include <domain/controller/Model.h>

namespace reseau_interurbain {
namespace domain {
Model::Model() : m_useZoomOut(false) {
#if wxUSE_DC_TRANSFORM_MATRIX
    m_mtx = nullptr;
#endif
}
#if wxUSE_DC_TRANSFORM_MATRIX
Model::Model(wxAffineMatrix2D* p_mtx) : m_mtx(p_mtx), m_useZoomOut(true) {
}
#endif
Model::~Model() {
#if wxUSE_DC_TRANSFORM_MATRIX
    delete m_mtx;
#endif
}
void Model::EnableZoomOut(bool p_use) {
#if wxUSE_DC_TRANSFORM_MATRIX
    if (m_mtx != nullptr)
        m_useZoomOut = p_use;
#endif
}
bool Model::IsZoomOutEnabled() {
    return m_useZoomOut;
}
}  // namespace domain
}  // namespace reseau_interurbain

