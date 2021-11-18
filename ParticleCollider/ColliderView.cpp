#include "ColliderView.h"

#include <thread>
#include <wx/dcbuffer.h>
#include <wx/numdlg.h>
#include <wx/progdlg.h>

ColliderView::ColliderView(wxWindow* parent, ColliderConfiguration* colliderConfiguration, int refreshRate)
	: wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition,
		wxDefaultSize, wxBORDER_SIMPLE),
	colliderConfiguration(colliderConfiguration),
	toggleAnimation(true),
	cellSize(2),
	isLeftVisible(true),
	isCentralVisible(true),
	isRightVisible(true) {
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
	SetScrollbars(10, 10, panelSize / 10, panelSize / 10);
	Scroll(50, 200);

	paintTimer.SetOwner(this);
	paintTimer.Start(refreshRate);

	Connect(paintTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(ColliderView::timerEvent));
}

ColliderView::~ColliderView() {
	delete colliderConfiguration;
}

void ColliderView::restart() {
	bool curPaintActive = toggleAnimation;
	toggleAnimation = false;

	if (wxMessageBox("Restart Collider?", "Confirm", wxYES_NO | wxYES_DEFAULT, this) == wxYES) {
		colliderConfiguration->getCollisionSystem().restart();
		curPaintActive = true;
		isCentralVisible = true;
		isLeftVisible = true;
		isRightVisible = true;
	}

	toggleAnimation = curPaintActive;
}

void ColliderView::paintEvent(wxPaintEvent& evt) {
	wxBufferedPaintDC dc(this);
	DoPrepareDC(dc);
	render(dc);
}

void ColliderView::timerEvent(wxTimerEvent& evt) {
	if (toggleAnimation) {
		processCollider();

		/*GetParent()->SetLabel(wxT("Iteration - " + 
			to_string(colliderConfiguration->getCurrentIteration())));*/

		Refresh();
	}
}

void ColliderView::render(wxDC& dc) {
	if (zoom != 1) {
		dc.SetUserScale(2, 2);
	}
	
	dc.DrawBitmap(mainPanelBitmap, 0, 0);

	dc.SetTextBackground(wxTRANSPARENT);
	dc.SetTextForeground(*wxWHITE);
	dc.DrawText("Iteration " + std::to_string(colliderConfiguration->getCurrentIteration()),
		10, 10);
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

	if (isLeftVisible) {
		if (colliderConfiguration->getCollisionSystem().isLeftRingEnabled()) {
			dc.SetPen(wxPen(wxColour(80, 165, 110)));
		}
		else {
			dc.SetPen(wxPen(wxColour(90, 90, 90)));
		}
		dc.DrawCircle(leftRingCenter.x, panelSize - leftRingCenter.y, colliderConfiguration->getLeftRingRadius());
	}

	if (isRightVisible) {
		if (colliderConfiguration->getCollisionSystem().isRightRingEnabled()) {
			dc.SetPen(wxPen(wxColour(165, 80, 110)));
		}
		else {
			dc.SetPen(wxPen(wxColour(90, 90, 90)));
		}
		dc.DrawCircle(rightRingCenter.x, panelSize - rightRingCenter.y, colliderConfiguration->getRightRingRadius());
	}

	if (isCentralVisible) {
		if (colliderConfiguration->getCollisionSystem().isCentralRingEnabled()) {
			dc.SetPen(wxPen(wxColour(80, 110, 165)));
		}
		else {
			dc.SetPen(wxPen(wxColour(90, 90, 90)));
		}
		dc.DrawCircle(centralRingCenter.x, panelSize - centralRingCenter.y, colliderConfiguration->getCentralRingRadius());
	}

	if (isCentralVisible)
		paintCentralRing(dc);
	if (isLeftVisible)
		paintLeftRing(dc);
	if (isRightVisible)
		paintRightRing(dc);

	dc.SetPen(*wxTRANSPARENT_PEN);
	
	if (colliderConfiguration->getCollisionSystem().isLeftRingEnabled()
		&& colliderConfiguration->getCollisionSystem().isCentralRingEnabled()
		&& colliderConfiguration->getCollisionSystem().isLeftContactEnabled()) {
		dc.SetBrush(*wxRED_BRUSH);
	}
	else {
		dc.SetBrush(wxBrush(wxColour(90, 90, 90)));
	}
	dc.DrawCircle(leftContactPos.x, panelSize - leftContactPos.y, 5);

	if (colliderConfiguration->getCollisionSystem().isRightRingEnabled()
		&& colliderConfiguration->getCollisionSystem().isCentralRingEnabled()
		&& colliderConfiguration->getCollisionSystem().isRightContactEnabled()) {
		dc.SetBrush(*wxRED_BRUSH);
	}
	else {
		dc.SetBrush(wxBrush(wxColour(90, 90, 90)));
	}
	dc.DrawCircle(rightContactPos.x, panelSize - rightContactPos.y, 5);

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
			dc.DrawRectangle(centralRingCenter.x + projX, panelSize - (centralRingCenter.y + projY), cellSize, cellSize);
		}
	}
	dc.SetPen(colliderConfiguration->getDeadCellColor());
	dc.SetBrush(colliderConfiguration->getDeadCellColor());
	for (int i = 0; i < centralN; i++) {
		if (centralFilter[i] == '0' && centralState[i] == '0') {
			double angle = colliderConfiguration->getCentralAngleForPos(i);
			double projX = colliderConfiguration->getCentralRingRadius() * std::cos(angle);
			double projY = colliderConfiguration->getCentralRingRadius() * std::sin(angle);
			dc.DrawRectangle(centralRingCenter.x + projX, panelSize - (centralRingCenter.y + projY), cellSize, cellSize);
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
			dc.DrawRectangle(leftRingCenter.x + projX, panelSize - (leftRingCenter.y + projY), cellSize, cellSize);
		}
	}
	dc.SetPen(colliderConfiguration->getDeadCellColor());
	dc.SetBrush(colliderConfiguration->getDeadCellColor());
	for (int i = 0; i < leftN; i++) {
		if (leftFilter[i] == '0' && leftState[i] == '0') {
			double angle = colliderConfiguration->getLeftAngleForPos(i);
			double projX = colliderConfiguration->getLeftRingRadius() * std::cos(angle);
			double projY = colliderConfiguration->getLeftRingRadius() * std::sin(angle);
			dc.DrawRectangle(leftRingCenter.x + projX, panelSize - (leftRingCenter.y + projY), cellSize, cellSize);
		}
	}
}

void ColliderView::paintRightRing(wxDC& dc) {
	/*wxMemoryDC dc(rightBitmap);
	dc.SetBackground(*wxGREEN);
	dc.Clear();*/

	int rightN = colliderConfiguration->getCollisionSystem().getRightN();
	string rightState = colliderConfiguration->getCollisionSystem().getRightState();
	string rightFilter = colliderConfiguration->getCollisionSystem().getRightFilter();
	
	dc.SetPen(colliderConfiguration->getAliveCellColor());
	dc.SetBrush(colliderConfiguration->getAliveCellColor());
	for (int i = 0; i < rightN; i++) {
		if (rightFilter[i] == '0' && rightState[i] == '1') {
			double angle = colliderConfiguration->getRightAngleForPos(i);
			double projX = colliderConfiguration->getRightRingRadius() * std::cos(angle);
			double projY = colliderConfiguration->getRightRingRadius() * std::sin(angle);
			dc.DrawRectangle(rightRingCenter.x + projX, panelSize - (rightRingCenter.y + projY), cellSize, cellSize);
		}
	}
	dc.SetPen(colliderConfiguration->getDeadCellColor());
	dc.SetBrush(colliderConfiguration->getDeadCellColor());
	for (int i = 0; i < rightN; i++) {
		if (rightFilter[i] == '0' && rightState[i] == '0') {
			double angle = colliderConfiguration->getRightAngleForPos(i);
			double projX = colliderConfiguration->getRightRingRadius() * std::cos(angle);
			double projY = colliderConfiguration->getRightRingRadius() * std::sin(angle);
			dc.DrawRectangle(rightRingCenter.x + projX, panelSize - (rightRingCenter.y + projY), cellSize, cellSize);
		}
	}
}

void ColliderView::showLeft() {
	isLeftVisible = !isLeftVisible;
	Refresh();
}

void ColliderView::showCentral() {
	isCentralVisible = !isCentralVisible;
	Refresh();
}

void ColliderView::showRight() {
	isRightVisible = !isRightVisible;
	Refresh();
}

void ColliderView::OnKeyDown(wxKeyEvent& evt) {
	switch ((int)evt.GetKeyCode()) {
	case '1':
		showLeft();
		break;
	case '2':
		showCentral();
		break;
	case '3':
		showRight();
		break;
	case 'p':
	case 'P':
		playPause();
		break;
	case 'j':
	case 'J':
		jumpTo();
		break;
	case 'r':
	case 'R':
		restart();
		break;
	case 's':
	case 'S':
		saveToImage();
		break;
	case 'z':
	case 'Z':
		zoom = zoom == 1 ? 2 : 1;
		if (zoom == 2) {
			SetScrollbars(20, 20, panelSize / 20, panelSize / 20);
		}
		else {
			SetScrollbars(10, 10, panelSize / 10, panelSize / 10);
		}
		break;
	}
	evt.Skip();
}

void ColliderView::playPause() {
	toggleAnimation = !toggleAnimation;
}

void ColliderView::jumpTo() {
	bool curPaintActive = toggleAnimation;
	toggleAnimation = false;

	int currentIteration = colliderConfiguration->getCurrentIteration();

	long it = wxGetNumberFromUser("Jump To Iteration:",
		"", "Jump To",
		currentIteration, 0, 100000000, this);

	if (it != -1) {
		wxProgressDialog* progress = new wxProgressDialog("Processing",
			"Jumping to new iteration, please wait.", 
			100, nullptr, wxPD_AUTO_HIDE);
		int k = 0;
		std::function<void(int)> lambda = [&](int newIt) {
			if ((newIt * 100) % it == 0) {
				progress->Update(k++);
			}
			progress->SetTitle("Processing (" + std::to_string(newIt) + "/" + std::to_string(it));
		};
		colliderConfiguration->getCollisionSystem().jumpToIteration(it, lambda);
		progress->Update(100);
	}
	
	toggleAnimation = curPaintActive;
}

void ColliderView::saveToImage() {
	bool curPaintActive = toggleAnimation;
	toggleAnimation = false;

	wxFileDialog saveFileDialog(this, _("Save file"), wxGetCwd(), "",
		"PNG files (*.png)|*.png", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (saveFileDialog.ShowModal() == wxID_CANCEL) {
		return;
	}

	wxProgressDialog progress("Processing",
		"Saving image, please wait.",
		100, nullptr, wxPD_AUTO_HIDE);

	progress.Update(50);
	
	mainPanelBitmap.SaveFile(saveFileDialog.GetPath(), wxBITMAP_TYPE_PNG);
	
	progress.Update(100);

	toggleAnimation = curPaintActive;
}
