#pragma once

#include <wx/wx.h>

#include "EcaRingConfiguration.h"
#include "RingPanel.h"

class RingFrame : public wxFrame {
public:
	const wxSize MaxFrameSize = wxSize(wxSystemSettings::GetMetric(wxSYS_SCREEN_X) - 100,
									   wxSystemSettings::GetMetric(wxSYS_SCREEN_Y) - 150);
	RingPanel* drawPanel = nullptr;

	RingFrame(EcaRingConfiguration* config, bool rule110T3filterEnabled);

	void closeEvent(wxCloseEvent & evt);
	
	void PlayPause(wxCommandEvent& event);
	void Toggle3D(wxCommandEvent& event);
	void ToggleFilter(wxCommandEvent& event);
	void Restart(wxCommandEvent& event);
	void Reset(wxCommandEvent& event);
	void Save(wxCommandEvent& event);
};