#pragma once

#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <wx/clrpicker.h>
#include <wx/propgrid/propgrid.h>


#include "Rule110.h"
#include "NaiveController.h"
#include "CompressedController.h"
#include "ChunkTranslator.h"
#include "RingFrame.h"
#include "EcaRingConfiguration.h"

class SimulatorMenu : public wxFrame {
public:
	Rule110 rule110;
	
	wxPanel menuPanel;

	std::unique_ptr<wxPropertyGrid> pg;
	std::unique_ptr<wxButton> createEcaButton;
	std::unique_ptr<wxButton> goToButton;
	

	SimulatorMenu();

	void setRandomInitialConditionEvent();
	void adjustNumCellsToInitialConditionEvent();

	void CreateEcaEvent(wxCommandEvent& event);
	void GoTo(wxCommandEvent& event);
	void toggleModeOptions();

	void OnChangedProperty(wxPropertyGridEvent& event);

	void closeEvent(wxCloseEvent& evt);
};

