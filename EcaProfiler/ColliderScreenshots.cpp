
#include "pch.h"

#include "ColliderConfig.h"
#include "FilteredCollisionSystem.h"

#include <wx/wx.h>
#include <wx/dcgraph.h>
#include <wx/progdlg.h>

#include "Rule110.h"


using namespace std;



void paintCentralRing(wxDC& dc, ColliderConfig* ColliderConfig, int cellSize, wxPoint centralRingCenter, int panelSize) {
	int centralN = ColliderConfig->getCollisionSystem().getCentralN();
	string centralState = ColliderConfig->getCollisionSystem().getCentralState();
	string centralFilter = ColliderConfig->getCollisionSystem().getCentralFilter();

	dc.SetPen(ColliderConfig->getAliveCellColor());
	dc.SetBrush(ColliderConfig->getAliveCellColor());
	for (int i = 0; i < centralN; i++) {
		if (centralFilter[i] == '0' && centralState[i] == '1') {
			double angle = ColliderConfig->getCentralAngleForPos(i);
			double projX = ColliderConfig->getCentralRingRadius() * std::cos(angle);
			double projY = ColliderConfig->getCentralRingRadius() * std::sin(angle);
			dc.DrawRectangle(centralRingCenter.x + projX, panelSize - (centralRingCenter.y + projY), cellSize, cellSize);
		}
	}
	dc.SetPen(ColliderConfig->getDeadCellColor());
	dc.SetBrush(ColliderConfig->getDeadCellColor());
	for (int i = 0; i < centralN; i++) {
		if (centralFilter[i] == '0' && centralState[i] == '0') {
			double angle = ColliderConfig->getCentralAngleForPos(i);
			double projX = ColliderConfig->getCentralRingRadius() * std::cos(angle);
			double projY = ColliderConfig->getCentralRingRadius() * std::sin(angle);
			dc.DrawRectangle(centralRingCenter.x + projX, panelSize - (centralRingCenter.y + projY), cellSize, cellSize);
		}
	}
}

void paintLeftRing(wxDC& dc, ColliderConfig* ColliderConfig, int cellSize, wxPoint leftRingCenter, int panelSize) {
	int leftN = ColliderConfig->getCollisionSystem().getLeftN();
	string leftState = ColliderConfig->getCollisionSystem().getLeftState();
	string leftFilter = ColliderConfig->getCollisionSystem().getLeftFilter();

	dc.SetPen(ColliderConfig->getAliveCellColor());
	dc.SetBrush(ColliderConfig->getAliveCellColor());
	for (int i = 0; i < leftN; i++) {
		if (leftFilter[i] == '0' && leftState[i] == '1') {
			double angle = ColliderConfig->getLeftAngleForPos(i);
			double projX = ColliderConfig->getLeftRingRadius() * std::cos(angle);
			double projY = ColliderConfig->getLeftRingRadius() * std::sin(angle);
			dc.DrawRectangle(leftRingCenter.x + projX, panelSize - (leftRingCenter.y + projY), cellSize, cellSize);
		}
	}
	dc.SetPen(ColliderConfig->getDeadCellColor());
	dc.SetBrush(ColliderConfig->getDeadCellColor());
	for (int i = 0; i < leftN; i++) {
		if (leftFilter[i] == '0' && leftState[i] == '0') {
			double angle = ColliderConfig->getLeftAngleForPos(i);
			double projX = ColliderConfig->getLeftRingRadius() * std::cos(angle);
			double projY = ColliderConfig->getLeftRingRadius() * std::sin(angle);
			dc.DrawRectangle(leftRingCenter.x + projX, panelSize - (leftRingCenter.y + projY), cellSize, cellSize);
		}
	}
}

void paintRightRing(wxDC& dc, ColliderConfig* ColliderConfig, int cellSize, wxPoint rightRingCenter, int panelSize) {
	int rightN = ColliderConfig->getCollisionSystem().getRightN();
	string rightState = ColliderConfig->getCollisionSystem().getRightState();
	string rightFilter = ColliderConfig->getCollisionSystem().getRightFilter();

	dc.SetPen(ColliderConfig->getAliveCellColor());
	dc.SetBrush(ColliderConfig->getAliveCellColor());
	for (int i = 0; i < rightN; i++) {
		if (rightFilter[i] == '0' && rightState[i] == '1') {
			double angle = ColliderConfig->getRightAngleForPos(i);
			double projX = ColliderConfig->getRightRingRadius() * std::cos(angle);
			double projY = ColliderConfig->getRightRingRadius() * std::sin(angle);
			dc.DrawRectangle(rightRingCenter.x + projX, panelSize - (rightRingCenter.y + projY), cellSize, cellSize);
		}
	}
	dc.SetPen(ColliderConfig->getDeadCellColor());
	dc.SetBrush(ColliderConfig->getDeadCellColor());
	for (int i = 0; i < rightN; i++) {
		if (rightFilter[i] == '0' && rightState[i] == '0') {
			double angle = ColliderConfig->getRightAngleForPos(i);
			double projX = ColliderConfig->getRightRingRadius() * std::cos(angle);
			double projY = ColliderConfig->getRightRingRadius() * std::sin(angle);
			dc.DrawRectangle(rightRingCenter.x + projX, panelSize - (rightRingCenter.y + projY), cellSize, cellSize);
		}
	}
}

void processAfterExecute(wxBitmap& mainPanelBitmap, int panelSize, wxPoint leftRingCenter,
	wxPoint rightRingCenter, wxPoint centralRingCenter,
	wxPoint leftContactPos, wxPoint rightContactPos, int cellSize,
	ColliderConfig* ColliderConfig) {

	wxMemoryDC dc(mainPanelBitmap);
	dc.SetBackground(*wxBLACK_BRUSH);
	dc.Clear();

	dc.SetBrush(*wxTRANSPARENT_BRUSH);

	dc.SetPen(wxPen(wxColour(80, 165, 110)));
	dc.DrawCircle(leftRingCenter.x, panelSize - leftRingCenter.y, ColliderConfig->getLeftRingRadius());

	dc.SetPen(wxPen(wxColour(165, 80, 110)));
	dc.DrawCircle(rightRingCenter.x, panelSize - rightRingCenter.y, ColliderConfig->getRightRingRadius());

	dc.SetPen(wxPen(wxColour(80, 110, 165)));
	dc.DrawCircle(centralRingCenter.x, panelSize - centralRingCenter.y, ColliderConfig->getCentralRingRadius());

	paintCentralRing(dc, ColliderConfig, cellSize, centralRingCenter, panelSize);
	paintLeftRing(dc, ColliderConfig, cellSize, leftRingCenter, panelSize);
	paintRightRing(dc, ColliderConfig, cellSize, rightRingCenter, panelSize);

	dc.SetPen(*wxTRANSPARENT_PEN);

	dc.SetBrush(*wxRED_BRUSH);
	dc.DrawCircle(leftContactPos.x, panelSize - leftContactPos.y, 5);

	dc.SetBrush(*wxRED_BRUSH);
	dc.DrawCircle(rightContactPos.x, panelSize - rightContactPos.y, 5);

	dc.SelectObject(wxNullBitmap);
}

void paint(int ssInterval, int ssEnd, int ssOffset, string leftIc, string rightIc, string centralIc,
	int leftToCentral, int centralToLeft, int rightToCentral, int centralToRight,
	string actions, int centralRingRadius, string path) {

	wxInitialize();
	wxInitAllImageHandlers();
	wxBrush deadCellBrush = wxBrush(wxColour(220, 170, 15));

	FilteredCollisionSystem system(leftIc, rightIc, centralIc,
		leftToCentral, centralToLeft,
		rightToCentral, centralToRight,
		actions);
	system.setAllContactsEnabled(true);

	if (ssOffset > 0) {
		//wxProgressDialog progress("Setting ECA offset", "Processing, please wait", 100, nullptr, wxPD_AUTO_HIDE);

		int j = 0;
		for (int i = 0; i < ssOffset; i++) {
			/*if ((i * 100) % ssOffset == 0) {
				progress.Update(j++);
			}*/
			system.execute();
		}
		//progress.Update(100);
	}

	ColliderConfig config(&system, centralRingRadius,
		wxColour(245, 245, 245), wxColour(255, 255, 255));

	wxPoint centralRingCenter;
	wxPoint leftRingCenter;
	wxPoint rightRingCenter;

	wxPoint leftContactPos;
	wxPoint rightContactPos;

	bool toggleAnimation = true;


	int cellSize = 2;
	int panelSize = 6 * config.getCentralRingRadius();

	centralRingCenter = wxPoint(panelSize / 2, panelSize / 2);
	leftRingCenter = centralRingCenter + config.getRelativeLeftRingCenter();
	rightRingCenter = centralRingCenter + config.getRelativeRightRingCenter();

	leftContactPos = centralRingCenter + config.getRelativeLeftContactPos();
	rightContactPos = centralRingCenter + config.getRelativeRightContactPos();


	wxBitmap mainPanelBitmap(panelSize, panelSize);
	wxProgressDialog progress1("Setting ECA offset", "Processing, please wait", 100, NULL, wxPD_AUTO_HIDE);
	progress1.Update(50);
	for (int i = ssOffset; i < ssEnd; i++) {
		progress1.SetTitle("Iteration " + std::to_string(i) + "/" + std::to_string(ssEnd));
		if (i % ssInterval == 0) {
			progress1.SetTitle("Iteration " + std::to_string(i) + "/" + std::to_string(ssEnd) + " (printing)");

			processAfterExecute(mainPanelBitmap, panelSize, leftRingCenter,
				rightRingCenter, centralRingCenter,
				leftContactPos, rightContactPos, cellSize,
				&config);
			mainPanelBitmap.SaveFile(path + std::to_string(i) + ".png", wxBITMAP_TYPE_PNG);
		}
		system.execute();
	}
	progress1.Update(100);
}

void paint() {
	int ssInterval = 100;
	int ssEnd = 42000;
	int ssOffset = 0;

	Rule110 r;

	string leftIc = r.Translate("4_A4(F2)-87e-4_A4(F1)-87e-4_A4(F3)-87e-4_A4(F2)-87e-4_A4(F1)-87e-4_A4(F3)-86e");
	string centralIc = r.Translate("1000e-1050e-1Ele_C2(A,f1_1)-420e");
	string rightIc = r.Translate("A3(A,f1_1)-SepInit_EE_(C,f3_1)-1BloP_E_(C,f4_1)-SepInit_EE_(C,f3_1)-1BloP_E_(C,f4_1)-0Blo_E_(C,f4_1)-1BloS_E_(A,f4_1)-SepInit_EE_(A,f2_1)-1BloP_E_(F,f1_1)-SepInit_EE_(A,f2_1)-1BloP_E_(F,f1_1)-0Blo_E_(E,f4_1)-1BloS_E_(C,f4_1)-SepInit_EE_(B,f1_1)-1BloP_E_(F,f3_1)-SepInit_EE_(B,f1_1)");

	int leftToCentral = 0;
	int centralToLeft = 14000;
	int rightToCentral = 0;
	int centralToRight = 0;

	leftToCentral = (leftToCentral - 1 + leftIc.length()) % leftIc.length();
	rightToCentral = (rightToCentral - 1 + rightIc.length()) % rightIc.length();
	centralToLeft = (centralToLeft - 1 + centralIc.length()) % centralIc.length();
	centralToRight = (centralToRight - 1 + centralIc.length()) % centralIc.length();

	string actions = "";
	int centralRingRadius = 2000;
	string path = "D:/olbrl/Downloads/ColliderScreenshots/ss";

	paint(ssInterval, ssEnd, ssOffset, leftIc, rightIc, centralIc,
		leftToCentral, centralToLeft, rightToCentral, centralToRight,
		actions, centralRingRadius, path);

}

TEST(GetColliderSS, Descriptor) {
	int ssInterval = 100;
	int ssEnd = 42000;
	int ssOffset = 0;

	Rule110 r;

	string leftIc = r.Translate("4_A4(F2)-87e-4_A4(F1)-87e-4_A4(F3)-87e-4_A4(F2)-87e-4_A4(F1)-87e-4_A4(F3)-86e");
	string centralIc = r.Translate("1000e-1050e-1Ele_C2(A,f1_1)-420e");
	string rightIc = r.Translate("A3(A,f1_1)-SepInit_EE_(C,f3_1)-1BloP_E_(C,f4_1)-SepInit_EE_(C,f3_1)-1BloP_E_(C,f4_1)-0Blo_E_(C,f4_1)-1BloS_E_(A,f4_1)-SepInit_EE_(A,f2_1)-1BloP_E_(F,f1_1)-SepInit_EE_(A,f2_1)-1BloP_E_(F,f1_1)-0Blo_E_(E,f4_1)-1BloS_E_(C,f4_1)-SepInit_EE_(B,f1_1)-1BloP_E_(F,f3_1)-SepInit_EE_(B,f1_1)");

	int leftToCentral = 0;
	int centralToLeft = 14000;
	int rightToCentral = 0;
	int centralToRight = 0;

	leftToCentral = (leftToCentral - 1 + leftIc.length()) % leftIc.length();
	rightToCentral = (rightToCentral - 1 + rightIc.length()) % rightIc.length();
	centralToLeft = (centralToLeft - 1 + centralIc.length()) % centralIc.length();
	centralToRight = (centralToRight - 1 + centralIc.length()) % centralIc.length();

	string actions = "";
	int centralRingRadius = 2000;
	
	string path = "D:\olbrl\Downloads\WolframCollider7\Ring";

	paint(ssInterval, ssEnd, ssOffset, leftIc, rightIc, centralIc,
		leftToCentral, centralToLeft, rightToCentral, centralToRight,
		actions, centralRingRadius, path);

	EXPECT_EQ(1, 1);
}