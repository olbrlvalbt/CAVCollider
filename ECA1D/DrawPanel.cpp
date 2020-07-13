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

	Connect(GetId(), wxEVT_PAINT, wxPaintEventHandler(DrawPanel::paintEvent));
	Connect(GetId(), wxEVT_CHAR_HOOK, wxKeyEventHandler(DrawPanel::OnKeyDown));
	wxInitAllImageHandlers();

	//SetScrollbars(1, 1, eca->N * cellSize, numIterations * cellSize, 0, 0);
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	SetClientSize(eca->N * cellSize, numIterations * cellSize);
}

void DrawPanel::paintEvent(wxPaintEvent & evt) {
	if (shouldRedraw) {
		wxAutoBufferedPaintDC dc(this);
		render(dc);
	}
}

void DrawPanel::render(wxDC& dc) {
	wxProgressDialog* progress = new wxProgressDialog("Rendering", "Processing image, please wait", numIterations, GetParent(), wxPD_AUTO_HIDE);
	
	dc.DrawText(wxT("Rule " + to_string(eca->ruleNumber)), 10, 10);
	dc.DrawText(wxT("N = " + to_string(eca->N)), 100, 10);
	dc.DrawText(wxT("Iterations " + to_string((currentShowingIteration - 1) * numIterations)
		+ " through " + to_string((currentShowingIteration)* numIterations)), 200, 10);

	dc.DrawText(wxT("" + to_string(currentShowingIteration)), 500, 10);

	dc.SetPen(wxPen(wxColor(0, 0, 0), 1, wxPENSTYLE_TRANSPARENT));

	for (int j = 0; j < numIterations; j++) {
		progress->Update(j);

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
		//wxMilliSleep(1);
	}
	shouldRedraw = false;

	saveToImage(dc);
	progress->Update(numIterations);
}

bool DrawPanel::saveToImage(wxDC& dc) {
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
			eca->initialCondition = eca->createRandomInitialCondition(eca->N);
			eca->currentState = eca->initialCondition;
			currentShowingIteration = 1;
			shouldRedraw = true;
			Refresh();
		}
		break;
	case WXK_SPACE:
		currentShowingIteration++;
		shouldRedraw = true;
		Refresh();
		break;
	case 'r':
	case 'R':
		eca->currentState = eca->initialCondition;
		currentShowingIteration = 1;
		shouldRedraw = true;
		Refresh();
		break;
	case 's':
	case 'S':
		//saveToImage();
		break;
	}
	event.Skip();
}
