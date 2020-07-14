#include "EcaFrame.h"

EcaFrame::EcaFrame(EcaLogic* ecaLogic, int numIterations, int cellSize = 1,
				   wxColour deadCellColor = wxColour(220, 170, 15),
				   wxColour aliveCellColor = wxColour(115, 35, 15))
		: wxFrame(nullptr, wxID_ANY, wxT("ECA R" + to_string(ecaLogic->ruleNumber) + " - N: " + to_string(ecaLogic->N)),
				  wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE ^ wxRESIZE_BORDER) {
	initEcaFrame(ecaLogic, numIterations, cellSize, deadCellColor, aliveCellColor);
}

void EcaFrame::initEcaFrame(EcaLogic* ecaLogic, int numIterations, int cellSize,
							wxColour deadCellColor, wxColour aliveCellColor) {
	drawPanel = new DrawPanel(this, ecaLogic, numIterations, cellSize, deadCellColor, aliveCellColor);
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	sizer->Add(drawPanel, 1, wxEXPAND);
	SetSizer(sizer);
	SetClientSize(drawPanel->GetSize());
	Center();

	/*SetSize(700, 500);
	wxBoxSizer* frameSizer = new wxBoxSizer(wxHORIZONTAL);

	drawPanel = new DrawPanel(this, ecaLogic, numIterations, cellSize, deadCellColor, aliveCellColor);
	frameSizer->Add(drawPanel, 1, wxALL | wxEXPAND);
	SetSizer(frameSizer);
	Center();*/
}
