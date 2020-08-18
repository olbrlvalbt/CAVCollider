#pragma once

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/dcbuffer.h>
#include <wx/progdlg.h>
#include <wx/filefn.h>
#include <wx/dcgraph.h>

#include "EcaLogic.h"

class SimulatorPanel : public wxScrolledWindow {
public:
	EcaLogic* eca = nullptr;
	wxBitmap currentBitmap;
	wxBitmap helperBitmap;

	int ringOffset = 1;
	int ringWidth = 2;
	int ringRadius = 500;
	int panelSize = 1500;
	wxPoint ringCenter = wxPoint(panelSize / 2, panelSize / 2);

	bool filterOn = true;
	bool toggleAnimation = true;
	bool enable3d = false;
	int refreshRate = 50;
	int currentIteration = 0;

	wxPen* deadCellPenColor;
	wxPen* aliveCellPenColor;
	wxPen* filterExteriorPenColor;
	wxPen* filterInteriorPenColor;

	wxTimer paintTimer;

	SimulatorPanel(wxWindow* parent, EcaLogic* ecaLogic, int _ringRadius, int _panelSize,
				   wxColour _deadCellColor, wxColour _aliveCellColor,
				   wxColour _filterExteriorColor, wxColour _filterInteriorColor);

	
private:
	string iterationGroup[4] = { "", "", "", "" };
	string filterGroup[4] = { "", "", "", "" };
	
	void paintEvent(wxPaintEvent & evt);
	void timerEvent(wxTimerEvent& evt);
	void OnKeyDown(wxKeyEvent& evt);

	void render();
	void createBitmap();
	void clearBitmap(wxBitmap& bitmap);
	void saveToImage();

	void createBitmapWithT3Filter();
	void paintIterationWithT3Filter(wxDC& dc);
	void filterT3();
	void paintIteration(wxDC& dc);

	void initializeFilterGroup();
};
