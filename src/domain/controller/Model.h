/*****************************************************************//**
 * \file    Model.h
 * \brief   Defines Model class used by the controller to store all data
 * used by the domain.
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
	Model(wxAffineMatrix2D* p_mtx);
	wxAffineMatrix2D* GetAffineMatrix() { return m_mtx; };
	~Model();

	void EnableZoomOut(bool p_use = true);
	bool IsZoomOutEnabled();
private:
	wxAffineMatrix2D* m_mtx;
	bool m_useZoomOut;

};
} // namespace domain
} // namespace reseau_interurbain

