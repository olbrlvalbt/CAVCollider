#include "ColliderView.h"


#include <thread>
#include <wx/dcbuffer.h>

ColliderView::ColliderView(wxWindow* parent, ColliderConfiguration* colliderConfiguration, int refreshRate)
	: wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition,
		wxDefaultSize, wxBORDER_SIMPLE),
	colliderConfiguration(colliderConfiguration),
	toggleAnimation(true) {
	/*panelSize = 2 * colliderConfiguration->getCentralRingRadius()
		+ 2 * colliderConfiguration->getLeftRingRadius()
		+ 2 * colliderConfiguration->getRightRingRadius();*/
	panelSize = 6 * colliderConfiguration->getCentralRingRadius();
	
	centralRingCenter = wxPoint(panelSize / 2, panelSize / 2);
	leftRingCenter = centralRingCenter + colliderConfiguration->getRelativeLeftRingCenter();
	rightRingCenter = centralRingCenter + colliderConfiguration->getRelativeRightRingCenter();
	
	leftContactPos = centralRingCenter + colliderConfiguration->getRelativeLeftContactPos();
	rightContactPos = centralRingCenter + colliderConfiguration->getRelativeRightContactPos();

	wxInitAllImageHandlers();
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	
	mainPanelBitmap = wxBitmap(panelSize, panelSize);

	centralBitmap = wxBitmap(panelSize, panelSize);
	leftBitmap = wxBitmap(panelSize, panelSize);
	rightBitmap = wxBitmap(panelSize, panelSize);
	/*centralBitmap = wxBitmap(colliderConfiguration->getCentralRingRadius() * 2,
		colliderConfiguration->getCentralRingRadius() * 2);
	leftBitmap = wxBitmap(colliderConfiguration->getLeftRingRadius() * 2,
		colliderConfiguration->getLeftRingRadius() * 2);
	rightBitmap = wxBitmap(colliderConfiguration->getRightRingRadius() * 2,
		colliderConfiguration->getRightRingRadius() * 2);*/

	Connect(GetId(), wxEVT_PAINT, wxPaintEventHandler(ColliderView::paintEvent));

	SetClientSize(panelSize, panelSize);
	SetScrollbars(1, 1, panelSize, panelSize, 0, 0);

	paintTimer.SetOwner(this);
	paintTimer.Start(refreshRate);

	Connect(paintTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(ColliderView::timerEvent));
}

ColliderView::~ColliderView() {
	delete colliderConfiguration;
}

void ColliderView::paintEvent(wxPaintEvent& evt) {
	wxBufferedPaintDC dc(this);
	DoPrepareDC(dc);
	render(dc);
}

void ColliderView::timerEvent(wxTimerEvent& evt) {
	if (toggleAnimation) {
		processCollider();

		GetParent()->SetLabel(wxT("Iteration - " + 
			to_string(colliderConfiguration->getCurrentIteration())));

		Refresh();
	}
}

void ColliderView::render(wxDC& dc) {
	dc.DrawBitmap(mainPanelBitmap, 0, 0);
	if (colliderConfiguration->getCollisionSystem().isLeftEnabled()) {
		dc.SetBrush(*wxRED_BRUSH);
	}
	else {
		dc.SetBrush(*wxBLUE_BRUSH);
	}
	dc.DrawCircle(leftContactPos, 5);
	if (colliderConfiguration->getCollisionSystem().isRightEnabled()) {
		dc.SetBrush(*wxRED_BRUSH);
	}
	else {
		dc.SetBrush(*wxBLUE_BRUSH);
	}
	dc.DrawCircle(rightContactPos, 5);
}

void ColliderView::processCollider() {
	wxMemoryDC dc(mainPanelBitmap);
	dc.SetBackground(*wxBLACK_BRUSH);
	dc.Clear();

	colliderConfiguration->getCollisionSystem().execute();

	/*auto leftLambda = [&]() {
		paintLeftRing();
	};
	auto rightLambda = [&]() {
		paintRightRing();
	};
	auto centralLambda = [&]() {
		paintCentralRing();
	};

	std::thread leftThread(leftLambda);
	std::thread rightThread(rightLambda);
	std::thread centralThread(centralLambda);

	leftThread.join();
	rightThread.join();
	centralThread.join();*/

	paintCentralRing();
	paintLeftRing();
	paintRightRing();
	
	centralBitmap.SetMask(new wxMask(centralBitmap, *wxGREEN));
	wxMemoryDC centralDc(centralBitmap);
	dc.Blit(0, 0,
		panelSize, panelSize,
		&centralDc,
		0, 0, wxCOPY, true);
	centralBitmap.SetMask(NULL);

	leftBitmap.SetMask(new wxMask(leftBitmap, *wxGREEN));
	wxMemoryDC leftDc(leftBitmap);
	dc.Blit(0, 0,
		panelSize, panelSize,
		&leftDc,
		0, 0, wxCOPY, true);
	leftBitmap.SetMask(NULL);

	rightBitmap.SetMask(new wxMask(rightBitmap, *wxGREEN));
	wxMemoryDC rightDc(rightBitmap);
	dc.Blit(0, 0,
		panelSize, panelSize,
		&rightDc,
		0, 0, wxCOPY, true);
	rightBitmap.SetMask(NULL);
	
	dc.SelectObject(wxNullBitmap);
}

void ColliderView::paintCentralRing() {
	wxMemoryDC dc(centralBitmap);
	dc.SetBackground(*wxGREEN);
	dc.Clear();
	
	int centralN = colliderConfiguration->getCollisionSystem().getCentralN();
	string centralState = colliderConfiguration->getCollisionSystem().getCentralState();

	dc.SetPen(colliderConfiguration->getAliveCellPen());
	for (int i = 0; i < centralN; i++) {
		if (centralState[i] == '1') {
			double projX = colliderConfiguration->getCentralRingRadius() * std::cos(i * colliderConfiguration->getCentralAlphaRad());
			double projY = colliderConfiguration->getCentralRingRadius() * std::sin(i * colliderConfiguration->getCentralAlphaRad());
			dc.DrawPoint(centralRingCenter.x + projX, centralRingCenter.y + projY);
		}
	}
	dc.SetPen(colliderConfiguration->getDeadCellPen());
	for (int i = 0; i < centralN; i++) {
		if (centralState[i] == '0') {
			double projX = colliderConfiguration->getCentralRingRadius() * std::cos(i * colliderConfiguration->getCentralAlphaRad());
			double projY = colliderConfiguration->getCentralRingRadius() * std::sin(i * colliderConfiguration->getCentralAlphaRad());
			dc.DrawPoint(centralRingCenter.x + projX, centralRingCenter.y + projY);
		}
	}
}

void ColliderView::paintLeftRing() {
	wxMemoryDC dc(leftBitmap);
	dc.SetBackground(*wxGREEN);
	dc.Clear();

	int leftN = colliderConfiguration->getCollisionSystem().getLeftN();
	string leftState = colliderConfiguration->getCollisionSystem().getLeftState();
	
	dc.SetPen(colliderConfiguration->getAliveCellPen());
	for (int i = 0; i < leftN; i++) {
		if (leftState[i] == '1') {
			double projX = colliderConfiguration->getLeftRingRadius() * std::cos(i * colliderConfiguration->getLeftAlphaRad());
			double projY = colliderConfiguration->getLeftRingRadius() * std::sin(i * colliderConfiguration->getLeftAlphaRad());
			dc.DrawPoint(leftRingCenter.x + projX, leftRingCenter.y + projY);
		}
	}
	dc.SetPen(colliderConfiguration->getDeadCellPen());
	for (int i = 0; i < leftN; i++) {
		if (leftState[i] == '0') {
			double projX = colliderConfiguration->getLeftRingRadius() * std::cos(i * colliderConfiguration->getLeftAlphaRad());
			double projY = colliderConfiguration->getLeftRingRadius() * std::sin(i * colliderConfiguration->getLeftAlphaRad());
			dc.DrawPoint(leftRingCenter.x + projX, leftRingCenter.y + projY);
		}
	}
}

void ColliderView::paintRightRing() {
	wxMemoryDC dc(rightBitmap);
	dc.SetBackground(*wxGREEN);
	dc.Clear();

	int rightN = colliderConfiguration->getCollisionSystem().getRightN();
	string rightState = colliderConfiguration->getCollisionSystem().getRightState();
	
	dc.SetPen(colliderConfiguration->getAliveCellPen());
	for (int i = 0; i < rightN; i++) {
		if (rightState[i] == '1') {
			double projX = colliderConfiguration->getRightRingRadius() * std::cos(i * colliderConfiguration->getRightAlphaRad());
			double projY = colliderConfiguration->getRightRingRadius() * std::sin(i * colliderConfiguration->getRightAlphaRad());
			dc.DrawPoint(rightRingCenter.x + projX, rightRingCenter.y + projY);
		}
	}
	dc.SetPen(colliderConfiguration->getDeadCellPen());
	for (int i = 0; i < rightN; i++) {
		if (rightState[i] == '0') {
			double projX = colliderConfiguration->getRightRingRadius() * std::cos(i * colliderConfiguration->getRightAlphaRad());
			double projY = colliderConfiguration->getRightRingRadius() * std::sin(i * colliderConfiguration->getRightAlphaRad());
			dc.DrawPoint(rightRingCenter.x + projX, rightRingCenter.y + projY);
		}
	}
}
