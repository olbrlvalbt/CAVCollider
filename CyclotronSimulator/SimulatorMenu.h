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
	
	wxPanel* menuPanel;

	wxPropertyGrid* pg;
	
	/*wxFlexGridSizer* fgs;
	
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


	wxStaticText* numIterationsText;
	wxSpinCtrl* numIterationsCtrl;

	wxStaticText* cellSizeText;
	wxSpinCtrl* cellSizeCtrl;
	

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

	wxStaticText* enableRingModeText;
	wxCheckBox* enableRingModeBox;*/

	wxButton* createEcaButton;
	

	SimulatorMenu();

	void setRandomInitialConditionEvent();
	void adjustNumCellsToInitialConditionEvent();
	
	void CreateEcaEvent(wxCommandEvent& event);
	void toggleModeOptions();

	void OnChangedProperty(wxPropertyGridEvent& event);
};
