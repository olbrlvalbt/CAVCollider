#include "EcaGui.h"

wxIMPLEMENT_APP(EcaGui);

bool EcaGui::OnInit() {
	mainFrame = new MainFrame();
	mainFrame->SetAutoLayout(true);
	mainFrame->Show();


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

	return true;
}

MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, wxT("ECA1D"), wxDefaultPosition, wxSize(500, 700)) {
	mainPanel = new wxPanel(this, wxID_ANY);

	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
	wxFlexGridSizer* fgs = new wxFlexGridSizer(11, 2, 10, 20);


	ruleText = new wxStaticText(mainPanel, wxID_ANY, wxT("Rule:"));
	ruleCtrl = new wxTextCtrl(mainPanel, wxID_ANY, to_string(RULE));
	fgs->Add(ruleText);
	fgs->Add(ruleCtrl, 1, wxEXPAND);

	setRandomInitialConditionText = new wxStaticText(mainPanel, wxID_ANY, wxT("Set random initial condition:"));
	setRandomInitialConditionBox = new wxCheckBox(mainPanel, wxID_ANY, "");
	Connect(setRandomInitialConditionBox->GetId(), wxEVT_CHECKBOX, wxCommandEventHandler(MainFrame::SetRandomInitialConditionBoxEvent));
	fgs->Add(setRandomInitialConditionText);
	fgs->Add(setRandomInitialConditionBox);

	initialConditionText = new wxStaticText(mainPanel, wxID_ANY, wxT("Initial Condition:"));
	initialConditionCtrl = new wxTextCtrl(mainPanel, wxID_ANY, wxT("1"));
	Connect(initialConditionCtrl->GetId(), wxEVT_TEXT, wxCommandEventHandler(MainFrame::SetNewNumCellsAfterEtherEvent));
	fgs->Add(initialConditionText);
	fgs->Add(initialConditionCtrl, 1, wxEXPAND);

	adjustNumCellsToInitialConditionText = new wxStaticText(mainPanel, wxID_ANY, wxT("Adjust N to fit initial condition length:"));
	adjustNumCellsToInitialConditionBox = new wxCheckBox(mainPanel, wxID_ANY, "");
	Connect(adjustNumCellsToInitialConditionBox->GetId(), wxEVT_CHECKBOX, wxCommandEventHandler(MainFrame::AdjustNumCellsToInitialConditionBoxEvent));
	fgs->Add(adjustNumCellsToInitialConditionText);
	fgs->Add(adjustNumCellsToInitialConditionBox);

	numCellsText = new wxStaticText(mainPanel, wxID_ANY, wxT("N:"));
	numCellsCtrl = new wxSpinCtrl(mainPanel, wxID_ANY, wxT("100"));
	Connect(numCellsCtrl->GetId(), wxEVT_TEXT, wxCommandEventHandler(MainFrame::SetNewNumCellsAfterEtherEvent));
	fgs->Add(numCellsText);
	fgs->Add(numCellsCtrl);

	numIterationsText = new wxStaticText(mainPanel, wxID_ANY, wxT("Iterations:"));
	numIterationsCtrl = new wxSpinCtrl(mainPanel, wxID_ANY, wxT("300"));
	fgs->Add(numIterationsText);
	fgs->Add(numIterationsCtrl);

	setClosedBoundaryText = new wxStaticText(mainPanel, wxID_ANY, wxT("Set closed boundary condition:"));
	setClosedBoundaryBox = new wxCheckBox(mainPanel, wxID_ANY, "");
	fgs->Add(setClosedBoundaryText);
	fgs->Add(setClosedBoundaryBox);

	cellSizeText = new wxStaticText(mainPanel, wxID_ANY, wxT("Cell size (px):"));
	cellSizeCtrl = new wxSpinCtrl(mainPanel, wxID_ANY, wxT("3"));
	fgs->Add(cellSizeText);
	fgs->Add(cellSizeCtrl);

	fillEdgesWithRule110EtherText = new wxStaticText(mainPanel, wxID_ANY, wxT("Fill edges with rule 110 ether:"));
	fillEdgesWithRule110EtherBox = new wxCheckBox(mainPanel, wxID_ANY, "");
	Connect(fillEdgesWithRule110EtherBox->GetId(), wxEVT_CHECKBOX, wxCommandEventHandler(MainFrame::FillEdgesWithRule110EtherBoxEvent));
	fgs->Add(fillEdgesWithRule110EtherText);
	fgs->Add(fillEdgesWithRule110EtherBox);

	numEtherRule110ForEdgesText = new wxStaticText(mainPanel, wxID_ANY, wxT("Number of ether:"));
	numEtherRule110ForEdgesCtrl = new wxSpinCtrl(mainPanel, wxID_ANY, "1");
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

	createEcaButton = new wxButton(mainPanel, wxID_ANY, wxT("Create ECA"));
	Connect(createEcaButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::CreateEca));




	fgs->AddGrowableCol(1, 1);
	vbox->Add(fgs, 1, wxALL | wxEXPAND, 15);
	vbox->Add(createEcaButton, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM, 30);

	mainPanel->SetSizer(vbox);

	Centre();
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
			
		}
		else {
			int numEtherRule110ForEdges = numEtherRule110ForEdgesCtrl->GetValue();
			newNumCells = initialConditionLength + (numEtherRule110ForEdges * 14 * 2);
			newNumCellsAfterEtherResult->SetLabel(to_string(newNumCells));
		}


	}
}

void MainFrame::CreateEca(wxCommandEvent& event) {

}

EcaFrame::EcaFrame(int width, int height)
		: wxFrame(nullptr, -1, wxT("ECA1D"), wxPoint(0, 0), wxSize(width, height)) {

}

void EcaFrame::OnKeyDown(wxKeyEvent& event) {
	switch ((int)event.GetKeyCode()) {
		case 'n':
		case 'N':
			if (wxMessageBox("Create new random initial condition?", "Confirm", wxYES_NO | wxYES_DEFAULT, this) == wxYES) {
				((DrawPane*)drawPane)->eca->initialCondition = ((DrawPane*)drawPane)->eca->createRandomInitialCondition(((DrawPane*)drawPane)->eca->N);
				((DrawPane*)drawPane)->eca->currentState = ((DrawPane*)drawPane)->eca->initialCondition;
				((DrawPane*)drawPane)->currentShowingIteration = 1;
				((DrawPane*)drawPane)->shouldRedraw = true;
				drawPane->Refresh();
			}
			break;
		case WXK_SPACE:
			((DrawPane*)drawPane)->currentShowingIteration++;
			((DrawPane*)drawPane)->shouldRedraw = true;
			drawPane->Refresh();
			break;
		case 'r':
		case 'R':
			((DrawPane*)drawPane)->eca->currentState = ((DrawPane*)drawPane)->eca->initialCondition;
			((DrawPane*)drawPane)->currentShowingIteration = 1;
			((DrawPane*)drawPane)->shouldRedraw = true;
			drawPane->Refresh();
			break;
		case 's':
		case 'S':
			((DrawPane*)drawPane)->saveToImage();
			break;
	}
	event.Skip();
}

BEGIN_EVENT_TABLE(DrawPane, wxPanel)
	EVT_PAINT(DrawPane::paintEvent)
END_EVENT_TABLE()


DrawPane::DrawPane(EcaFrame* parent, EcaLogic* ecaLogic, int numIterationsI, int cellSizeI, int textOffsetI = 30)
		: wxPanel(parent) {
	parent->drawPane = this;
	eca = ecaLogic;
	numIterations = numIterationsI;
	cellSize = cellSizeI;
	textOffset = textOffsetI;
	wxInitAllImageHandlers();
}

void DrawPane::paintEvent(wxPaintEvent & evt) {
	if(shouldRedraw) {
		dc = new wxPaintDC(this);
		render();
	}
}

void DrawPane::render() {
	//wxBrush* whiteBrush = new wxBrush(wxColor(200, 200, 200), wxBRUSHSTYLE_TRANSPARENT);
	//wxBrush* blackBrush = new wxBrush(wxColor(0, 0, 0), wxBRUSHSTYLE_TRANSPARENT);
	wxBrush* whiteBrush = new wxBrush(wxColor(220, 170, 15));
	wxBrush* blackBrush = new wxBrush(wxColor(115, 35, 15));

	dc->DrawText(wxT("Rule " + to_string(eca->ruleNumber)), 10, 10);
	dc->DrawText(wxT("N = " + to_string(eca->N)), 100, 10);
	dc->DrawText(wxT("Iterations " + to_string((currentShowingIteration - 1) * numIterations)
					+ " through " + to_string((currentShowingIteration) * numIterations)), 200, 10);

	dc->DrawText(wxT("" + to_string(currentShowingIteration)), 500, 10);

	dc->SetPen(wxPen(wxColor(0, 0, 0), 1, wxPENSTYLE_TRANSPARENT));
	
	for (int j = 0; j < numIterations; j++) {

		for (int i = 0; i < eca->N; i++) {
			if(eca->currentState.at(i) == '1') {
				dc->SetBrush(*blackBrush);
			}
			else {
				dc->SetBrush(*whiteBrush);
			}
			dc->DrawRectangle(i * cellSize, j * cellSize + textOffset, cellSize, cellSize);
		}

		eca->applyRule();
		//wxMilliSleep(1);
	}
	shouldRedraw = false;

	saveToImage();
}

bool DrawPane::saveToImage() {
	wxBitmap *screenshot = new wxBitmap(eca->N * cellSize, numIterations * cellSize + textOffset);

	wxMemoryDC memDC;

	memDC.SelectObject(*screenshot);
	memDC.Blit(0, //Copy to this X coordinate
		0, //Copy to this Y coordinate
		eca->N * cellSize, //Copy this width
		numIterations * cellSize + textOffset, //Copy this height
		dc, //From where do we copy?
		0, //What's the X offset in the original DC?
		0  //What's the Y offset in the original DC?
	);
	memDC.SelectObject(wxNullBitmap);

	screenshot->SaveFile("screenshot.jpg", wxBITMAP_TYPE_JPEG);
	delete screenshot;
	return true;
}