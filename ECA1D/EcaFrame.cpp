#include "EcaFrame.h"

EcaFrame::EcaFrame(EcaLogic* ecaLogic, int numIterations, int cellSize = 1,
				   wxColour deadCellColor = wxColour(220, 170, 15),
				   wxColour aliveCellColor = wxColour(115, 35, 15))
		: wxFrame(nullptr, wxID_ANY, wxT("ECA R" + to_string(ecaLogic->ruleNumber) + " - N: " + to_string(ecaLogic->N)),
				  wxDefaultPosition,
				  wxSize(ecaLogic->N * cellSize + 50, numIterations * cellSize + VerticalOffset + 50)) {
	initEcaFrame(ecaLogic, numIterations, cellSize, deadCellColor, aliveCellColor);
}

void EcaFrame::initEcaFrame(EcaLogic* ecaLogic, int numIterations, int cellSize,
							wxColour deadCellColor, wxColour aliveCellColor) {
	drawPanel = new DrawPanel(this, ecaLogic, numIterations, cellSize, VerticalOffset, deadCellColor, aliveCellColor);
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	//drawPanel->SetSize(wxSize(numCells * cellSize, numIterations * cellSize + textOffset));
	sizer->Add(drawPanel, 1, wxEXPAND);
	SetSizer(sizer);
	//SetAutoLayout(true);

	Connect(GetId(), wxEVT_CHAR_HOOK, wxKeyEventHandler(EcaFrame::OnKeyDown));
}

void EcaFrame::OnKeyDown(wxKeyEvent& event) {
	switch ((int)event.GetKeyCode()) {
	case 'n':
	case 'N':
		if (wxMessageBox("Create new random initial condition?", "Confirm", wxYES_NO | wxYES_DEFAULT, this) == wxYES) {
			drawPanel->eca->initialCondition = drawPanel->eca->createRandomInitialCondition(drawPanel->eca->N);
			drawPanel->eca->currentState = drawPanel->eca->initialCondition;
			drawPanel->currentShowingIteration = 1;
			drawPanel->shouldRedraw = true;
			drawPanel->Refresh();
		}
		break;
	case WXK_SPACE:
		drawPanel->currentShowingIteration++;
		drawPanel->shouldRedraw = true;
		drawPanel->Refresh();
		break;
	case 'r':
	case 'R':
		drawPanel->eca->currentState = drawPanel->eca->initialCondition;
		drawPanel->currentShowingIteration = 1;
		drawPanel->shouldRedraw = true;
		drawPanel->Refresh();
		break;
	case 's':
	case 'S':
		drawPanel->saveToImage();
		break;
	}
	event.Skip();
}
