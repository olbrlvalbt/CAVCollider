#include "SimulatorMenu.h"

#include "EcaMeshConfiguration.h"
#include "MeshFrame.h"

#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>

#include "ColliderMenu.h"

SimulatorMenu::SimulatorMenu() : wxFrame(nullptr, wxID_ANY, wxT("ECA Simulator"),
		wxDefaultPosition, wxSize(600, 600),
		wxDEFAULT_FRAME_STYLE ^ wxRESIZE_BORDER),
		menuPanel(this, wxID_ANY) {
	
	pg = std::make_unique<wxPropertyGrid>(
		&menuPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize,
		wxPG_SPLITTER_AUTO_CENTER | wxPG_DEFAULT_STYLE);
	pg->SetExtraStyle(wxPG_EX_HELP_AS_TOOLTIPS);

	pg->Append(new wxPropertyCategory("Base Settings"));
	
	pg->Append(new wxUIntProperty("Rule", "rule", 110));
	pg->Append(new wxBoolProperty("Set Random Initial Condition", "setRandomIc", false));
	pg->Append(new wxLongStringProperty("Initial Condition", "ic", ""));
	pg->Append(new wxBoolProperty("Adjust Number of Cells to Initial Condition", "adjustN", false));
	pg->Append(new wxUIntProperty("N", "n", 3));
	pg->Append(new wxUIntProperty("Iteration Offset", "iterationOffset", 0));
	
	pg->Append(new wxPropertyCategory("Mode Settings"));

	wxArrayString visualOpts;
	visualOpts.Add("Grid");
	visualOpts.Add("Ring");
	wxArrayInt visualOptsInt;
	visualOptsInt.Add(0);
	visualOptsInt.Add(1);
	pg->Append(new wxEnumProperty("Visual Mode", "mode", visualOpts, visualOptsInt, 0));

	pg->Append(new wxUIntProperty("Number of Iterations", "iterations", 100));
	pg->Append(new wxUIntProperty("Cell Size", "cellSize", 5));

	pg->Append(new wxUIntProperty("Ring Width", "ringWidth", 2));
	pg->Append(new wxUIntProperty("Ring Radius", "ringRadius", 200));
	pg->Append(new wxUIntProperty("Ring Offset", "ringOffset", 1));
	pg->Append(new wxUIntProperty("Refresh Rate", "refreshRate", 50));


	pg->Append(new wxPropertyCategory("Visual Settings"));

	pg->Append(new wxColourProperty("Dead Cell Color", "deadColor", wxColour(220, 170, 15)));
	pg->Append(new wxColourProperty("Alive Cell Color", "aliveColor", wxColour(115, 35, 15)));

	pg->Append(new wxBoolProperty("Enable Rule 110 T3 Filter", "filter", true));

	toggleModeOptions();
	Connect(pg->GetId(), wxEVT_PG_CHANGED, wxPropertyGridEventHandler(SimulatorMenu::OnChangedProperty));


	createEcaButton = std::make_unique<wxButton>(&menuPanel, wxID_ANY, wxT("Create ECA"));
	Connect(createEcaButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(SimulatorMenu::CreateEcaEvent));

	goToButton = std::make_unique<wxButton>(&menuPanel, wxID_ANY, wxT("Go To Collider"));
	Connect(goToButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(SimulatorMenu::GoTo));

	wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
	vbox->Add(&*pg, 1, wxALL | wxEXPAND, 15);
	vbox->Add(&*createEcaButton, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM, 30);
	vbox->Add(&*goToButton, 0, wxALIGN_LEFT | wxLEFT | wxBOTTOM, 30);

	menuPanel.SetSizer(vbox);
	Centre();
	Connect(GetId(), wxEVT_CLOSE_WINDOW, wxCloseEventHandler(SimulatorMenu::closeEvent));
}

void SimulatorMenu::closeEvent(wxCloseEvent& evt) {
	Destroy();
}

void SimulatorMenu::setRandomInitialConditionEvent() {
	if (pg->GetPropertyByName("setRandomIc")->GetValue().GetBool()) {
		pg->GetPropertyByName("ic")->Enable(false);
		
		pg->GetPropertyByName("adjustN")->Enable(false);
		pg->GetPropertyByName("adjustN")->SetValue(false);

		pg->GetPropertyByName("n")->Enable(true);

	}
	else {
		pg->GetPropertyByName("ic")->Enable(true);

		pg->GetPropertyByName("adjustN")->Enable(true);
	}
}

void SimulatorMenu::adjustNumCellsToInitialConditionEvent() {
	if (pg->GetPropertyByName("adjustN")->GetValue().GetBool()) {
		pg->GetPropertyByName("n")->Enable(false);
	}
	else {
		pg->GetPropertyByName("n")->Enable(true);
	}
}

void SimulatorMenu::toggleModeOptions() {
	int mode = pg->GetPropertyByName("mode")->GetChoiceSelection();
	bool ringModeEnabled = mode == 1;
	
	pg->GetPropertyByName("iterations")->Enable(!ringModeEnabled);
	pg->GetPropertyByName("cellSize")->Enable(!ringModeEnabled);
	
	pg->GetPropertyByName("ringRadius")->Enable(ringModeEnabled);
	pg->GetPropertyByName("ringWidth")->Enable(ringModeEnabled);
	pg->GetPropertyByName("refreshRate")->Enable(ringModeEnabled);
	pg->GetPropertyByName("ringOffset")->Enable(ringModeEnabled);
}

void SimulatorMenu::OnChangedProperty(wxPropertyGridEvent& event) {
	wxPGProperty* p = event.GetProperty();
	if (p) {
		if (p->GetName() == "setRandomIc") {
			setRandomInitialConditionEvent();
		}
		else if (p->GetName() == "adjustN") {
			adjustNumCellsToInitialConditionEvent();
		}
		else if (p->GetName() == "mode") {
			toggleModeOptions();
		}
	}
}

void SimulatorMenu::CreateEcaEvent(wxCommandEvent& event) {
	EcaController* eca;

	wxVariant ruleVariant = pg->GetPropertyByName("rule")->GetValue();
	if (ruleVariant.IsNull() || ruleVariant.GetLong() < 0 || ruleVariant.GetLong() > 255) {
		std::unique_ptr<wxMessageDialog> errorDial = std::make_unique<wxMessageDialog>(this,
			"Rule must be between 0-255", wxT("Invalid rule"), wxOK | wxICON_ERROR);
		errorDial->ShowModal();
	}
	int rule = ruleVariant.GetLong();

	wxVariant dc = pg->GetPropertyByName("deadColor")->GetValue();
	wxColour deadColor;
	deadColor << dc;
	wxVariant ac = ((wxColourProperty*)pg->GetPropertyByName("aliveColor"))->GetValue();
	wxColour aliveColor;
	aliveColor << ac;

	
	bool enableRule110T3Filter = pg->GetPropertyByName("filter")->GetValue().GetBool();

	int N;
	string initialCondition;

	if (pg->GetPropertyByName("setRandomIc")->GetValue().GetBool()) {
		N = pg->GetPropertyByName("n")->GetValue().GetLong();

		try {
			eca = new NaiveController(N, rule);
		}
		catch (exception& e) {
			wxMessageDialog* errorDial = new wxMessageDialog(this,
				e.what(), wxT("ECA Controller error"), wxOK | wxICON_ERROR);
			errorDial->ShowModal();

			return;
		}
	}
	else {
		try {
			string s = pg->GetPropertyByName("ic")->GetValue().GetString().ToStdString();
			s = std::regex_replace(s, std::regex("\\\\n"), "");
			initialCondition = rule110.Translate(s);
		}
		catch (exception& e) {
			wxMessageDialog* errorDial = new wxMessageDialog(this,
				e.what(), wxT("Initial condition invalid"), wxOK | wxICON_ERROR);
			errorDial->ShowModal();

			return;
		}

		if (pg->GetPropertyByName("adjustN")->GetValue().GetBool()) {
			N = initialCondition.length();
		}
		else {
			N = pg->GetPropertyByName("n")->GetValue().GetLong();
		}

		try {
			eca = new NaiveController(N, rule, initialCondition);
		}
		catch (exception& e) {
			wxMessageDialog* errorDial = new wxMessageDialog(this,
				e.what(), wxT("ECA Controller error"), wxOK | wxICON_ERROR);
			errorDial->ShowModal();

			return;
		}
	}


	int iterationOffset = pg->GetPropertyByName("iterationOffset")->GetValue().GetLong();

	if (iterationOffset > 0) {
		wxProgressDialog* progress = new wxProgressDialog("Setting ECA offset", "Processing, please wait", 100, nullptr, wxPD_AUTO_HIDE);

		int j = 0;
		for (int i = 0; i < iterationOffset; i++) {
			if ((i * 100) % iterationOffset == 0) {
				progress->Update(j++);
			}
			eca->applyRule();
		}
		progress->Update(100);

		string newIc = eca->getCurrentState()[0];
		eca->reset(newIc);
		((NaiveController*)eca)->setCurrentIteration(iterationOffset);
	}

	if (pg->GetPropertyByName("mode")->GetChoiceSelection() == 1) {
		int ringWidth = pg->GetPropertyByName("ringWidth")->GetValue().GetLong();
		int ringRadius = pg->GetPropertyByName("ringRadius")->GetValue().GetLong();
		int refreshRate = pg->GetPropertyByName("refreshRate")->GetValue().GetLong();
		int ringOffset = pg->GetPropertyByName("ringOffset")->GetValue().GetLong();

		EcaRingConfiguration* config = new EcaRingConfiguration(eca, deadColor, aliveColor,
			ringWidth, ringRadius, refreshRate, ringOffset);

		RingFrame* simFrame = new RingFrame(config, enableRule110T3Filter);

		simFrame->Show();
	}
	else {
		int numIterations = pg->GetPropertyByName("iterations")->GetValue().GetLong();
		int cellSize = pg->GetPropertyByName("cellSize")->GetValue().GetLong();

		EcaMeshConfiguration* config = new EcaMeshConfiguration(eca, numIterations, cellSize,
			deadColor, aliveColor, iterationOffset);

		MeshFrame* simFrame = new MeshFrame(config, enableRule110T3Filter);

		simFrame->Show();
	}
}

void SimulatorMenu::GoTo(wxCommandEvent& event) {
	ColliderMenu* menu = new ColliderMenu();
	menu->Show();
	Close(true);
}
