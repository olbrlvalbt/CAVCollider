#include "SimulatorPanel.h"

SimulatorPanel::SimulatorPanel(wxWindow * parent, EcaLogic * ecaLogic, int _ringRadius = 500,
							   wxColour _deadCellColor = wxColour(220, 170, 15),
							   wxColour _aliveCellColor = wxColour(115, 35, 15),
							   wxColour _filterExteriorColor = wxColour(15, 15, 95),
							   wxColour _filterInteriorColor = wxColour(45, 45, 120))
	: wxScrolledWindow(parent) {
	eca = ecaLogic;
	ringRadius = _ringRadius;
	panelSize = 3 * ringRadius;
	ringCenter = wxPoint(panelSize / 2, panelSize / 2);
	deadCellPenColor = new wxPen(_deadCellColor, ringWidth);
	deadCellPenColor->SetCap(wxCAP_BUTT);
	aliveCellPenColor = new wxPen(_aliveCellColor, ringWidth);
	aliveCellPenColor->SetCap(wxCAP_BUTT);
	filterExteriorPenColor = new wxPen(_filterExteriorColor, ringWidth);
	filterInteriorPenColor = new wxPen(_filterInteriorColor, ringWidth);

	wxInitAllImageHandlers();
	SetBackgroundStyle(wxBG_STYLE_PAINT);

	currentBitmap = wxBitmap(panelSize, panelSize);
	helperBitmap = wxBitmap(panelSize, panelSize);
	clearBitmap(currentBitmap);
	clearBitmap(helperBitmap);

	if(filterOn) {
		initializeFilterGroup();
	}

	Connect(GetId(), wxEVT_PAINT, wxPaintEventHandler(SimulatorPanel::paintEvent));
	Connect(GetId(), wxEVT_KEY_DOWN, wxKeyEventHandler(SimulatorPanel::OnKeyDown));

	SetClientSize(500, 500);
	SetScrollbars(1, 1, panelSize, panelSize, 0, 0);

	paintTimer.SetOwner(this);
	paintTimer.Start(refreshRate);

	Connect(paintTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(SimulatorPanel::timerEvent));
}

void SimulatorPanel::paintEvent(wxPaintEvent & evt) {
	render();
}

void SimulatorPanel::render() {
	wxBufferedPaintDC paintDC(this);
	DoPrepareDC(paintDC);
	paintDC.DrawBitmap(currentBitmap, 0, 0, true);
	
	GetParent()->SetLabel("ECA R" + to_string(eca->ruleNumber) + ", N: " + to_string(eca->N)
		+ ", Iteration " + to_string(currentIteration));
}

void SimulatorPanel::createBitmap() {
	wxMemoryDC helperMemDc(helperBitmap);
	wxGCDC dc(helperMemDc);
	helperMemDc.SetBrush(*wxBLACK_BRUSH);
	helperMemDc.Clear();
	wxMemoryDC currentMemDc(currentBitmap);

	if (enable3d) {
		helperMemDc.Blit(0, 0,
						 panelSize - ringOffset, panelSize - ringOffset,
						 &currentMemDc,
						 ringOffset, ringOffset);
	}

	dc.SetBrush(*wxTRANSPARENT_BRUSH);

	double currentDegree = 0;
	double newDegree = 0;
	const double degreeIncrement = 360 / (double)(eca->N);

	for (int i = 0; i < eca->N; i++) {
		if (eca->currentState.at(i) == '1') {
			dc.SetPen(*aliveCellPenColor);
		}
		else {
			dc.SetPen(*deadCellPenColor);
		}
		newDegree += degreeIncrement;
		dc.DrawEllipticArc(ringCenter.x - ringRadius, ringCenter.y - ringRadius, 2 * ringRadius, 2 * ringRadius,
			currentDegree, newDegree);
		currentDegree = newDegree;
	}

	eca->applyRule();

	currentMemDc.Blit(0, 0,
		 			  panelSize - ringOffset, panelSize - ringOffset,
					  &helperMemDc,
					  ringOffset, ringOffset);

	helperMemDc.SelectObject(wxNullBitmap);
	currentMemDc.SelectObject(wxNullBitmap);
}

void SimulatorPanel::createBitmapWithT3Filter() {
	wxMemoryDC helperMemDc(helperBitmap);
	wxGCDC dc(helperMemDc);
	helperMemDc.SetBrush(*wxBLACK_BRUSH);
	helperMemDc.Clear();
	wxMemoryDC currentMemDc(currentBitmap);

	if (enable3d) {
		helperMemDc.Blit(0, 0,
						 panelSize - ringOffset, panelSize - ringOffset,
						 &currentMemDc,
					 	 ringOffset, ringOffset);
	}

	dc.SetBrush(*wxTRANSPARENT_BRUSH);

	paintIterationWithT3Filter(dc);
	eca->applyRule();
	currentIteration++;


	currentMemDc.Blit(0, 0,
					 panelSize - ringOffset, panelSize - ringOffset,
					 &helperMemDc,
					 ringOffset, ringOffset);

	helperMemDc.SelectObject(wxNullBitmap);
	currentMemDc.SelectObject(wxNullBitmap);
}

void SimulatorPanel::clearBitmap(wxBitmap& bitmap) {
	wxMemoryDC memDc(bitmap);
	memDc.SetBrush(*wxBLACK_BRUSH);
	memDc.Clear();
	memDc.SelectObject(wxNullBitmap);
}

void SimulatorPanel::timerEvent(wxTimerEvent& evt) {
	if(toggleAnimation) {
		if(filterOn) {
			createBitmapWithT3Filter();
		}
		else {
			createBitmap();
		}
		Refresh();
	}
}

void SimulatorPanel::OnKeyDown(wxKeyEvent& evt) {
	bool curPaintActive = toggleAnimation;
	
	switch ((int)evt.GetKeyCode()) {
	case 'n':
	case 'N':
		toggleAnimation = false;
		if (wxMessageBox("Create new random initial condition?", "Confirm", wxYES_NO | wxYES_DEFAULT, this) == wxYES) {
			eca->initialCondition = eca->CreateRandomInitialCondition(eca->N);
			eca->currentState = eca->initialCondition;
			if(filterOn) {
				initializeFilterGroup();
			}
			currentIteration = 0;
			clearBitmap(currentBitmap);
			enable3d = false;
			curPaintActive = true;
		}
		toggleAnimation = curPaintActive;
		break;
	case WXK_SPACE:
		enable3d = !enable3d;
		break;
	case 'p':
	case 'P':
		toggleAnimation = !toggleAnimation;
		break;
	case 'r':
	case 'R':
		toggleAnimation = false;
		if (wxMessageBox("Restart ECA?", "Confirm", wxYES_NO | wxYES_DEFAULT, this) == wxYES) {
			eca->currentState = eca->initialCondition;
			if (filterOn) {
				initializeFilterGroup();
			}
			currentIteration = 0;
			clearBitmap(currentBitmap);
			enable3d = false;
			curPaintActive = true;
		}
		toggleAnimation = curPaintActive;
		break;
	case 'f':
	case 'F':
		/*filterOn = !filterOn;
		Refresh();*/
		break;
	case 's':
	case 'S':
		toggleAnimation = false;
		saveToImage();
		toggleAnimation = curPaintActive;
		break;
	}
	evt.Skip();
}

void SimulatorPanel::saveToImage() {
	wxFileDialog saveFileDialog(this, _("Save file"), wxGetCwd(), "",
								"PNG files (*.png)|*.png", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (saveFileDialog.ShowModal() == wxID_CANCEL) {
		return;
	}
	currentBitmap.SaveFile(saveFileDialog.GetPath(), wxBITMAP_TYPE_PNG);
}

void SimulatorPanel::paintIterationWithT3Filter(wxDC& dc) {
	filterT3();
	paintIteration(dc);
}

void SimulatorPanel::filterT3() {
	string f1 = "";
	string f2 = "";
	string f3 = "";
	string f4 = "";

	int n = eca->N;

	for (int i = 0; i < n; i++) {
		f1 = iterationGroup[0].at(i);
		f1 += iterationGroup[0].at((i + 1) % n);
		f1 += iterationGroup[0].at((i + 2) % n);
		f1 += iterationGroup[0].at((i + 3) % n);

		f2 = iterationGroup[1].at(i);
		f2 += iterationGroup[1].at((i + 1) % n);
		f2 += iterationGroup[1].at((i + 2) % n);
		f2 += iterationGroup[1].at((i + 3) % n);

		f3 = iterationGroup[2].at(i);
		f3 += iterationGroup[2].at((i + 1) % n);
		f3 += iterationGroup[2].at((i + 2) % n);
		f3 += iterationGroup[2].at((i + 3) % n);

		f4 = iterationGroup[3].at(i);
		f4 += iterationGroup[3].at((i + 1) % n);

		if (f1.compare("1111") == 0 && f2.compare("1000") == 0 && f3.compare("1001") == 0 && f4.compare("10") == 0) {
			filterGroup[0][i] = '1';
			filterGroup[0][(i + 1) % n] = '1';
			filterGroup[0][(i + 2) % n] = '1';
			filterGroup[0][(i + 3) % n] = '1';

			filterGroup[1][i] = '1';
			filterGroup[1][(i + 1) % n] = '2';
			filterGroup[1][(i + 2) % n] = '2';
			filterGroup[1][(i + 3) % n] = '2';

			filterGroup[2][i] = '1';
			filterGroup[2][(i + 1) % n] = '2';
			filterGroup[2][(i + 2) % n] = '2';
			filterGroup[2][(i + 3) % n] = '1';

			filterGroup[3][i] = '1';
			filterGroup[3][(i + 1) % n] = '2';
		}
	}
}

void SimulatorPanel::paintIteration(wxDC& dc) {
	double currentDegree = 0;
	double newDegree = 0;
	const double degreeIncrement = 360 / (double)(eca->N);
	
	for (int i = 0; i < eca->N; i++) {
		if (filterGroup[0].at(i) == '1') {
			dc.SetPen(*filterExteriorPenColor);
		}
		else if (filterGroup[0].at(i) == '2') {
			dc.SetPen(*filterInteriorPenColor);
		}
		else if (iterationGroup[0].at(i) == '1') {
			dc.SetPen(*aliveCellPenColor);
		}
		else {
			dc.SetPen(*deadCellPenColor);
		}
		newDegree += degreeIncrement;
		dc.DrawEllipticArc(ringCenter.x - ringRadius, ringCenter.y - ringRadius, 2 * ringRadius, 2 * ringRadius,
			currentDegree, newDegree);
		currentDegree = newDegree;
	}

	iterationGroup[0] = iterationGroup[1];
	iterationGroup[1] = iterationGroup[2];
	iterationGroup[2] = iterationGroup[3];
	iterationGroup[3] = eca->currentState;

	filterGroup[0] = filterGroup[1];
	filterGroup[1] = filterGroup[2];
	filterGroup[2] = filterGroup[3];
	filterGroup[3] = string(eca->N, '0');
}

void SimulatorPanel::initializeFilterGroup() {
	for (int i = 0; i < 4; i++) {
		iterationGroup[i] = eca->currentState;
		filterGroup[i] = string(eca->N, '0');
		eca->applyRule();
	}
}
