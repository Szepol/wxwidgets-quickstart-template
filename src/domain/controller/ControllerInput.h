/*****************************************************************//**
 * \file    ControllerInput.h
 * \brief   
 * 
 * \author  Szepol
 * \date    December 2021
 * \license This project is released under MIT license.
 *********************************************************************/

#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <domain/controller/Model.h>

namespace reseau_interurbain
{
namespace domain
{
class ControllerInput
{
public:
	ControllerInput(Model* p_model);
	~ControllerInput();

	void Zoom(const int p_direction, int p_x, int p_y);
	void Move(int p_dx, int p_dy);
private:
	Model* m_model;
};
} // namespace domain
} // namespace reseau_interurbain

