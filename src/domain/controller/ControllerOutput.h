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

#ifndef RESEAUINTERURBAIN_SRC_DOMAIN_CONTROLLER_CONTROLLEROUTPUT_H_
#define RESEAUINTERURBAIN_SRC_DOMAIN_CONTROLLER_CONTROLLEROUTPUT_H_

#include <wx/graphics.h>
#include <wx/panel.h>
#include <domain/controller/Model.h>

namespace reseau_interurbain {
namespace domain {
class ControllerOutput {
 public:
    ControllerOutput(wxPanel* parent, Model* p_model);
    ~ControllerOutput() {}
#if wxUSE_GRAPHICS_CONTEXT
    void UseGraphicRenderer(wxGraphicsRenderer* renderer);
#endif  // wxUSE_GRAPHICS_CONTEXT
    bool IsUsingBuffer() { return m_useBuffer; }
    void EnableAntiAliasing(bool use = true) {
        m_useAntiAliasing = use; m_parent->Refresh();
    }
    void EnableBuffer(bool use = true) {
        m_useBuffer = use; m_parent->Refresh();
    }
    void DrawComponent(wxDC& dc); // NOLINT

 protected:
    void DrawGrid(wxDC& dc); // NOLINT

 private:
    Model* m_model;
    bool m_useBuffer;
    bool m_useAntiAliasing;
    bool m_useAffineMatrix;
    wxPanel* m_parent;
    wxGraphicsRenderer* m_renderer;
};
}  // namespace domain
}  // namespace reseau_interurbain

#endif  // RESEAUINTERURBAIN_SRC_DOMAIN_CONTROLLER_CONTROLLEROUTPUT_H_
