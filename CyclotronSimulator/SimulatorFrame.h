#pragma once

#include <wx/wx.h>

#include "EcaLogic.h"
#include "SimulatorPanel.h"

class SimulatorFrame : public wxFrame {
public:
	const wxSize MaxFrameSize = wxSize(wxSystemSettings::GetMetric(wxSYS_SCREEN_X) - 100,
									   wxSystemSettings::GetMetric(wxSYS_SCREEN_Y) - 100);
	SimulatorPanel* drawPanel = nullptr;

	SimulatorFrame(EcaLogic* ecaLogic, CyclotronConfiguration* config);

	void closeEvent(wxCloseEvent & evt);
};