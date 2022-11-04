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

	int zoom = 1;

	bool isLeftVisible;
	bool isCentralVisible;
	bool isRightVisible;

public:
	ColliderView(wxWindow* parent, ColliderConfiguration* colliderConfiguration, int refreshRate);
	~ColliderView();

	void saveToImage();
	void playPause();
	void jumpTo();
	void toggle3D();
	void restart();

	void showLeft();
	void showCentral();
	void showRight();

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

