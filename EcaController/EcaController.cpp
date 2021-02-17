#include "pch.h"
#include "EcaController.h"

EcaController::EcaController(int _N, int _rule)
	: EcaController(_N, _rule, CreateRandomBinaryString(_N)) {
}

EcaController::EcaController(int _N, int _rule, string _initialCondition) {
	if (_rule < 0 || _rule > 255) {
		throw exception("Rule must be between 0 and 255");
	}
	if (_N < 3) {
		throw exception("N cannot be less than 3");
	}
	if (_N < _initialCondition.length()) {
		throw exception("N cannot be less than the length of the initial condition");
	}
	if (!IsBinaryString(_initialCondition)) {
		throw exception("Initial condition is not a binary string");
	}

	N = _N;
	ruleNumber = _rule;
	rule = FormatBinaryString(_rule, 8);

	initialCondition = _initialCondition;
}

int EcaController::getN() {
	return N;
}

size_t EcaController::getRuleNumber() {
	return ruleNumber;
}

string EcaController::getRule() {
	return rule;
}

EcaController::~EcaController() {
}