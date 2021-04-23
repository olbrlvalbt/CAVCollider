#include "SimulatorFrame.h"

SimulatorFrame::SimulatorFrame(EcaController* ecaController, CyclotronConfiguration* config)
	: wxFrame(nullptr, wxID_ANY, wxT("ECA R" + to_string(ecaController->getRuleNumber()) + " - N: " + to_string(ecaController->getN())),
			  wxDefaultPosition, wxDefaultSize) {
	wxBoxSizer* frameSizer = new wxBoxSizer(wxHORIZONTAL);

	drawPanel = new SimulatorPanel(this, ecaController, config);
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
	Connect(GetId(), wxEVT_CLOSE_WINDOW, wxCloseEventHandler(SimulatorFrame::closeEvent));
}

void SimulatorFrame::closeEvent(wxCloseEvent& evt) {
	drawPanel->Destroy();
	evt.Skip();
}