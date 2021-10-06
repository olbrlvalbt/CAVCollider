#include "ColliderView.h"


#include <thread>
#include <wx/dcbuffer.h>

ColliderView::ColliderView(wxWindow* parent, ColliderConfiguration* colliderConfiguration, int refreshRate)
	: wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition,
		wxDefaultSize, wxBORDER_SIMPLE),
	colliderConfiguration(colliderConfiguration),
	toggleAnimation(true),
	cellSize(2){
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

	/*centralBitmap = wxBitmap(panelSize, panelSize);
	leftBitmap = wxBitmap(panelSize, panelSize);
	rightBitmap = wxBitmap(panelSize, panelSize);*/

	Connect(GetId(), wxEVT_PAINT, wxPaintEventHandler(ColliderView::paintEvent));
	Connect(GetId(), wxEVT_KEY_DOWN, wxKeyEventHandler(ColliderView::OnKeyDown));
	
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

	wxMemoryDC dc(mainPanelBitmap);
	dc.SetBackground(*wxBLACK_BRUSH);
	dc.Clear();
	
	dc.SetBrush(*wxTRANSPARENT_BRUSH);
	dc.SetPen(wxPen(wxColour(30, 115, 60)));
	dc.DrawCircle(leftRingCenter, colliderConfiguration->getLeftRingRadius());
	dc.SetPen(wxPen(wxColour(115, 30, 60)));
	dc.DrawCircle(rightRingCenter, colliderConfiguration->getRightRingRadius());
	dc.SetPen(wxPen(wxColour(30, 60, 115)));
	dc.DrawCircle(centralRingCenter, colliderConfiguration->getCentralRingRadius());

	paintCentralRing(dc);
	paintLeftRing(dc);
	paintRightRing(dc);

	/*centralBitmap.SetMask(new wxMask(centralBitmap, *wxGREEN));
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
	rightBitmap.SetMask(NULL);*/

	dc.SelectObject(wxNullBitmap);
}

void ColliderView::paintCentralRing(wxDC& dc) {
	/*wxMemoryDC dc(centralBitmap);
	dc.SetBackground(*wxGREEN);
	dc.Clear();*/
	
	int centralN = colliderConfiguration->getCollisionSystem().getCentralN();
	string centralState = colliderConfiguration->getCollisionSystem().getCentralState();
	string centralFilter = colliderConfiguration->getCollisionSystem().getCentralFilter();

	dc.SetPen(colliderConfiguration->getAliveCellColor());
	dc.SetBrush(colliderConfiguration->getAliveCellColor());
	for (int i = 0; i < centralN; i++) {
		if (centralFilter[i] == '0' && centralState[i] == '1') {
			double angle = colliderConfiguration->getCentralAngleForPos(i);
			double projX = colliderConfiguration->getCentralRingRadius() * std::cos(angle);
			double projY = colliderConfiguration->getCentralRingRadius() * std::sin(angle);
			dc.DrawRectangle(centralRingCenter.x + projX, centralRingCenter.y + projY, cellSize, cellSize);
		}
	}
	dc.SetPen(colliderConfiguration->getDeadCellColor());
	dc.SetBrush(colliderConfiguration->getDeadCellColor());
	for (int i = 0; i < centralN; i++) {
		if (centralFilter[i] == '0' && centralState[i] == '0') {
			double angle = colliderConfiguration->getCentralAngleForPos(i);
			double projX = colliderConfiguration->getCentralRingRadius() * std::cos(angle);
			double projY = colliderConfiguration->getCentralRingRadius() * std::sin(angle);
			dc.DrawRectangle(centralRingCenter.x + projX, centralRingCenter.y + projY, cellSize, cellSize);
		}
	}
}

void ColliderView::paintLeftRing(wxDC& dc) {
	/*wxMemoryDC dc(leftBitmap);
	dc.SetBackground(*wxGREEN);
	dc.Clear();*/

	int leftN = colliderConfiguration->getCollisionSystem().getLeftN();
	string leftState = colliderConfiguration->getCollisionSystem().getLeftState();
	string leftFilter = colliderConfiguration->getCollisionSystem().getLeftFilter();
	
	dc.SetPen(colliderConfiguration->getAliveCellColor());
	dc.SetBrush(colliderConfiguration->getAliveCellColor());
	for (int i = 0; i < leftN; i++) {
		if (leftFilter[i] == '0' && leftState[i] == '1') {
			double angle = colliderConfiguration->getLeftAngleForPos(i);
			double projX = colliderConfiguration->getLeftRingRadius() * std::cos(angle);
			double projY = colliderConfiguration->getLeftRingRadius() * std::sin(angle);
			dc.DrawRectangle(leftRingCenter.x + projX, leftRingCenter.y + projY, cellSize, cellSize);
		}
	}
	dc.SetPen(colliderConfiguration->getDeadCellColor());
	dc.SetBrush(colliderConfiguration->getDeadCellColor());
	for (int i = 0; i < leftN; i++) {
		if (leftFilter[i] == '0' && leftState[i] == '0') {
			double angle = colliderConfiguration->getLeftAngleForPos(i);
			double projX = colliderConfiguration->getLeftRingRadius() * std::cos(angle);
			double projY = colliderConfiguration->getLeftRingRadius() * std::sin(angle);
			dc.DrawRectangle(leftRingCenter.x + projX, leftRingCenter.y + projY, cellSize, cellSize);
		}
	}
}

void ColliderView::paintRightRing(wxDC& dc) {
	/*wxMemoryDC dc(rightBitmap);
	dc.SetBackground(*wxGREEN);
	dc.Clear();*/

	int rightN = colliderConfiguration->getCollisionSystem().getRightN();
	string rightState = colliderConfiguration->getCollisionSystem().getRightState();
	string rightFilter = colliderConfiguration->getCollisionSystem().geRightFilter();
	
	dc.SetPen(colliderConfiguration->getAliveCellColor());
	dc.SetBrush(colliderConfiguration->getAliveCellColor());
	for (int i = 0; i < rightN; i++) {
		if (rightFilter[i] == '0' && rightState[i] == '1') {
			double angle = colliderConfiguration->getRightAngleForPos(i);
			double projX = colliderConfiguration->getRightRingRadius() * std::cos(angle);
			double projY = colliderConfiguration->getRightRingRadius() * std::sin(angle);
			dc.DrawRectangle(rightRingCenter.x + projX, rightRingCenter.y + projY, cellSize, cellSize);
		}
	}
	dc.SetPen(colliderConfiguration->getDeadCellColor());
	dc.SetBrush(colliderConfiguration->getDeadCellColor());
	for (int i = 0; i < rightN; i++) {
		if (rightFilter[i] == '0' && rightState[i] == '0') {
			double angle = colliderConfiguration->getRightAngleForPos(i);
			double projX = colliderConfiguration->getRightRingRadius() * std::cos(angle);
			double projY = colliderConfiguration->getRightRingRadius() * std::sin(angle);
			dc.DrawRectangle(rightRingCenter.x + projX, rightRingCenter.y + projY, cellSize, cellSize);
		}
	}
}

void ColliderView::OnKeyDown(wxKeyEvent& evt) {
	switch ((int)evt.GetKeyCode()) {
	case 'p':
	case 'P':
		playPause();
		break;
	/*case 'r':
	case 'R':
		restart();
		break;*/
	case 's':
	case 'S':
		saveToImage();
		break;
	}
	evt.Skip();
}

void ColliderView::playPause() {
	toggleAnimation = !toggleAnimation;
}

void ColliderView::saveToImage() {
	bool curPaintActive = toggleAnimation;
	toggleAnimation = false;

	wxFileDialog saveFileDialog(this, _("Save file"), wxGetCwd(), "",
		"PNG files (*.png)|*.png", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (saveFileDialog.ShowModal() == wxID_CANCEL) {
		return;
	}
	mainPanelBitmap.SaveFile(saveFileDialog.GetPath(), wxBITMAP_TYPE_PNG);

	toggleAnimation = curPaintActive;
}