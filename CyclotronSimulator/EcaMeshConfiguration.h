#pragma once

#include "EcaConfiguration.h"

class EcaMeshConfiguration : public EcaConfiguration {
protected:
	int numIterations;
	int cellSize;
	long iterationOffset;
	
	wxBrush deadCellBrush;
	wxBrush aliveCellBrush;

public:
	EcaMeshConfiguration(EcaController* _ecaController);

	EcaMeshConfiguration(EcaController* _ecaController,
		int _numIterations, int _cellSize,
		wxColour _deadCellColor, wxColour _aliveCellColor,
		long _iterationOffset = 0);

	wxBrush& getDeadCellBrush();
	wxBrush& getAliveCellBrush();
	
	int getNumIterations();
	int getCellSize();
	long getIterationOffset();
};

