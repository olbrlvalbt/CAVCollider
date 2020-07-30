#pragma once

#include <wx/wx.h>
#include <wx/sizer.h>

#include "EcaLogic.h"
#include "DrawPanel.h"

class EcaFrame : public wxFrame {
public:
	const wxSize MaxFrameSize = wxSize(wxSystemSettings::GetMetric(wxSYS_SCREEN_X) - 100,
									   wxSystemSettings::GetMetric(wxSYS_SCREEN_Y) - 100);
	DrawPanel* drawPanel = nullptr;

	void initEcaFrame(EcaLogic* ecaLogic, int _numIterations, int _cellSize,
					  wxColour deadCellColor, wxColour aliveCellColor,
					  wxColour filterExteriorColor, wxColour filterInteriorColor);
	EcaFrame(EcaLogic* ecaLogic, int numIterations, int cellSize,
			 wxColour deadCellColor, wxColour aliveCellColor,
			 wxColour filterExteriorColor, wxColour filterInteriorColor);
};

