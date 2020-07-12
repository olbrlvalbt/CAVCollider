#pragma once
#include "wx/wx.h"
#include "wx/sizer.h"
#include "EcaLogic.h"
#include "DrawPanel.h"

class EcaFrame : public wxFrame {
public:
	DrawPanel* drawPanel = nullptr;
	wxPoint* PanelOffset = new wxPoint(0, 30);

	void initEcaFrame(EcaLogic* ecaLogic, int _numIterations, int _cellSize,
					  wxColour* deadCellColor, wxColour* aliveCellColor);
	EcaFrame(EcaLogic* ecaLogic, int numIterations, int cellSize,
			 wxColour* deadCellColor, wxColour* aliveCellColor);
	void OnKeyDown(wxKeyEvent& event);
};

