#include "pch.h"
#include "ChunkLUT.h"

ChunkLUT::ChunkLUT(string _rule, int _bitSize) {
	rule = _rule;

	bitSize = _bitSize;
	lutSize = pow(2, bitSize);

	lut = (CHUNK***)malloc(sizeof(CHUNK**) * lutSize);

	int i, j;
	for (i = 0; i < lutSize; i++) {
		lut[i] = (CHUNK**)malloc(sizeof(CHUNK*) * 2);

		lut[i][0] = (CHUNK*)malloc(sizeof(CHUNK) * 2);
		lut[i][1] = (CHUNK*)malloc(sizeof(CHUNK) * 2);

		string iState = FormatBinaryString(ToBinaryString(i), bitSize);
		string nextIState = FormatBinaryString("", bitSize);
		
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

ChunkLUT::~ChunkLUT() {
	int i;
	for(i = 0; i < lutSize; i++) {
		free(lut[i][0]);
		free(lut[i][1]);

		free(lut[i]);
	}
	
	free(lut);
}

int ChunkLUT::getLutSize() {
	return lutSize;
}

CHUNK ChunkLUT::get(int state, int leftLSB, int rightMSB) {
	return lut[state][leftLSB][rightMSB];
}

char ChunkLUT::applyElementalRule(char prev, char cur, char next) {
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