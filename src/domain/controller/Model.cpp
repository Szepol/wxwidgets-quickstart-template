/*****************************************************************//**
 * \file    Model.cpp
 * \brief   
 * 
 * \author  Szepol
 * \date    December 2021
 * \license This project is released under MIT license.
 *********************************************************************/

#include "Model.h"

namespace reseau_interurbain
{
namespace domain
{
Model::Model()
{

}
#if wxUSE_DC_TRANSFORM_MATRIX
Model::Model(wxAffineMatrix2D* p_mtx) : m_mtx(p_mtx)
{

}
#endif
Model::~Model()
{
#if wxUSE_DC_TRANSFORM_MATRIX
	delete m_mtx;
#endif
}
} // namespace domain
} // namespace reseau_interurbain
