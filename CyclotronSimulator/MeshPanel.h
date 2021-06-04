#pragma once

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/dcbuffer.h>
#include <wx/progdlg.h>
#include <wx/dcgraph.h>

#include "EcaMeshConfiguration.h"

class MeshPanel : public wxScrolledWindow {
public:
	EcaMeshConfiguration* meshConfig = nullptr;
	wxBitmap* bitmap;
	wxBitmap* filterBitmap;

	bool rule110T3filterEnabled = false;
	
	int currentSpace = 1;

	MeshPanel(wxWindow* parent, EcaMeshConfiguration* config, bool _rule110T3filterEnabled);

	void paintEvent(wxPaintEvent& evt);
	void OnKeyDown(wxKeyEvent& event);

	void render();
	void createBitmap();
	void paintIteration(wxDC& dc, int iteration);
	void createBitmapWithT3Filter();
	void filterT3(string(&iterationGroup)[4], wxGCDC& filterDc, int iteration);
	bool saveToImage();
	void nextSpace();
	void restartSpace();
	void resetSpace();
};

