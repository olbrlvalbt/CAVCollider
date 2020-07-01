#include "EcaLogic.h"

EcaLogic::EcaLogic(int NI, int ruleI, int initialConditionI, EcaBoundary ecaBoundary) {
	if (initialConditionI == -1) {
		init(NI, ruleI, createRandomInitialCondition(NI), ecaBoundary);
	}
	else {
		init(NI, ruleI, toBinary(initialConditionI), ecaBoundary);
	}
}

EcaLogic::EcaLogic(int NI, int ruleI, string initialConditionI, EcaBoundary ecaBoundary) {
	init(NI, ruleI, initialConditionI, ecaBoundary);
}
void EcaLogic::init(int NI, int ruleI, string initialConditionI, EcaBoundary ecaBoundary) {
	N = NI;
	ruleNumber = ruleI;
	rule = toBinary(ruleI);
	for (int i = rule.length(); i < 8; i++) {
		rule = "0" + rule;
	}
	initialCondition = initialConditionI;
	for (int i = initialCondition.length(); i < N; i++) {
		initialCondition = "0" + initialCondition;
	}
	currentState = initialCondition;
	auxState = currentState;

	boundaryType = ecaBoundary;
}

EcaLogic::~EcaLogic() {
}

string EcaLogic::createRandomInitialCondition(int N) {
	srand(time(NULL));
	string newInitial = "";
	for (int i = 0; i < N; i++) {
		newInitial = to_string(rand() % 2) + newInitial;
	}
	return newInitial;
}

string EcaLogic::applyRule() {
	for (int i = 0; i < N; i++) {
		char prev, cur, next;
		if (i == 0) {
			switch (boundaryType) {
				case ECABOUNDARY_CLOSED:
					prev = '0';
					break;
				default:
					prev = currentState.at(N - 1);
			}
		}
		else {
			prev = currentState.at(i - 1);
		}
		cur = currentState.at(i);
		if (i == N - 1) {
			switch (boundaryType) {
			case ECABOUNDARY_CLOSED:
				next = '0';
				break;
			default:
				next = currentState.at(0);
			}
		}
		else {
			next = currentState.at(i + 1);
		}

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
	return auxState;
}

string EcaLogic::toBinary(int n) {
	string r = "";
	while (n != 0) {
		r = (n % 2 == 0 ? "0" : "1") + r;
		n /= 2;
	}
	return r;
}