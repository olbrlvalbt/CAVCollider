#pragma once

#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <wx/propgrid/propgrid.h>


#include "Rule110.h"

class ColliderMenu : public wxFrame {
public:
	enum class SIDE{LEFT, RIGHT, CENTRAL};
	
	Rule110 rule110;

	wxPanel menuPanel;

	std::unique_ptr<wxPropertyGrid> pg;

	std::unique_ptr<wxButton> createButton;
	std::unique_ptr<wxButton> goToButton;

	string leftIc;
	string rightIc;
	string centralIc;


	ColliderMenu();

	void OnChangedProperty(wxPropertyGridEvent& event);
	void updateN(SIDE side);
	void checkCP(wxUIntProperty& p, SIDE side);
	void checkActions(const wxArrayStringProperty& p);

	void OnCreate(wxCommandEvent& event);
	void GoTo(wxCommandEvent& event);

	void closeEvent(wxCloseEvent& evt);
};
