#pragma once

#include <wx/wx.h>
#include "SimulatorMenu.h"

class SimulatorApp : public wxApp {
public:
	SimulatorMenu* mainFrame = nullptr;

	virtual bool OnInit();
};
