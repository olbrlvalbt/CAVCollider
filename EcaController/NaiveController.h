#pragma once

#include "EcaController.h"
#include "EcaControllerCore.h"

class ECACONTROLLER_DLL NaiveController : public EcaController {
protected:
	string currentState = "";
	string auxState;
	
	long currentIteration;

	string savedState;
	long savedIteration;

	vector<string> stateVector;

public:
	NaiveController(int _N, int _rule);
	NaiveController(int _N, int _rule, string _initialCondition);
	~NaiveController();

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
	virtual void getNeighbors(int i, char& prev, char& cur, char& next);

	char setAtPosition(int position, char newValue);
	char getAtPosition(int position);
};
