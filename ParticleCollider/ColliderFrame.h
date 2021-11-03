#pragma once

#include <wx/wx.h>

#include "ColliderConfiguration.h"
#include "ColliderView.h"

class ColliderFrame : public wxFrame {
public:
	const wxSize MaxFrameSize = wxSize(wxSystemSettings::GetMetric(wxSYS_SCREEN_X) - 100,
		wxSystemSettings::GetMetric(wxSYS_SCREEN_Y) - 150);
	ColliderView* drawPanel;

	ColliderFrame(ColliderConfiguration* config, int refreshRate);

	void closeEvent(wxCloseEvent& evt);

	void PlayPause(wxCommandEvent& event);
	void Restart(wxCommandEvent& event);
	void Save(wxCommandEvent& event);
	void ShowLeft(wxCommandEvent& event);
	void ShowCentral(wxCommandEvent& event);
	void ShowRight(wxCommandEvent& event);
};

