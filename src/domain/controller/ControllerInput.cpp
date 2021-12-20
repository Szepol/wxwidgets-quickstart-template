/*****************************************************************//**
 * \file    ControllerInput.cpp
 * \brief   
 * 
 * \author  Szepol
 * \date    December 2021
 * \license This project is released under MIT license.
 *********************************************************************/

#include "ControllerInput.h"

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
} // domain
} // reseau_interurbain

