#include "SimulatorMenu.h"

#include "EcaMeshConfiguration.h"
#include "MeshFrame.h"

#include <wx/propgrid/advprops.h>

SimulatorMenu::SimulatorMenu() : wxFrame(nullptr, wxID_ANY, wxT("Eca Simulator"),
                                         wxDefaultPosition, wxSize(600, 500),
                                         wxDEFAULT_FRAME_STYLE ^ wxRESIZE_BORDER),
								 rule110() {
	menuPanel = new wxPanel(this, wxID_ANY);

	
	pg = new wxPropertyGrid(
		menuPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize,
		wxPG_SPLITTER_AUTO_CENTER | wxPG_DEFAULT_STYLE);
	pg->SetExtraStyle(wxPG_EX_HELP_AS_TOOLTIPS);

	pg->Append(new wxPropertyCategory("Base Settings"));
	
	pg->Append(new wxUIntProperty("Rule", "rule", 110));
	pg->Append(new wxBoolProperty("Set Random Initial Condition", "setRandomIc", false));
	pg->Append(new wxLongStringProperty("Initial Condition", "ic", ""));
	pg->Append(new wxBoolProperty("Adjust Number of Cells to Initial Condition", "adjustN", false));
	pg->Append(new wxUIntProperty("N", "n", 3));
	
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

	
	createEcaButton = new wxButton(menuPanel, wxID_ANY, wxT("Create Collider"));
	Connect(createEcaButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(SimulatorMenu::CreateEcaEvent));


	wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
	vbox->Add(pg, 1, wxALL | wxEXPAND, 15);
	vbox->Add(createEcaButton, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM, 30);

	menuPanel->SetSizer(vbox);
	Centre();

	
	
	/*wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
	fgs = new wxFlexGridSizer(22, 2, 10, 20);


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

	fgs->AddSpacer(0);
	fgs->AddSpacer(0);

	enableRingModeText = new wxStaticText(menuPanel, wxID_ANY, wxT("Enable ring mode:"));
	enableRingModeBox = new wxCheckBox(menuPanel, wxID_ANY, "");
	enableRingModeBox->SetValue(true);
	Connect(enableRingModeBox->GetId(), wxEVT_CHECKBOX, wxCommandEventHandler(SimulatorMenu::ToggleRingModeOptions));
	fgs->Add(enableRingModeText);
	fgs->Add(enableRingModeBox);

	/*filterExteriorColorText = new wxStaticText(menuPanel, wxID_ANY, wxT("Filter exterior color:"));
	filterExteriorColorCtrl = new wxColourPickerCtrl(menuPanel, wxID_ANY, wxColour(15, 15, 95));
	//fgs->Add(filterExteriorColorText);
	//fgs->Add(filterExteriorColorCtrl);
	filterExteriorColorText->Hide();
	filterExteriorColorCtrl->Hide();

	filterInteriorColorText = new wxStaticText(menuPanel, wxID_ANY, wxT("Filter interior color:"));
	filterInteriorColorCtrl = new wxColourPickerCtrl(menuPanel, wxID_ANY, wxColour(45, 45, 120));
	//fgs->Add(filterInteriorColorText);
	//fgs->Add(filterInteriorColorCtrl);
	filterInteriorColorText->Hide();
	filterInteriorColorCtrl->Hide();*/
	

	/*numIterationsText = new wxStaticText(menuPanel, wxID_ANY, wxT("Iterations:"));
	numIterationsCtrl = new wxSpinCtrl(menuPanel, wxID_ANY, wxT("200"), wxDefaultPosition, wxSize(60, -1), wxSP_ARROW_KEYS, 1, 100000);
	fgs->Add(numIterationsText);
	fgs->Add(numIterationsCtrl);
	fgs->Show(numIterationsText, false);
	fgs->Show(numIterationsCtrl, false);

	cellSizeText = new wxStaticText(menuPanel, wxID_ANY, wxT("Cell size (px):"));
	cellSizeCtrl = new wxSpinCtrl(menuPanel, wxID_ANY, wxT("3"), wxDefaultPosition, wxSize(60, -1), wxSP_ARROW_KEYS, 1, 500);
	fgs->Add(cellSizeText);
	fgs->Add(cellSizeCtrl);
	fgs->Show(cellSizeText, false);
	fgs->Show(cellSizeCtrl, false);
	

	ringWidthText = new wxStaticText(menuPanel, wxID_ANY, wxT("Ring width (px):"));
	ringWidthCtrl = new wxSpinCtrl(menuPanel, wxID_ANY, wxT("2"), wxDefaultPosition, wxSize(60, -1), wxSP_ARROW_KEYS, 1, 50);
	fgs->Add(ringWidthText);
	fgs->Add(ringWidthCtrl);

	ringRadiusText = new wxStaticText(menuPanel, wxID_ANY, wxT("Ring radius (px):"));
	ringRadiusCtrl = new wxSpinCtrl(menuPanel, wxID_ANY, wxT("200"), wxDefaultPosition, wxSize(60, -1), wxSP_ARROW_KEYS, 1, 10000);
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
	

	createEcaButton = new wxButton(menuPanel, wxID_ANY, wxT("Create ECA"));
	Connect(createEcaButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(SimulatorMenu::CreateEcaEvent));


	fgs->AddGrowableCol(1, 1);
	vbox->Add(fgs, 1, wxALL | wxEXPAND, 15);
	vbox->Add(createEcaButton, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM, 30);

	menuPanel->SetSizer(vbox);
	Centre();
	initialConditionCtrl->SetFocus();
	initialConditionCtrl->SelectAll();*/

	//ChunkTranslator::GetInstance();
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
	
	/*if (setRandomInitialConditionBox->GetValue()) {
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
	}*/
}

void SimulatorMenu::adjustNumCellsToInitialConditionEvent() {
	if (pg->GetPropertyByName("adjustN")->GetValue().GetBool()) {
		pg->GetPropertyByName("n")->Enable(false);
	}
	else {
		pg->GetPropertyByName("n")->Enable(true);
	}
	
	/*if (adjustNumCellsToInitialConditionBox->GetValue()) {
		numCellsText->Enable(false);
		numCellsCtrl->Enable(false);
	}
	else {
		numCellsText->Enable(true);
		numCellsCtrl->Enable(true);
	}
	//setNewNumCellsAfterEther();*/
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
		wxMessageDialog* errorDial = new wxMessageDialog(this,
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

		eca = new NaiveController(N, rule);
	}
	else {
		try {
			string s = pg->GetPropertyByName("ic")->GetValue().GetString().ToStdString();
			s = std::regex_replace(s, std::regex("\\\\n"), "");
			initialCondition = rule110.Translate(s);
		}
		catch (TranslationException e) {
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

		eca = new NaiveController(N, rule, initialCondition);
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
			deadColor, aliveColor);

		MeshFrame* simFrame = new MeshFrame(config, enableRule110T3Filter);

		simFrame->Show();
	}

	//wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
}
