#include "pch.h"
#include "CompressedState.h"

CompressedState::CompressedState(string _initialCondition)
	: CompressedState(_initialCondition.length(), _initialCondition) { }

CompressedState::CompressedState(int _N, string _initialCondition) {
	if (_N <= 0) {
		throw exception("N cannot be negative nor zero");
	}
	if (_N < _initialCondition.length()) {
		throw exception("N cannot be less than the length of the initial condition");
	}
	if (!IsBinaryString(_initialCondition)) {
		throw exception("Initial condition is not a binary string");
	}

	N = _N;
	
	mostSignificativeChunkBitSize = N % CHUNK_BITSIZE;
	mostSignificativeChunkBitSize = (mostSignificativeChunkBitSize == 0 ? CHUNK_BITSIZE : mostSignificativeChunkBitSize);

	chunkArrayLength = N / CHUNK_BITSIZE;
	if (hasAdjustedMostSignificativeChunk()) {
		chunkArrayLength++;
	}

	savedIteration = -1;

	rawState = vector<string>(chunkArrayLength, "");
	ChunkTranslator::GetInstance();

	createChunkArray(&initialStateChunkArray);
	createChunkArray(&currentStateChunkArray);

	start(_initialCondition);
}

void CompressedState::reset(string _newInitialCondition) {
	if (_newInitialCondition.empty()) {
		throw exception("Initial condition cannot be empty");
	}
	if (N < _newInitialCondition.length()) {
		string ex = "Initial condition cannot be longer than current N: " + to_string(N);
		throw exception(ex.c_str());
	}
	if (!IsBinaryString(_newInitialCondition)) {
		throw exception("Initial condition is not a binary string");
	}
	
	createChunkArray(&initialStateChunkArray);
	createChunkArray(&currentStateChunkArray);
	
	start(_newInitialCondition);
}

void CompressedState::start(string& _initialCondition) {
	mostSignificativeChunkPosition = chunkArrayLength - 1;
	currentIteration = 0;

	compress(&initialStateChunkArray, _initialCondition);
	copyChunkArray(&initialStateChunkArray, &currentStateChunkArray);
}

void CompressedState::restart() {
	mostSignificativeChunkPosition = chunkArrayLength - 1;
	currentIteration = 0;
	
	copyChunkArray(&initialStateChunkArray, &currentStateChunkArray);
}

void CompressedState::saveState() {
	copyChunkArray(&currentStateChunkArray, &savedStateChunkArray);
	savedIteration = currentIteration;
	savedMSChunkPosition = mostSignificativeChunkPosition;
}

void CompressedState::applySavedState(bool applySavedCount) {
	if (savedIteration == -1) {
		throw exception("Saved state not found");
	}
	
	mostSignificativeChunkPosition = savedMSChunkPosition;
	copyChunkArray(&savedStateChunkArray, &currentStateChunkArray);

	if (applySavedCount) {
		currentIteration = savedIteration;
	}
	else {
		savedIteration++;
	}
}

void CompressedState::resetWithSavedState() {
	if (savedIteration == -1) {
		throw exception("Saved state not found");
	}

	currentIteration = 0;
	mostSignificativeChunkPosition = savedMSChunkPosition;
	copyChunkArray(&savedStateChunkArray, &initialStateChunkArray);
}

void CompressedState::compress(CHUNK** pDestArray, string & _state) {
	int i, j, k;
	string stateChunk = "";
	for (i = _state.length() - 1, j = 1, k = 0; i >= 0; i--, j++) {
		stateChunk = _state.at(i) + stateChunk;
		
		if (j >= CHUNK_BITSIZE) {
			(*pDestArray)[k] = stoi(stateChunk, 0, 2);

			stateChunk = "";
			k++;
			j = 0;
		}
	}
	if (!stateChunk.empty()) {
		(*pDestArray)[k] = stoi(stateChunk, 0, 2);
		k++;
	}
	
	for (k; k < chunkArrayLength; k++) {
		(*pDestArray)[k] = 0;
	}
}

void CompressedState::createChunkArray(CHUNK** pChunkArray) {
	*pChunkArray = (CHUNK*)malloc(sizeof(CHUNK) * chunkArrayLength);
}

void CompressedState::copyChunkArray(CHUNK** pSourceArray, CHUNK** pDestArray) {
	CHUNK* iSrc = *pSourceArray;
	CHUNK* iDst = *pDestArray;

	int i;
	for (i = 0; i < chunkArrayLength; i++, iSrc++, iDst++) {
		*iDst = *iSrc;
	}
}

void CompressedState::applyRule(ChunkLUTAgent& lutAgent) {
	if (chunkArrayLength == 1) {
		currentStateChunkArray[0] = lutAgent.applyRule(currentStateChunkArray[0],
													   currentStateChunkArray[0] & 1,
													   getMSBAt(0),
													   isMostSignificativeChunkPosition(0)
		);
	}
	else {
		CHUNK leftmostChunk = currentStateChunkArray[0];
		CHUNK leftmostNextChunk = lutAgent.applyRule(leftmostChunk,
												 	 currentStateChunkArray[chunkArrayLength - 1] & 1,
													 getMSBAt(1),
													 isMostSignificativeChunkPosition(0)
		);
		int msbAt0 = getMSBAt(0);

		int i;
		for (i = 1; i < chunkArrayLength - 1; i++) {
			currentStateChunkArray[i - 1] = lutAgent.applyRule(currentStateChunkArray[i],
															   currentStateChunkArray[i - 1] & 1,
															   getMSBAt(i + 1),
															   isMostSignificativeChunkPosition(i)
			);
		}
		currentStateChunkArray[chunkArrayLength - 2] = lutAgent.applyRule(currentStateChunkArray[chunkArrayLength - 1],
																		  currentStateChunkArray[chunkArrayLength - 2] & 1,
																		  msbAt0,
																		  isMostSignificativeChunkPosition(chunkArrayLength - 1)
		);

		currentStateChunkArray[chunkArrayLength - 1] = leftmostNextChunk;

		mostSignificativeChunkPosition = (mostSignificativeChunkPosition - 1 + chunkArrayLength) % chunkArrayLength;
	}
}

bool CompressedState::hasAdjustedMostSignificativeChunk() {
	return mostSignificativeChunkBitSize != CHUNK_BITSIZE;
}

size_t CompressedState::getMostSignificativeChunkPosition() {
	return mostSignificativeChunkPosition;
}

bool CompressedState::isMostSignificativeChunkPosition(int i) {
	return mostSignificativeChunkPosition == i;
}

int CompressedState::getMostSignificativeChunkBitSize() {
	return mostSignificativeChunkBitSize;
}

size_t CompressedState::getChunkArrayLength() {
	return chunkArrayLength;
}

long CompressedState::getCurrentIteration() {
	return currentIteration;
}

CHUNK CompressedState::at(int i) {
	return currentStateChunkArray[i];
}

int CompressedState::getMSBAt(int i) {
	if (i == mostSignificativeChunkPosition) {
		return (currentStateChunkArray[i] >> (mostSignificativeChunkBitSize - 1)) & 1;
	}
	else {
		return (currentStateChunkArray[i] >> (CHUNK_BITSIZE - 1)) & 1;
	}
}

const vector<string>& CompressedState::getRawState() {
	int i, j;
	rawState[0] = ChunkTranslator::GetInstance().translate(
		currentStateChunkArray[mostSignificativeChunkPosition]
	).substr(CHUNK_BITSIZE - mostSignificativeChunkBitSize);
	
	for (i = mostSignificativeChunkPosition - 1, j = 1; i >= 0; i--, j++) {
		rawState[j] = ChunkTranslator::GetInstance().translate(currentStateChunkArray[i]);
	}
	for (i = chunkArrayLength - 1; i > mostSignificativeChunkPosition; i--, j++) {
		rawState[j] = ChunkTranslator::GetInstance().translate(currentStateChunkArray[i]);
	}

	return rawState;
}