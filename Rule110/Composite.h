#pragma once

#include "Rule110DLL.h"

#include "PhaseSet.h"

class RULE110_DLL Composite {
private:
	std::vector<PhaseSet> phaseSets;
	std::string id;

public:
	Composite();
	Composite(std::string _id, std::vector<std::string> _phases);

	std::string getId();
	PhaseSet getPhaseSet(std::string phaseKey);
	std::string getPhase(std::string phaseKey, int phase);
	std::string getByIndex(int phaseKeyIndex, int phaseIndex);

	static int TranslatePhaseKey(std::string phaseKey);
};

