#include "EcaGui.h"

wxIMPLEMENT_APP(EcaGui);

bool EcaGui::OnInit() {
	EcaLogic* ecaLogic = new EcaLogic(NUMCELLS, RULE, INITIALCONDITION, ECABOUNDARY_PERIODIC);


	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	frame = new EcaFrame();

	drawPane = new DrawPane(frame, ecaLogic);

	drawPane->Bind(wxEVT_CHAR_HOOK, &EcaFrame::OnKeyDown, frame);
	sizer->Add(drawPane, 1, wxEXPAND);

	frame->SetSizer(sizer);
	frame->SetAutoLayout(true);
	frame->Show();

	return true;
}

EcaFrame::EcaFrame() : wxFrame(nullptr, -1, wxT("ECA1D"), wxPoint(0, 0), wxSize(WIDTH, HEIGHT)) {

}

void EcaFrame::OnKeyDown(wxKeyEvent& event) {
	switch ((int)event.GetKeyCode()) {
		case 'n':
		case 'N':
			if (wxMessageBox("Create new random initial condition?", "Confirm", wxYES_NO | wxYES_DEFAULT, this) == wxYES) {
				((DrawPane*)drawPane)->eca->initialCondition = ((DrawPane*)drawPane)->eca->createRandomInitialCondition(((DrawPane*)drawPane)->eca->N);
				((DrawPane*)drawPane)->eca->currentState = ((DrawPane*)drawPane)->eca->initialCondition;
				((DrawPane*)drawPane)->currentShowingIteration = 1;
				drawPane->Refresh();
			}
			break;
		case WXK_SPACE:
			((DrawPane*)drawPane)->currentShowingIteration++;
			drawPane->Refresh();
			break;
		case 'r':
		case 'R':
			((DrawPane*)drawPane)->eca->currentState = ((DrawPane*)drawPane)->eca->initialCondition;
			((DrawPane*)drawPane)->currentShowingIteration = 1;
			drawPane->Refresh();
			break;
		case 's':
		case 'S':
			((DrawPane*)drawPane)->saveToImage();
			break;
	}
	event.Skip();
}

BEGIN_EVENT_TABLE(DrawPane, wxPanel)
	EVT_PAINT(DrawPane::paintEvent)
END_EVENT_TABLE()


DrawPane::DrawPane(EcaFrame* parent, EcaLogic* ecaLogic) : wxPanel(parent) {
	parent->drawPane = this;
	eca = ecaLogic;
	wxInitAllImageHandlers();
}

void DrawPane::paintEvent(wxPaintEvent & evt) {
	dc = new wxPaintDC(this);
	render();
}

void DrawPane::render() {
	dc->DrawText(wxT("Rule " + to_string(eca->ruleNumber)), 10, 10);
	dc->DrawText(wxT("N = " + to_string(NUMCELLS)), 100, 10);
	dc->DrawText(wxT("Iterations " + to_string((currentShowingIteration - 1) * NUMCOLS)
					+ " through " + to_string((currentShowingIteration) * NUMCOLS)), 200, 10);

	dc->DrawText(wxT("" + to_string(currentShowingIteration)), 500, 10);

	dc->SetPen(wxPen(wxColor(0, 0, 0), 1, wxPENSTYLE_TRANSPARENT));
	wxBrush* whiteBrush = new wxBrush(wxColor(200, 200, 200), wxBRUSHSTYLE_TRANSPARENT);
	
	for (int j = 0; j < NUMCOLS; j++) {

		for (int i = 0; i < NUMCELLS; i++) {
			if(eca->currentState.at(i) == '1') {
				dc->SetBrush(*wxBLACK_BRUSH);
			}
			else {
				dc->SetBrush(*whiteBrush);
			}
			dc->DrawRectangle(i * CELLSIZE, j * CELLSIZE + TEXTOFFSET, CELLSIZE, CELLSIZE);
		}

		eca->applyRule();
		//wxMilliSleep(1);
	}
	saveToImage();
}

bool DrawPane::saveToImage() {
	wxBitmap *screenshot = new wxBitmap(WIDTH, HEIGHT);

	wxMemoryDC memDC;

	memDC.SelectObject(*screenshot);
	memDC.Blit(0, //Copy to this X coordinate
		0, //Copy to this Y coordinate
		NUMCELLS * CELLSIZE, //Copy this width
		NUMCOLS * CELLSIZE, //Copy this height
		dc, //From where do we copy?
		0, //What's the X offset in the original DC?
		TEXTOFFSET  //What's the Y offset in the original DC?
	);
	memDC.SelectObject(wxNullBitmap);

	screenshot->SaveFile("screenshot.jpg", wxBITMAP_TYPE_JPEG);
	delete screenshot;
	return true;
}