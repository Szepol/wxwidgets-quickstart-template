/*****************************************************************//**
 * \file    ControllerInput.h
 * \brief   
 * 
 * \author  Szepol
 * \date    December 2021
 * \license This project is released under MIT license.
 *********************************************************************/

#pragma once

#include "Model.h"

namespace reseau_interurbain
{
namespace domain
{
class ControllerInput
{
public:
	ControllerInput(Model* p_model);
	~ControllerInput();
private:
	Model* m_model;
};
} // namespace domain
} // namespace reseau_interurbain

