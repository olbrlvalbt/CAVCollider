#include "DrawPanel.h"

DrawPanel::DrawPanel(wxWindow * parent, EcaLogic * ecaLogic, int _numIterations,
					 int _cellSize = 1,
					 wxColour _deadCellColor = wxColour(220, 170, 15),
					 wxColour _aliveCellColor = wxColour(115, 35, 15))
		 : wxScrolledWindow(parent) {
	eca = ecaLogic;
	numIterations = _numIterations;
	cellSize = _cellSize;
	deadCellBrushColor = new wxBrush(_deadCellColor);
	aliveCellBrushColor = new wxBrush(_aliveCellColor);

	wxInitAllImageHandlers();
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	createBitmap();

	Connect(GetId(), wxEVT_PAINT, wxPaintEventHandler(DrawPanel::paintEvent));
	Connect(GetId(), wxEVT_KEY_DOWN, wxKeyEventHandler(DrawPanel::OnKeyDown));


	SetClientSize(eca->N * cellSize, numIterations * cellSize);
	SetScrollbars(1, 1, eca->N * cellSize, numIterations * cellSize, 0, 0);
}

void DrawPanel::paintEvent(wxPaintEvent & evt) {
	render();
}

void DrawPanel::render() {
	wxClientDC paintDC(this);
	DoPrepareDC(paintDC);
	paintDC.DrawBitmap(*bitmap, 0, 0, true);
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
			createBitmap();
			Refresh();
		}
		break;
	case WXK_SPACE:
		currentShowingIteration++;
		createBitmap();
		Refresh();
		break;
	case 'r':
	case 'R':
		eca->currentState = eca->initialCondition;
		currentShowingIteration = 1;
		createBitmap();
		Refresh();
		break;
	case 's':
	case 'S':
		//saveToImage();
		break;
	}
	event.Skip();
}
