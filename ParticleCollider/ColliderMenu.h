#pragma once

#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <wx/propgrid/propgrid.h>


#include "Rule110.h"

class ColliderMenu : public wxFrame {
public:
	enum class SIDE{LEFT, RIGHT, CENTRAL};
	
	Rule110 rule110;

	wxPanel* menuPanel;

	wxPropertyGrid* pg;

	wxButton* createButton;

	string leftIc;
	string rightIc;
	string centralIc;


	ColliderMenu();

	void OnChangedProperty(wxPropertyGridEvent& event);
	void updateN(SIDE side);
	void checkCP(wxUIntProperty& p, SIDE side);
	void checkActions(const wxArrayStringProperty& p);

	void OnCreate(wxCommandEvent& event);
};
