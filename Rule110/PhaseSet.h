#pragma once

#include "Rule110DLL.h"

#include <vector>

class RULE110_DLL PhaseSet {
private:
	std::vector<std::string> phases;

public:
	PhaseSet();
	PhaseSet(std::string phase1, std::string phase2, std::string phase3, std::string phase4);
	std::string getPhase(int i);
};

