#pragma once

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/dcbuffer.h>
#include <wx/progdlg.h>
#include <wx/filefn.h>
#include <wx/dcgraph.h>


#include "NaiveController.h"
#include "CompressedController.h"
#include "EcaRingConfiguration.h"

class RingPanel : public wxScrolledWindow {
public:
	EcaRingConfiguration* cyclotronConfiguration = nullptr;
	wxBitmap currentBitmap;

	int panelSize;
	wxPoint ringCenter = wxPoint(panelSize / 2, panelSize / 2);

	bool toggleAnimation = true;
	bool enable3d = false;
	int currentIteration = 0;

	bool enableRule110T3Filter;

	wxTimer paintTimer;

	RingPanel(wxWindow* parent, EcaRingConfiguration* config, bool _rule110T3filterEnabled);
	~RingPanel();

	void saveToImage();
	void playPause();
	void toggle3D();
	void toggleFilter();
	void restart();
	void reset();
	
private:
	wxBitmap helperBitmap;

	wxBitmap baseBitmap;

	wxBitmap aliveBitmap;
	wxBitmap deadBitmap;

	wxBitmap filterAliveBitmap;
	wxBitmap filterDeadBitmap;

	wxBitmap depthOnFilterOnBitmap;
	wxBitmap depthOnFilterOffBitmap;

	wxMask mask;
	wxColour maskColour;
	
	
	string iterationGroup[4] = { "", "", "", "" };
	string filterGroup[4] = { "", "", "", "" };
	
	void paintEvent(wxPaintEvent & evt);
	void timerEvent(wxTimerEvent& evt);
	void OnKeyDown(wxKeyEvent& evt);

	void render();
	void createBitmap();
	void clearBitmap(wxBitmap& bitmap);

	void createBitmapWithT3Filter();
	void paintIterationWithT3Filter(wxDC& dc);
	void filterT3();
	void paintIteration(wxDC& dc);

	void paintMask(wxMemoryDC& memDc, char flag);

	void initializeFilterGroup();
};
