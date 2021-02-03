#pragma once

#include <vector>

#include "EcaControllerCore.h"
#include "ChunkTranslator.h"
#include "ChunkLUTAgent.h"

using namespace std;
using namespace EcaControllerCore;

class ECACONTROLLER_DLL CompressedState {
private:
	
	int N;
	CHUNK* initialStateChunkArray;
	CHUNK* currentStateChunkArray;
	CHUNK* savedStateChunkArray;
	size_t chunkArrayLength;
	int mostSignificativeChunkBitSize;
	size_t mostSignificativeChunkPosition;
	long currentIteration;
	long savedIteration;
	size_t savedMSChunkPosition;

	vector<string> rawState;

private:
	void start(string& _initialCondition);
	void compress(CHUNK** pDestArray, string& _state);
	
	void createChunkArray(CHUNK** pChunkArray);
	void copyChunkArray(CHUNK** pSourceArray, CHUNK** pDestArray);

	int getMSBAt(int i);
	
public:
	CompressedState(string _initialCondition);
	CompressedState(int _N, string _initialCondition);
	
	void reset(string _newInitialCondition);
	void restart();

	void saveState();
	void applySavedState(bool applySavedCount = true);
	void resetWithSavedState();
	
	void applyRule(ChunkLUTAgent& lutAgent);

	bool hasAdjustedMostSignificativeChunk();
	size_t getMostSignificativeChunkPosition();
	bool isMostSignificativeChunkPosition(int i);
	int getMostSignificativeChunkBitSize();
	size_t getChunkArrayLength();
	long getCurrentIteration();
	CHUNK at(int i);

	const vector<string>& getRawState();
};
