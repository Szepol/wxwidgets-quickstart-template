/*****************************************************************//**
 * \file    ControllerInput.cpp
 * \brief   
 * 
 * \author  Szepol
 * \date    December 2021
 * \license This project is released under MIT license.
 *********************************************************************/

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "ControllerInput.h"
#include "wx/affinematrix2d.h"

namespace reseau_interurbain
{
namespace domain
{
ControllerInput::ControllerInput(Model* p_model) : m_model(p_model)
{

}
ControllerInput::~ControllerInput()
{
	delete m_model;
}
void ControllerInput::Zoom(const int p_direction, int p_x, int p_y)
{
	if (p_direction > 0 && !m_model->IsZoomOutEnabled())
		return;
	wxAffineMatrix2D* mtx = m_model->GetAffineMatrix();
	wxPoint2DDouble point = wxPoint2DDouble(wxDouble(p_x), wxDouble(p_y));
	mtx->Invert();
	point = mtx->TransformPoint(point);
	mtx->Invert();
	OutputDebugStringA(("x :" + std::to_string(point.m_x) + "\n").c_str());
	OutputDebugStringA(("y :" + std::to_string(point.m_y) + "\n").c_str());
	if (p_direction > 0)
	{

		mtx->Translate(point.m_x, point.m_y);
		mtx->Scale(0.91, 0.91);
		mtx->Translate(-point.m_x, -point.m_y);
	}
	else
	{
		if (!m_model->IsZoomOutEnabled())
			m_model->EnableZoomOut(true);
		mtx->Translate(point.m_x, point.m_y);
		mtx->Scale(1.09, 1.09);
		mtx->Translate(-point.m_x, -point.m_y);
	}
}
void ControllerInput::Move(int p_dx, int p_dy)
{
	wxAffineMatrix2D* mtx = m_model->GetAffineMatrix();
	wxMatrix2D* temp_mtx = new wxMatrix2D();
	mtx->Invert();
	mtx->Get(temp_mtx, nullptr);
	mtx->Invert();
	mtx->Translate(-p_dx * temp_mtx->m_11, -p_dy * temp_mtx->m_22);
}
} // domain
} // reseau_interurbain

