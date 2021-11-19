#include "MeshFrame.h"

MeshFrame::MeshFrame(EcaMeshConfiguration* config, bool rule110T3filterEnabled)
	: wxFrame(nullptr, wxID_ANY, wxT("ECA R" + to_string(config->getEca().getRuleNumber()) + " - N: " + to_string(config->getEca().getN())),
		wxDefaultPosition, wxDefaultSize) {
	wxBoxSizer* frameSizer = new wxBoxSizer(wxHORIZONTAL);

	wxImage::AddHandler(new wxPNGHandler);

	wxToolBar* toolbar = CreateToolBar(wxTB_TEXT);
	wxToolBarToolBase* nextButton = toolbar->AddTool(wxID_ANY, wxT("Next (Space)"), wxBitmap("..\\Icons\\nextIcon.png", wxBITMAP_TYPE_PNG));
	wxToolBarToolBase* restartButton = toolbar->AddTool(wxID_ANY, wxT("Restart (R)"), wxBitmap("..\\Icons\\restartIcon.png", wxBITMAP_TYPE_PNG));
	wxToolBarToolBase* resetButton = toolbar->AddTool(wxID_ANY, wxT("Random reset (N)"), wxBitmap("..\\Icons\\resetIcon.png", wxBITMAP_TYPE_PNG));
	wxToolBarToolBase* saveButton = toolbar->AddTool(wxID_ANY, wxT("Save (S)"), wxBitmap("..\\Icons\\saveIcon.png", wxBITMAP_TYPE_PNG));
	toolbar->Realize();
	Connect(nextButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MeshFrame::NextSpace));
	Connect(restartButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MeshFrame::RestartSpace));
	Connect(resetButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MeshFrame::ResetSpace));
	Connect(saveButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MeshFrame::SaveSpace));

	drawPanel = new MeshPanel(this, config, rule110T3filterEnabled);
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

void MeshFrame::NextSpace(wxCommandEvent& event) {
	drawPanel->nextSpace();
}

void MeshFrame::RestartSpace(wxCommandEvent& event) {
	drawPanel->restartSpace();
}

void MeshFrame::ResetSpace(wxCommandEvent& event) {
	drawPanel->resetSpace();
}

void MeshFrame::SaveSpace(wxCommandEvent& event) {
	drawPanel->saveToImage();
}
