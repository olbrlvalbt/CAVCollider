#include "pch.h"

#include "NaiveController.h"
#include "GliderMap.h"

#include <string>
#include <wx/wx.h>
#include <wx/dcgraph.h>

#include "CollisionSystem.h"

using namespace std;

void filterT3(int cellsize, NaiveController* eca, wxGCDC& filterDc, string iterationGroup[4], int iteration) {
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
			filterDc.SetBrush(*wxBLACK_BRUSH);
			filterDc.DrawRectangle(i * cellsize, iteration * cellsize, cellsize, cellsize);
			filterDc.DrawRectangle(((i + 1) % n) * cellsize, iteration * cellsize, cellsize, cellsize);
			filterDc.DrawRectangle(((i + 2) % n) * cellsize, iteration * cellsize, cellsize, cellsize);
			filterDc.DrawRectangle(((i + 3) % n) * cellsize, iteration * cellsize, cellsize, cellsize);

			filterDc.DrawRectangle(i * cellsize, (iteration + 1) * cellsize, cellsize, cellsize);
			filterDc.DrawRectangle(((i + 1) % n) * cellsize, (iteration + 1) * cellsize, cellsize, cellsize);
			filterDc.DrawRectangle(((i + 2) % n) * cellsize, (iteration + 1) * cellsize, cellsize, cellsize);
			filterDc.DrawRectangle(((i + 3) % n) * cellsize, (iteration + 1) * cellsize, cellsize, cellsize);

			filterDc.DrawRectangle(i * cellsize, (iteration + 2) * cellsize, cellsize, cellsize);
			filterDc.DrawRectangle(((i + 1) % n) * cellsize, (iteration + 2) * cellsize, cellsize, cellsize);
			filterDc.DrawRectangle(((i + 2) % n) * cellsize, (iteration + 2) * cellsize, cellsize, cellsize);
			filterDc.DrawRectangle(((i + 3) % n) * cellsize, (iteration + 2) * cellsize, cellsize, cellsize);

			filterDc.DrawRectangle(i * cellsize, (iteration + 3) * cellsize, cellsize, cellsize);
			filterDc.DrawRectangle(((i + 1) % n) * cellsize, (iteration + 3) * cellsize, cellsize, cellsize);
		}
	}
}

void createCollision(string ic, int n = 1000, int cellsize = 5, string path = "") {
	wxInitAllImageHandlers();
	
	wxBrush deadCellBrush = wxBrush(wxColour(220, 170, 15));
	wxBrush aliveCellBrush = wxBrush(wxColour(115, 35, 15));
	
	NaiveController* eca = new NaiveController(ic.length(), 110, ic);

	wxBitmap* bitmap = new wxBitmap(ic.length() * cellsize, n * cellsize);
	wxMemoryDC baseDc(*bitmap);
	baseDc.SetPen(wxPen(wxColor(0, 0, 0), 1, wxPENSTYLE_TRANSPARENT));


	wxBitmap* filterBitmap = new wxBitmap(ic.length() * cellsize, n * cellsize, 32);
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
		for (int i = 0; i < eca->getN(); i++) {
			if (eca->getCurrentState()[0].at(i) == '1') {
				baseDc.SetBrush(aliveCellBrush);
			}
			else {
				baseDc.SetBrush(deadCellBrush);
			}
			baseDc.DrawRectangle(i * cellsize, j * cellsize, cellsize, cellsize);
		}

		iterationGroup[j] = eca->getCurrentState()[0];
		eca->applyRule();
	}

	for (; j < n; j++) {
		filterT3(cellsize, eca, filterDc, iterationGroup, j - 4);

		
		iterationGroup[0] = iterationGroup[1];
		iterationGroup[1] = iterationGroup[2];
		iterationGroup[2] = iterationGroup[3];
		iterationGroup[3] = eca->getCurrentState()[0];

		for (int i = 0; i < eca->getN(); i++) {
			if (eca->getCurrentState()[0].at(i) == '1') {
				baseDc.SetBrush(aliveCellBrush);
			}
			else {
				baseDc.SetBrush(deadCellBrush);
			}
			baseDc.DrawRectangle(i * cellsize, j * cellsize, cellsize, cellsize);
		}

		eca->applyRule();
	}

	filterT3(cellsize, eca, filterDc, iterationGroup, j - 4);

	baseDc.SelectObject(wxNullBitmap);
	filterMemDc.SelectObject(wxNullBitmap);
	

	wxFileDialog saveFileDialog(NULL, _("Save file"), wxGetCwd(), "",
		"PNG files (*.png)|*.png", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	if (path.empty()) {
		if (saveFileDialog.ShowModal() == wxID_CANCEL) {
			return;
		}
	}
	
	wxBitmap* screenshot = new wxBitmap(eca->getN() * cellsize, n * cellsize);

	wxMemoryDC memDC(*screenshot);

	wxMemoryDC baseSSDc(*bitmap);
	memDC.Blit(0, //Copy to this X coordinate
		0, //Copy to this Y coordinate
		eca->getN() * cellsize, //Copy this width
		n * cellsize, //Copy this height
		&baseSSDc, //From where do we copy?
		0, //What's the X offset in the original DC?
		0  //What's the Y offset in the original DC?
	);
	baseSSDc.SelectObject(wxNullBitmap);

	wxMemoryDC filterSSDc(*filterBitmap);
	memDC.Blit(0, //Copy to this X coordinate
		0, //Copy to this Y coordinate
		eca->getN() * cellsize, //Copy this width
		n * cellsize, //Copy this height
		&filterSSDc, //From where do we copy?
		0, //What's the X offset in the original DC?
		0  //What's the Y offset in the original DC?
	);
	filterSSDc.SelectObject(wxNullBitmap);

	memDC.SelectObject(wxNullBitmap);

	if (path.empty()) {
		screenshot->SaveFile(saveFileDialog.GetPath(), wxBITMAP_TYPE_PNG);
	}
	else {
		screenshot->SaveFile(path, wxBITMAP_TYPE_PNG);
	}
	delete screenshot;
}

TEST(CreateCollisionsA_Eb, A_Eb) {
	int leftEthers = 2;
	int midEthers = 0;
	int rightEthers = 2;
	const string ether = "11111000100110";

	string leftEthersString = "";
	string midEthersString = "";
	string rightEthersString = "";

	int i, j, k, l;

	for (i = 0; i < leftEthers; i++) {
		leftEthersString += ether;
	}
	for (i = 0; i < midEthers; i++) {
		midEthersString += ether;
	}
	for (i = 0; i < rightEthers; i++) {
		rightEthersString += ether;
	}
	GliderMap gm = GliderMap();

	//string gliderA = gm.get("A", "A", 1);
	//string gliderEb = gm.get("E_", "A", 1);
	
	for (i = 0; i < 1; i++) {
		for (j = 0; j < 4; j++) {
			for (k = 0; k < 8; k++) {
				for (l = 0; l < 4; l++) {
					string controllerIC = leftEthersString + gm.getByIndex("A", i, j) + midEthersString + gm.getByIndex("Eb", k, l)  + rightEthersString;
					string path = "C:/Users/olbrl/Desktop/ECA1D/ParticleEnciclopedia/Collisions/A_Eb/A-" + to_string(i) + "-" + to_string(j) + "_Eb-" + to_string(k) + "-" + to_string(l) + ".png";
					createCollision(controllerIC, 100, 10, path);
				}
			}
		}
	}
	
	EXPECT_EQ(1, 1);
}
TEST(efe, A_Ewwb) {
	CollisionSystem system(14, "11111000100110", 14, "11111000100110", 28, "1111100010011011111000100110",
		13, 27, 13, 13);

	EXPECT_EQ(1, 1);
}