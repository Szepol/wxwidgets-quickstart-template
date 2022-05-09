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

#include <domain/controller/Model.h>

namespace reseau_interurbain
{
namespace domain
{
Model::Model() : m_mtx(nullptr), m_useZoomOut(false)
{

}
Model::Model(wxAffineMatrix2D* p_mtx) : m_mtx(p_mtx), m_useZoomOut(true)
{

}
Model::~Model()
{
	delete m_mtx;
}
void Model::EnableZoomOut(bool p_use)
{
	if (m_mtx != nullptr)
		m_useZoomOut = p_use;
}
bool Model::IsZoomOutEnabled()
{
	return m_useZoomOut;
}
} // namespace domain
} // namespace reseau_interurbain

