#include "RingFrame.h"

RingFrame::RingFrame(EcaRingConfiguration* config, bool rule110T3filterEnabled)
	: wxFrame(nullptr, wxID_ANY, wxT("ECA R" + to_string(config->getEca().getRuleNumber()) + " - N: " + to_string(config->getEca().getN())),
			  wxDefaultPosition, wxDefaultSize) {
	wxBoxSizer* frameSizer = new wxBoxSizer(wxHORIZONTAL);

	wxImage::AddHandler(new wxPNGHandler);

	wxToolBar* toolbar = CreateToolBar(wxTB_TEXT);
	wxToolBarToolBase* playPauseButton = toolbar->AddTool(wxID_ANY, wxT("Play/Pause (P)"), wxBitmap("..\\Icons\\playPauseIcon.png", wxBITMAP_TYPE_PNG));
	wxToolBarToolBase* toggle3dButton = toolbar->AddTool(wxID_ANY, wxT("Toggle 3D (Space)"), wxBitmap("..\\Icons\\toggle3dIcon.png", wxBITMAP_TYPE_PNG));
	//wxToolBarToolBase* filterButton = toolbar->AddTool(wxID_ANY, wxT("Toggle filter (F)"), wxBitmap("..\\Icons\\filterIcon.png", wxBITMAP_TYPE_PNG));
	wxToolBarToolBase* restartButton = toolbar->AddTool(wxID_ANY, wxT("Restart (R)"), wxBitmap("..\\Icons\\restartIcon.png", wxBITMAP_TYPE_PNG));
	wxToolBarToolBase* resetButton = toolbar->AddTool(wxID_ANY, wxT("Random reset (N)"), wxBitmap("..\\Icons\\resetIcon.png", wxBITMAP_TYPE_PNG));
	wxToolBarToolBase* saveButton = toolbar->AddTool(wxID_ANY, wxT("Save (S)"), wxBitmap("..\\Icons\\saveIcon.png", wxBITMAP_TYPE_PNG));
	toolbar->Realize();
	Connect(playPauseButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(RingFrame::PlayPause));
	Connect(toggle3dButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(RingFrame::Toggle3D));
	//Connect(filterButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(RingFrame::ToggleFilter));
	Connect(restartButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(RingFrame::Restart));
	Connect(resetButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(RingFrame::Reset));
	Connect(saveButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(RingFrame::Save));

	drawPanel = new RingPanel(this, config, rule110T3filterEnabled);
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
	Connect(GetId(), wxEVT_CLOSE_WINDOW, wxCloseEventHandler(RingFrame::closeEvent));
}

RingFrame::~RingFrame() {
	//delete drawPanel;
}

void RingFrame::closeEvent(wxCloseEvent& evt) {
	drawPanel->Destroy();
	evt.Skip();
}

void RingFrame::PlayPause(wxCommandEvent& event) {
	drawPanel->playPause();
}

void RingFrame::Toggle3D(wxCommandEvent& event) {
	drawPanel->toggle3D();
}

void RingFrame::ToggleFilter(wxCommandEvent& event) {
	drawPanel->toggleFilter();
}

void RingFrame::Restart(wxCommandEvent& event) {
	drawPanel->restart();
}

void RingFrame::Reset(wxCommandEvent& event) {
	drawPanel->reset();
}

void RingFrame::Save(wxCommandEvent& event) {
	drawPanel->saveToImage();
}
