#pragma once

#ifdef ECALOGIC_EXPORTS
#define ECALOGIC_API __declspec(dllexport)
#else
#define ECALOGIC_API __declspec(dllimport)
#endif

#include <string>
#include <regex>
#include <time.h>

using namespace std;

enum ECALOGIC_API EcaBoundary {ECABOUNDARY_PERIODIC, ECABOUNDARY_CLOSED};

class ECALOGIC_API EcaLogic {
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
	
	string applyRule();
	static string CreateRandomInitialCondition(int N);
	static string ToBinary(int n);
	static string CleanString(string s);
};

