#include "pch.h"
#include "NaiveController.h"

NaiveController::NaiveController(int _N, int _rule)
	: NaiveController(_N, _rule, CreateRandomBinaryString(_N)) {
}

NaiveController::NaiveController(int _N, int _rule, string _initialCondition)
	: EcaController(_N, _rule, _initialCondition) {
	initialCondition = FormatBinaryString(_initialCondition, N);

	currentState = initialCondition;
	auxState = currentState;

	currentIteration = 0;
	savedIteration = -1;
}

NaiveController::~NaiveController() {
}

void NaiveController::reset() {
	reset(CreateRandomBinaryString(N));
}

void NaiveController::reset(string _newInitialCondition) {
	if (_newInitialCondition.empty()) {
		throw exception("Initial condition cannot be empty");
	}
	if (N < _newInitialCondition.length()) {
		string ex = "Initial condition cannot be longer than current N: " + to_string(N);
		throw exception(ex.c_str());
	}
	if (!IsBinaryString(_newInitialCondition)) {
		throw exception("Initial condition is not a binary string");
	}
	
	initialCondition = FormatBinaryString(_newInitialCondition, N);

	currentState = initialCondition;
	auxState = currentState;

	currentIteration = 0;
}

void NaiveController::restart() {
	currentState = initialCondition;
	auxState = currentState;

	currentIteration = 0;
}

void NaiveController::saveState() {
	savedState = currentState;
	savedIteration = currentIteration;
}

void NaiveController::applySavedState(bool applySavedCount) {
	if (savedIteration == -1) {
		throw exception("Saved state not found");
	}

	currentState = savedState;

	if (applySavedCount) {
		currentIteration = savedIteration;
	}
	else {
		currentIteration++;
	}
}

void NaiveController::resetWithSavedState() {
	if (savedIteration == -1) {
		throw exception("Saved state not found");
	}

	initialCondition = savedState;

	currentState = initialCondition;
	auxState = currentState;
	
	currentIteration = 0;
}

long NaiveController::getCurrentIteration() {
	return currentIteration;
}

void NaiveController::setCurrentIteration(long newIt) {
	currentIteration = newIt;
}

const vector<string>& NaiveController::getCurrentState() {
	stateVector = { currentState };
	return stateVector;
}

void NaiveController::getNeighbors(int i, char& prev, char& cur, char& next) {
	if (i == 0) {
		prev = currentState.at(N - 1);
	}
	else {
		prev = currentState.at(i - 1);
	}
	cur = currentState.at(i);
	if (i == N - 1) {
		next = currentState.at(0);
	}
	else {
		next = currentState.at(i + 1);
	}
}

void NaiveController::applyRule() {
	char prev, cur, next;
	for (int i = 0; i < N; i++) {
		getNeighbors(i, prev, cur, next);

		if (prev == '1') {
			if (cur == '1') {
				if (next == '1') { // 111
					auxState.at(i) = rule.at(0);
				}
				else { // 110
					auxState.at(i) = rule.at(1);
				}
			}
			else {
				if (next == '1') { // 101
					auxState.at(i) = rule.at(2);
				}
				else { // 100
					auxState.at(i) = rule.at(3);
				}

			}
		}
		else {
			if (cur == '1') {
				if (next == '1') { // 011
					auxState.at(i) = rule.at(4);
				}
				else { // 010
					auxState.at(i) = rule.at(5);
				}
			}
			else {
				if (next == '1') { // 001
					auxState.at(i) = rule.at(6);
				}
				else { // 000
					auxState.at(i) = rule.at(7);
				}

			}
		}
	}
	
	currentState = auxState;
	currentIteration++;
}

char NaiveController::setAtPosition(int position, char newValue) {
	char oldValue = getAtPosition(position);

	currentState[position] = newValue;

	return oldValue;
}

char NaiveController::getAtPosition(int position) {
	return currentState[position];
}
