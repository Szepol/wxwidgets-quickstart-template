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

#ifndef RESEAUINTERURBAIN_SRC_APP_H_
#define RESEAUINTERURBAIN_SRC_APP_H_

#include <wx/app.h>
#include <Version.h>

#define APPLICATION_NAME L"Reseau Interurbain"
#define MINIMUM_SIZE_HEIGHT 720
#define MINIMUM_SIZE_WIDTH 1280

namespace reseau_interurbain {
class App : public wxApp {
 public:
    virtual bool OnInit() wxOVERRIDE;
    virtual int OnExit() wxOVERRIDE { return 0; };
};
}  // namespace reseau_interurbain

#endif  // RESEAUINTERURBAIN_SRC_APP_H_
