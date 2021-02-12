#pragma once
#include "EcaControllerCore.h"

using namespace std;
using namespace EcaControllerCore;

class ECACONTROLLER_DLL ChunkLUT {
private:
	CHUNK*** lut;
	string rule;
	size_t bitSize;
	int lutSize;

public:
	ChunkLUT(string _rule, int _bitSize = CHUNK_BITSIZE);
	~ChunkLUT();
	
	int getLutSize();

	CHUNK get(int state, int leftLSB, int rightMSB);

private:
	char applyElementalRule(char prev, char cur, char next);
};

