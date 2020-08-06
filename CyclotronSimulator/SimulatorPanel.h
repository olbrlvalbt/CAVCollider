#pragma once

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/dcbuffer.h>
#include <wx/progdlg.h>
#include <wx/dcgraph.h>

#include "EcaLogic.h"

class SimulatorPanel : public wxScrolledWindow {
public:
	EcaLogic* eca = nullptr;
	wxBitmap* bitmap;
	wxBitmap* filterBitmap;

	int ringWidth = 2;
	int ringRadius = 500;
	int panelSize = 1500;
	wxPoint ringCenter = wxPoint(panelSize / 2, panelSize / 2);

	bool filterOn = false;

	wxPen* deadCellPenColor;
	wxPen* aliveCellPenColor;
	wxPen* filterExteriorPenColor;
	wxPen* filterInteriorPenColor;

	SimulatorPanel(wxWindow* parent, EcaLogic* ecaLogic, int _ringRadius, int _panelSize,
				   wxColour _deadCellColor, wxColour _aliveCellColor,
				   wxColour _filterExteriorColor, wxColour _filterInteriorColor);

	void paintEvent(wxPaintEvent & evt);
	//void OnKeyDown(wxKeyEvent& event);

	void render();
	void createBitmap();
	void paintIteration(wxDC& dc, int iteration);
	//void createBitmapWithT3Filter();
	//void filterT3(string(&iterationGroup)[4], wxGCDC& filterDc, int iteration);
	//bool saveToImage(wxBufferedDC& dc);
};
