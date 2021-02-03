#pragma once
#include "CompressedState.h"
#include "EcaControllerCore.h"

using namespace std;
using namespace EcaControllerCore;

class ECACONTROLLER_DLL EcaController {
private:
	int N = 100;
	size_t ruleNumber = 110;
	string rule = "";
	string initialCondition = "";

	CompressedState* compressedState;
	ChunkLUTAgent* lutAgent;

private:

public:
	EcaController(int _N, int _rule);
	EcaController(int _N, int _rule, string _initialCondition);

	int getN();
	string getRule();
	
	void reset(string _newInitialCondition);
	void restart();

	void saveState();
	void applySavedState(bool applySavedCount = true);
	void resetWithSavedState();

	void applyRule();
	size_t getChunkArrayLength();
	long getCurrentIteration();

	const vector<string>& getCurrentState();
};