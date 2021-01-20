#pragma once
#include "EcaControllerCore.h"

using namespace std;
using namespace EcaControllerCore;

class ECACONTROLLER_DLL CompressedStateChunkLUT {
private:
	unsigned short*** lut;
	string rule;
	unsigned char chunkLength;
	unsigned int lutSize;

public:
	CompressedStateChunkLUT(string _rule, unsigned char _chunkLength = 16);
	unsigned int getLutSize();

	unsigned short applyRule(unsigned short state, unsigned char leftLSB, unsigned char rightMSB);

private:
	char applyElementalRule(char prev, char cur, char next);
};

