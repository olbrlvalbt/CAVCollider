#pragma once
#include "EcaControllerDLL.h"

namespace EcaControllerCore {
	ECACONTROLLER_DLL string ToBinaryString(int n);
	ECACONTROLLER_DLL bool IsBinaryString(string& s);
	ECACONTROLLER_DLL string FormatBinaryString(int k, int n);
	ECACONTROLLER_DLL string FormatBinaryString(string s, int n);
}

