#pragma once
#include "EcaControllerCore.h"

using namespace std;
using namespace EcaControllerCore;

class ECACONTROLLER_DLL CompressedStateChunkArray {
private:
	typedef unsigned short* ChunkArray;

	string state;
	ChunkArray initialStateChunkArray;
	ChunkArray currentStateChunkArray;
	size_t stateChunkArrayLength;
	bool hasMostSignificativeChunkLut;
	size_t mostSignificativeChunkPosition;

private:
	void compress(ChunkArray* pChunkArray, string& _state);
	void createChunkArray(ChunkArray* pChunkArray);
	void copyChunkArray(ChunkArray* pSourceArray, ChunkArray* pDestArray);
public:
	CompressedStateChunkArray(string _state);
};
