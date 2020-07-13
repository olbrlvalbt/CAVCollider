#pragma once

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/dcbuffer.h>

#include "EcaLogic.h"

class DrawPanel : public wxScrolledWindow {
public:
	EcaLogic* eca = nullptr;
	bool shouldRedraw = true;
	int numIterations = 1;
	int currentShowingIteration = 1;
	int cellSize = 1;
	wxBrush* deadCellBrushColor;
	wxBrush* aliveCellBrushColor;

	DrawPanel(wxWindow* parent, EcaLogic* ecaLogic, int _numIterations, int _cellSize,
			  wxColour _deadCellColor, wxColour _aliveCellColor);

	void paintEvent(wxPaintEvent & evt);
	void OnKeyDown(wxKeyEvent& event);

	void render(wxDC& dc);
	bool saveToImage(wxDC& dc);
};

