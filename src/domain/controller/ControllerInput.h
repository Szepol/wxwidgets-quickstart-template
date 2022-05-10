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

#ifndef RESEAUINTERURBAIN_SRC_DOMAIN_CONTROLLER_CONTROLLERINPUT_H_
#define RESEAUINTERURBAIN_SRC_DOMAIN_CONTROLLER_CONTROLLERINPUT_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <domain/controller/Model.h>

namespace reseau_interurbain {
namespace domain {
class ControllerInput {
 public:
    explicit ControllerInput(Model* p_model);
    ~ControllerInput();
    void Zoom(const int p_direction, int p_x, int p_y);
    void Move(int p_dx, int p_dy);

 private:
    Model* m_model;
};
}  // namespace domain
}  // namespace reseau_interurbain

#endif  // RESEAUINTERURBAIN_SRC_DOMAIN_CONTROLLER_CONTROLLERINPUT_H_
