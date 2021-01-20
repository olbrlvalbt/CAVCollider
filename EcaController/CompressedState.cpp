#include "pch.h"
#include "CompressedState.h"

CompressedState::CompressedState(unsigned int _N, unsigned char _rule, string _initialCondition) {
	if (_initialCondition.empty()) {
		throw "The initial condition cannot be empty";
	}
	if (_N < _initialCondition.length()) {
		throw "N cannot be less than the length of the initial condition";
	}

	N = _N;
	ruleNumber = _rule;
	rule = FormatBinaryString(ToBinaryString(_rule), 8);

	initialCondition = _initialCondition;

	//compressedCurrentState = CompressedState(initialCondition);
}