#pragma once
#include <string>
#include <regex>
#include <time.h>

using namespace std;

enum EcaBoundary {ECABOUNDARY_PERIODIC, ECABOUNDARY_CLOSED};

class EcaLogic {
public:
	int N = 100;
	int ruleNumber = 110;
	string rule = "";
	string initialCondition = "";
	string currentState = "";
	EcaBoundary boundaryType = ECABOUNDARY_PERIODIC;

	const string Rule110Ether = "11111000100110";

private:
	string auxState;
	void init(int _N, int _rule, string _initialCondition, int numEtherRule110ForEdges, EcaBoundary boundaryType);

public:
	EcaLogic(int _N, int _rule, EcaBoundary boundaryType);
	EcaLogic(int _N, int _rule, int _initialCondition, int numEtherRule110ForEdges, EcaBoundary boundaryType);
	EcaLogic(int _N, int _rule, string _initialCondition, int numEtherRule110ForEdges, EcaBoundary boundaryType);
	
	string createRandomInitialCondition(int N);
	string applyRule();
	string toBinary(int n);
	string cleanString(string s);
};

