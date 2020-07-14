#include "EcaApp.h"

wxIMPLEMENT_APP(EcaApp);

bool EcaApp::OnInit() {
	mainFrame = new MainFrame();
	mainFrame->SetAutoLayout(true);
	mainFrame->Show();

	return true;
}

MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, wxT("ECA1D"), wxDefaultPosition, wxSize(600, 700),
								 wxDEFAULT_FRAME_STYLE ^ wxRESIZE_BORDER) {
	mainPanel = new wxPanel(this, wxID_ANY);

	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
	wxFlexGridSizer* fgs = new wxFlexGridSizer(14, 2, 10, 20);


	ruleText = new wxStaticText(mainPanel, wxID_ANY, wxT("Rule:"));
	ruleCtrl = new wxSpinCtrl(mainPanel, wxID_ANY, wxT("110"), wxDefaultPosition, wxSize(60, -1), wxSP_ARROW_KEYS, 0, 255);
	fgs->Add(ruleText);
	fgs->Add(ruleCtrl);

	setRandomInitialConditionText = new wxStaticText(mainPanel, wxID_ANY, wxT("Set random initial condition:"));
	setRandomInitialConditionBox = new wxCheckBox(mainPanel, wxID_ANY, "");
	Connect(setRandomInitialConditionBox->GetId(), wxEVT_CHECKBOX, wxCommandEventHandler(MainFrame::SetRandomInitialConditionBoxEvent));
	fgs->Add(setRandomInitialConditionText);
	fgs->Add(setRandomInitialConditionBox);

	initialConditionText = new wxStaticText(mainPanel, wxID_ANY, wxT("Initial Condition:"));
	initialConditionCtrl = new wxTextCtrl(mainPanel, wxID_ANY, wxT("1"), wxDefaultPosition, wxSize(-1, 100), wxTE_MULTILINE | wxTE_CHARWRAP);
	Connect(initialConditionCtrl->GetId(), wxEVT_TEXT, wxCommandEventHandler(MainFrame::SetNewNumCellsAfterEtherEvent));
	fgs->Add(initialConditionText);
	fgs->Add(initialConditionCtrl, 1, wxEXPAND);
	fgs->AddGrowableRow(2, 1);

	adjustNumCellsToInitialConditionText = new wxStaticText(mainPanel, wxID_ANY, wxT("Adjust N to fit initial condition length:"));
	adjustNumCellsToInitialConditionBox = new wxCheckBox(mainPanel, wxID_ANY, "");
	Connect(adjustNumCellsToInitialConditionBox->GetId(), wxEVT_CHECKBOX, wxCommandEventHandler(MainFrame::AdjustNumCellsToInitialConditionBoxEvent));
	fgs->Add(adjustNumCellsToInitialConditionText);
	fgs->Add(adjustNumCellsToInitialConditionBox);

	numCellsText = new wxStaticText(mainPanel, wxID_ANY, wxT("N:"));
	numCellsCtrl = new wxSpinCtrl(mainPanel, wxID_ANY, wxT("500"), wxDefaultPosition, wxSize(60, -1), wxSP_ARROW_KEYS, 3, 100000);
	Connect(numCellsCtrl->GetId(), wxEVT_TEXT, wxCommandEventHandler(MainFrame::SetNewNumCellsAfterEtherEvent));
	fgs->Add(numCellsText);
	fgs->Add(numCellsCtrl);

	numIterationsText = new wxStaticText(mainPanel, wxID_ANY, wxT("Iterations:"));
	numIterationsCtrl = new wxSpinCtrl(mainPanel, wxID_ANY, wxT("200"), wxDefaultPosition, wxSize(60, -1), wxSP_ARROW_KEYS, 1, 100000);
	fgs->Add(numIterationsText);
	fgs->Add(numIterationsCtrl);

	setClosedBoundaryText = new wxStaticText(mainPanel, wxID_ANY, wxT("Set closed boundary condition:"));
	setClosedBoundaryBox = new wxCheckBox(mainPanel, wxID_ANY, "");
	fgs->Add(setClosedBoundaryText);
	fgs->Add(setClosedBoundaryBox);

	fillEdgesWithRule110EtherText = new wxStaticText(mainPanel, wxID_ANY, wxT("Fill edges with rule 110 ether:"));
	fillEdgesWithRule110EtherBox = new wxCheckBox(mainPanel, wxID_ANY, "");
	Connect(fillEdgesWithRule110EtherBox->GetId(), wxEVT_CHECKBOX, wxCommandEventHandler(MainFrame::FillEdgesWithRule110EtherBoxEvent));
	fgs->Add(fillEdgesWithRule110EtherText);
	fgs->Add(fillEdgesWithRule110EtherBox);

	numEtherRule110ForEdgesText = new wxStaticText(mainPanel, wxID_ANY, wxT("Number of ether:"));
	numEtherRule110ForEdgesCtrl = new wxSpinCtrl(mainPanel, wxID_ANY, wxT("2"), wxDefaultPosition, wxSize(60, -1), wxSP_ARROW_KEYS, 0, 10000);
	numEtherRule110ForEdgesText->Enable(false);
	numEtherRule110ForEdgesCtrl->Enable(false);
	Connect(numEtherRule110ForEdgesCtrl->GetId(), wxEVT_TEXT, wxCommandEventHandler(MainFrame::SetNewNumCellsAfterEtherEvent));
	fgs->Add(numEtherRule110ForEdgesText);
	fgs->Add(numEtherRule110ForEdgesCtrl);

	newNumCellsAfterEtherText = new wxStaticText(mainPanel, wxID_ANY, wxT("New N after ether:"));
	newNumCellsAfterEtherResult = new wxStaticText(mainPanel, wxID_ANY, wxT(""));
	newNumCellsAfterEtherText->Enable(false);
	newNumCellsAfterEtherResult->Enable(false);
	fgs->Add(newNumCellsAfterEtherText);
	fgs->Add(newNumCellsAfterEtherResult);

	dummyText = new wxStaticText(mainPanel, wxID_ANY, wxT(" "));
	dummyText->Enable(false);
	fgs->Add(dummyText);
	fgs->AddSpacer(0);

	cellSizeText = new wxStaticText(mainPanel, wxID_ANY, wxT("Cell size (px):"));
	cellSizeCtrl = new wxSpinCtrl(mainPanel, wxID_ANY, wxT("3"), wxDefaultPosition, wxSize(60, -1), wxSP_ARROW_KEYS, 1, 100);
	fgs->Add(cellSizeText);
	fgs->Add(cellSizeCtrl);

	deadCellColorText = new wxStaticText(mainPanel, wxID_ANY, wxT("Dead cell (0) color:"));
	deadCellColorCtrl = new wxColourPickerCtrl(mainPanel, wxID_ANY, wxColour(220, 170, 15));
	fgs->Add(deadCellColorText);
	fgs->Add(deadCellColorCtrl);

	aliveCellColorText = new wxStaticText(mainPanel, wxID_ANY, wxT("Alive cell (1) color:"));
	aliveCellColorCtrl = new wxColourPickerCtrl(mainPanel, wxID_ANY, wxColour(115, 35, 15));
	fgs->Add(aliveCellColorText);
	fgs->Add(aliveCellColorCtrl);

	createEcaButton = new wxButton(mainPanel, wxID_ANY, wxT("Create ECA"));
	Connect(createEcaButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::CreateEcaEvent));


	fgs->AddGrowableCol(1, 1);
	vbox->Add(fgs, 1, wxALL | wxEXPAND, 15);
	vbox->Add(createEcaButton, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM, 30);

	mainPanel->SetSizer(vbox);
	Centre();
	initialConditionCtrl->SetFocus();
	initialConditionCtrl->SelectAll();
}

void MainFrame::SetRandomInitialConditionBoxEvent(wxCommandEvent& event) {
	if (setRandomInitialConditionBox->GetValue()) {
		initialConditionText->Enable(false);
		initialConditionCtrl->Enable(false);

		adjustNumCellsToInitialConditionText->Enable(false);
		adjustNumCellsToInitialConditionBox->Enable(false);
		adjustNumCellsToInitialConditionBox->SetValue(false);

		numCellsText->Enable(true);
		numCellsCtrl->Enable(true);

		fillEdgesWithRule110EtherText->Enable(false);
		fillEdgesWithRule110EtherBox->Enable(false);

		numEtherRule110ForEdgesText->Enable(false);
		numEtherRule110ForEdgesCtrl->Enable(false);

		newNumCellsAfterEtherText->Enable(false);
		newNumCellsAfterEtherResult->Enable(false);
		newNumCellsAfterEtherResult->SetLabel("");
	}
	else {
		initialConditionText->Enable(true);
		initialConditionCtrl->Enable(true);

		adjustNumCellsToInitialConditionText->Enable(true);
		adjustNumCellsToInitialConditionBox->Enable(true);

		fillEdgesWithRule110EtherText->Enable(true);
		fillEdgesWithRule110EtherBox->Enable(true);

		numEtherRule110ForEdgesText->Enable(fillEdgesWithRule110EtherBox->GetValue());
		numEtherRule110ForEdgesCtrl->Enable(fillEdgesWithRule110EtherBox->GetValue());

		newNumCellsAfterEtherText->Enable(fillEdgesWithRule110EtherBox->GetValue());
		newNumCellsAfterEtherResult->Enable(fillEdgesWithRule110EtherBox->GetValue());
		if (fillEdgesWithRule110EtherBox->GetValue()) {
			setNewNumCellsAfterEther();
		}
	}
}

void MainFrame::AdjustNumCellsToInitialConditionBoxEvent(wxCommandEvent& event) {
	if (adjustNumCellsToInitialConditionBox->GetValue()) {
		numCellsText->Enable(false);
		numCellsCtrl->Enable(false);
	}
	else {
		numCellsText->Enable(true);
		numCellsCtrl->Enable(true);
	}
	setNewNumCellsAfterEther();
}

void MainFrame::FillEdgesWithRule110EtherBoxEvent(wxCommandEvent& event) {
	if (fillEdgesWithRule110EtherBox->GetValue()) {
		numEtherRule110ForEdgesText->Enable(true);
		numEtherRule110ForEdgesCtrl->Enable(true);

		newNumCellsAfterEtherText->Enable(true);
		newNumCellsAfterEtherResult->Enable(true);
		setNewNumCellsAfterEther();
	}
	else {
		numEtherRule110ForEdgesText->Enable(false);
		numEtherRule110ForEdgesCtrl->Enable(false);

		newNumCellsAfterEtherText->Enable(false);
		newNumCellsAfterEtherResult->Enable(false);
		newNumCellsAfterEtherResult->SetLabel("");
	}
}

void MainFrame::SetNewNumCellsAfterEtherEvent(wxCommandEvent& event) {
	setNewNumCellsAfterEther();
}

void MainFrame::setNewNumCellsAfterEther() {
	if (fillEdgesWithRule110EtherBox->GetValue()) {
		int initialConditionLength = initialConditionCtrl->GetLineLength(0);
		int numCells = initialConditionLength;
		if (!adjustNumCellsToInitialConditionBox->GetValue()) {
			numCells = numCellsCtrl->GetValue();
		}
		int newNumCells;

		if (initialConditionLength < numCells) {
			int requiredEther = ((numCells - initialConditionLength) / 2) / 14;
			requiredEther++;

			newNumCells = initialConditionLength + (requiredEther * 14 * 2);
			newNumCellsAfterEtherResult->SetLabel(to_string(newNumCells) + " (" + to_string(requiredEther) + "e added to fit N)");

			numEtherRule110ForEdgesText->Enable(false);
			numEtherRule110ForEdgesCtrl->Enable(false);
		}
		else {
			numEtherRule110ForEdgesText->Enable(true);
			numEtherRule110ForEdgesCtrl->Enable(true);

			int numEtherRule110ForEdges = numEtherRule110ForEdgesCtrl->GetValue();
			newNumCells = initialConditionLength + (numEtherRule110ForEdges * 14 * 2);
			newNumCellsAfterEtherResult->SetLabel(to_string(newNumCells));

		}
	}
}

void MainFrame::CreateEcaEvent(wxCommandEvent& event) {
	EcaLogic* eca;

	int rule = ruleCtrl->GetValue();
	int numIterations = numIterationsCtrl->GetValue();
	bool setClosedBoundary = setClosedBoundaryBox->GetValue();

	int cellSize = cellSizeCtrl->GetValue();
	wxColour deadCellColor = deadCellColorCtrl->GetColour();
	wxColour aliveCellColor = aliveCellColorCtrl->GetColour();

	int N;
	string initialCondition;
	int numEtherRule110ForEdges = 0;

	if (setRandomInitialConditionBox->GetValue()) {
		N = numCellsCtrl->GetValue();

		eca = new EcaLogic(N, rule, setClosedBoundary ? ECABOUNDARY_CLOSED : ECABOUNDARY_PERIODIC);
	}
	else {
		initialCondition =  initialConditionCtrl->GetValue().ToStdString();

		//Validar

		if (adjustNumCellsToInitialConditionBox->GetValue()) {
			N = initialCondition.length();
			if (fillEdgesWithRule110EtherBox->GetValue()) {
				numEtherRule110ForEdges = numEtherRule110ForEdgesCtrl->GetValue();
			}
		}
		else {
			N = numCellsCtrl->GetValue();
			if (fillEdgesWithRule110EtherBox->GetValue()) {
				if (initialCondition.length() < N) {
					numEtherRule110ForEdges = 1;
				}
				else {
					numEtherRule110ForEdges = numEtherRule110ForEdgesCtrl->GetValue();

				}
			}
		}

		eca = new EcaLogic(N, rule, initialCondition, numEtherRule110ForEdges, setClosedBoundary ? ECABOUNDARY_CLOSED : ECABOUNDARY_PERIODIC);
	}
	 
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	EcaFrame* ecaFrame = new EcaFrame(eca, numIterations, cellSize, deadCellColor, aliveCellColor);

	ecaFrame->Show();

	/*EcaLogic* ecaLogic = new EcaLogic(NUMCELLS, RULE, INITIALCONDITION, ECABOUNDARY_PERIODIC);

	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	int numCells = NUMCELLS;
	int cellSize = CELLSIZE;
	int numIterations = NUMITERATIONS;
	int textOffset = TEXTOFFSET;
	frame = new EcaFrame(numCells * cellSize, numIterations * cellSize + textOffset);

	drawPane = new DrawPane(frame, ecaLogic, numIterations, cellSize, textOffset);

	drawPane->Bind(wxEVT_CHAR_HOOK, &EcaFrame::OnKeyDown, frame);
	drawPane->SetSize(wxSize(numCells * cellSize, numIterations * cellSize + textOffset));
	sizer->Add(drawPane, 1, wxEXPAND);

	frame->SetSizer(sizer);
	frame->SetAutoLayout(true);
	frame->Show();*/

}
