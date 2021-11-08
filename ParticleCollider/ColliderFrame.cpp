#include "ColliderFrame.h"

ColliderFrame::ColliderFrame(ColliderConfiguration* config, int refreshRate)
	: wxFrame(nullptr, wxID_ANY, "Collider",
		wxDefaultPosition, wxDefaultSize) {
	wxBoxSizer* frameSizer = new wxBoxSizer(wxHORIZONTAL);

	wxImage::AddHandler(new wxPNGHandler);

	wxToolBar* toolbar = CreateToolBar(wxTB_TEXT);
	wxToolBarToolBase* playPauseButton = toolbar->AddTool(wxID_ANY, wxT("Play/Pause (P)"), wxBitmap("..\\Icons\\playPauseIcon.png", wxBITMAP_TYPE_PNG));
	wxToolBarToolBase* jumpToButton = toolbar->AddTool(wxID_ANY, wxT("Jump To (J)"), wxBitmap("..\\Icons\\nextIcon.png", wxBITMAP_TYPE_PNG));
	wxToolBarToolBase* showLeftIcon = toolbar->AddTool(wxID_ANY, wxT("Show Left (1)"), wxBitmap("..\\Icons\\showLeftIcon.png", wxBITMAP_TYPE_PNG));
	wxToolBarToolBase* showCentralIcon = toolbar->AddTool(wxID_ANY, wxT("Show Central (2)"), wxBitmap("..\\Icons\\showCentralIcon.png", wxBITMAP_TYPE_PNG));
	wxToolBarToolBase* showRightIcon = toolbar->AddTool(wxID_ANY, wxT("Show Right (3)"), wxBitmap("..\\Icons\\showRightIcon.png", wxBITMAP_TYPE_PNG));
	wxToolBarToolBase* saveButton = toolbar->AddTool(wxID_ANY, wxT("Save (S)"), wxBitmap("..\\Icons\\saveIcon.png", wxBITMAP_TYPE_PNG));
	wxToolBarToolBase* restartButton = toolbar->AddTool(wxID_ANY, wxT("Restart (R)"), wxBitmap("..\\Icons\\restartIcon.png", wxBITMAP_TYPE_PNG));
	toolbar->Realize();
	Connect(playPauseButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(ColliderFrame::PlayPause));
	Connect(jumpToButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(ColliderFrame::JumpTo));
	Connect(restartButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(ColliderFrame::Restart));
	Connect(showLeftIcon->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(ColliderFrame::ShowLeft));
	Connect(showCentralIcon->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(ColliderFrame::ShowCentral));
	Connect(showRightIcon->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(ColliderFrame::ShowRight));
	Connect(saveButton->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(ColliderFrame::Save));
	
	drawPanel = new ColliderView(this, config, refreshRate);
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

void ColliderFrame::closeEvent(wxCloseEvent& evt) {
	drawPanel->Destroy();
	evt.Skip();
}

void ColliderFrame::PlayPause(wxCommandEvent& event) {
	drawPanel->playPause();
}

void ColliderFrame::JumpTo(wxCommandEvent& event) {
	drawPanel->jumpTo();
}

void ColliderFrame::Restart(wxCommandEvent& event) {
	drawPanel->restart();
}

void ColliderFrame::Save(wxCommandEvent& event) {
	drawPanel->saveToImage();
}

void ColliderFrame::ShowLeft(wxCommandEvent& event) {
	drawPanel->showLeft();
}

void ColliderFrame::ShowCentral(wxCommandEvent& event) {
	drawPanel->showCentral();
}

void ColliderFrame::ShowRight(wxCommandEvent& event) {
	drawPanel->showRight();
}
