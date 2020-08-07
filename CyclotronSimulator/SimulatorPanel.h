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
	wxBitmap* bitmap;
	wxBitmap* filterBitmap;

	int ringOffset = 1;
	int ringWidth = 2;
	int ringRadius = 500;
	int panelSize = 1500;
	wxPoint ringCenter = wxPoint(panelSize / 2, panelSize / 2);

	bool filterOn = false;
	bool paintActive = true;
	bool enable3d = false;

	wxPen* deadCellPenColor;
	wxPen* aliveCellPenColor;
	wxPen* filterExteriorPenColor;
	wxPen* filterInteriorPenColor;

	wxTimer paintTimer;

	SimulatorPanel(wxWindow* parent, EcaLogic* ecaLogic, int _ringRadius, int _panelSize,
				   wxColour _deadCellColor, wxColour _aliveCellColor,
				   wxColour _filterExteriorColor, wxColour _filterInteriorColor);

	void paintEvent(wxPaintEvent & evt);
	void timerEvent(wxTimerEvent& evt);
	void OnKeyDown(wxKeyEvent& evt);

	void render();
	void createBitmap();
	void clearBitmap();
	//void paintIteration(wxDC& dc, int iteration);
	void saveToImage();
	//void createBitmapWithT3Filter();
	//void filterT3(string(&iterationGroup)[4], wxGCDC& filterDc, int iteration);
	//bool saveToImage(wxBufferedDC& dc);
};
