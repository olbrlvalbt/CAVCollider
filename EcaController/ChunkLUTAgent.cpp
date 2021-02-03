#include "pch.h"
#include "ChunkLUTAgent.h"

ChunkLUTAgent::ChunkLUTAgent(string _rule, int _N) {
	if (_N <= 0) {
		throw exception("N cannot be negative nor zero");
	}
	if (_rule.length() != 8 || !IsBinaryString(_rule)) {
		throw exception("Rule must be an 8-digit binary string");
	}
	rule = _rule;
	N = _N;

	adjustedLutBitSize = N % CHUNK_BITSIZE;

	regularLut = new ChunkLUT(rule);
	if (hasAdjustedLut()) {
		adjustedLut = new ChunkLUT(rule, adjustedLutBitSize);
	}
}

int ChunkLUTAgent::getN() {
	return N;
}

string ChunkLUTAgent::getRule() {
	return rule;
}

bool ChunkLUTAgent::hasAdjustedLut() {
	return adjustedLutBitSize != 0;
}

int ChunkLUTAgent::getAdjustedLutBitSize() {
	if (hasAdjustedLut()) {
		return adjustedLutBitSize;
	}
	
	return -1;
}

CHUNK ChunkLUTAgent::applyRule(CHUNK c, int leftLSB, int rightMSB, bool adjusted) {
	if (adjusted) {
		return adjustedLut->get(c, leftLSB, rightMSB);
	}

	return regularLut->get(c, leftLSB, rightMSB);
}