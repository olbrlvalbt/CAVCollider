#pragma once

#include <vector>
#include "EcaControllerCore.h"

using namespace std;
using namespace EcaControllerCore;

class ECACONTROLLER_DLL EcaController {
protected:
	int N = 100;
	size_t ruleNumber = 110;
	string rule = "";
	string initialCondition = "";
	
	EcaController(int _N, int _rule);
	EcaController(int _N, int _rule, string _initialCondition);

public:
	virtual ~EcaController();
	
	virtual int getN();
	virtual size_t getRuleNumber();
	virtual string getRule();

	virtual void reset() = 0;
	virtual void reset(string _newInitialCondition) = 0;
	virtual void restart() = 0;

	virtual void saveState() = 0;
	virtual void applySavedState(bool _applySavedCount = true) = 0;
	virtual void resetWithSavedState() = 0;

	virtual void applyRule() = 0;
	virtual long getCurrentIteration() = 0;

	const virtual vector<string>& getCurrentState() = 0;
};