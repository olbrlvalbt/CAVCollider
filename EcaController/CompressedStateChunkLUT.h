#pragma once
#include "EcaControllerCore.h"

using namespace std;
using namespace EcaControllerCore;

class ECACONTROLLER_DLL CompressedStateChunkLUT {
private:
	unsigned short*** lut;
	string rule;
	size_t chunkSize;
	int lutSize;

public:
	CompressedStateChunkLUT(int _rule, int _chunkSize = 16);
	CompressedStateChunkLUT(string _rule, int _chunkSize = 16);
	int getLutSize();
	string getRule();

	unsigned short applyRule(int state, int leftLSB, int rightMSB);

private:
	char applyElementalRule(char prev, char cur, char next);
};

