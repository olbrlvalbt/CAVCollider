#pragma once

#include <string>
#include <time.h>
#include "EcaControllerDLL.h"

using namespace std;

namespace EcaControllerCore {
	typedef unsigned short CHUNK;
	ECACONTROLLER_DLL extern const int CHUNK_BITSIZE;
	
	ECACONTROLLER_DLL string ToBinaryString(int n);
	ECACONTROLLER_DLL bool IsBinaryString(string& s);
	ECACONTROLLER_DLL string FormatBinaryString(int k, int n);
	ECACONTROLLER_DLL string FormatBinaryString(string s, int n);
	ECACONTROLLER_DLL string CreateRandomBinaryString(int n);
}