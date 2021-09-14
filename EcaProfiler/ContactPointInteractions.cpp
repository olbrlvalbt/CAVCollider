#include "pch.h"

#include "NaiveController.h"
#include "InteractionAgent.h"

#include <string>
#include <wx/wx.h>
#include <wx/dcgraph.h>

using namespace std;

void createCollision(InteractionAgent& point, int n = 1000, int cellsize = 5, string path = "") {
	wxInitAllImageHandlers();

	wxBrush deadCellBrush = wxBrush(wxColour(220, 170, 15));
	wxBrush aliveCellBrush = wxBrush(wxColour(115, 35, 15));


	wxBitmap bitmap1(point.getController(1).getN() * cellsize, n * cellsize);
	wxMemoryDC dc1(bitmap1);
	dc1.SetPen(wxPen(wxColor(0, 0, 0), 1, wxPENSTYLE_TRANSPARENT));

	wxBitmap bitmap2(point.getController(2).getN() * cellsize, n * cellsize);
	wxMemoryDC dc2(bitmap2);
	dc2.SetPen(wxPen(wxColor(0, 0, 0), 1, wxPENSTYLE_TRANSPARENT));

	string c1 = "";
	string c2 = "";
	
	
	for (int j = 0; j < n; j++) {
		for (int i = 0; i < point.getController(1).getN(); i++) {
			if (point.getController(1).getCurrentState()[0].at(i) == '1') {
				dc1.SetBrush(aliveCellBrush);
			}
			else {
				dc1.SetBrush(deadCellBrush);
			}
			dc1.DrawRectangle(i * cellsize, j * cellsize, cellsize, cellsize);
		}
		for (int i = 0; i < point.getController(2).getN(); i++) {
			if (point.getController(2).getCurrentState()[0].at(i) == '1') {
				dc2.SetBrush(aliveCellBrush);
			}
			else {
				dc2.SetBrush(deadCellBrush);
			}
			dc2.DrawRectangle(i * cellsize, j * cellsize, cellsize, cellsize);
		}

		c1 += '\n' + point.getController(1).getCurrentState()[0];
		c2 += '\n' + point.getController(2).getCurrentState()[0];
		
		point.executePoint();
		point.getController(1).applyRule();
		point.getController(2).applyRule();
	}

	
	wxFileDialog saveFileDialog(NULL, _("Save file"), wxGetCwd(), "",
		"PNG files (*.png)|*.png", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	if (path.empty()) {
		if (saveFileDialog.ShowModal() == wxID_CANCEL) {
			return;
		}
	}

	wxBitmap* screenshot1 = new wxBitmap(point.getController(1).getN() * cellsize, n * cellsize);
	wxMemoryDC memDC1(*screenshot1);
	wxMemoryDC baseSSDc1(bitmap1);
	memDC1.Blit(0, //Copy to this X coordinate
		0, //Copy to this Y coordinate
		point.getController(1).getN()* cellsize, //Copy this width
		n* cellsize, //Copy this height
		&baseSSDc1, //From where do we copy?
		0, //What's the X offset in the original DC?
		0  //What's the Y offset in the original DC?
	);
	baseSSDc1.SelectObject(wxNullBitmap);

	wxBitmap* screenshot2 = new wxBitmap(point.getController(2).getN() * cellsize, n * cellsize);
	wxMemoryDC memDC2(*screenshot2);
	wxMemoryDC baseSSDc2(bitmap2);
	memDC2.Blit(0, //Copy to this X coordinate
		0, //Copy to this Y coordinate
		point.getController(2).getN() * cellsize, //Copy this width
		n * cellsize, //Copy this height
		&baseSSDc2, //From where do we copy?
		0, //What's the X offset in the original DC?
		0  //What's the Y offset in the original DC?
	);
	baseSSDc2.SelectObject(wxNullBitmap);
	

	if (path.empty()) {
		screenshot1->SaveFile(saveFileDialog.GetPath() + "1.png", wxBITMAP_TYPE_PNG);
		screenshot2->SaveFile(saveFileDialog.GetPath() + "2.png", wxBITMAP_TYPE_PNG);
	}
	else {
		screenshot1->SaveFile(path + "1.png", wxBITMAP_TYPE_PNG);
		screenshot2->SaveFile(path + "2.png", wxBITMAP_TYPE_PNG);
	}
	delete screenshot1;
	delete screenshot2;
}


void createMixedCollision(InteractionAgent& point, int mixStartIteration = 0, int n = 1000, int cellsize = 5, string path = "") {
	wxInitAllImageHandlers();

	wxBrush deadCellBrush = wxBrush(wxColour(220, 170, 15));
	wxBrush aliveCellBrush = wxBrush(wxColour(115, 35, 15));


	wxBitmap bitmap1((point.getController(1).getN() + point.getController(2).getN()) * cellsize, n * cellsize);
	wxMemoryDC dc1(bitmap1);
	dc1.SetPen(wxPen(wxColor(0, 0, 0), 1, wxPENSTYLE_TRANSPARENT));

	string c1 = "";
	string c2 = "";


	for (int j = 0; j < n; j++) {
		int i = 0;
		int k = 0;
		int l = 0;
		int t = 0;
		for (i = 0; i <= point.getInteractionPositionFor(1); i++) {
			if (point.getController(1).getCurrentState()[0].at(i) == '1') {
				dc1.SetBrush(aliveCellBrush);
			}
			else {
				dc1.SetBrush(deadCellBrush);
			}
			dc1.DrawRectangle(i * cellsize, j * cellsize, cellsize, cellsize);
		}
		for (t = 0, k = point.getInteractionPositionFor(2) + 1; k < point.getController(2).getN(); t++, k++) {
			if (point.getController(2).getCurrentState()[0].at(k) == '1') {
				dc1.SetBrush(aliveCellBrush);
			}
			else {
				dc1.SetBrush(deadCellBrush);
			}
			dc1.DrawRectangle((i + t) * cellsize, j * cellsize, cellsize, cellsize);
		}
		for (l = 0; l <= point.getInteractionPositionFor(2); l++) {
			if (point.getController(2).getCurrentState()[0].at(l) == '1') {
				dc1.SetBrush(aliveCellBrush);
			}
			else {
				dc1.SetBrush(deadCellBrush);
			}
			dc1.DrawRectangle((i + t + l) * cellsize, j * cellsize, cellsize, cellsize);
		}
		for (; i < point.getController(1).getN(); i++) {
			if (point.getController(1).getCurrentState()[0].at(i) == '1') {
				dc1.SetBrush(aliveCellBrush);
			}
			else {
				dc1.SetBrush(deadCellBrush);
			}
			dc1.DrawRectangle((i + t + l) * cellsize, j * cellsize, cellsize, cellsize);
		}

		c1 += '\n' + point.getController(1).getCurrentState()[0];
		c2 += '\n' + point.getController(2).getCurrentState()[0];

		if (j >= mixStartIteration) {
			point.enable();
			point.executePoint();
		}
		point.getController(1).applyRule();
		point.getController(2).applyRule();
	}


	wxFileDialog saveFileDialog(NULL, _("Save file"), wxGetCwd(), "",
		"PNG files (*.png)|*.png", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	if (path.empty()) {
		if (saveFileDialog.ShowModal() == wxID_CANCEL) {
			return;
		}
	}

	wxBitmap* screenshot1 = new wxBitmap((point.getController(1).getN() + point.getController(2).getN()) * cellsize, n * cellsize);
	wxMemoryDC memDC1(*screenshot1);
	wxMemoryDC baseSSDc1(bitmap1);
	memDC1.Blit(0, //Copy to this X coordinate
		0, //Copy to this Y coordinate
		(point.getController(1).getN() + point.getController(2).getN()) * cellsize, //Copy this width
		n * cellsize, //Copy this height
		&baseSSDc1, //From where do we copy?
		0, //What's the X offset in the original DC?
		0  //What's the Y offset in the original DC?
	);
	baseSSDc1.SelectObject(wxNullBitmap);


	if (path.empty()) {
		screenshot1->SaveFile(saveFileDialog.GetPath() + "1.png", wxBITMAP_TYPE_PNG);
	}
	else {
		screenshot1->SaveFile(path + "Mixed.png", wxBITMAP_TYPE_PNG);
	}
	delete screenshot1;
}

TEST(ContactPointDefault, InteractionOnDemand) {
	InteractionController c1(4, 110, "0110");
	InteractionController c2(5, 110, "00000");

	InteractionAgent point(c1, 1, c2, 4);

	point.enable();

	int i = 0;
	for (i = 0; i < 5; i++) {
		point.executePoint();
		c1.applyRule();
		c2.applyRule();
	}

	EXPECT_EQ(1, 1);
}

TEST(ContactPointCollision, GliderBGoesThrough) {
	string s1 = "1111100010011011111000100110111110001001101111100010011011111000100110111110000100011111010";
	string s2 = "1111100010011011111000100110";
	InteractionController c1(s1.length(), 110, s1);
	InteractionController c2(s2.length(), 110, s2);

	InteractionAgent point(c1, 13, c2, 13);

	point.disable();
	//point.enable();

	createMixedCollision(point, 56, 500, 5, "C:/Users/olbrl/Desktop/ECA1D/ParticleEnciclopedia/Collisions/ContactPoint/B");

	EXPECT_EQ(1, 1);
}