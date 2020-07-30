#include "DrawPanel.h"

DrawPanel::DrawPanel(wxWindow * parent, EcaLogic * ecaLogic, int _numIterations,
					 int _cellSize = 1,
					 wxColour _deadCellColor = wxColour(220, 170, 15),
					 wxColour _aliveCellColor = wxColour(115, 35, 15),
					 wxColour _filterExteriorColor = wxColour(15, 15, 95),
					 wxColour _filterInteriorColor = wxColour(45, 45, 120))
		 : wxScrolledWindow(parent) {
	eca = ecaLogic;
	numIterations = _numIterations;
	cellSize = _cellSize;
	deadCellBrushColor = new wxBrush(_deadCellColor);
	aliveCellBrushColor = new wxBrush(_aliveCellColor);
	filterExteriorBrushColor = new wxBrush(_filterExteriorColor);
	filterInteriorBrushColor = new wxBrush(_filterInteriorColor);

	wxInitAllImageHandlers();
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	createBitmapWithT3Filter();

	Connect(GetId(), wxEVT_PAINT, wxPaintEventHandler(DrawPanel::paintEvent));
	Connect(GetId(), wxEVT_KEY_DOWN, wxKeyEventHandler(DrawPanel::OnKeyDown));


	SetClientSize(eca->N * cellSize, numIterations * cellSize);
	SetScrollbars(1, 1, eca->N * cellSize, numIterations * cellSize, 0, 0);
}

void DrawPanel::paintEvent(wxPaintEvent & evt) {
	render();
}

void DrawPanel::render() {
	wxBufferedPaintDC paintDC(this);
	DoPrepareDC(paintDC);
	paintDC.DrawBitmap(*bitmap, 0, 0, true);
	if (filterOn) {
		paintDC.DrawBitmap(*filterBitmap, 0, 0, true);
	}
}

void DrawPanel::createBitmap() {
	wxProgressDialog* progress = new wxProgressDialog("Rendering", "Processing image, please wait", 100, nullptr, wxPD_AUTO_HIDE);

	bitmap = new wxBitmap(eca->N * cellSize, numIterations * cellSize);

	wxMemoryDC dc(*bitmap);
	int k = 0;

	dc.SetPen(wxPen(wxColor(0, 0, 0), 1, wxPENSTYLE_TRANSPARENT));

	for (int j = 0; j < numIterations; j++) {
		if ((j * 100) % numIterations == 0) {
			progress->Update(k++);
		}

		for (int i = 0; i < eca->N; i++) {
			if (eca->currentState.at(i) == '1') {
				dc.SetBrush(*aliveCellBrushColor);
			}
			else {
				dc.SetBrush(*deadCellBrushColor);
			}
			dc.DrawRectangle(i * cellSize, j * cellSize, cellSize, cellSize);
		}

		eca->applyRule();
	}

	GetParent()->SetLabel("ECA R" + to_string(eca->ruleNumber) + ", N: " + to_string(eca->N)
		+ ", Iterations " + to_string((currentShowingIteration - 1) * numIterations)
		+ "-" + to_string(currentShowingIteration * numIterations - 1)
		+ " (" + to_string(currentShowingIteration) + ")");

	dc.SelectObject(wxNullBitmap);

	progress->Update(100);

	progress = new wxProgressDialog("Rendering", "Painting image, please wait", 100, nullptr, wxPD_AUTO_HIDE);

	bitmap->SaveFile("screenshot.png", wxBITMAP_TYPE_PNG);

	progress->Update(100);
}

void DrawPanel::createBitmapWithT3Filter() {
	wxProgressDialog* progress = new wxProgressDialog("Rendering", "Processing image, please wait", 100, nullptr, wxPD_AUTO_HIDE);

	bitmap = new wxBitmap(eca->N * cellSize, numIterations * cellSize);
	wxMemoryDC baseDc(*bitmap);
	baseDc.SetPen(wxPen(wxColor(0, 0, 0), 1, wxPENSTYLE_TRANSPARENT));


	filterBitmap = new wxBitmap(eca->N * cellSize, numIterations * cellSize, 32);
	filterBitmap->UseAlpha();
	wxMemoryDC filterMemDc(*filterBitmap);

	wxGCDC filterDc(filterMemDc);
	filterDc.SetBackground(*wxTRANSPARENT_BRUSH);
	filterDc.Clear();
	filterDc.SetPen(*wxTRANSPARENT_PEN);

	string iterationGroup[4] = { "", "", "", "" };


	int k = 0;
	int j = 0;

	for (; j < 4; j++) {
		if ((j * 100) % numIterations == 0) {
			progress->Update(k++);
		}

		paintIteration(baseDc, j);

		iterationGroup[j] = eca->currentState;
		eca->applyRule();
	}

	for (; j < numIterations; j++) {
		if ((j * 100) % numIterations == 0) {
			progress->Update(k++);
		}

		filterT3(iterationGroup, filterDc, j - 4);
		iterationGroup[0] = iterationGroup[1];
		iterationGroup[1] = iterationGroup[2];
		iterationGroup[2] = iterationGroup[3];
		iterationGroup[3] = eca->currentState;

		paintIteration(baseDc, j);

		eca->applyRule();
	}

	filterT3(iterationGroup, filterDc, j - 4);


	GetParent()->SetLabel("ECA R" + to_string(eca->ruleNumber) + ", N: " + to_string(eca->N)
		+ ", Iterations " + to_string((currentShowingIteration - 1) * numIterations)
		+ "-" + to_string(currentShowingIteration * numIterations - 1)
		+ " (" + to_string(currentShowingIteration) + ")");

	baseDc.SelectObject(wxNullBitmap);
	filterMemDc.SelectObject(wxNullBitmap);

	progress->Update(100);

	progress = new wxProgressDialog("Rendering", "Painting image, please wait", 100, nullptr, wxPD_AUTO_HIDE);

	bitmap->SaveFile("screenshot.png", wxBITMAP_TYPE_PNG);
	progress->Update(50);
	filterBitmap->SaveFile("screenshotFilter.png", wxBITMAP_TYPE_PNG);

	progress->Update(100);
}

void DrawPanel::paintIteration(wxDC& dc, int iteration) {
	for (int i = 0; i < eca->N; i++) {
		if (eca->currentState.at(i) == '1') {
			dc.SetBrush(*aliveCellBrushColor);
		}
		else {
			dc.SetBrush(*deadCellBrushColor);
		}
		dc.DrawRectangle(i * cellSize, iteration * cellSize, cellSize, cellSize);
	}
}

void DrawPanel::filterT3(string(&iterationGroup)[4], wxGCDC&filterDc, int iteration) {
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
			filterDc.SetBrush(*filterExteriorBrushColor);
			filterDc.DrawRectangle(i * cellSize, iteration * cellSize, cellSize, cellSize);
			filterDc.DrawRectangle(((i + 1) % n) * cellSize, iteration * cellSize, cellSize, cellSize);
			filterDc.DrawRectangle(((i + 2) % n) * cellSize, iteration * cellSize, cellSize, cellSize);
			filterDc.DrawRectangle(((i + 3) % n) * cellSize, iteration * cellSize, cellSize, cellSize);

			filterDc.DrawRectangle(i * cellSize, (iteration + 1) * cellSize, cellSize, cellSize);
			filterDc.SetBrush(*filterInteriorBrushColor);
			filterDc.DrawRectangle(((i + 1) % n) * cellSize, (iteration + 1) * cellSize, cellSize, cellSize);
			filterDc.DrawRectangle(((i + 2) % n) * cellSize, (iteration + 1) * cellSize, cellSize, cellSize);
			filterDc.DrawRectangle(((i + 3) % n) * cellSize, (iteration + 1) * cellSize, cellSize, cellSize);

			filterDc.SetBrush(*filterExteriorBrushColor);
			filterDc.DrawRectangle(i * cellSize, (iteration + 2) * cellSize, cellSize, cellSize);
			filterDc.SetBrush(*filterInteriorBrushColor);
			filterDc.DrawRectangle(((i + 1) % n) * cellSize, (iteration + 2) * cellSize, cellSize, cellSize);
			filterDc.DrawRectangle(((i + 2) % n) * cellSize, (iteration + 2) * cellSize, cellSize, cellSize);
			filterDc.SetBrush(*filterExteriorBrushColor);
			filterDc.DrawRectangle(((i + 3) % n) * cellSize, (iteration + 2) * cellSize, cellSize, cellSize);

			filterDc.DrawRectangle(i * cellSize, (iteration + 3) * cellSize, cellSize, cellSize);
			filterDc.SetBrush(*filterInteriorBrushColor);
			filterDc.DrawRectangle(((i + 1) % n) * cellSize, (iteration + 3) * cellSize, cellSize, cellSize);
		}
	}
}

bool DrawPanel::saveToImage(wxBufferedDC& dc) {
	wxBitmap *screenshot = new wxBitmap(eca->N * cellSize, numIterations * cellSize);

	wxMemoryDC memDC;

	memDC.SelectObject(*screenshot);
	memDC.Blit(0, //Copy to this X coordinate
		0, //Copy to this Y coordinate
		eca->N * cellSize, //Copy this width
		numIterations * cellSize, //Copy this height
		&dc, //From where do we copy?
		0, //What's the X offset in the original DC?
		0  //What's the Y offset in the original DC?
	);
	memDC.SelectObject(wxNullBitmap);

	screenshot->SaveFile("screenshot.jpg", wxBITMAP_TYPE_JPEG);
	delete screenshot;
	return true;
}

void DrawPanel::OnKeyDown(wxKeyEvent& event) {
	switch ((int)event.GetKeyCode()) {
	case 'n':
	case 'N':
		if (wxMessageBox("Create new random initial condition?", "Confirm", wxYES_NO | wxYES_DEFAULT, this) == wxYES) {
			eca->initialCondition = eca->CreateRandomInitialCondition(eca->N);
			eca->currentState = eca->initialCondition;
			currentShowingIteration = 1;
			createBitmapWithT3Filter();
			Refresh();
		}
		break;
	case WXK_SPACE:
		currentShowingIteration++;
		createBitmapWithT3Filter();
		Refresh();
		break;
	case 'r':
	case 'R':
		eca->currentState = eca->initialCondition;
		currentShowingIteration = 1;
		createBitmapWithT3Filter();
		Refresh();
		break;
	case 'f':
	case 'F':
		filterOn = !filterOn;
		Refresh();
		break;
	case 's':
	case 'S':
		//saveToImage();
		break;
	}
	event.Skip();
}
