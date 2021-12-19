/*****************************************************************//**
 * \file    MainWindowFrame.h
 * \brief   Defines the MainWindowFrame that correspond to the main
 * interface that interacts with the user.
 * 
 * \author  Szepol
 * \date    December 2021
 * \license This project is released under MIT license.
 *********************************************************************/

#include <wx/frame.h>
#include <wx/panel.h>

namespace RI_GUI 
{

class MainWindowFrame : public wxFrame 
{
public:
	MainWindowFrame(wxWindow* parent, wxWindowID id = wxID_ANY);
	~MainWindowFrame() {};
	
	void OnCloseWindow(wxCloseEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

protected:
	wxPanel* m_drawPanel;
	wxPanel* m_sidePanel;

private:
	void InitMenu();

	wxDECLARE_EVENT_TABLE();
};

} // namespace RI_GUI