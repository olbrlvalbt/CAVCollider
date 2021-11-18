#include "ColliderMenu.h"
#include <wx/propgrid/propgrid.h>

#include "ColliderActionList.h"
#include "ColliderFrame.h"
#include "FilteredCollisionSystem.h"

#include "SimulatorMenu.h"

ColliderMenu::ColliderMenu() : wxFrame(nullptr, wxID_ANY, wxT("Rule 110 Particle Collider"),
		wxDefaultPosition, wxSize(500, 500),
		wxDEFAULT_FRAME_STYLE^ wxRESIZE_BORDER),
		menuPanel(this, wxID_ANY) {

    pg = std::make_unique<wxPropertyGrid>(
        &menuPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize,
        wxPG_SPLITTER_AUTO_CENTER | wxPG_DEFAULT_STYLE);
    pg->SetExtraStyle(wxPG_EX_HELP_AS_TOOLTIPS);

    pg->Append(new wxPropertyCategory("Left Ring"));
    pg->Append(new wxLongStringProperty("Initial Condition", "leftIc", ""));
    pg->Append(new wxUIntProperty("Contact Point", "leftToCentral"));
	
    pg->Append(new wxPropertyCategory("Right Ring"));
    pg->Append(new wxLongStringProperty("Initial Condition", "rightIc", ""));
    pg->Append(new wxUIntProperty("Contact Point", "rightToCentral"));

    pg->Append(new wxPropertyCategory("Central Ring"));
    pg->Append(new wxLongStringProperty("Initial Condition", "centralIc", ""));
    pg->Append(new wxUIntProperty("Left Contact Point", "centralToLeft"));
    pg->Append(new wxUIntProperty("Right Contact Point", "centralToRight"));

    pg->Append(new wxPropertyCategory("Other"));
    pg->Append(new wxArrayStringProperty("Collider Actions", "actions"));
    pg->Append(new wxUIntProperty("Central Ring Radius", "centralRingRadius", 100));
    pg->Append(new wxUIntProperty("Refresh Rate", "refreshRate", 20));
	
    Connect(pg->GetId(), wxEVT_PG_CHANGED, wxPropertyGridEventHandler(ColliderMenu::OnChangedProperty));


    createButton = std::make_unique<wxButton>(&menuPanel, wxID_ANY, wxT("Create Collider"));
	Connect(createButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ColliderMenu::OnCreate));

    goToButton = std::make_unique<wxButton>(&menuPanel, wxID_ANY, wxT("Go To Simulator"));
    Connect(goToButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ColliderMenu::GoTo));

    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
    vbox->Add(&*pg, 1, wxALL | wxEXPAND, 15);
    vbox->Add(&*createButton, 0 , wxALIGN_RIGHT | wxRIGHT | wxBOTTOM, 30);
    vbox->Add(&*goToButton, 0, wxALIGN_LEFT | wxLEFT | wxBOTTOM, 30);

    menuPanel.SetSizer(vbox);
    Centre();
    Connect(GetId(), wxEVT_CLOSE_WINDOW, wxCloseEventHandler(ColliderMenu::closeEvent));

    leftIc = "";
    rightIc = "";
    centralIc = "";
}

void ColliderMenu::closeEvent(wxCloseEvent& evt) {
    Destroy();
}

void ColliderMenu::OnChangedProperty(wxPropertyGridEvent& event) {
    wxPGProperty* p = event.GetProperty();
    if (p) {
	    if (p->GetName() == "leftIc") {
            updateN(SIDE::LEFT);
	    }
        else if (p->GetName() == "rightIc") {
            updateN(SIDE::RIGHT);
        }
        else if (p->GetName() == "centralIc") {
            updateN(SIDE::CENTRAL);
        }
        else if (p->GetName() == "leftToCentral" && !((wxUIntProperty*)p)->GetValue().IsNull()) {
            checkCP(*((wxUIntProperty*)p), SIDE::LEFT);
        }
        else if (p->GetName() == "rightToCentral" && !((wxUIntProperty*)p)->GetValue().IsNull()) {
            checkCP(*((wxUIntProperty*)p), SIDE::RIGHT);
        }
        else if ((p->GetName() == "centralToLeft" || p->GetName() == "centralToRight")
            && !((wxUIntProperty*)p)->GetValue().IsNull()) {
            checkCP(*((wxUIntProperty*)p), SIDE::CENTRAL);
        }
        else if (p->GetName() == "actions") {
            checkActions(*((wxArrayStringProperty*)p));
        }
    }
}

void ColliderMenu::updateN(SIDE side) {
    switch (side) {
	    case SIDE::LEFT: {
	    	try {
                string s = pg->GetPropertyByName("leftIc")->GetValue().GetString().ToStdString();
                s = std::regex_replace(s, std::regex("\\\\n"), "");
                leftIc = rule110.Translate(s);
                pg->GetPropertyByName("leftToCentral")->SetLabel("Contact Point (0-" + std::to_string(leftIc.length()) + ")");
	    	}
	    	catch (exception& e) {
                wxMessageDialog* errorDial = new wxMessageDialog(this,
                    e.what(), wxT("Initial condition invalid"), wxOK | wxICON_ERROR);
                errorDial->ShowModal();
	    		
                pg->GetPropertyByName("leftIc")->SetValue("");
                pg->GetPropertyByName("leftToCentral")->SetLabel("Contact Point");
                leftIc = "";
	    	}

            checkCP(*(wxUIntProperty*)(pg->GetPropertyByName("leftToCentral")), SIDE::LEFT);
	        break;
	    }
	    case SIDE::RIGHT: {
            try {
                string s = pg->GetPropertyByName("rightIc")->GetValue().GetString().ToStdString();
                s = std::regex_replace(s, std::regex("\\\\n"), "");
                rightIc = rule110.Translate(s);
                pg->GetPropertyByName("rightToCentral")->SetLabel("Contact Point (0-" + std::to_string(rightIc.length()) + ")");
            }
            catch (exception& e) {
                wxMessageDialog* errorDial = new wxMessageDialog(this,
                    e.what(), wxT("Initial condition invalid"), wxOK | wxICON_ERROR);
                errorDial->ShowModal();
            	
                pg->GetPropertyByName("rightIc")->SetValue("");
                pg->GetPropertyByName("rightToCentral")->SetLabel("Contact Point");
                rightIc = "";
            }
	    	
	        checkCP(*(wxUIntProperty*)(pg->GetPropertyByName("rightToCentral")), SIDE::RIGHT);
	        break;
	    }
	    case SIDE::CENTRAL: {
            try {
                string s = pg->GetPropertyByName("centralIc")->GetValue().GetString().ToStdString();
                s = std::regex_replace(s, std::regex("\\\\n"), "");
                centralIc = rule110.Translate(s);
                pg->GetPropertyByName("centralToLeft")->SetLabel("Left Contact Point (0-" + std::to_string(centralIc.length()) + ")");
                pg->GetPropertyByName("centralToRight")->SetLabel("Right Contact Point (0-" + std::to_string(centralIc.length()) + ")");
            }
            catch (exception& e) {
                wxMessageDialog* errorDial = new wxMessageDialog(this,
                    e.what(), wxT("Initial condition invalid"), wxOK | wxICON_ERROR);
                errorDial->ShowModal();

                pg->GetPropertyByName("centralIc")->SetValue("");
                pg->GetPropertyByName("centralToLeft")->SetLabel("Left Contact Point");
                pg->GetPropertyByName("centralToRight")->SetLabel("Right Contact Point");
                centralIc = "";
            }
	    	
	        checkCP(*(wxUIntProperty*)(pg->GetPropertyByName("centralToLeft")), SIDE::CENTRAL);
	        checkCP(*(wxUIntProperty*)(pg->GetPropertyByName("centralToRight")), SIDE::CENTRAL);
	        break;
	    }
    }
}

void ColliderMenu::checkCP(wxUIntProperty& p, SIDE side) {
	switch (side) {
	    case SIDE::LEFT:
            if (((wxUIntProperty&)p).GetValue().GetLong() >= leftIc.length()) {
                int n = leftIc.length() > 0 ? leftIc.length() - 1 : 0;
                p.SetValue(n);
            }
            break;
	    case SIDE::RIGHT:
            if (((wxUIntProperty&)p).GetValue().GetLong() >= rightIc.length()) {
                int n = rightIc.length() > 0 ? rightIc.length() - 1 : 0;
                p.SetValue(n);
            }
            break;
	    case SIDE::CENTRAL:
            if (((wxUIntProperty&)p).GetValue().GetLong() >= centralIc.length()) {
                int n = centralIc.length() > 0 ? centralIc.length() - 1 : 0;
                p.SetValue(n);
            }
            break;
	}
}

void ColliderMenu::checkActions(const wxArrayStringProperty& p) {
    wxArrayString arr = pg->GetPropertyByName("actions")->GetValue();
    vector<string> s;
    for(wxString w : arr) {
        s.emplace_back(w.ToStdString());
    }

    int i = ColliderActionList::validate(s);
    if (i != -1) {
        wxMessageDialog* errorDial = new wxMessageDialog(this,
            "Invalid action: " + s[i], wxT("Action invalid"), wxOK | wxICON_ERROR);
        errorDial->ShowModal();
        pg->GetPropertyByName("actions")->SetValue(wxArrayString());
    }
}

void ColliderMenu::OnCreate(wxCommandEvent& event) {
    if (leftIc.length() == 0 || rightIc.length() == 0 || centralIc.length() == 0) {
        wxMessageDialog* errorDial = new wxMessageDialog(this,
            "Ring conditions cannot be empty", wxT("Invalid conditions"), wxOK | wxICON_ERROR);
        errorDial->ShowModal();

        return;
    }

    int leftToCentral = pg->GetPropertyByName("leftToCentral")->GetValue().GetLong();
    leftToCentral = (leftToCentral - 1 + leftIc.length()) % leftIc.length();

    int rightToCentral = pg->GetPropertyByName("rightToCentral")->GetValue().GetLong();
    rightToCentral = (rightToCentral - 1 + rightIc.length()) % rightIc.length();

    int centralToLeft = pg->GetPropertyByName("centralToLeft")->GetValue().GetLong();
    centralToLeft = (centralToLeft - 1 + centralIc.length()) % centralIc.length();

    int centralToRight = pg->GetPropertyByName("centralToRight")->GetValue().GetLong();
    centralToRight = (centralToRight - 1 + centralIc.length()) % centralIc.length();

	if (centralToLeft == centralToRight) {
        wxMessageDialog* errorDial = new wxMessageDialog(this,
            "Central ring contact points cannot overlap", wxT("Invalid contact points"), wxOK | wxICON_ERROR);
        errorDial->ShowModal();

        return;
    }


    wxArrayString arr = pg->GetPropertyByName("actions")->GetValue();
    vector<string> actions;
    for (wxString w : arr) {
        actions.emplace_back(w.ToStdString());
    }


    int centralRingRadius = pg->GetPropertyByName("centralRingRadius")->GetValue().GetLong();
    int refreshRate = pg->GetPropertyByName("refreshRate")->GetValue().GetLong();
	

    try {
        FilteredCollisionSystem* system = new FilteredCollisionSystem(leftIc, rightIc, centralIc,
            leftToCentral, centralToLeft,
            rightToCentral, centralToRight,
            actions);
        system->setAllContactsEnabled(true);
        ColliderConfiguration* config = new ColliderConfiguration(system, centralRingRadius,
            wxColour(245, 245, 245), wxColour(255, 255, 255));

        ColliderFrame* mainFrame = new ColliderFrame(config, refreshRate);
        mainFrame->Show();
    }
    catch (exception& e) {
        wxMessageDialog* errorDial = new wxMessageDialog(this,
            e.what(), wxT("Controller error"), wxOK | wxICON_ERROR);
        errorDial->ShowModal();

        return;
    }
}

void ColliderMenu::GoTo(wxCommandEvent& event) {
    SimulatorMenu* menu = new SimulatorMenu();
    menu->Show();
    Close(true);
}
