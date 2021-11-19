#pragma once

#include "EcaConfiguration.h"

class EcaRingConfiguration : public EcaConfiguration {
	wxPen deadCellPen;
	wxPen aliveCellPen;
	
	int ringWidth;
	int ringRadius;
	int refreshRate;
	int ringOffset;

public:
	EcaRingConfiguration(EcaController* _ecaController);

	EcaRingConfiguration(EcaController* _ecaController, wxColour _deadCellColor, wxColour _aliveCellColor,
						 int _ringWidth, int _ringRadius,
						 int _refreshRate, int _ringOffset);

	wxPen& getDeadCellPen();
	wxPen& getAliveCellPen();
	int getRingWidth();
	int getRingRadius();
	int getRefreshRate();
	int getRingOffset();
};
