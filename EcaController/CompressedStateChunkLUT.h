#pragma once
#include "EcaControllerCore.h"

using namespace std;
using namespace EcaControllerCore;

class ECACONTROLLER_DLL CompressedStateChunkLUT {
private:
	chunk*** lut;
	string rule;
	size_t chunkFunctionalSize;
	int lutSize;

public:
	CompressedStateChunkLUT(int _rule, int _chunkFunctionalSize = CHUNK_SIZE);
	CompressedStateChunkLUT(string _rule, int _chunkFunctionalSize = CHUNK_SIZE);
	int getLutSize();
	string getRule();

	chunk applyRule(int state, int leftLSB, int rightMSB);

private:
	char applyElementalRule(char prev, char cur, char next);
};

