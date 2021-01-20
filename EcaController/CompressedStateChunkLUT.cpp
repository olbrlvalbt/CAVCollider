#include "pch.h"
#include "CompressedStateChunkLUT.h"

CompressedStateChunkLUT::CompressedStateChunkLUT(string _rule, unsigned char _chunkLength) {
	if (_rule.empty()) {
		throw exception("Rule cannot be empty");
	}
	if (!IsBinaryString(_rule)) {
		throw exception("Rule is not a binary string");
	}
	if (_rule.length() > 8) {
		throw exception("Rule length cannot exceed 8");
	}
	if (_chunkLength > 16 || _chunkLength == 0) {
		throw exception("Chunk length must be between 1 and 16");
	}

	rule = _rule;

	chunkLength = _chunkLength;
	lutSize = pow(2, chunkLength);

	lut = (unsigned short***)malloc(lutSize);

	int i, j;
	for (i = 0; i < lutSize; i++) {
		lut[i] = (unsigned short**)malloc(2);

		lut[i][0] = (unsigned short*)malloc(2);
		lut[i][1] = (unsigned short*)malloc(2);

		string iState = FormatBinaryString(ToBinaryString(i), chunkLength);
		string nextIState = FormatBinaryString("", chunkLength);

		char prev, cur, next;
		for (j = 1; j < iState.length() - 1; j++) {
			prev = iState.at(j - 1);
			cur = iState.at(j);
			next = iState.at(j + 1);

			nextIState.at(j) = applyRule(prev, cur, next);
		}

		nextIState.at(0) = applyRule('0', iState.at(0), iState.at(1));
		nextIState.at(iState.length() - 1) = applyRule(iState.at(iState.length() - 2), iState.at(iState.length() - 1), '0');
		unsigned short compressedNext00 = std::stoi(nextIState);
		lut[i][0][0] = compressedNext00;

		nextIState.at(0) = applyRule('0', iState.at(0), iState.at(1));
		nextIState.at(iState.length() - 1) = applyRule(iState.at(iState.length() - 2), iState.at(iState.length() - 1), '1');
		unsigned short compressedNext01 = std::stoi(nextIState);
		lut[i][0][1] = compressedNext01;

		nextIState.at(0) = applyRule('1', iState.at(0), iState.at(1));
		nextIState.at(iState.length() - 1) = applyRule(iState.at(iState.length() - 2), iState.at(iState.length() - 1), '0');
		unsigned short compressedNext10 = std::stoi(nextIState);
		lut[i][1][0] = compressedNext10;

		nextIState.at(0) = applyRule('1', iState.at(0), iState.at(1));
		nextIState.at(iState.length() - 1) = applyRule(iState.at(iState.length() - 2), iState.at(iState.length() - 1), '1');
		unsigned short compressedNext11 = std::stoi(nextIState);
		lut[i][1][1] = compressedNext11;
	}
}

unsigned int CompressedStateChunkLUT::getLutSize() {
	return lutSize;
}

unsigned short CompressedStateChunkLUT::applyRule(unsigned short state, unsigned char leftLSB, unsigned char rightMSB) {
	if (state >= lutSize) {
		throw exception("State out of bounds for lut of size " + lutSize);
	}
	if (leftLSB != 0 && leftLSB != 1) {
		throw exception("Left LSB must be 0 or 1");
	}
	if (rightMSB != 0 && rightMSB != 1) {
		throw exception("Right MSB must be 0 or 1");
	}

	return lut[state][leftLSB][rightMSB];
}

char CompressedStateChunkLUT::applyElementalRule(char prev, char cur, char next) {
	if (prev == '1') {
		if (cur == '1') {
			if (next == '1') { // 111
				return rule.at(0);
			}
			else { // 110
				return rule.at(1);
			}
		}
		else {
			if (next == '1') { // 101
				return rule.at(2);
			}
			else { // 100
				return rule.at(3);
			}
		}
	}
	else {
		if (cur == '1') {
			if (next == '1') { // 011
				return rule.at(4);
			}
			else { // 010
				return rule.at(5);
			}
		}
		else {
			if (next == '1') { // 001
				return rule.at(6);
			}
			else { // 000
				return rule.at(7);
			}
		}
	}
}