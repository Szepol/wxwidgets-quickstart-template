/*****************************************************************//**
 * \file    Model.cpp
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

#include "Model.h"

namespace reseau_interurbain
{
namespace domain
{
/**
 * \brief .
 * 
 */
Model::Model()
{

}
#if wxUSE_DC_TRANSFORM_MATRIX
/**
 * \brief .
 * 
 * \param p_mtx
 */
Model::Model(wxAffineMatrix2D* p_mtx) : m_mtx(p_mtx), m_useZoomOut(true)
{

}
#endif
/**
 * \brief .
 * 
 */
Model::~Model()
{
#if wxUSE_DC_TRANSFORM_MATRIX
	delete m_mtx;
#endif
}
/**
 * \brief .
 * 
 * \param p_use
 */
void Model::EnableZoomOut(bool p_use)
{
	m_useZoomOut = p_use;
}
/**
 * \brief .
 * 
 * \return 
 */
bool Model::GetZoomOut()
{
	return m_useZoomOut;
}
} // namespace domain
} // namespace reseau_interurbain

