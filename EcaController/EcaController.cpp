#include "pch.h"
#include "EcaController.h"

EcaController::EcaController(int _N, int _rule)
	: EcaController(_N, _rule, CreateRandomBinaryString(_N)) {
}

EcaController::EcaController(int _N, int _rule, string _initialCondition) {
	if (_rule < 0 || _rule > 255) {
		throw exception("Rule must be between 0 and 255");
	}

	N = _N;
	ruleNumber = _rule;
	rule = FormatBinaryString(_rule, 8);

	initialCondition = _initialCondition;

	compressedState = new CompressedState(N, initialCondition);
	lutAgent = new ChunkLUTAgent(rule, N);
}



void EcaController::reset(string _newInitialCondition) {
	compressedState->reset(_newInitialCondition);
}

void EcaController::restart() {
	compressedState->restart();
}

void EcaController::saveState() {
	compressedState->saveState();
}

void EcaController::applySavedState(bool applySavedCount) {
	compressedState->applySavedState(applySavedCount);
}

void EcaController::resetWithSavedState() {
	compressedState->resetWithSavedState();
}

void EcaController::applyRule() {
	compressedState->applyRule(*lutAgent);
}

size_t EcaController::getChunkArrayLength() {
	return compressedState->getChunkArrayLength();
}

long EcaController::getCurrentIteration() {
	return compressedState->getCurrentIteration();
}

const vector<string>& EcaController::getCurrentState() {
	return compressedState->getRawState();
}

int EcaController::getN() {
	return N;
}

string EcaController::getRule() {
	return rule;
}