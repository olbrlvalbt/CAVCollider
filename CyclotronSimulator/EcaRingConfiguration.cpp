#include "EcaRingConfiguration.h"

EcaRingConfiguration::EcaRingConfiguration(EcaController* _ecaController)
		: EcaConfiguration(_ecaController) {
	ringWidth = 2;
	ringRadius = 500;
	refreshRate = 50;
	ringOffset = 1;
	
	deadCellPen = wxPen(wxColour(220, 170, 15), ringWidth);
	deadCellPen.SetCap(wxCAP_BUTT);
	aliveCellPen = wxPen(wxColour(115, 35, 15), ringWidth);
	aliveCellPen.SetCap(wxCAP_BUTT);
}

EcaRingConfiguration::EcaRingConfiguration(EcaController* _ecaController, wxColour _deadCellColor, wxColour _aliveCellColor,
										   int _ringWidth, int _ringRadius,
										   int _refreshRate, int _ringOffset)
		: EcaConfiguration(_ecaController) {
	ringWidth = _ringWidth;
	ringRadius = _ringRadius;
	refreshRate = _refreshRate;
	ringOffset = _ringOffset;

	deadCellPen = wxPen(_deadCellColor, ringWidth);
	deadCellPen.SetCap(wxCAP_BUTT);
	aliveCellPen = wxPen(_aliveCellColor, ringWidth);
	aliveCellPen.SetCap(wxCAP_BUTT);
}

wxPen& EcaRingConfiguration::getDeadCellPen() {
	return deadCellPen;
}

wxPen& EcaRingConfiguration::getAliveCellPen() {
	return aliveCellPen;
}

int EcaRingConfiguration::getRingWidth() {
	return ringWidth;
}

int EcaRingConfiguration::getRingRadius() {
	return ringRadius;
}

int EcaRingConfiguration::getRefreshRate() {
	return refreshRate;
}

int EcaRingConfiguration::getRingOffset() {
	return ringOffset;
}