#pragma once

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/dcbuffer.h>
#include <wx/progdlg.h>
#include <wx/filefn.h>
#include <wx/dcgraph.h>


#include "CyclotronConfiguration.h"
#include "EcaLogic.h"

class SimulatorPanel : public wxScrolledWindow {
public:
	EcaLogic* eca = nullptr;
	CyclotronConfiguration* cyclotronConfiguration = nullptr;
	wxBitmap currentBitmap;

	int panelSize;
	wxPoint ringCenter = wxPoint(panelSize / 2, panelSize / 2);

	bool toggleAnimation = true;
	bool enable3d = false;
	int currentIteration = 0;

	wxTimer paintTimer;

	SimulatorPanel(wxWindow* parent, EcaLogic* ecaLogic, CyclotronConfiguration* config);

	
private:
	wxBitmap helperBitmap;
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
