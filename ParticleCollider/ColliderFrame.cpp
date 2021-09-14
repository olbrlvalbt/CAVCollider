#include "ColliderFrame.h"

ColliderFrame::ColliderFrame(ColliderConfiguration* config, int refreshRate)
	: wxFrame(nullptr, wxID_ANY, "Collider",
		wxDefaultPosition, wxDefaultSize) {
	wxBoxSizer* frameSizer = new wxBoxSizer(wxHORIZONTAL);

	wxImage::AddHandler(new wxPNGHandler);

	wxToolBar* toolbar = CreateToolBar(wxTB_TEXT);
	wxToolBarToolBase* playPauseButton = toolbar->AddTool(wxID_ANY, wxT("Play/Pause (P)"), wxBitmap("..\\Icons\\playPauseIcon.png", wxBITMAP_TYPE_PNG));
	wxToolBarToolBase* toggle3dButton = toolbar->AddTool(wxID_ANY, wxT("Toggle 3D (Space)"), wxBitmap("..\\Icons\\toggle3dIcon.png", wxBITMAP_TYPE_PNG));
	wxToolBarToolBase* restartButton = toolbar->AddTool(wxID_ANY, wxT("Restart (R)"), wxBitmap("..\\Icons\\restartIcon.png", wxBITMAP_TYPE_PNG));
	wxToolBarToolBase* resetButton = toolbar->AddTool(wxID_ANY, wxT("Random reset (N)"), wxBitmap("..\\Icons\\resetIcon.png", wxBITMAP_TYPE_PNG));
	wxToolBarToolBase* saveButton = toolbar->AddTool(wxID_ANY, wxT("Save (S)"), wxBitmap("..\\Icons\\saveIcon.png", wxBITMAP_TYPE_PNG));
	toolbar->Realize();
	
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