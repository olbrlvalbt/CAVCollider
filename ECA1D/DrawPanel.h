#pragma once

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/dcbuffer.h>
#include <wx/progdlg.h>
#include <wx/dcgraph.h>

#include "EcaLogic.h"

class DrawPanel : public wxScrolledWindow {
public:
	EcaLogic* eca = nullptr;
	wxBitmap* bitmap;
	wxBitmap* filterBitmap;

	bool filterOn = false;

	int numIterations = 1;
	int currentShowingIteration = 1;
	int cellSize = 1;
	wxBrush* deadCellBrushColor;
	wxBrush* aliveCellBrushColor;

	DrawPanel(wxWindow* parent, EcaLogic* ecaLogic, int _numIterations, int _cellSize,
			  wxColour _deadCellColor, wxColour _aliveCellColor);

	void paintEvent(wxPaintEvent & evt);
	void OnKeyDown(wxKeyEvent& event);

	void render();
	void createBitmap();
	void paintIteration(wxDC& dc, int iteration);
	void createBitmapWithT3Filter();
	void filterT3(string (&iterationGroup)[4], wxGCDC& filterDc, int iteration);
	bool saveToImage(wxBufferedDC& dc);
};

