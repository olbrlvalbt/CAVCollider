#pragma once

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/spinctrl.h>
#include <wx/clrpicker.h>

#include "EcaLogic.h"
#include "EcaFrame.h"

class MainFrame : public wxFrame {
public:
	wxPanel* mainPanel;

	wxStaticText* ruleText;
	wxSpinCtrl* ruleCtrl;

	wxStaticText* setRandomInitialConditionText;
	wxCheckBox* setRandomInitialConditionBox;

	wxStaticText* initialConditionText;
	wxTextCtrl* initialConditionCtrl;

	wxStaticText* adjustNumCellsToInitialConditionText;
	wxCheckBox* adjustNumCellsToInitialConditionBox;

	wxStaticText* numIterationsText;
	wxSpinCtrl* numIterationsCtrl;

	wxStaticText* setClosedBoundaryText;
	wxCheckBox* setClosedBoundaryBox;

	wxStaticText* numCellsText;
	wxSpinCtrl* numCellsCtrl;

	wxStaticText* fillEdgesWithRule110EtherText;
	wxCheckBox* fillEdgesWithRule110EtherBox;

	wxStaticText* numEtherRule110ForEdgesText;
	wxSpinCtrl* numEtherRule110ForEdgesCtrl;

	wxStaticText* newNumCellsAfterEtherText;
	wxStaticText* newNumCellsAfterEtherResult;

	wxStaticText* dummyText;

	wxStaticText* cellSizeText;
	wxSpinCtrl* cellSizeCtrl;

	wxStaticText* deadCellColorText;
	wxColourPickerCtrl* deadCellColorCtrl;

	wxStaticText* aliveCellColorText;
	wxColourPickerCtrl* aliveCellColorCtrl;

	wxButton* createEcaButton;

	MainFrame();
	
	void SetRandomInitialConditionBoxEvent(wxCommandEvent& event);
	void AdjustNumCellsToInitialConditionBoxEvent(wxCommandEvent& event);
	void FillEdgesWithRule110EtherBoxEvent(wxCommandEvent& event);
	void SetNewNumCellsAfterEtherEvent(wxCommandEvent& event);
	void CreateEcaEvent(wxCommandEvent& event);

	void setNewNumCellsAfterEther();
};

class EcaApp : public wxApp {
public:
	MainFrame* mainFrame = nullptr;
	EcaFrame* frame = nullptr;
	DrawPanel* drawPane = nullptr;

	virtual bool OnInit();
};