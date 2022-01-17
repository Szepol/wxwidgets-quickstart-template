/*****************************************************************//**
 * \file    Model.h
 * \brief   
 * 
 * \author  Szepol
 * \date    December 2021
 * \license This project is released under MIT license.
 *********************************************************************/

#pragma once

#include <vector>

#include <wx/affinematrix2d.h>

namespace reseau_interurbain
{
namespace domain
{
class Model
{
public:
	Model();
#if wxUSE_DC_TRANSFORM_MATRIX
	Model(wxAffineMatrix2D* p_mtx);
	wxAffineMatrix2D* GetAffineMatrix() { return m_mtx; };
#endif
	~Model();

	void EnableZoomOut(bool p_use = true);
	bool GetZoomOut();
private:
#if wxUSE_DC_TRANSFORM_MATRIX
	wxAffineMatrix2D* m_mtx;
#endif
	bool m_useZoomOut;

};
} // namespace domain
} // namespace reseau_interurbain

