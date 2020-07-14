#include "EcaLogic.h"

EcaLogic::EcaLogic(int _N, int _rule, EcaBoundary ecaBoundary = ECABOUNDARY_PERIODIC) {
	if (_N < 3) {
		_N = 3;
	}
	init(_N, _rule, createRandomInitialCondition(_N), 0, ecaBoundary);
}

EcaLogic::EcaLogic(int _N, int _rule, int _initialCondition, int numEtherRule110ForEdges = 0, EcaBoundary ecaBoundary = ECABOUNDARY_PERIODIC) {
	if (_N < 3 && numEtherRule110ForEdges == 0) {
		_N = 3;
	}
	if (_initialCondition == -1) {
		init(_N, _rule, createRandomInitialCondition(_N), numEtherRule110ForEdges, ecaBoundary);
	}
	else {
		init(_N, _rule, ToBinary(_initialCondition), numEtherRule110ForEdges, ecaBoundary);
	}
}

EcaLogic::EcaLogic(int _N, int _rule, string _initialCondition, int numEtherRule110ForEdges = 0, EcaBoundary ecaBoundary = ECABOUNDARY_PERIODIC) {
	if (_N < 3 && numEtherRule110ForEdges == 0) {
		_N = 3;
	}
	init(_N, _rule, _initialCondition, numEtherRule110ForEdges, ecaBoundary);
}

void EcaLogic::init(int _N, int _rule, string _initialCondition, int numEtherRule110ForEdges = 0, EcaBoundary ecaBoundary = ECABOUNDARY_PERIODIC) {
	ruleNumber = _rule;
	rule = ToBinary(_rule);
	for (int i = rule.length(); i < 8; i++) {
		rule = "0" + rule;
	}
	boundaryType = ecaBoundary;

	_initialCondition = CleanString(_initialCondition);

	int initialConditionLength = _initialCondition.length();

	initialCondition = _initialCondition;
	if (numEtherRule110ForEdges > 0) {
		if (initialConditionLength < _N) {
			int requiredEther = ((_N - initialConditionLength) / 2) / 14;
			requiredEther++;

			N = initialConditionLength + (requiredEther * 14 * 2);
			for (int i = 0; i < requiredEther; i++) {
				initialCondition = Rule110Ether + initialCondition + Rule110Ether;
			}
		}
		else {
			N = initialConditionLength + (numEtherRule110ForEdges * 14 * 2);
			for (int i = 0; i < numEtherRule110ForEdges; i++) {
				initialCondition = Rule110Ether + initialCondition + Rule110Ether;
			}
		}
	}
	else {
		if (initialConditionLength < _N) {
			N = _N;

			for (int i = initialConditionLength; i < N; i++) {
				initialCondition = "0" + initialCondition;
			}
		}
		else {
			N = initialConditionLength;
		}
	}

	currentState = initialCondition;
	auxState = currentState;
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
	/*char prev;
	char cur;
	char next;

	int boundaryInterval;
	switch (boundaryType) {
		case ECABOUNDARY_CLOSED:
			currentState.at(0) = '0';
			currentState.at(N - 1) = '0';
			boundaryInterval = 1;
			break;
		case ECABOUNDARY_PERIODIC:
		default:
			boundaryInterval = -1;
	}

	prev = currentState.at(0);
	cur = currentState.at(1);
	for (int i = boundaryInterval; i < N - boundaryInterval; i++) {
		next = currentState.at((i + 1 + N) % N);

		if (prev == '1') {
			if (cur == '1') {
				if (next == '1') { // 111
					auxState.at((i + N) % N) = rule.at(0);
				}
				else { // 110
					auxState.at((i + N) % N) = rule.at(1);
				}
			}
			else {
				if (next == '1') { // 101
					auxState.at((i + N) % N) = rule.at(2);
				}
				else { // 100
					auxState.at((i + N) % N) = rule.at(3);
				}
			}
		}
		else {
			if (cur == '1') {
				if (next == '1') { // 011
					auxState.at((i + N) % N) = rule.at(4);
				}
				else { // 010
					auxState.at((i + N) % N) = rule.at(5);
				}
			}
			else {
				if (next == '1') { // 001
					auxState.at((i + N) % N) = rule.at(6);
				}
				else { // 000
					auxState.at((i + N) % N) = rule.at(7);
				}
			}
		}
		prev = cur;
		cur = next;
	}

	currentState = auxState;
	return auxState;*/
	char prev, cur, next;
	for (int i = 0; i < N; i++) {
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

string EcaLogic::ToBinary(int n) {
	string r = "";
	while (n != 0) {
		r = (n % 2 == 0 ? "0" : "1") + r;
		n /= 2;
	}
	return r;
}

string EcaLogic::CleanString(string s) {
	regex regexp("[^01]");
	return regex_replace(s, regexp, "");
}