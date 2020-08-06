#include "SimulatorFrame.h"

SimulatorFrame::SimulatorFrame(EcaLogic* ecaLogic, int _ringRadius = 500, int _panelSize = 1500,
							   wxColour _deadCellColor = wxColour(220, 170, 15),
							   wxColour _aliveCellColor = wxColour(115, 35, 15),
							   wxColour _filterExteriorColor = wxColour(15, 15, 95),
							   wxColour _filterInteriorColor = wxColour(45, 45, 120))
	: wxFrame(nullptr, wxID_ANY, wxT("ECA R" + to_string(ecaLogic->ruleNumber) + " - N: " + to_string(ecaLogic->N)),
			  wxDefaultPosition, wxDefaultSize) {
	wxBoxSizer* frameSizer = new wxBoxSizer(wxHORIZONTAL);

	drawPanel = new SimulatorPanel(this, ecaLogic, _ringRadius, _panelSize,
								   _deadCellColor, _aliveCellColor,
								   _filterExteriorColor, _filterInteriorColor);
	frameSizer->Add(drawPanel, 1, wxALL | wxEXPAND);
	SetSizer(frameSizer);
	wxSize panelSize = drawPanel->GetClientSize();
	wxSize frameSize = panelSize;
	if (panelSize.x > MaxFrameSize.x) {
		frameSize.x = MaxFrameSize.x;
	}
	if (panelSize.y > MaxFrameSize.y) {
		frameSize.y = MaxFrameSize.y;
	}
	SetClientSize(frameSize);
	SetMaxClientSize(panelSize);
	Center();
}