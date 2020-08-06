#pragma once

#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <wx/clrpicker.h>

#include "Rule110.h"
#include "EcaLogic.h"
#include "SimulatorFrame.h"

class SimulatorMenu : public wxFrame {
public:
	wxPanel* menuPanel;
	
	wxStaticText* ruleText;
	wxSpinCtrl* ruleCtrl;

	wxStaticText* setRandomInitialConditionText;
	wxCheckBox* setRandomInitialConditionBox;

	wxStaticText* initialConditionText;
	wxTextCtrl* initialConditionCtrl;

	wxStaticText* adjustNumCellsToInitialConditionText;
	wxCheckBox* adjustNumCellsToInitialConditionBox;

	wxStaticText* numCellsText;
	wxSpinCtrl* numCellsCtrl;
	

	wxStaticText* cellSizeText;
	wxSpinCtrl* cellSizeCtrl;

	wxStaticText* deadCellColorText;
	wxColourPickerCtrl* deadCellColorCtrl;

	wxStaticText* aliveCellColorText;
	wxColourPickerCtrl* aliveCellColorCtrl;

	wxStaticText* filterExteriorColorText;
	wxColourPickerCtrl* filterExteriorColorCtrl;

	wxStaticText* filterInteriorColorText;
	wxColourPickerCtrl* filterInteriorColorCtrl;

	wxButton* createEcaButton;
	

	SimulatorMenu();

	void SetRandomInitialConditionBoxEvent(wxCommandEvent& event);
	void AdjustNumCellsToInitialConditionBoxEvent(wxCommandEvent& event);
	
	void CreateEcaEvent(wxCommandEvent& event);
};

