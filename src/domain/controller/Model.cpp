/*****************************************************************//**
 * \file    Model.cpp
 * \brief   Implementation of the Model class used by the controller 
 * to store all data used by the domain.
 * 
 * \author  Szepol
 * \date    December 2021
 * \license This project is released under MIT license.
 *********************************************************************/


#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "Model.h"

namespace reseau_interurbain
{
namespace domain
{
/**
 * \brief Default Model constructor, zoom is disabled.
 * 
 */
Model::Model() : m_mtx(nullptr), m_useZoomOut(false)
{

}
/**
 * \brief Model constructor using a pointer to an AffineMatrix as parameter to handle zoom transformation.
 * 
 * \param p_mtx
 */
Model::Model(wxAffineMatrix2D* p_mtx) : m_mtx(p_mtx), m_useZoomOut(true)
{

}
/**
 * \brief Model destructor, if using zoom it handles the deletion of the pointer to the allocated AffineMatrix on the stack
 * 
 */
Model::~Model()
{
	delete m_mtx;
}
/**
 * \brief Method used to toggle weither the zoom is enabled or disable.
 * 
 * \param p_use boolean of the logical truth value
 */
void Model::EnableZoomOut(bool p_use)
{
	if (m_mtx != nullptr)
		m_useZoomOut = p_use;
}
/**
 * \brief Method to get weither the zoom is enabled or disabled
 * 
 * \return bool of the logical truth value
 */
bool Model::IsZoomOutEnabled()
{
	return m_useZoomOut;
}
} // namespace domain
} // namespace reseau_interurbain

