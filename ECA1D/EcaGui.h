#pragma once
#include "wx/wx.h"
#include "wx/spinctrl.h"
#include "wx/sizer.h"
#include "EcaLogic.h"

#define RULE 110
#define INITIALCONDITION "1111100001000111110101111100010011011111000100110111110000101100100110111110001110110010110111110001000110011000111110001001101111100010011011111011111101111101011111000100110111110001001101111100001000111110101111100010011011111000100110011000111111000100110111110001001101111100010011011111000101101000011011111001111101110011011101110011000010011011111000100110111110001001101110001110110001001101111100010011011111000100110011000111111000100110"
#define NUMCELLS sizeof(INITIALCONDITION) - 1
#define NUMITERATIONS 200
#define CELLSIZE 3
//#define NUMCELLS 1300
//#define NUMITERATIONS 700
//#define CELLSIZE 1
#define TEXTOFFSET 30

class EcaFrame : public wxFrame {
public:
	wxPanel* drawPane = nullptr;

	EcaFrame(int width, int height);
	void OnKeyDown(wxKeyEvent& event);
};


class DrawPane : public wxPanel {
public:
	EcaLogic* eca = nullptr;
	wxPaintDC* dc = nullptr;
	int numIterations = 1;
	int currentShowingIteration = 1;
	int cellSize = 1;
	int textOffset = 30;
	bool shouldRedraw = true;

	DrawPane(EcaFrame* parent, EcaLogic* ecaLogic, int numIterationsI, int cellSizeI, int textOffsetI);
	void paintEvent(wxPaintEvent & evt);
	void render();
	bool saveToImage();

	DECLARE_EVENT_TABLE()
};

class MainFrame : public wxFrame {
public:
	wxPanel* mainPanel;

	wxStaticText* ruleText;
	wxTextCtrl* ruleCtrl;

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

	wxStaticText* setClosedBoundaryText;
	wxCheckBox* setClosedBoundaryBox;

	wxStaticText* cellSizeText;
	wxSpinCtrl* cellSizeCtrl;

	wxStaticText* fillEdgesWithRule110EtherText;
	wxCheckBox* fillEdgesWithRule110EtherBox;

	wxStaticText* numEtherRule110ForEdgesText;
	wxSpinCtrl* numEtherRule110ForEdgesCtrl;

	wxStaticText* newNumCellsAfterEtherText;
	wxStaticText* newNumCellsAfterEtherResult;

	wxButton* createEcaButton;

	MainFrame();
	
	void SetRandomInitialConditionBoxEvent(wxCommandEvent& event);
	void AdjustNumCellsToInitialConditionBoxEvent(wxCommandEvent& event);
	void FillEdgesWithRule110EtherBoxEvent(wxCommandEvent& event);
	void SetNewNumCellsAfterEtherEvent(wxCommandEvent& event);
	void CreateEca(wxCommandEvent& event);

	void setNewNumCellsAfterEther();
};

class EcaGui : public wxApp {
public:
	MainFrame* mainFrame = nullptr;
	EcaFrame* frame = nullptr;
	DrawPane* drawPane = nullptr;

	virtual bool OnInit();
};