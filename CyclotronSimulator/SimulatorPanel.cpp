#include "SimulatorPanel.h"
#include <chrono>
#include <sstream>

SimulatorPanel::SimulatorPanel(wxWindow * parent, EcaController* ecaController, CyclotronConfiguration* config)
	: wxScrolledWindow(parent) {
	eca = ecaController;
	cyclotronConfiguration = config;
	panelSize = 3 * cyclotronConfiguration->ringRadius;
	ringCenter = wxPoint(panelSize / 2, panelSize / 2);

	wxInitAllImageHandlers();
	SetBackgroundStyle(wxBG_STYLE_PAINT);

	currentBitmap = wxBitmap(panelSize, panelSize);
	helperBitmap = wxBitmap(panelSize, panelSize);
	clearBitmap(currentBitmap);
	clearBitmap(helperBitmap);

	baseBitmap = wxBitmap(panelSize, panelSize);
	//baseBitmap.UseAlpha();

	filterAliveBitmap = wxBitmap(panelSize, panelSize);
	filterDeadBitmap = wxBitmap(panelSize, panelSize);
	//filterAliveBitmap.UseAlpha();
	//filterDeadBitmap.UseAlpha();

	depthOnFilterOnBitmap = wxBitmap(panelSize, panelSize);
	depthOnFilterOffBitmap = wxBitmap(panelSize, panelSize);
	//depthOnFilterOnBitmap.UseAlpha();
	//depthOnFilterOffBitmap.UseAlpha();

	maskColour = *wxGREEN;

	if(cyclotronConfiguration->enableRule110T3Filter) {
		initializeFilterGroup();
	}

	Connect(GetId(), wxEVT_PAINT, wxPaintEventHandler(SimulatorPanel::paintEvent));
	Connect(GetId(), wxEVT_KEY_DOWN, wxKeyEventHandler(SimulatorPanel::OnKeyDown));

	SetClientSize(panelSize, panelSize);
	SetScrollbars(1, 1, panelSize, panelSize, 0, 0);

	paintTimer.SetOwner(this);
	paintTimer.Start(cyclotronConfiguration->refreshRate);

	Connect(paintTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(SimulatorPanel::timerEvent));
}

SimulatorPanel::~SimulatorPanel() {
	delete eca;
}

void SimulatorPanel::paintEvent(wxPaintEvent & evt) {
	render();
}

void SimulatorPanel::render() {
	wxBufferedPaintDC paintDC(this);
	DoPrepareDC(paintDC);
	paintDC.DrawBitmap(currentBitmap, 0, 0, true);
}

void SimulatorPanel::createBitmap() {
	wxMemoryDC dc(helperBitmap);
	dc.SetBrush(*wxBLACK_BRUSH);
	dc.Clear();
	wxMemoryDC currentMemDc(currentBitmap);

	if (enable3d) {
		dc.Blit(0, 0,
						 panelSize - cyclotronConfiguration->ringOffset, panelSize - cyclotronConfiguration->ringOffset,
						 &currentMemDc,
						 cyclotronConfiguration->ringOffset, cyclotronConfiguration->ringOffset);
	}

	dc.SetBrush(*wxTRANSPARENT_BRUSH);

	dc.SetPen(cyclotronConfiguration->deadCellPenColor);
	dc.DrawEllipticArc(ringCenter.x - cyclotronConfiguration->ringRadius, ringCenter.y - cyclotronConfiguration->ringRadius,
		2 * cyclotronConfiguration->ringRadius, 2 * cyclotronConfiguration->ringRadius,
		0, 360);
	
	dc.SetPen(cyclotronConfiguration->aliveCellPenColor);
	
	double currentDegree = 0;
	double newDegree = 0;
	const double degreeIncrement = 360 / (double)(eca->getN());
	int counter = 0;
	int i = 0;
	for (const string& st : eca->getCurrentState()) {
		for (const char& c : st) {
			if (c == '1') {
				counter++;
			}
			else {
				if (counter != 0) {
					dc.DrawEllipticArc(ringCenter.x - cyclotronConfiguration->ringRadius, ringCenter.y - cyclotronConfiguration->ringRadius,
						2 * cyclotronConfiguration->ringRadius, 2 * cyclotronConfiguration->ringRadius,
						(i - counter) * degreeIncrement, i * degreeIncrement);

					counter = 0;
				}
			}
			i++;
		}
	}


	/*int i = 0;
	double currentDegree = 0;
	double newDegree = 0;
	const double degreeIncrement = 360 / (double)(eca->getN());

	for (const string& st : eca->getCurrentState()) {
		for (const char& c : st) {
			if (c == '1') {
				dc.SetPen(cyclotronConfiguration->aliveCellPenColor);
			}
			else {
				dc.SetPen(cyclotronConfiguration->deadCellPenColor);
			}
			newDegree += degreeIncrement;
			dc.DrawEllipticArc(ringCenter.x - cyclotronConfiguration->ringRadius, ringCenter.y - cyclotronConfiguration->ringRadius, 2 * cyclotronConfiguration->ringRadius, 2 * cyclotronConfiguration->ringRadius,
				currentDegree, newDegree);
			currentDegree = newDegree;
			i++;
		}
	}*/
	
	
	eca->applyRule();

	currentMemDc.Blit(0, 0,
		 			  panelSize - cyclotronConfiguration->ringOffset, panelSize - cyclotronConfiguration->ringOffset,
					  &dc,
					  cyclotronConfiguration->ringOffset, cyclotronConfiguration->ringOffset);

	dc.SelectObject(wxNullBitmap);
	currentMemDc.SelectObject(wxNullBitmap);
}

void SimulatorPanel::createBitmapWithT3Filter() {
	wxMemoryDC dc(helperBitmap);
	dc.SetBackground(*wxBLACK_BRUSH);
	dc.Clear();
	wxMemoryDC currentMemDc(currentBitmap);

	if (enable3d) {
		dc.Blit(0, 0,
						 panelSize - cyclotronConfiguration->ringOffset, panelSize - cyclotronConfiguration->ringOffset,
						 &currentMemDc,
					 	 cyclotronConfiguration->ringOffset, cyclotronConfiguration->ringOffset);
	}

	dc.SetBrush(*wxTRANSPARENT_BRUSH);

	paintIterationWithT3Filter(dc);
	eca->applyRule();
	currentIteration++;


	currentMemDc.Blit(0, 0,
					 panelSize - cyclotronConfiguration->ringOffset, panelSize - cyclotronConfiguration->ringOffset,
					 &dc,
					 cyclotronConfiguration->ringOffset, cyclotronConfiguration->ringOffset);

	dc.SelectObject(wxNullBitmap);
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
		if(cyclotronConfiguration->enableRule110T3Filter) {
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
			eca->reset();
			if(cyclotronConfiguration->enableRule110T3Filter) {
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
			eca->restart();
			if (cyclotronConfiguration->enableRule110T3Filter) {
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

	int n = eca->getN();

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
	try {
		wxMemoryDC filterAliveDc(filterAliveBitmap);
		filterAliveDc.SetBackground(maskColour);
		filterAliveDc.Clear();
		filterAliveDc.SetBrush(*wxTRANSPARENT_BRUSH);
		filterAliveDc.SetPen(cyclotronConfiguration->filterExteriorPenColor);
		
		wxMemoryDC filterDeadDc(filterDeadBitmap);
		filterDeadDc.SetBackground(maskColour);
		filterDeadDc.Clear();
		filterDeadDc.SetBrush(*wxTRANSPARENT_BRUSH);
		filterDeadDc.SetPen(cyclotronConfiguration->filterInteriorPenColor);

		dc.SetPen(cyclotronConfiguration->deadCellPenColor);
		dc.DrawEllipticArc(ringCenter.x - cyclotronConfiguration->ringRadius, ringCenter.y - cyclotronConfiguration->ringRadius,
			2 * cyclotronConfiguration->ringRadius, 2 * cyclotronConfiguration->ringRadius,
			0, 360);
		
		dc.SetPen(cyclotronConfiguration->aliveCellPenColor);

		double currentDegree = 0;
		double newDegree = 0;
		const double degreeIncrement = 360 / (double)(eca->getN());

		for (int i = 0; i < eca->getN(); i++) {
			if (filterGroup[0].at(i) == '1') {
				filterAliveDc.DrawEllipticArc(ringCenter.x - cyclotronConfiguration->ringRadius, ringCenter.y - cyclotronConfiguration->ringRadius,
					2 * cyclotronConfiguration->ringRadius, 2 * cyclotronConfiguration->ringRadius,
					(i - 1) * degreeIncrement, i * degreeIncrement);
			}
			else if (filterGroup[0].at(i) == '2') {
				filterDeadDc.DrawEllipticArc(ringCenter.x - cyclotronConfiguration->ringRadius, ringCenter.y - cyclotronConfiguration->ringRadius,
					2 * cyclotronConfiguration->ringRadius, 2 * cyclotronConfiguration->ringRadius,
					(i - 1) * degreeIncrement, i * degreeIncrement);
			}
			else if (iterationGroup[0].at(i) == '1') {
				dc.DrawEllipticArc(ringCenter.x - cyclotronConfiguration->ringRadius, ringCenter.y - cyclotronConfiguration->ringRadius,
					2 * cyclotronConfiguration->ringRadius, 2 * cyclotronConfiguration->ringRadius,
					(i - 1) * degreeIncrement, i * degreeIncrement);
			}
		}


		filterAliveBitmap.SaveFile("D:\\olbrl\\Downloads\\Gg\\img1.png", wxBITMAP_TYPE_PNG);
		filterDeadBitmap.SaveFile("D:\\olbrl\\Downloads\\Gg\\img2.png", wxBITMAP_TYPE_PNG);
		helperBitmap.SaveFile("D:\\olbrl\\Downloads\\Gg\\img3.png", wxBITMAP_TYPE_PNG);

		filterAliveDc.SelectObject(wxNullBitmap);
		filterAliveBitmap.SetMask(new wxMask(filterAliveBitmap, maskColour));
		wxMemoryDC filterAliveMemDcc(filterAliveBitmap);
		dc.Blit(0, 0,
			panelSize, panelSize,
			&filterAliveMemDcc,
			0, 0, wxCOPY, true);
		filterAliveBitmap.SetMask(NULL);

		filterDeadDc.SelectObject(wxNullBitmap);
		filterDeadBitmap.SetMask(new wxMask(filterDeadBitmap, maskColour));
		wxMemoryDC filterDeadMemDcc(filterDeadBitmap);
		dc.Blit(0, 0,
			panelSize, panelSize,
			&filterDeadMemDcc,
			0, 0, wxCOPY, true);
		filterDeadBitmap.SetMask(NULL);

		iterationGroup[0] = iterationGroup[1];
		iterationGroup[1] = iterationGroup[2];
		iterationGroup[2] = iterationGroup[3];
		string s = "";
		for (const string& a : eca->getCurrentState()) {
			s += a;
		}
		iterationGroup[3] = s;

		filterGroup[0] = filterGroup[1];
		filterGroup[1] = filterGroup[2];
		filterGroup[2] = filterGroup[3];
		filterGroup[3] = string(eca->getN(), '0');
	}
	catch(exception ex) {
		int tr;
	}
}

void SimulatorPanel::initializeFilterGroup() {
	for (int i = 0; i < 4; i++) {
		string s = "";
		for (const string& a : eca->getCurrentState()) {
			s += a;
		}
		iterationGroup[i] = s;
		filterGroup[i] = string(eca->getN(), '0');
		eca->applyRule();
	}
}
