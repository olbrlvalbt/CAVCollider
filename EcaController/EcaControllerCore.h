#pragma once
#include "EcaControllerDLL.h"

namespace EcaControllerCore {
	ECACONTROLLER_DLL string ToBinaryString(unsigned int n);
	ECACONTROLLER_DLL bool IsBinaryString(string& s);
	ECACONTROLLER_DLL string FormatBinaryString(string s, unsigned int n);
}

