#include "SimulatorMenu.h"

SimulatorMenu::SimulatorMenu() : wxFrame(nullptr, wxID_ANY, wxT("Cyclotron"),
									 wxDefaultPosition, wxSize(600, 750),
									 wxDEFAULT_FRAME_STYLE ^ wxRESIZE_BORDER) {
	menuPanel = new wxPanel(this, wxID_ANY);
	
	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
	wxFlexGridSizer* fgs = new wxFlexGridSizer(20, 2, 10, 20);


	ruleText = new wxStaticText(menuPanel, wxID_ANY, wxT("Rule:"));
	ruleCtrl = new wxSpinCtrl(menuPanel, wxID_ANY, wxT("110"), wxDefaultPosition, wxSize(60, -1), wxSP_ARROW_KEYS, 0, 255);
	fgs->Add(ruleText);
	fgs->Add(ruleCtrl);

	setRandomInitialConditionText = new wxStaticText(menuPanel, wxID_ANY, wxT("Set random initial condition:"));
	setRandomInitialConditionBox = new wxCheckBox(menuPanel, wxID_ANY, "");
	Connect(setRandomInitialConditionBox->GetId(), wxEVT_CHECKBOX, wxCommandEventHandler(SimulatorMenu::SetRandomInitialConditionBoxEvent));
	fgs->Add(setRandomInitialConditionText);
	fgs->Add(setRandomInitialConditionBox);

	initialConditionText = new wxStaticText(menuPanel, wxID_ANY, wxT("Initial Condition:"));
	initialConditionCtrl = new wxTextCtrl(menuPanel, wxID_ANY, wxT("1"), wxDefaultPosition, wxSize(-1, 100), wxTE_MULTILINE | wxTE_CHARWRAP);
	//Connect(initialConditionCtrl->GetId(), wxEVT_TEXT, wxCommandEventHandler(SimulatorMenu::SetNewNumCellsAfterEtherEvent));
	fgs->Add(initialConditionText);
	fgs->Add(initialConditionCtrl, 1, wxEXPAND);
	fgs->AddGrowableRow(2, 1);

	adjustNumCellsToInitialConditionText = new wxStaticText(menuPanel, wxID_ANY, wxT("Adjust N to fit initial condition length:"));
	adjustNumCellsToInitialConditionBox = new wxCheckBox(menuPanel, wxID_ANY, "");
	Connect(adjustNumCellsToInitialConditionBox->GetId(), wxEVT_CHECKBOX, wxCommandEventHandler(SimulatorMenu::AdjustNumCellsToInitialConditionBoxEvent));
	fgs->Add(adjustNumCellsToInitialConditionText);
	fgs->Add(adjustNumCellsToInitialConditionBox);

	numCellsText = new wxStaticText(menuPanel, wxID_ANY, wxT("N:"));
	numCellsCtrl = new wxSpinCtrl(menuPanel, wxID_ANY, wxT("500"), wxDefaultPosition, wxSize(60, -1), wxSP_ARROW_KEYS, 3, 100000);
	//Connect(numCellsCtrl->GetId(), wxEVT_TEXT, wxCommandEventHandler(SimulatorMenu::SetNewNumCellsAfterEtherEvent));
	fgs->Add(numCellsText);
	fgs->Add(numCellsCtrl);

	fgs->AddSpacer(0);
	fgs->AddSpacer(0);

	ringWidthText = new wxStaticText(menuPanel, wxID_ANY, wxT("Ring width (px):"));
	ringWidthCtrl = new wxSpinCtrl(menuPanel, wxID_ANY, wxT("2"), wxDefaultPosition, wxSize(60, -1), wxSP_ARROW_KEYS, 1, 50);
	fgs->Add(ringWidthText);
	fgs->Add(ringWidthCtrl);

	ringRadiusText = new wxStaticText(menuPanel, wxID_ANY, wxT("Ring radius (px):"));
	ringRadiusCtrl = new wxSpinCtrl(menuPanel, wxID_ANY, wxT("500"), wxDefaultPosition, wxSize(60, -1), wxSP_ARROW_KEYS, 1, 1000);
	fgs->Add(ringRadiusText);
	fgs->Add(ringRadiusCtrl);

	refreshRateText = new wxStaticText(menuPanel, wxID_ANY, wxT("Refresh rate (ms):"));
	refreshRateCtrl = new wxSpinCtrl(menuPanel, wxID_ANY, wxT("50"), wxDefaultPosition, wxSize(60, -1), wxSP_ARROW_KEYS, 20, 10000);
	fgs->Add(refreshRateText);
	fgs->Add(refreshRateCtrl);

	ringOffsetText = new wxStaticText(menuPanel, wxID_ANY, wxT("Ring offset (px):"));
	ringOffsetCtrl = new wxSpinCtrl(menuPanel, wxID_ANY, wxT("1"), wxDefaultPosition, wxSize(60, -1), wxSP_ARROW_KEYS, 1, 100);
	fgs->Add(ringOffsetText);
	fgs->Add(ringOffsetCtrl);

	deadCellColorText = new wxStaticText(menuPanel, wxID_ANY, wxT("Dead cell (0) color:"));
	deadCellColorCtrl = new wxColourPickerCtrl(menuPanel, wxID_ANY, wxColour(220, 170, 15));
	fgs->Add(deadCellColorText);
	fgs->Add(deadCellColorCtrl);

	aliveCellColorText = new wxStaticText(menuPanel, wxID_ANY, wxT("Alive cell (1) color:"));
	aliveCellColorCtrl = new wxColourPickerCtrl(menuPanel, wxID_ANY, wxColour(115, 35, 15));
	fgs->Add(aliveCellColorText);
	fgs->Add(aliveCellColorCtrl);

	enableRule110T3FilterText = new wxStaticText(menuPanel, wxID_ANY, wxT("Filter rule 110 T3 tiles:"));
	enableRule110T3FilterBox = new wxCheckBox(menuPanel, wxID_ANY, "");
	enableRule110T3FilterBox->SetValue(true);
	Connect(enableRule110T3FilterBox->GetId(), wxEVT_CHECKBOX, wxCommandEventHandler(SimulatorMenu::ToggleFilterColorsEvent));
	fgs->Add(enableRule110T3FilterText);
	fgs->Add(enableRule110T3FilterBox);

	filterExteriorColorText = new wxStaticText(menuPanel, wxID_ANY, wxT("Filter exterior color:"));
	filterExteriorColorCtrl = new wxColourPickerCtrl(menuPanel, wxID_ANY, wxColour(15, 15, 95));
	fgs->Add(filterExteriorColorText);
	fgs->Add(filterExteriorColorCtrl);

	filterInteriorColorText = new wxStaticText(menuPanel, wxID_ANY, wxT("Filter interior color:"));
	filterInteriorColorCtrl = new wxColourPickerCtrl(menuPanel, wxID_ANY, wxColour(45, 45, 120));
	fgs->Add(filterInteriorColorText);
	fgs->Add(filterInteriorColorCtrl);

	createEcaButton = new wxButton(menuPanel, wxID_ANY, wxT("Create ECA"));
	Connect(createEcaButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(SimulatorMenu::CreateEcaEvent));


	fgs->AddGrowableCol(1, 1);
	vbox->Add(fgs, 1, wxALL | wxEXPAND, 15);
	vbox->Add(createEcaButton, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM, 30);

	menuPanel->SetSizer(vbox);
	Centre();
	initialConditionCtrl->SetFocus();
	initialConditionCtrl->SelectAll();

}

void SimulatorMenu::SetRandomInitialConditionBoxEvent(wxCommandEvent& event) {
	if (setRandomInitialConditionBox->GetValue()) {
		initialConditionText->Enable(false);
		initialConditionCtrl->Enable(false);

		adjustNumCellsToInitialConditionText->Enable(false);
		adjustNumCellsToInitialConditionBox->Enable(false);
		adjustNumCellsToInitialConditionBox->SetValue(false);

		numCellsText->Enable(true);
		numCellsCtrl->Enable(true);

	}
	else {
		initialConditionText->Enable(true);
		initialConditionCtrl->Enable(true);

		adjustNumCellsToInitialConditionText->Enable(true);
		adjustNumCellsToInitialConditionBox->Enable(true);

		//setNewNumCellsAfterEther();
	}
}

void SimulatorMenu::AdjustNumCellsToInitialConditionBoxEvent(wxCommandEvent& event) {
	if (adjustNumCellsToInitialConditionBox->GetValue()) {
		numCellsText->Enable(false);
		numCellsCtrl->Enable(false);
	}
	else {
		numCellsText->Enable(true);
		numCellsCtrl->Enable(true);
	}
	//setNewNumCellsAfterEther();
}

void SimulatorMenu::CreateEcaEvent(wxCommandEvent& event) {
	EcaLogic* eca;

	int rule = ruleCtrl->GetValue();

	wxColour deadCellColor = deadCellColorCtrl->GetColour();
	wxColour aliveCellColor = aliveCellColorCtrl->GetColour();
	wxColour filterExteriorColor = filterExteriorColorCtrl->GetColour();
	wxColour filterInteriorColor = filterInteriorColorCtrl->GetColour();

	int N;
	string initialCondition;

	if (setRandomInitialConditionBox->GetValue()) {
		N = numCellsCtrl->GetValue();

		eca = new EcaLogic(N, rule, ECABOUNDARY_PERIODIC);
	}
	else {
		try {
			initialCondition = Rule110::Translate(initialConditionCtrl->GetValue().ToStdString());
		}
		catch (TranslationException e) {
			wxMessageDialog *errorDial = new wxMessageDialog(this,
				e.what(), wxT("Initial condition invalid"), wxOK | wxICON_ERROR);
			errorDial->ShowModal();

			return;
		}

		if (adjustNumCellsToInitialConditionBox->GetValue()) {
			N = initialCondition.length();
		}
		else {
			N = numCellsCtrl->GetValue();
		}

		eca = new EcaLogic(N, rule, initialCondition, 0, ECABOUNDARY_PERIODIC);
	}

	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

	SimulatorFrame* simFrame = new SimulatorFrame(eca, 200,
												  deadCellColor, aliveCellColor,
												  filterExteriorColor, filterInteriorColor);

	simFrame->Show();
}

void SimulatorMenu::ToggleFilterColorsEvent(wxCommandEvent& event) {
	bool filterChecked = event.IsChecked();
	filterExteriorColorText->Enable(filterChecked);
	filterExteriorColorCtrl->Enable(filterChecked);
	filterInteriorColorText->Enable(filterChecked);
	filterInteriorColorCtrl->Enable(filterChecked);
}