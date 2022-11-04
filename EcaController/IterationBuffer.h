#pragma once
#include "EcaControllerCore.h"

class ECACONTROLLER_DLL IterationBuffer {
public:
	string state[4] = {"", "", "", ""};
	string filter[4] = { "", "", "", "" };
};

