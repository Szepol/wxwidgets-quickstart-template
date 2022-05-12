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

#include <gui/View.h>
#include <domain/controller/ControllerOutput.h>
#include <domain/controller/ControllerInput.h>
#include <domain/controller/Model.h>
#include <wx/dcbuffer.h>

namespace reseau_interurbain {
namespace gui {

wxBEGIN_EVENT_TABLE(View, wxPanel)
    EVT_RIGHT_DOWN(View::OnRightMouse)
    EVT_MOUSEWHEEL(View::OnZoom)
    EVT_MOTION(View::UpdateMouse)
    EVT_PAINT(View::OnPaint)
    EVT_ERASE_BACKGROUND(View::OnEraseBackground)
wxEND_EVENT_TABLE()

View::View(wxFrame* p_parent, domain::Model* p_model)
      : wxPanel(p_parent),
      m_controller(new domain::ControllerOutput(this, p_model)),
      m_point(wxPoint(0, 0)) {
    SetDoubleBuffered(true);
}
View::~View() {
    delete m_controller;
}

void View::OnZoom(wxMouseEvent& event) {
    reinterpret_cast<MainWindowFrame*>(GetParent())->m_controller->Zoom(
        event.GetWheelRotation(),
        ScreenToClient(wxGetMousePosition()).x,
        ScreenToClient(wxGetMousePosition()).y);
    Update();
    Refresh();
}
void View::UpdateMouse(wxMouseEvent& event) {
    if (event.Dragging() && event.RightIsDown()) {
        reinterpret_cast<MainWindowFrame*>(GetParent())->m_controller->Move(
            m_point.x - ScreenToClient(wxGetMousePosition()).x,
            m_point.y - ScreenToClient(wxGetMousePosition()).y);
        m_point.x = ScreenToClient(wxGetMousePosition()).x;
        m_point.y = ScreenToClient(wxGetMousePosition()).y;
        Update();
        Refresh();
    }
}
void View::OnRightMouse(wxMouseEvent& WXUNUSED(event)) {
    m_point.x = ScreenToClient(wxGetMousePosition()).x;
    m_point.y = ScreenToClient(wxGetMousePosition()).y;
}
void View::OnPaint(wxPaintEvent& WXUNUSED(event)) {
    if (m_controller->IsUsingBuffer()) {
        wxBufferedPaintDC bpdc(this);
        m_controller->DrawComponent(bpdc);
    } else {
        wxPaintDC pdc(this);
        m_controller->DrawComponent(pdc);
    }
}
void View::OnEraseBackground(wxEraseEvent& WXUNUSED(event)) {
}
#if wxUSE_GRAPHICS_CONTEXT
void View::UseGraphicRenderer(wxGraphicsRenderer* renderer) {
    m_controller->UseGraphicRenderer(renderer);
}
#endif  // wxUSE_GRAPHICS_CONTEXT
}  // namespace gui
}  // namespace reseau_interurbain

