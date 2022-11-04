#include "pch.h"
#include "ChunkTranslator.h"

ChunkTranslator& ChunkTranslator::GetInstance() {
	static ChunkTranslator instance;
	return instance;
}

ChunkTranslator::ChunkTranslator() {
	 int ctLength = pow(2, CHUNK_BITSIZE);
	 int i;
	 for (i = 0; i < ctLength; i++) {
	     CHUNK_TRANSLATOR.push_back(FormatBinaryString(i, CHUNK_BITSIZE));
	 }
}

string ChunkTranslator::translate(int k) {
	/*if (k < 0 || k >= CHUNK_TRANSLATOR.size()) {
		throw exception("Index out of bounds for chunk translator of size " + CHUNK_TRANSLATOR.size());
	}*/

	return CHUNK_TRANSLATOR[k];
}