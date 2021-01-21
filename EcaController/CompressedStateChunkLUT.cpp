#include "pch.h"
#include "CompressedStateChunkLUT.h"

CompressedStateChunkLUT::CompressedStateChunkLUT(int _rule, int _chunkFunctionalSize)
	: CompressedStateChunkLUT(FormatBinaryString(_rule, 8), _chunkFunctionalSize){ }

CompressedStateChunkLUT::CompressedStateChunkLUT(string _rule, int _chunkFunctionalSize) {
	if (_rule.empty()) {
		throw exception("Rule cannot be empty");
	}
	if (!IsBinaryString(_rule)) {
		throw exception("Rule is not a binary string");
	}
	if (_rule.length() > 8) {
		throw exception("Rule length cannot exceed 8");
	}
	if (_chunkFunctionalSize > CHUNK_SIZE || _chunkFunctionalSize <= 0) {
		throw exception("Chunk size must be between 1 and " + CHUNK_SIZE);
	}

	rule = FormatBinaryString(_rule, 8);

	chunkFunctionalSize = _chunkFunctionalSize;
	lutSize = pow(2, chunkFunctionalSize);

	lut = (chunk***)malloc(sizeof(chunk**) * lutSize);

	int i, j;
	for (i = 0; i < lutSize; i++) {
		lut[i] = (chunk**)malloc(sizeof(chunk*) * 2);

		lut[i][0] = (chunk*)malloc(sizeof(chunk) * 2);
		lut[i][1] = (chunk*)malloc(sizeof(chunk) * 2);

		string iState = FormatBinaryString(ToBinaryString(i), chunkFunctionalSize);
		string nextIState = FormatBinaryString("", chunkFunctionalSize);
		
		if (iState.length() == 1) {
			nextIState.at(0) = applyElementalRule('0', iState.at(0), '0');
			lut[i][0][0] = stoi(nextIState, 0, 2);
			nextIState.at(0) = applyElementalRule('0', iState.at(0), '1');
			lut[i][0][1] = stoi(nextIState, 0, 2);
			nextIState.at(0) = applyElementalRule('1', iState.at(0), '0');
			lut[i][1][0] = stoi(nextIState, 0, 2);
			nextIState.at(0) = applyElementalRule('1', iState.at(0), '1');
			lut[i][1][1] = stoi(nextIState, 0, 2);
		}
		else {
			char prev, cur, next;
			for (j = 1; j < iState.length() - 1; j++) {
				prev = iState.at(j - 1);
				cur = iState.at(j);
				next = iState.at(j + 1);

				nextIState.at(j) = applyElementalRule(prev, cur, next);
			}

			nextIState.at(0) = applyElementalRule('0', iState.at(0), iState.at(1));
			nextIState.at(iState.length() - 1) = applyElementalRule(iState.at(iState.length() - 2), iState.at(iState.length() - 1), '0');
			lut[i][0][0] = stoi(nextIState, 0, 2);

			nextIState.at(0) = applyElementalRule('0', iState.at(0), iState.at(1));
			nextIState.at(iState.length() - 1) = applyElementalRule(iState.at(iState.length() - 2), iState.at(iState.length() - 1), '1');
			lut[i][0][1] = stoi(nextIState, 0, 2);

			nextIState.at(0) = applyElementalRule('1', iState.at(0), iState.at(1));
			nextIState.at(iState.length() - 1) = applyElementalRule(iState.at(iState.length() - 2), iState.at(iState.length() - 1), '0');
			lut[i][1][0] = stoi(nextIState, 0, 2);

			nextIState.at(0) = applyElementalRule('1', iState.at(0), iState.at(1));
			nextIState.at(iState.length() - 1) = applyElementalRule(iState.at(iState.length() - 2), iState.at(iState.length() - 1), '1');
			lut[i][1][1] = stoi(nextIState, 0, 2);
		}
	}
}

int CompressedStateChunkLUT::getLutSize() {
	return lutSize;
}

string CompressedStateChunkLUT::getRule() {
	return rule;
}

chunk CompressedStateChunkLUT::applyRule(int state, int leftLSB, int rightMSB) {
	if (state < 0) {
		throw exception("State cannot be negative");
	}
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