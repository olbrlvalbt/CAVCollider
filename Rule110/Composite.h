#pragma once

#include "Rule110DLL.h"

#include "PhaseSet.h"

class RULE110_DLL Composite {
private:
	std::vector<PhaseSet> phaseSets;
	std::string id;
	int horizontalSpeed;
	int verticalSpeed;

public:
	Composite();
	Composite(std::string _id, int _horizontalSpeed, int _verticalSpeed, std::vector<std::string> _phases);

	std::string getId() const;
	int horizontalSpeed1() const;
	int verticalSpeed1() const;
	PhaseSet getPhaseSet(std::string phaseKey);
	std::string getPhase(std::string phaseKey, int phase);
	std::string getByIndex(int phaseKeyIndex, int phaseIndex);

	static int TranslatePhaseKey(std::string phaseKey);
};

