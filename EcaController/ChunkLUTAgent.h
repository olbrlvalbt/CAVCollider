#pragma once

#include "EcaControllerCore.h"
#include "ChunkLUT.h"

class ChunkLUTAgent {
private:
	ChunkLUT* regularLut;
	ChunkLUT* adjustedLut;

	int N;
	string rule;
	int adjustedLutBitSize;

public:
	ChunkLUTAgent(string _rule, int _N);

	int getN();
	string getRule();
	bool hasAdjustedLut();
	int getAdjustedLutBitSize();
	CHUNK applyRule(CHUNK c, int leftLSB, int rightMSB, bool adjusted = false);
};

