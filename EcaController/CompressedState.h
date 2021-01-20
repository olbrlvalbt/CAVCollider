#pragma once
#include "EcaControllerCore.h"

using namespace std;
using namespace EcaControllerCore;

//enum ECALOGIC_API EcaBoundary {ECABOUNDARY_PERIODIC, ECABOUNDARY_CLOSED};

class ECACONTROLLER_DLL CompressedState {
private:
	//CompressedState compressedInitialCondition;
	//CompressedState compressedCurrentState;
	//CompressedStateChunkLUT stateLUT;
	//CompressedStateChunkLUT mostSignificativeStateLUT;
public:
	unsigned int N = 100;
	size_t ruleNumber = 110;
	string rule = "";
	string initialCondition = "";

private:
	/*string auxState;
	void init(int _N, int _rule, string _initialCondition, int numEtherRule110ForEdges, EcaBoundary boundaryType);*/
	//static string ToBinary(int n);
	void initializeLUTs();
	int compress(unsigned short** compressedState);

public:
	CompressedState(unsigned int _N, unsigned char _rule);
	CompressedState(unsigned int _N, unsigned char _rule, string _initialCondition);



	/*EcaLogic(int _N, int _rule, EcaBoundary boundaryType);
	EcaLogic(int _N, int _rule, int _initialCondition, int numEtherRule110ForEdges, EcaBoundary boundaryType);
	EcaLogic(int _N, int _rule, string _initialCondition, int numEtherRule110ForEdges, EcaBoundary boundaryType);

	string applyRule();
	static string CreateRandomInitialCondition(int N);
	static string ToBinary(int n);
	static string CleanString(string s);*/


};