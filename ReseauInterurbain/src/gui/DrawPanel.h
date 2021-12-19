/*****************************************************************//**
 * \file    DrawPanel.h
 * \brief   Defines the DrawPanel where all the objects 
 * rendering is done.
 * 
 * \author  Szepol
 * \date    December 2021
 * \license This project is released under MIT license.
 *********************************************************************/

#include <wx/frame.h>
#include <wx/panel.h>

// Forward declaration ( Class is defined in source file )
namespace RI_DOMAIN 
{
class PlaneGraphics;
} // RI_DOMAIN

namespace RI_GUI 
{

class DrawPanel : wxPanel 
{
public:
	DrawPanel(wxFrame* parent);
	~DrawPanel();

	void OnPaint(wxPaintEvent& event);
protected:
	RI_DOMAIN::PlaneGraphics*		planeGraphics;

	wxDECLARE_EVENT_TABLE();
};

} // namespace RI_GUI
