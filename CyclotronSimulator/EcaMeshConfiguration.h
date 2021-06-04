#pragma once

#include "EcaConfiguration.h"

class EcaMeshConfiguration : public EcaConfiguration {
protected:
	int numIterations;
	int cellSize;
	
	wxBrush deadCellBrush;
	wxBrush aliveCellBrush;

public:
	EcaMeshConfiguration(EcaController* _ecaController);

	EcaMeshConfiguration(EcaController* _ecaController,
		int _numIterations, int _cellSize,
		wxColour _deadCellColor, wxColour _aliveCellColor);

	wxBrush& getDeadCellBrush();
	wxBrush& getAliveCellBrush();
	
	int getNumIterations();
	int getCellSize();
};

