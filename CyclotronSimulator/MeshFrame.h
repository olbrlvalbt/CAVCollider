#pragma once

#include <wx/wx.h>
#include <wx/sizer.h>

#include "EcaMeshConfiguration.h"
#include "MeshPanel.h"

class MeshFrame : public wxFrame {
public:
	const wxSize MaxFrameSize = wxSize(wxSystemSettings::GetMetric(wxSYS_SCREEN_X) - 100,
		wxSystemSettings::GetMetric(wxSYS_SCREEN_Y) - 150);
	MeshPanel* drawPanel = nullptr;

	MeshFrame(EcaMeshConfiguration* config, bool rule110T3filterEnabled);

	void NextSpace(wxCommandEvent& event);
	void RestartSpace(wxCommandEvent& event);
	void ResetSpace(wxCommandEvent& event);
	void SaveSpace(wxCommandEvent& event);
};


