#include "stdafx.h"
#include "Composite.h"

Composite::Composite()
	: id(""), horizontalSpeed(0), verticalSpeed(0), phaseSets({}){
}

Composite::Composite(std::string _id, int _horizontalSpeed, int _verticalSpeed, std::vector<std::string> _phases)
	:id(_id), horizontalSpeed(_horizontalSpeed), verticalSpeed(_verticalSpeed) {
	if (_phases.size() % 4 != 0) {
		throw exception("PhaseSets must have 4 components");
	}
	int i;
	int numPhaseSets = _phases.size() / 4;

	for (i = 3; i < _phases.size(); i+= 4) {
		phaseSets.push_back(PhaseSet(_phases[i - 3], _phases[i - 2], _phases[i - 1], _phases[i]));
	}
}

std::string Composite::getId() const {
	return id;
}

int Composite::horizontalSpeed1() const {
	return horizontalSpeed;
}

int Composite::verticalSpeed1() const {
	return verticalSpeed;
}

int Composite::TranslatePhaseKey(std::string phaseKey) {
	char phaseKeyChar = toupper(phaseKey.at(0));
	if (phaseKeyChar < 'A' || phaseKeyChar > 'Z') {
		throw exception("Invalid phaseKey");
	}

	int phaseKeyNum = 1;

	if (phaseKey.length() > 1) {
		try {
			phaseKeyNum = stoi(phaseKey.substr(1));
		}
		catch (exception e) {
			throw exception("Invalid phaseKey");
		}
	}

	if (phaseKeyNum <= 0) {
		throw exception("Invalid phaseKey");
	}

	return (phaseKeyChar - 'A') + ((phaseKeyNum - 1) * 8);
}

PhaseSet Composite::getPhaseSet(std::string phaseKey) {
	int phaseSetIdx = TranslatePhaseKey(phaseKey);
	if (phaseSetIdx >= phaseSets.size()) {
		throw PhaseNotFoundException(id);
	}

	return phaseSets[phaseSetIdx];
}
std::string Composite::getPhase(std::string phaseKey, int phase) {
	int phaseSetIdx = TranslatePhaseKey(phaseKey);
	if (phaseSetIdx >= phaseSets.size()) {
		throw PhaseNotFoundException(id);
	}

	if (phase < 1 || phase > 4) {
		throw exception("Phase must be 1 - 4");
	}

	std::string phaseResult = phaseSets[phaseSetIdx].getPhase(phase);
	if (phaseResult.length() == 0) {
		throw PhaseNotFoundException(id);
	}

	return phaseResult;
}

std::string Composite::getByIndex(int phaseKeyIndex, int phaseIndex) {
	if (phaseKeyIndex >= phaseSets.size()) {
		throw PhaseNotFoundException(id);
	}

	if (phaseIndex < 0 || phaseIndex > 3) {
		throw exception("Phase index must be 0 - 3");
	}

	std::string phaseResult = phaseSets[phaseKeyIndex].getPhase(phaseIndex + 1);
	if (phaseResult.length() == 0) {
		throw PhaseNotFoundException(id);
	}

	return phaseResult;
}
