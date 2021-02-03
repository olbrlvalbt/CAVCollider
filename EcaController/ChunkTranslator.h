#pragma once

#include <vector>

#include "EcaControllerCore.h"

using namespace std;
using namespace EcaControllerCore;

class ECACONTROLLER_DLL ChunkTranslator {
public:
    static ChunkTranslator& GetInstance();
	
private:
    vector<string> CHUNK_TRANSLATOR;
    ChunkTranslator();
	
    //ChunkTranslator(ChunkTranslator const&);
    //void operator=(ChunkTranslator const&);

public:
    ChunkTranslator(ChunkTranslator const&) = delete;
    void operator=(ChunkTranslator const&) = delete;

    string translate(int k);
};