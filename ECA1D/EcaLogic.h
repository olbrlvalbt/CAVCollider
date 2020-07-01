#pragma once
#include <string>
#include <time.h>

using namespace std;


enum EcaBoundary {ECABOUNDARY_PERIODIC, ECABOUNDARY_CLOSED};

class EcaLogic {
public:
	int N = 100;
	int ruleNumber = 0;
	string rule = "";
	string initialCondition = "";
	string currentState = "";
	EcaBoundary boundaryType = ECABOUNDARY_PERIODIC;

private:
	string auxState;
	void init(int NI, int ruleI, string initialConditionI, EcaBoundary boundaryType = ECABOUNDARY_PERIODIC);

public:
	EcaLogic(int NI, int ruleI, int initialConditionI, EcaBoundary boundaryType = ECABOUNDARY_PERIODIC);
	EcaLogic(int NI, int ruleI, string initialConditionI, EcaBoundary boundaryType = ECABOUNDARY_PERIODIC);
	~EcaLogic();
	
	string createRandomInitialCondition(int N);
	string applyRule();
	string toBinary(int n);
};

