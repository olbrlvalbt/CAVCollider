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
	

	wxStaticText* ringWidthText;
	wxSpinCtrl* ringWidthCtrl;

	wxStaticText* ringRadiusText;
	wxSpinCtrl* ringRadiusCtrl;

	wxStaticText* refreshRateText;
	wxSpinCtrl* refreshRateCtrl;

	wxStaticText* ringOffsetText;
	wxSpinCtrl* ringOffsetCtrl;

	wxStaticText* deadCellColorText;
	wxColourPickerCtrl* deadCellColorCtrl;

	wxStaticText* aliveCellColorText;
	wxColourPickerCtrl* aliveCellColorCtrl;

	wxStaticText* enableRule110T3FilterText;
	wxCheckBox* enableRule110T3FilterBox;

	wxStaticText* filterExteriorColorText;
	wxColourPickerCtrl* filterExteriorColorCtrl;

	wxStaticText* filterInteriorColorText;
	wxColourPickerCtrl* filterInteriorColorCtrl;

	wxButton* createEcaButton;
	

	SimulatorMenu();

	void SetRandomInitialConditionBoxEvent(wxCommandEvent& event);
	void AdjustNumCellsToInitialConditionBoxEvent(wxCommandEvent& event);
	
	void CreateEcaEvent(wxCommandEvent& event);
	void ToggleFilterColorsEvent(wxCommandEvent& event);
};

