#pragma once
#include "wx/wx.h"
#include "wx/sizer.h"
#include "EcaLogic.h"

#define RULE 110
#define NUMCELLS 750
#define INITIALCONDITION 1
#define NUMCOLS 350
#define CELLSIZE 2
#define WIDTH 1550
#define HEIGHT 800
#define TEXTOFFSET 30


class EcaFrame : public wxFrame {
public:
	wxPanel* drawPane = nullptr;

	EcaFrame();
	void OnKeyDown(wxKeyEvent& event);
};

class DrawPane : public wxPanel {
public:
	EcaLogic* eca = nullptr;
	wxPaintDC* dc = nullptr;
	int currentShowingIteration = 1;

	DrawPane(EcaFrame* parent, EcaLogic* ecaLogic);
	void paintEvent(wxPaintEvent & evt);
	void render();
	bool saveToImage();

	DECLARE_EVENT_TABLE()
};

class EcaGui : public wxApp {

public:
	virtual bool OnInit();
	EcaFrame* frame = nullptr;
	DrawPane* drawPane = nullptr;
};