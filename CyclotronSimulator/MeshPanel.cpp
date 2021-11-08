#include "MeshPanel.h"

MeshPanel::MeshPanel(wxWindow* parent, EcaMeshConfiguration* config, bool _rule110T3filterEnabled)
	: wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition,
		wxDefaultSize, wxBORDER_SIMPLE) {
	meshConfig = config;
	
	rule110T3filterEnabled = _rule110T3filterEnabled;

	wxInitAllImageHandlers();
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	createBitmapWithT3Filter();

	Connect(GetId(), wxEVT_PAINT, wxPaintEventHandler(MeshPanel::paintEvent));
	Connect(GetId(), wxEVT_KEY_DOWN, wxKeyEventHandler(MeshPanel::OnKeyDown));


	SetClientSize(meshConfig->getEca()->getN() * meshConfig->getCellSize(), meshConfig->getNumIterations() * meshConfig->getCellSize());
	SetScrollbars(1, 1, meshConfig->getEca()->getN() * meshConfig->getCellSize(), meshConfig->getNumIterations() * meshConfig->getCellSize(), 0, 0);
}

void MeshPanel::paintEvent(wxPaintEvent& evt) {
	render();
}

void MeshPanel::render() {
	wxBufferedPaintDC paintDC(this);
	DoPrepareDC(paintDC);
	paintDC.DrawBitmap(*bitmap, 0, 0, true);
	if (rule110T3filterEnabled) {
		paintDC.DrawBitmap(*filterBitmap, 0, 0, true);
	}
}

void MeshPanel::createBitmap() {
	wxProgressDialog* progress = new wxProgressDialog("Rendering", "Processing image, please wait", 100, nullptr, wxPD_AUTO_HIDE);

	bitmap = new wxBitmap(meshConfig->getEca()->getN() * meshConfig->getCellSize(), meshConfig->getNumIterations() * meshConfig->getCellSize());

	wxMemoryDC dc(*bitmap);
	int k = 0;

	dc.SetPen(wxPen(wxColor(0, 0, 0), 1, wxPENSTYLE_TRANSPARENT));

	for (int j = 0; j < meshConfig->getNumIterations(); j++) {
		if ((j * 100) % meshConfig->getNumIterations() == 0) {
			progress->Update(k++);
		}

		for (int i = 0; i < meshConfig->getEca()->getN(); i++) {
			if (meshConfig->getEca()->getCurrentState()[0].at(i) == '1') {
				dc.SetBrush(meshConfig->getAliveCellBrush());
			}
			else {
				dc.SetBrush(meshConfig->getDeadCellBrush());
			}
			dc.DrawRectangle(i * meshConfig->getCellSize(), j * meshConfig->getCellSize(), meshConfig->getCellSize(), meshConfig->getCellSize());
		}

		meshConfig->getEca()->applyRule();
	}

	GetParent()->SetLabel("ECA R" + to_string(meshConfig->getEca()->getRuleNumber()) + ", N: " + to_string(meshConfig->getEca()->getN())
		+ ", Iterations " + to_string((currentSpace - 1) * meshConfig->getNumIterations())
		+ "-" + to_string(currentSpace * meshConfig->getNumIterations() - 1)
		+ " (" + to_string(currentSpace) + ")");

	dc.SelectObject(wxNullBitmap);

	progress->Update(100);
}

void MeshPanel::createBitmapWithT3Filter() {
	wxProgressDialog* progress = new wxProgressDialog("Rendering", "Processing image, please wait", 100, nullptr, wxPD_AUTO_HIDE);

	bitmap = new wxBitmap(meshConfig->getEca()->getN() * meshConfig->getCellSize(), meshConfig->getNumIterations() * meshConfig->getCellSize());
	wxMemoryDC baseDc(*bitmap);
	baseDc.SetPen(wxPen(wxColor(0, 0, 0), 1, wxPENSTYLE_TRANSPARENT));


	filterBitmap = new wxBitmap(meshConfig->getEca()->getN() * meshConfig->getCellSize(), meshConfig->getNumIterations() * meshConfig->getCellSize(), 32);
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
		if ((j * 100) % meshConfig->getNumIterations() == 0) {
			progress->Update(k++);
		}

		paintIteration(baseDc, j);

		iterationGroup[j] = meshConfig->getEca()->getCurrentState()[0];
		meshConfig->getEca()->applyRule();
	}

	for (; j < meshConfig->getNumIterations(); j++) {
		if ((j * 100) % meshConfig->getNumIterations() == 0) {
			progress->Update(k++);
		}

		filterT3(iterationGroup, filterDc, j - 4);
		iterationGroup[0] = iterationGroup[1];
		iterationGroup[1] = iterationGroup[2];
		iterationGroup[2] = iterationGroup[3];
		iterationGroup[3] = meshConfig->getEca()->getCurrentState()[0];

		paintIteration(baseDc, j);

		meshConfig->getEca()->applyRule();
	}

	filterT3(iterationGroup, filterDc, j - 4);


	GetParent()->SetLabel("ECA R" + to_string(meshConfig->getEca()->getRuleNumber()) + ", N: " + to_string(meshConfig->getEca()->getN())
		+ ", Iterations " + to_string((currentSpace - 1) * meshConfig->getNumIterations() + meshConfig->getIterationOffset())
		+ "-" + to_string(currentSpace * meshConfig->getNumIterations() - 1 + meshConfig->getIterationOffset())
		+ " (" + to_string(currentSpace) + ")");

	baseDc.SelectObject(wxNullBitmap);
	filterMemDc.SelectObject(wxNullBitmap);

	progress->Update(100);
}

void MeshPanel::paintIteration(wxDC& dc, int iteration) {
	const string state = meshConfig->getEca()->getCurrentState()[0];
	for (int i = 0; i < meshConfig->getEca()->getN(); i++) {
		if (state.at(i) == '1') {
			dc.SetBrush(meshConfig->getAliveCellBrush());
		}
		else {
			dc.SetBrush(meshConfig->getDeadCellBrush());
		}
		dc.DrawRectangle(i * meshConfig->getCellSize(), iteration * meshConfig->getCellSize(), meshConfig->getCellSize(), meshConfig->getCellSize());
	}
}

void MeshPanel::filterT3(string(&iterationGroup)[4], wxGCDC& filterDc, int iteration) {
	string f1 = "";
	string f2 = "";
	string f3 = "";
	string f4 = "";

	int n = meshConfig->getEca()->getN();

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
			filterDc.SetBrush(*wxBLACK_BRUSH);
			filterDc.DrawRectangle(i * meshConfig->getCellSize(), iteration * meshConfig->getCellSize(), meshConfig->getCellSize(), meshConfig->getCellSize());
			filterDc.DrawRectangle(((i + 1) % n) * meshConfig->getCellSize(), iteration * meshConfig->getCellSize(), meshConfig->getCellSize(), meshConfig->getCellSize());
			filterDc.DrawRectangle(((i + 2) % n) * meshConfig->getCellSize(), iteration * meshConfig->getCellSize(), meshConfig->getCellSize(), meshConfig->getCellSize());
			filterDc.DrawRectangle(((i + 3) % n) * meshConfig->getCellSize(), iteration * meshConfig->getCellSize(), meshConfig->getCellSize(), meshConfig->getCellSize());

			filterDc.DrawRectangle(i * meshConfig->getCellSize(), (iteration + 1) * meshConfig->getCellSize(), meshConfig->getCellSize(), meshConfig->getCellSize());
			filterDc.DrawRectangle(((i + 1) % n) * meshConfig->getCellSize(), (iteration + 1) * meshConfig->getCellSize(), meshConfig->getCellSize(), meshConfig->getCellSize());
			filterDc.DrawRectangle(((i + 2) % n) * meshConfig->getCellSize(), (iteration + 1) * meshConfig->getCellSize(), meshConfig->getCellSize(), meshConfig->getCellSize());
			filterDc.DrawRectangle(((i + 3) % n) * meshConfig->getCellSize(), (iteration + 1) * meshConfig->getCellSize(), meshConfig->getCellSize(), meshConfig->getCellSize());

			filterDc.DrawRectangle(i * meshConfig->getCellSize(), (iteration + 2) * meshConfig->getCellSize(), meshConfig->getCellSize(), meshConfig->getCellSize());
			filterDc.DrawRectangle(((i + 1) % n) * meshConfig->getCellSize(), (iteration + 2) * meshConfig->getCellSize(), meshConfig->getCellSize(), meshConfig->getCellSize());
			filterDc.DrawRectangle(((i + 2) % n) * meshConfig->getCellSize(), (iteration + 2) * meshConfig->getCellSize(), meshConfig->getCellSize(), meshConfig->getCellSize());
			filterDc.DrawRectangle(((i + 3) % n) * meshConfig->getCellSize(), (iteration + 2) * meshConfig->getCellSize(), meshConfig->getCellSize(), meshConfig->getCellSize());

			filterDc.DrawRectangle(i * meshConfig->getCellSize(), (iteration + 3) * meshConfig->getCellSize(), meshConfig->getCellSize(), meshConfig->getCellSize());
			filterDc.DrawRectangle(((i + 1) % n) * meshConfig->getCellSize(), (iteration + 3) * meshConfig->getCellSize(), meshConfig->getCellSize(), meshConfig->getCellSize());
		}
	}
}

bool MeshPanel::saveToImage() {
	wxFileDialog saveFileDialog(this, _("Save file"), wxGetCwd(), "",
		"PNG files (*.png)|*.png", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (saveFileDialog.ShowModal() == wxID_CANCEL) {
		return false;
	}

	wxProgressDialog* progress = new wxProgressDialog("Saving", "Saving image, please wait", 100, nullptr, wxPD_AUTO_HIDE);

	if (rule110T3filterEnabled) {
		wxBitmap* screenshot = new wxBitmap(meshConfig->getEca()->getN() * meshConfig->getCellSize(), meshConfig->getNumIterations() * meshConfig->getCellSize());

		wxMemoryDC memDC(*screenshot);

		wxMemoryDC baseDc(*bitmap);
		memDC.Blit(0, //Copy to this X coordinate
			0, //Copy to this Y coordinate
			meshConfig->getEca()->getN() * meshConfig->getCellSize(), //Copy this width
			meshConfig->getNumIterations() * meshConfig->getCellSize(), //Copy this height
			&baseDc, //From where do we copy?
			0, //What's the X offset in the original DC?
			0  //What's the Y offset in the original DC?
		);
		baseDc.SelectObject(wxNullBitmap);

		progress->Update(50);

		wxMemoryDC filterDc(*filterBitmap);
		memDC.Blit(0, //Copy to this X coordinate
			0, //Copy to this Y coordinate
			meshConfig->getEca()->getN() * meshConfig->getCellSize(), //Copy this width
			meshConfig->getNumIterations() * meshConfig->getCellSize(), //Copy this height
			&filterDc, //From where do we copy?
			0, //What's the X offset in the original DC?
			0  //What's the Y offset in the original DC?
		);
		filterDc.SelectObject(wxNullBitmap);

		memDC.SelectObject(wxNullBitmap);

		screenshot->SaveFile(saveFileDialog.GetPath(), wxBITMAP_TYPE_PNG);
		delete screenshot;
	}
	else {
		bitmap->SaveFile(saveFileDialog.GetPath(), wxBITMAP_TYPE_PNG);
	}

	progress->Update(100);

	return true;
}

void MeshPanel::OnKeyDown(wxKeyEvent& event) {
	switch ((int)event.GetKeyCode()) {
	case 'n':
	case 'N':
		resetSpace();
		break;
	case WXK_SPACE:
		nextSpace();
		break;
	case 'r':
	case 'R':
		restartSpace();
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
	event.Skip();
}

void MeshPanel::nextSpace() {
	currentSpace++;
	createBitmapWithT3Filter();
	Refresh();
}

void MeshPanel::restartSpace() {
	meshConfig->getEca()->restart();
	currentSpace = 1;
	createBitmapWithT3Filter();
	Refresh();
}

void MeshPanel::resetSpace() {
	if (wxMessageBox("Create new random initial condition?", "Confirm", wxYES_NO | wxYES_DEFAULT, this) == wxYES) {
		meshConfig->getEca()->reset();
		currentSpace = 1;
		createBitmapWithT3Filter();
		Refresh();
	}
}