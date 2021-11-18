#pragma once

#include <wx/wx.h>

#include "SimulatorMenu.h"

class MainApp : public wxApp {
public:
	SimulatorMenu* m;
	
	virtual bool OnInit();
	MainApp();
};
