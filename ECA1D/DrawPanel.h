#pragma once
#include "wx/wx.h"
#include "wx/sizer.h"
#include "EcaLogic.h"

class DrawPanel : public wxPanel {
public:
	EcaLogic* eca = nullptr;
	wxPaintDC* dc = nullptr;
	bool shouldRedraw = true;
	int numIterations = 1;
	int currentShowingIteration = 1;
	int cellSize = 1;
	wxPoint* panelOffset = new wxPoint(0, 30);
	wxBrush* deadCellBrushColor;
	wxBrush* aliveCellBrushColor;

	DrawPanel(wxFrame* parent, EcaLogic* ecaLogic, int _numIterations, int _cellSize, wxPoint* _panelOffset,
			  wxColour* _deadCellColor, wxColour* _aliveCellColor);
	//DrawPanel(wxFrame* parent, EcaLogic* ecaLogic);
	void paintEvent(wxPaintEvent & evt);
	void render();
	bool saveToImage();
};