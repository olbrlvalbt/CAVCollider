#pragma once

#include <wx/wx.h>

#include "ColliderConfiguration.h"

class ColliderView : public wxScrolledWindow {
private:
	ColliderConfiguration* colliderConfiguration;

	int panelSize;
	wxPoint centralRingCenter;
	wxPoint leftRingCenter;
	wxPoint rightRingCenter;
	
	wxPoint leftContactPos;
	wxPoint rightContactPos;

	bool toggleAnimation = true;

	wxBitmap mainPanelBitmap;
	/*wxBitmap centralBitmap;
	wxBitmap leftBitmap;
	wxBitmap rightBitmap;*/

	wxTimer paintTimer;

	int cellSize;

public:
	ColliderView(wxWindow* parent, ColliderConfiguration* colliderConfiguration, int refreshRate);
	~ColliderView();

	void saveToImage();
	void playPause();
	void toggle3D();
	void restart();

private:
	void paintEvent(wxPaintEvent& evt);
	void timerEvent(wxTimerEvent& evt);
	void OnKeyDown(wxKeyEvent& evt);

	void render(wxDC& dc);
	void processCollider();

	void paintCentralRing(wxDC& dc);
	void paintLeftRing(wxDC& dc);
	void paintRightRing(wxDC& dc);
};

