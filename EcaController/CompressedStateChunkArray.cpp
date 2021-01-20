#include "pch.h"
#include "CompressedStateChunkArray.h"

CompressedStateChunkArray::CompressedStateChunkArray(string _state) {
	if (_state.empty()) {
		throw exception("State cannot be empty");
	}
	if (!IsBinaryString(_state)) {
		throw exception("State is not a binary string");
	}

	state = _state;

	hasMostSignificativeChunkLut = state.length() % 16 != 0;

	stateChunkArrayLength = (state.length() / 16);
	if (hasMostSignificativeChunkLut) {
		stateChunkArrayLength++;
	}

	mostSignificativeChunkPosition = stateChunkArrayLength - 1;

	createChunkArray(&initialStateChunkArray);
	compress(&initialStateChunkArray, state);

	createChunkArray(&currentStateChunkArray);
	copyChunkArray(&initialStateChunkArray, &currentStateChunkArray);
}

void CompressedStateChunkArray::compress(ChunkArray* pChunkArray, string& _state) {
	int i, j, k;

	string stateChunk = "";
	for (i = _state.length() - 1, j = 1, k = 0; i >= 0; i--, j++) {
		stateChunk = _state.at(i) + stateChunk;
		if (j > 16) {
			(*pChunkArray)[k] = stoi(stateChunk, 0, 2);

			stateChunk = "";
			k++;
			j = 0;
		}
	}
	(*pChunkArray)[k] = stoi(stateChunk, 0, 2);
}

void CompressedStateChunkArray::createChunkArray(ChunkArray* pChunkArray) {
	*pChunkArray = (ChunkArray)malloc(stateChunkArrayLength);
}

void CompressedStateChunkArray::copyChunkArray(ChunkArray* pSourceArray, ChunkArray* pDestArray) {
	ChunkArray iSrc = *pSourceArray;
	ChunkArray iDst = *pDestArray;

	int i;
	for (i = 0; i < stateChunkArrayLength; i++, iSrc++, iDst++) {
		*iDst = *iSrc;
	}
}