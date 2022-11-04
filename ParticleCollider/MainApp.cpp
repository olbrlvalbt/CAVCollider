#include "MainApp.h"

#include <wx/progdlg.h>

#include "ColliderConfiguration.h"

wxIMPLEMENT_APP(MainApp);

MainApp::MainApp() {
}



void paintCentralRing(wxDC& dc, ColliderConfiguration* ColliderConfiguration, int cellSize, wxPoint centralRingCenter, int panelSize) {
	int centralN = ColliderConfiguration->getCollisionSystem().getCentralN();
	string centralState = ColliderConfiguration->getCollisionSystem().getCentralState();
	string centralFilter = ColliderConfiguration->getCollisionSystem().getCentralFilter();

	dc.SetPen(ColliderConfiguration->getAliveCellColor());
	dc.SetBrush(ColliderConfiguration->getAliveCellColor());
	for (int i = 0; i < centralN; i++) {
		if (centralFilter[i] == '0' && centralState[i] == '1') {
			double angle = ColliderConfiguration->getCentralAngleForPos(i);
			double projX = ColliderConfiguration->getCentralRingRadius() * std::cos(angle);
			double projY = ColliderConfiguration->getCentralRingRadius() * std::sin(angle);
			dc.DrawRectangle(centralRingCenter.x + projX, panelSize - (centralRingCenter.y + projY), cellSize, cellSize);
		}
	}
	dc.SetPen(ColliderConfiguration->getDeadCellColor());
	dc.SetBrush(ColliderConfiguration->getDeadCellColor());
	for (int i = 0; i < centralN; i++) {
		if (centralFilter[i] == '0' && centralState[i] == '0') {
			double angle = ColliderConfiguration->getCentralAngleForPos(i);
			double projX = ColliderConfiguration->getCentralRingRadius() * std::cos(angle);
			double projY = ColliderConfiguration->getCentralRingRadius() * std::sin(angle);
			dc.DrawRectangle(centralRingCenter.x + projX, panelSize - (centralRingCenter.y + projY), cellSize, cellSize);
		}
	}
}

void paintLeftRing(wxDC& dc, ColliderConfiguration* ColliderConfiguration, int cellSize, wxPoint leftRingCenter, int panelSize) {
	int leftN = ColliderConfiguration->getCollisionSystem().getLeftN();
	string leftState = ColliderConfiguration->getCollisionSystem().getLeftState();
	string leftFilter = ColliderConfiguration->getCollisionSystem().getLeftFilter();

	dc.SetPen(ColliderConfiguration->getAliveCellColor());
	dc.SetBrush(ColliderConfiguration->getAliveCellColor());
	for (int i = 0; i < leftN; i++) {
		if (leftFilter[i] == '0' && leftState[i] == '1') {
			double angle = ColliderConfiguration->getLeftAngleForPos(i);
			double projX = ColliderConfiguration->getLeftRingRadius() * std::cos(angle);
			double projY = ColliderConfiguration->getLeftRingRadius() * std::sin(angle);
			dc.DrawRectangle(leftRingCenter.x + projX, panelSize - (leftRingCenter.y + projY), cellSize, cellSize);
		}
	}
	dc.SetPen(ColliderConfiguration->getDeadCellColor());
	dc.SetBrush(ColliderConfiguration->getDeadCellColor());
	for (int i = 0; i < leftN; i++) {
		if (leftFilter[i] == '0' && leftState[i] == '0') {
			double angle = ColliderConfiguration->getLeftAngleForPos(i);
			double projX = ColliderConfiguration->getLeftRingRadius() * std::cos(angle);
			double projY = ColliderConfiguration->getLeftRingRadius() * std::sin(angle);
			dc.DrawRectangle(leftRingCenter.x + projX, panelSize - (leftRingCenter.y + projY), cellSize, cellSize);
		}
	}
}

void paintRightRing(wxDC& dc, ColliderConfiguration* ColliderConfiguration, int cellSize, wxPoint rightRingCenter, int panelSize) {
	int rightN = ColliderConfiguration->getCollisionSystem().getRightN();
	string rightState = ColliderConfiguration->getCollisionSystem().getRightState();
	string rightFilter = ColliderConfiguration->getCollisionSystem().getRightFilter();

	dc.SetPen(ColliderConfiguration->getAliveCellColor());
	dc.SetBrush(ColliderConfiguration->getAliveCellColor());
	for (int i = 0; i < rightN; i++) {
		if (rightFilter[i] == '0' && rightState[i] == '1') {
			double angle = ColliderConfiguration->getRightAngleForPos(i);
			double projX = ColliderConfiguration->getRightRingRadius() * std::cos(angle);
			double projY = ColliderConfiguration->getRightRingRadius() * std::sin(angle);
			dc.DrawRectangle(rightRingCenter.x + projX, panelSize - (rightRingCenter.y + projY), cellSize, cellSize);
		}
	}
	dc.SetPen(ColliderConfiguration->getDeadCellColor());
	dc.SetBrush(ColliderConfiguration->getDeadCellColor());
	for (int i = 0; i < rightN; i++) {
		if (rightFilter[i] == '0' && rightState[i] == '0') {
			double angle = ColliderConfiguration->getRightAngleForPos(i);
			double projX = ColliderConfiguration->getRightRingRadius() * std::cos(angle);
			double projY = ColliderConfiguration->getRightRingRadius() * std::sin(angle);
			dc.DrawRectangle(rightRingCenter.x + projX, panelSize - (rightRingCenter.y + projY), cellSize, cellSize);
		}
	}
}

void processAfterExecute(wxBitmap& mainPanelBitmap, int panelSize, wxPoint leftRingCenter,
	wxPoint rightRingCenter, wxPoint centralRingCenter,
	wxPoint leftContactPos, wxPoint rightContactPos, int cellSize,
	ColliderConfiguration* ColliderConfiguration) {

	wxMemoryDC dc(mainPanelBitmap);
	//dc.SetBackground(*wxBLACK_BRUSH);
	dc.SetBackground(wxBrush(wxColour(230, 230, 230)));
	dc.Clear();

	dc.SetBrush(*wxTRANSPARENT_BRUSH);

	dc.SetPen(wxPen(wxColour(205, 205, 205)));
	//dc.SetPen(wxPen(wxColour(80, 165, 110)));
	dc.DrawCircle(leftRingCenter.x, panelSize - leftRingCenter.y, ColliderConfiguration->getLeftRingRadius());

	//dc.SetPen(wxPen(wxColour(165, 80, 110)));
	dc.DrawCircle(rightRingCenter.x, panelSize - rightRingCenter.y, ColliderConfiguration->getRightRingRadius());

	//dc.SetPen(wxPen(wxColour(80, 110, 165)));
	dc.DrawCircle(centralRingCenter.x, panelSize - centralRingCenter.y, ColliderConfiguration->getCentralRingRadius());

	paintCentralRing(dc, ColliderConfiguration, cellSize, centralRingCenter, panelSize);
	paintLeftRing(dc, ColliderConfiguration, cellSize, leftRingCenter, panelSize);
	paintRightRing(dc, ColliderConfiguration, cellSize, rightRingCenter, panelSize);

	/*dc.SetPen(*wxTRANSPARENT_PEN);

	dc.SetBrush(*wxRED_BRUSH);
	dc.DrawCircle(leftContactPos.x, panelSize - leftContactPos.y, 5);

	dc.SetBrush(*wxRED_BRUSH);
	dc.DrawCircle(rightContactPos.x, panelSize - rightContactPos.y, 5);*/

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

	ColliderConfiguration config(&system, centralRingRadius,
		wxColour(5, 5, 5), wxColour(0, 0, 0));

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
	int ssInterval = 50;
	int ssEnd = 93480;
	int ssOffset = 75300;

	Rule110 r;

	string leftIc = r.Translate("4_A4(F3)-87e-4_A4(F2)-87e-4_A4(F1)-87e-4_A4(F3)-86e-87e-4_A4(F2)-87e-4_A4(F1)-87e-4_A4(F3)-87e-4_A4(F2)-44e-86e-86e-86e-87e-4_A4(F1)-87e-4_A4(F3)-87e-4_A4(F2)-87e-4_A4(F1)-87e-4_A4(F3)-86e");
	string centralIc = r.Translate("1800e-1880e-1Ele_C2(A,f1_1)-752e");
	string rightIc = r.Translate("A3(A,f1_1)-SepInit_EE_(C,f3_1)-1BloP_E_(C,f4_1)-SepInit_EE_(C,f3_1)-1BloP_E_(C,f4_1)-0Blo_E_(C,f4_1)-1BloS_E_(A,f4_1)-SepInit_EE_(A,f2_1)-1BloP_E_(F,f1_1)-SepInit_EE_(A,f2_1)-1BloP_E_(F,f1_1)-0Blo_E_(E,f4_1)-1BloS_E_(C,f4_1)-SepInit_EE_(B,f1_1)-1BloP_E_(F,f3_1)-SepInit_EE_(B,f1_1)-1BloP_E_(F,f3_1)-0Blo_E_(F,f3_1)-1BloS_E_(D,f2_1)-SepInit_EE_(H,f1_1)-1BloP_E_(E,f3_1)-SepInit_EE_(H,f4_1)-1BloP_E_(E,f3_1)-0Blo_E_(E,f2_1)-1BloS_E_(C,f2_1)-SepInit_EE_(C,f1_1)-1BloP_E_(A,f3_1)");

	int leftToCentral = 0;
	int centralToLeft = 25200;
	int rightToCentral = 0;
	int centralToRight = 0;

	leftToCentral = (leftToCentral - 1 + leftIc.length()) % leftIc.length();
	rightToCentral = (rightToCentral - 1 + rightIc.length()) % rightIc.length();
	centralToLeft = (centralToLeft - 1 + centralIc.length()) % centralIc.length();
	centralToRight = (centralToRight - 1 + centralIc.length()) % centralIc.length();

	string actions = "";
	int centralRingRadius = 2000;
	string path = "D:/olbrl/Downloads/WolframCollider7/Ring/White/Complete/";

	paint(ssInterval, ssEnd, ssOffset, leftIc, rightIc, centralIc,
		leftToCentral, centralToLeft, rightToCentral, centralToRight,
		actions, centralRingRadius, path);

}


bool MainApp::OnInit() {
	//paint();

	m = new SimulatorMenu();
	m->Show();
	
	return true;
}