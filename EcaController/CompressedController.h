#pragma once

#include "CompressedState.h"
#include "EcaController.h"
#include "EcaControllerCore.h"

using namespace std;
using namespace EcaControllerCore;

class ECACONTROLLER_DLL CompressedController : public EcaController {
private:
	CompressedState* compressedState;
	ChunkLUTAgent* lutAgent;
	
public:
	CompressedController(int _N, int _rule);
	CompressedController(int _N, int _rule, string _initialCondition);
	~CompressedController();

	void reset();
	void reset(string _newInitialCondition);
	void restart();

	void saveState();
	void applySavedState(bool applySavedCount = true);
	void resetWithSavedState();

	void applyRule();
	size_t getChunkArrayLength();
	long getCurrentIteration();

	const vector<string>& getCurrentState();

	char setAtPosition(int position, char newValue);
	char getAtPosition(int position);
};

