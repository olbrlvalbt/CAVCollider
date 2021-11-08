#include "pch.h"

#include "NaiveController.h"
#include "GliderMap.h"

#include <string>
#include <wx/wx.h>
#include <wx/dcgraph.h>
#include <wx/progdlg.h>


#include "CollisionSystem.h"
#include "Rule110.h"

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

void createCollision(string ic, int n = 1000, int cellsize = 5, string path = "", int offset = 0) {
	wxInitAllImageHandlers();
	
	wxBrush deadCellBrush = wxBrush(wxColour(220, 170, 15));
	wxBrush aliveCellBrush = wxBrush(wxColour(115, 35, 15));
	
	NaiveController* eca = new NaiveController(ic.length(), 110, ic);

	for (int i = 0; i < offset; i++) {
		eca->applyRule();
	}

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

TEST(TestCTS10, Testing) {
	int minEthers = 12;
	int maxEthers = 100;

	int offset = 0;
	int numIterations = 3000;

	Rule110 r;

	string left = r.Translate("2e");

	string right = r.Translate("1Ele_C2(A, f1_1) - A3(A, f1_1) - SepInit_EE_(C, f3_1) - 1BloP_E_(C, f4_1)");

	vector<string> g0elec2 = {
		"1111100000010011011111000100110111110001001101111100000010011011111000100110111000110001001101111100010011011111000100000110"
		,
			"1111100010000011011111000100110111110001001101111100010000011011111000100110111110100111001101111100010011011111000100110000"
		,
			"0001111100010011011111000100110111110001001100001111100010011011111000111011010111110001001101111100010011011100011000100110"
		,
			"1110001100010011011111000100110111110001001101110001100010011011111000100110111111110001001101111100010011011111010011100110"

		,
			"1111101001110011011111000100110111110001001101111101001110011011111000100110111110000001001101111100010011011111000111011010"
		,
			"1111100011101101011111000100110111110001001101111100011101101011111000100110111110001000001101111100010011011111000100110111"
		,
			"1111111100010011011111000100110111110001001101111111100010011011111000100110000111110001001101111100010011011111000000100110"
	};
	
	string basePath = "D:/olbrl/Downloads/CollisionTest/";
	
	for (int i = minEthers; i < maxEthers; i++) {
		for (int j = 0; j < g0elec2.size(); j++) {
			cout << "Starting " + std::to_string(i) + "e_f" + std::to_string(j) << endl;
			string cur = to_string(i) + "e";
			string ic = left + g0elec2[j] + r.Translate(cur) + right;

			createCollision(ic, numIterations, 1, 
				basePath + "g_" + std::to_string(i) + "e_f" + std::to_string(j) + ".png",
				500);
		}
	}

	EXPECT_EQ(1, 1);
}


TEST(TestCTS10Dephased, Testing) {
	int offset = 12;
	int maxDephase = 200;
	int numIterations = 3000;

	int midEthers = 5;
	

	Rule110 r;

	string left = r.Translate("2e");
	
	string mid = r.Translate(std::to_string(midEthers) + "e");

	string right = r.Translate("e - 1Ele_C2(A, f1_1) - A3(A, f1_1) - SepInit_EE_(C, f3_1) - 1BloP_E_(C, f4_1)");

	NaiveController* dephasedEca = new NaiveController(right.length(), 110, right);
	for (int i = 0; i < offset; i++) {
		dephasedEca->applyRule();
	}

	vector<string> g0elec2 = {
		"1111100000010011011111000100110111110001001101111100000010011011111000100110111000110001001101111100010011011111000100000110"
		,
			"1111100010000011011111000100110111110001001101111100010000011011111000100110111110100111001101111100010011011111000100110000"
		,
			"0001111100010011011111000100110111110001001100001111100010011011111000111011010111110001001101111100010011011100011000100110"
		,
			"1110001100010011011111000100110111110001001101110001100010011011111000100110111111110001001101111100010011011111010011100110"

		,
			"1111101001110011011111000100110111110001001101111101001110011011111000100110111110000001001101111100010011011111000111011010"
		,
			"1111100011101101011111000100110111110001001101111100011101101011111000100110111110001000001101111100010011011111000100110111"
		,
			"1111111100010011011111000100110111110001001101111111100010011011111000100110000111110001001101111100010011011111000000100110"
	};

	vector<string> leftEthers = {
		"",
		"1111",
		"11111000",
		"111110001001",
		"11",
		"111110",
		"1111100010"
	};

	vector<string> rightEthers = {
		"",
		"1000100110",
		"100110",
		"10",
		"111000100110",
		"00100110",
		"0110"
	};
	
	string basePath = "D:/olbrl/Downloads/CollisionDephased/";

	for (int i = offset; i < maxDephase; i++) {
		for (int j = 0; j < g0elec2.size(); j++) {
			string ic = left + g0elec2[j] + mid + leftEthers[i % 7] + dephasedEca->getCurrentState()[0] + rightEthers[i % 7];

			createCollision(ic, numIterations, 1,
				basePath + "g_p" + std::to_string(i) + "_f" + std::to_string(j) + ".png",
				0);
		}

		dephasedEca->applyRule();
	}

	EXPECT_EQ(1, 1);
}