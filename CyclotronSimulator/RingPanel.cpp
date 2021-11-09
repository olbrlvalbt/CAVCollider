#include "RingPanel.h"
#include <chrono>
#include <sstream>
#include <thread>
#include <math.h>

RingPanel::RingPanel(wxWindow* parent, EcaRingConfiguration* config, bool _rule110T3filterEnabled)
	: wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition,
					   wxDefaultSize, wxBORDER_SIMPLE) {
	enableRule110T3Filter = _rule110T3filterEnabled;
	cyclotronConfiguration = config;
	panelSize = 3 * cyclotronConfiguration->getRingRadius();
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

	aliveBitmap = wxBitmap(panelSize, panelSize);
	deadBitmap = wxBitmap(panelSize, panelSize);
	//filterAliveBitmap.UseAlpha();
	//filterDeadBitmap.UseAlpha();

	depthOnFilterOnBitmap = wxBitmap(panelSize, panelSize);
	depthOnFilterOffBitmap = wxBitmap(panelSize, panelSize);
	//depthOnFilterOnBitmap.UseAlpha();
	//depthOnFilterOffBitmap.UseAlpha();

	maskColour = *wxGREEN;

	if(enableRule110T3Filter) {
		initializeFilterGroup();
	}

	Connect(GetId(), wxEVT_PAINT, wxPaintEventHandler(RingPanel::paintEvent));
	Connect(GetId(), wxEVT_KEY_DOWN, wxKeyEventHandler(RingPanel::OnKeyDown));

	SetClientSize(panelSize, panelSize);
	SetScrollbars(1, 1, panelSize, panelSize, 0, 0);

	paintTimer.SetOwner(this);
	paintTimer.Start(cyclotronConfiguration->getRefreshRate());

	Connect(paintTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(RingPanel::timerEvent));
}

RingPanel::~RingPanel() {
	delete cyclotronConfiguration;
}

void RingPanel::paintEvent(wxPaintEvent & evt) {
	render();
}

void RingPanel::render() {
	wxBufferedPaintDC paintDC(this);
	DoPrepareDC(paintDC);
	paintDC.DrawBitmap(currentBitmap, 0, 0, true);
}

void RingPanel::createBitmap() {
	wxMemoryDC dc(helperBitmap);
	dc.SetBrush(*wxBLACK_BRUSH);
	dc.Clear();
	wxMemoryDC currentMemDc(currentBitmap);

	if (enable3d) {
		dc.Blit(0, 0,
						 panelSize - cyclotronConfiguration->getRingOffset(), panelSize - cyclotronConfiguration->getRingOffset(),
						 &currentMemDc,
						 cyclotronConfiguration->getRingOffset(), cyclotronConfiguration->getRingOffset());
	}

	dc.SetBrush(*wxTRANSPARENT_BRUSH);

	dc.SetPen(cyclotronConfiguration->getDeadCellPen());
	dc.DrawEllipticArc(ringCenter.x - cyclotronConfiguration->getRingRadius(), ringCenter.y - cyclotronConfiguration->getRingRadius(),
		2 * cyclotronConfiguration->getRingRadius(), 2 * cyclotronConfiguration->getRingRadius(),
		0, 360);
	
	dc.SetPen(cyclotronConfiguration->getAliveCellPen());
	
	double currentDegree = 0;
	double newDegree = 0;
	const double degreeIncrement = 360 / (double)(cyclotronConfiguration->getEca().getN());
	int counter = 0;
	int i = 0;
	for (const string& st : cyclotronConfiguration->getEca().getCurrentState()) {
		for (const char& c : st) {
			if (c == '1') {
				counter++;
			}
			else {
				if (counter != 0) {
					dc.DrawEllipticArc(ringCenter.x - cyclotronConfiguration->getRingRadius(), ringCenter.y - cyclotronConfiguration->getRingRadius(),
						2 * cyclotronConfiguration->getRingRadius(), 2 * cyclotronConfiguration->getRingRadius(),
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
	
	
	cyclotronConfiguration->getEca().applyRule();

	currentMemDc.Blit(0, 0,
		 			  panelSize - cyclotronConfiguration->getRingOffset(), panelSize - cyclotronConfiguration->getRingOffset(),
					  &dc,
					  cyclotronConfiguration->getRingOffset(), cyclotronConfiguration->getRingOffset());

	dc.SelectObject(wxNullBitmap);
	currentMemDc.SelectObject(wxNullBitmap);
}

void RingPanel::createBitmapWithT3Filter() {
	wxMemoryDC dc(helperBitmap);
	dc.SetBackground(*wxBLACK_BRUSH);
	dc.Clear();
	wxMemoryDC currentMemDc(currentBitmap);

	if (enable3d) {
		dc.Blit(0, 0,
						 panelSize - cyclotronConfiguration->getRingOffset(), panelSize - cyclotronConfiguration->getRingOffset(),
						 &currentMemDc,
					 	 cyclotronConfiguration->getRingOffset(), cyclotronConfiguration->getRingOffset());
	}

	dc.SetBrush(*wxTRANSPARENT_BRUSH);

	paintIterationWithT3Filter(dc);
	cyclotronConfiguration->getEca().applyRule();
	currentIteration++;


	currentMemDc.Blit(0, 0,
					 panelSize - cyclotronConfiguration->getRingOffset(), panelSize - cyclotronConfiguration->getRingOffset(),
					 &dc,
					 cyclotronConfiguration->getRingOffset(), cyclotronConfiguration->getRingOffset());

	dc.SelectObject(wxNullBitmap);
	currentMemDc.SelectObject(wxNullBitmap);
}

void RingPanel::clearBitmap(wxBitmap& bitmap) {
	wxMemoryDC memDc(bitmap);
	memDc.SetBrush(*wxBLACK_BRUSH);
	memDc.Clear();
	memDc.SelectObject(wxNullBitmap);
}

void RingPanel::timerEvent(wxTimerEvent& evt) {
	if(toggleAnimation) {
		if(enableRule110T3Filter) {
			createBitmapWithT3Filter();
		}
		else {
			createBitmap();
		}

		GetParent()->SetLabel(wxT(
			"ECA R" + to_string(cyclotronConfiguration->getEca().getRuleNumber()) +
			" - N: " + to_string(cyclotronConfiguration->getEca().getN())
			+ " - " + to_string(cyclotronConfiguration->getEca().getCurrentIteration())
		));
		
		Refresh();
	}
}

void RingPanel::OnKeyDown(wxKeyEvent& evt) {
	
	switch ((int)evt.GetKeyCode()) {
	case 'n':
	case 'N':
		reset();
		break;
	case WXK_SPACE:
		toggle3D();
		break;
	case 'p':
	case 'P':
		playPause();
		break;
	case 'r':
	case 'R':
		restart();
		break;
	case 'f':
	case 'F':
		/*filterOn = !filterOn;
		Refresh();*/
		break;
	case 's':
	case 'S':
		saveToImage();
		break;
	}
	evt.Skip();
}

void RingPanel::saveToImage() {
	bool curPaintActive = toggleAnimation;
	toggleAnimation = false;
	
	wxFileDialog saveFileDialog(this, _("Save file"), wxGetCwd(), "",
								"PNG files (*.png)|*.png", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (saveFileDialog.ShowModal() == wxID_CANCEL) {
		return;
		}
	currentBitmap.SaveFile(saveFileDialog.GetPath(), wxBITMAP_TYPE_PNG);
	
	toggleAnimation = curPaintActive;
}

void RingPanel::paintIterationWithT3Filter(wxDC& dc) {
	filterT3();
	paintIteration(dc);
}

void RingPanel::filterT3() {
	string f1 = "";
	string f2 = "";
	string f3 = "";
	string f4 = "";

	int n = cyclotronConfiguration->getEca().getN();

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

void RingPanel::paintIteration(wxDC& dc) {
	try {
		wxMemoryDC aliveDc(aliveBitmap);
		aliveDc.SetBackground(maskColour);
		aliveDc.Clear();
		aliveDc.SetBrush(*wxTRANSPARENT_BRUSH);
		aliveDc.SetPen(cyclotronConfiguration->getAliveCellPen());
		
		wxMemoryDC deadDc(deadBitmap);
		deadDc.SetBackground(maskColour);
		deadDc.Clear();
		deadDc.SetBrush(*wxTRANSPARENT_BRUSH);
		deadDc.SetPen(cyclotronConfiguration->getDeadCellPen());

		dc.SetPen(*wxBLACK_PEN);
		dc.DrawEllipticArc(ringCenter.x - cyclotronConfiguration->getRingRadius(), ringCenter.y - cyclotronConfiguration->getRingRadius(),
			2 * cyclotronConfiguration->getRingRadius(), 2 * cyclotronConfiguration->getRingRadius(),
			0, 360);

		/*thread aliveThread(&RingPanel::paintMask, this, ref(aliveDc), '1');
		thread deadThread(&RingPanel::paintMask, this, ref(deadDc), '0');

		aliveThread.join();
		deadThread.join();*/

		paintMask(aliveDc, '1');
		paintMask(deadDc, '0');

		aliveDc.SelectObject(wxNullBitmap);
		aliveBitmap.SetMask(new wxMask(aliveBitmap, maskColour));
		wxMemoryDC aliveMemDcc(aliveBitmap);
		dc.Blit(0, 0,
			panelSize, panelSize,
			&aliveMemDcc,
			0, 0, wxCOPY, true);
		aliveBitmap.SetMask(NULL);

		deadDc.SelectObject(wxNullBitmap);
		deadBitmap.SetMask(new wxMask(deadBitmap, maskColour));
		wxMemoryDC deadMemDcc(deadBitmap);
		dc.Blit(0, 0,
			panelSize, panelSize,
			&deadMemDcc,
			0, 0, wxCOPY, true);
		deadBitmap.SetMask(NULL);

		iterationGroup[0] = iterationGroup[1];
		iterationGroup[1] = iterationGroup[2];
		iterationGroup[2] = iterationGroup[3];
		string s = "";
		for (const string& a : cyclotronConfiguration->getEca().getCurrentState()) {
			s += a;
		}
		iterationGroup[3] = s;

		filterGroup[0] = filterGroup[1];
		filterGroup[1] = filterGroup[2];
		filterGroup[2] = filterGroup[3];
		filterGroup[3] = string(cyclotronConfiguration->getEca().getN(), '0');
	}
	catch(exception ex) {
		int tr;
	}
}

void RingPanel::paintMask(wxMemoryDC& memDc, char flag) {
	double currentDegree = 0;
	double newDegree = 0;
	const double degreeIncrement = 360 / (double)(cyclotronConfiguration->getEca().getN());

	/*const double radianIncrement = degreeIncrement * M_PI / 180;
	
	for (int i = 0; i < cyclotronConfiguration->getEca().getN(); i++) {
		if (filterGroup[0].at(i) == '0' && iterationGroup[0].at(i) == flag) {
			double projX = cyclotronConfiguration->getRingRadius() * std::cos(i * radianIncrement);
			double projY = cyclotronConfiguration->getRingRadius() * std::sin(i * radianIncrement);
			memDc.DrawPoint(ringCenter.x + projX, ringCenter.y + projY);
		}
	}*/
	int acc = 0;
	
	for (int i = 0; i < cyclotronConfiguration->getEca().getN(); i++) {
		if (filterGroup[0].at(i) == '0') {
			if (iterationGroup[0].at(i) == flag) {
				acc++;
				continue;
			}
		}
		if (acc > 0) {
			memDc.DrawEllipticArc(ringCenter.x - cyclotronConfiguration->getRingRadius(), ringCenter.y - cyclotronConfiguration->getRingRadius(),
				2 * cyclotronConfiguration->getRingRadius(), 2 * cyclotronConfiguration->getRingRadius(),
				(i - acc) * degreeIncrement, i * degreeIncrement);
			acc = 0;
		}
	}
	if (acc > 0) {
		memDc.DrawEllipticArc(ringCenter.x - cyclotronConfiguration->getRingRadius(), ringCenter.y - cyclotronConfiguration->getRingRadius(),
			2 * cyclotronConfiguration->getRingRadius(), 2 * cyclotronConfiguration->getRingRadius(),
			(cyclotronConfiguration->getEca().getN() - acc) * degreeIncrement, cyclotronConfiguration->getEca().getN() * degreeIncrement);
	}
}

void RingPanel::initializeFilterGroup() {
	for (int i = 0; i < 4; i++) {
		string s = "";
		for (const string& a : cyclotronConfiguration->getEca().getCurrentState()) {
			s += a;
		}
		iterationGroup[i] = s;
		filterGroup[i] = string(cyclotronConfiguration->getEca().getN(), '0');
		cyclotronConfiguration->getEca().applyRule();
	}
}


void RingPanel::playPause() {
	toggleAnimation = !toggleAnimation;
}

void RingPanel::toggle3D() {
	enable3d = !enable3d;
}

void RingPanel::toggleFilter() {

}

void RingPanel::restart() {
	bool curPaintActive = toggleAnimation;
	toggleAnimation = false;
	
	if (wxMessageBox("Restart ECA?", "Confirm", wxYES_NO | wxYES_DEFAULT, this) == wxYES) {
		cyclotronConfiguration->getEca().restart();
		if (enableRule110T3Filter) {
			initializeFilterGroup();
		}
		currentIteration = 0;
		clearBitmap(currentBitmap);
		enable3d = false;
		curPaintActive = true;
	}
	
	toggleAnimation = curPaintActive;
}

void RingPanel::reset() {
	bool curPaintActive = toggleAnimation;
	toggleAnimation = false;
	
	if (wxMessageBox("Create new random initial condition?", "Confirm", wxYES_NO | wxYES_DEFAULT, this) == wxYES) {
		cyclotronConfiguration->getEca().reset();
		if (enableRule110T3Filter) {
			initializeFilterGroup();
		}
		currentIteration = 0;
		clearBitmap(currentBitmap);
		enable3d = false;
		curPaintActive = true;
	}
	
	toggleAnimation = curPaintActive;
}