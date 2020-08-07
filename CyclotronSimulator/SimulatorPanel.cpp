#include "SimulatorPanel.h"

SimulatorPanel::SimulatorPanel(wxWindow * parent, EcaLogic * ecaLogic,
							   int _ringRadius = 500, int _panelSize = 1500,
							   wxColour _deadCellColor = wxColour(220, 170, 15),
							   wxColour _aliveCellColor = wxColour(115, 35, 15),
							   wxColour _filterExteriorColor = wxColour(15, 15, 95),
							   wxColour _filterInteriorColor = wxColour(45, 45, 120))
	: wxScrolledWindow(parent) {
	eca = ecaLogic;
	ringRadius = _ringRadius;
	panelSize = _panelSize;
	ringCenter = wxPoint(panelSize / 2, panelSize / 2);
	deadCellPenColor = new wxPen(_deadCellColor, ringWidth);
	deadCellPenColor->SetCap(wxCAP_BUTT);
	aliveCellPenColor = new wxPen(_aliveCellColor, ringWidth);
	aliveCellPenColor->SetCap(wxCAP_BUTT);
	filterExteriorPenColor = new wxPen(_filterExteriorColor, ringWidth);
	filterInteriorPenColor = new wxPen(_filterInteriorColor, ringWidth);

	wxInitAllImageHandlers();
	SetBackgroundStyle(wxBG_STYLE_PAINT);

	bitmap = new wxBitmap(panelSize, panelSize);
	clearBitmap();

	Connect(GetId(), wxEVT_PAINT, wxPaintEventHandler(SimulatorPanel::paintEvent));
	Connect(GetId(), wxEVT_KEY_DOWN, wxKeyEventHandler(SimulatorPanel::OnKeyDown));
	//Connect(GetId(), wxEVT_KEY_DOWN, wxKeyEventHandler(SimulatorPanel::OnKeyDown));


	SetClientSize(panelSize, panelSize);
	//SetScrollbars(1, 1, panelSize, panelSize, 0, 0);

	paintTimer.SetOwner(this);
	paintTimer.Start(50);

	Connect(paintTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(SimulatorPanel::timerEvent));
	
	/*wxProgressDialog* progress = new wxProgressDialog("Rendering", "Processing image, please wait",
													  200, nullptr, wxPD_AUTO_HIDE);
	for (int i = 0; i < 200; i++) {
		createBitmap();
		//createBitmapWithT3Filter();
		progress->Update(i + 1);
	}*/
}

void SimulatorPanel::paintEvent(wxPaintEvent & evt) {
	render();
}

void SimulatorPanel::render() {
	wxBufferedPaintDC paintDC(this);
	DoPrepareDC(paintDC);
	paintDC.DrawBitmap(*bitmap, 0, 0, true);
	if (filterOn) {
		paintDC.DrawBitmap(*filterBitmap, 0, 0, true);
	}
}

void SimulatorPanel::createBitmap() {
	wxBitmap newBitmap(panelSize, panelSize);

	wxMemoryDC memDc(newBitmap);
	wxGCDC dc(memDc);
	memDc.SetBrush(*wxBLACK_BRUSH);
	memDc.Clear();

	if(enable3d) {
		wxMemoryDC previousDc(*bitmap);
		memDc.Blit(0, 0,
				   panelSize - ringOffset, panelSize - ringOffset,
				   &previousDc,
				   ringOffset, ringOffset);
		previousDc.SelectObject(wxNullBitmap);
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

	/*GetParent()->SetLabel("ECA R" + to_string(eca->ruleNumber) + ", N: " + to_string(eca->N)
		+ ", Iterations " + to_string((currentShowingIteration - 1) * numIterations)
		+ "-" + to_string(currentShowingIteration * numIterations - 1)
		+ " (" + to_string(currentShowingIteration) + ")");*/

	memDc.SelectObject(wxNullBitmap);

	bitmap = new wxBitmap(newBitmap);
	//bitmap->SaveFile("screenshot.png", wxBITMAP_TYPE_PNG);
}
void SimulatorPanel::clearBitmap() {
	wxMemoryDC memDc(*bitmap);
	memDc.SetBrush(*wxBLACK_BRUSH);
	memDc.Clear();
	memDc.SelectObject(wxNullBitmap);
}

void SimulatorPanel::timerEvent(wxTimerEvent& evt) {
	if(toggleAnimation) {
		createBitmap();
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
			clearBitmap();
			enable3d = false;
			curPaintActive = true;
		}
		toggleAnimation = curPaintActive;
		break;
	case WXK_SPACE:
		enable3d = true;
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
			clearBitmap();
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
	bitmap->SaveFile(saveFileDialog.GetPath(), wxBITMAP_TYPE_PNG);
}