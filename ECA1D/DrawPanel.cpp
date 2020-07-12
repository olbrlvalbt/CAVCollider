#include "DrawPanel.h"

DrawPanel::DrawPanel(wxFrame * parent, EcaLogic * ecaLogic, int _numIterations,
					 int _cellSize = 1, wxPoint* _panelOffset = new wxPoint(0, 30),
					 wxColour* _deadCellColor = new wxColour(115, 35, 15),
					 wxColour* _aliveCellColor = new wxColour(220, 170, 15))
		 : wxPanel(parent) {
	eca = ecaLogic;
	numIterations = _numIterations;
	cellSize = _cellSize;
	panelOffset = _panelOffset;
	deadCellBrushColor = new wxBrush(*_deadCellColor);
	deadCellBrushColor = new wxBrush(*_aliveCellColor);

	Connect(GetId(), wxEVT_PAINT, wxPaintEventHandler(DrawPanel::paintEvent));
	wxInitAllImageHandlers();
}

void DrawPanel::paintEvent(wxPaintEvent & evt) {
	if (shouldRedraw) {
		dc = new wxPaintDC(this);
		render();
	}
}

void DrawPanel::render() {
	//wxBrush* whiteBrush = new wxBrush(wxColor(200, 200, 200), wxBRUSHSTYLE_TRANSPARENT);
	//wxBrush* blackBrush = new wxBrush(wxColor(0, 0, 0), wxBRUSHSTYLE_TRANSPARENT);
	wxBrush* whiteBrush = new wxBrush(wxColor(220, 170, 15));
	wxBrush* blackBrush = new wxBrush(wxColor(115, 35, 15));

	dc->DrawText(wxT("Rule " + to_string(eca->ruleNumber)), 10, 10);
	dc->DrawText(wxT("N = " + to_string(eca->N)), 100, 10);
	dc->DrawText(wxT("Iterations " + to_string((currentShowingIteration - 1) * numIterations)
		+ " through " + to_string((currentShowingIteration)* numIterations)), 200, 10);

	dc->DrawText(wxT("" + to_string(currentShowingIteration)), 500, 10);

	dc->SetPen(wxPen(wxColor(0, 0, 0), 1, wxPENSTYLE_TRANSPARENT));

	for (int j = 0; j < numIterations; j++) {

		for (int i = 0; i < eca->N; i++) {
			if (eca->currentState.at(i) == '1') {
				dc->SetBrush(*blackBrush);
			}
			else {
				dc->SetBrush(*whiteBrush);
			}
			dc->DrawRectangle(i * cellSize + panelOffset->x, j * cellSize + panelOffset->y, cellSize, cellSize);
		}

		eca->applyRule();
		//wxMilliSleep(1);
	}
	shouldRedraw = false;

	saveToImage();
}

bool DrawPanel::saveToImage() {
	wxBitmap *screenshot = new wxBitmap(eca->N * cellSize + panelOffset->x, numIterations * cellSize + panelOffset->y);

	wxMemoryDC memDC;

	memDC.SelectObject(*screenshot);
	memDC.Blit(0, //Copy to this X coordinate
		0, //Copy to this Y coordinate
		eca->N * cellSize + panelOffset->x, //Copy this width
		numIterations * cellSize + panelOffset->y, //Copy this height
		dc, //From where do we copy?
		0, //What's the X offset in the original DC?
		0  //What's the Y offset in the original DC?
	);
	memDC.SelectObject(wxNullBitmap);

	screenshot->SaveFile("screenshot.jpg", wxBITMAP_TYPE_JPEG);
	delete screenshot;
	return true;
}