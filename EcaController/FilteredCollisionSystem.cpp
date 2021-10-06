#include "pch.h"

#include "FilteredCollisionSystem.h"

#include <thread>

FilteredCollisionSystem::FilteredCollisionSystem(int leftN, string leftIC, int rightN, string rightIC, int centralN, string centralIC,
                                                 int leftToCentralIP, int centralToLeftIP, int rightToCentralIP, int centralToRightIP)
		: CollisionSystem(leftN, leftIC, rightN, rightIC, centralN, centralIC,
			leftToCentralIP, centralToLeftIP, rightToCentralIP, centralToRightIP) {
	resetAllBuffers();
}

bool FilteredCollisionSystem::setLeftEnabled(bool enabled) {
	bool previous = CollisionSystem::setLeftEnabled(enabled);
	
	if (previous != enabled) {
		resetLeftBuffers();
	}

	return previous;
}

bool FilteredCollisionSystem::setRightEnabled(bool enabled) {
	bool previous = CollisionSystem::setRightEnabled(enabled);

	if (previous != enabled) {
		resetRightBuffers();
	}

	return previous;
}

void FilteredCollisionSystem::setAllEnabled(bool enabled) {
	CollisionSystem::setAllEnabled(enabled);
	
	resetAllBuffers();
}

const string& FilteredCollisionSystem::getLeftState() {
	return leftBuffer.state[0];
}

const string& FilteredCollisionSystem::getRightState() {
	return rightBuffer.state[0];
}

const string& FilteredCollisionSystem::getCentralState() {
	return centralBuffer.state[0];
}

const string& FilteredCollisionSystem::getLeftFilter() {
	return leftBuffer.filter[0];
}

const string& FilteredCollisionSystem::geRightFilter() {
	return rightBuffer.filter[0];
}

const string& FilteredCollisionSystem::getCentralFilter() {
	return centralBuffer.filter[0];
}

void FilteredCollisionSystem::execute() {
	CollisionSystem::execute();

	for (int i = 0; i < 3; i++) {
		leftBuffer.state[i] = leftBuffer.state[i + 1];
		rightBuffer.state[i] = rightBuffer.state[i + 1];
		centralBuffer.state[i] = centralBuffer.state[i + 1];

		leftBuffer.filter[i] = leftBuffer.filter[i + 1];
		rightBuffer.filter[i] = rightBuffer.filter[i + 1];
		centralBuffer.filter[i] = centralBuffer.filter[i + 1];
	}

	leftBuffer.state[3] = leftRing.getCurrentState()[0];
	rightBuffer.state[3] = rightRing.getCurrentState()[0];
	centralBuffer.state[3] = centralRing.getCurrentState()[0];

	leftBuffer.filter[3] = string(leftRing.getN(), '0');
	rightBuffer.filter[3] = string(rightRing.getN(), '0');
	centralBuffer.filter[3] = string(centralRing.getN(), '0');

	filterAll();
}

void FilteredCollisionSystem::restart() {
	CollisionSystem::restart();
	
	resetAllBuffers();
}

void FilteredCollisionSystem::resetLeftBuffers() {
	leftRing.hardReset(leftBuffer.state[0]);
	centralRing.hardReset(centralBuffer.state[0]);

	for (int i = 1; i < 4; i++) {
		if (leftInteractionAgent.isEnabled()) {
			leftInteractionAgent.executePoint();
		}

		leftRing.applyRule();
		centralRing.applyRule();

		leftBuffer.state[i] = leftRing.getCurrentState()[0];
		centralBuffer.state[i] = centralRing.getCurrentState()[0];

		leftBuffer.filter[i] = string(leftRing.getN(), '0');
		centralBuffer.filter[i] = string(centralRing.getN(), '0');
	}

	filter(leftBuffer);
	filter(centralBuffer);
}

void FilteredCollisionSystem::resetRightBuffers() {
	rightRing.hardReset(rightBuffer.state[0]);
	centralRing.hardReset(centralBuffer.state[0]);
	
	for (int i = 1; i < 4; i++) {
		if (rightInteractionAgent.isEnabled()) {
			rightInteractionAgent.executePoint();
		}
		
		rightRing.applyRule();
		centralRing.applyRule();
		
		rightBuffer.state[i] = rightRing.getCurrentState()[0];
		centralBuffer.state[i] = centralRing.getCurrentState()[0];
		
		rightBuffer.filter[i] = string(rightRing.getN(), '0');
		centralBuffer.filter[i] = string(centralRing.getN(), '0');
	}

	filter(rightBuffer);
	filter(centralBuffer);
}


void FilteredCollisionSystem::resetAllBuffers() {
	for (int i = 0; i < 4; i++) {
		if (i != 0) {
			executeAllInteractions();
			applyAll();
		}
		
		leftBuffer.state[i] = leftRing.getCurrentState()[0];
		rightBuffer.state[i] = rightRing.getCurrentState()[0];
		centralBuffer.state[i] = centralRing.getCurrentState()[0];

		leftBuffer.filter[i] = string(leftRing.getN(), '0');
		rightBuffer.filter[i] = string(rightRing.getN(), '0');
		centralBuffer.filter[i] = string(centralRing.getN(), '0');
	}

	filterAll();
}

void FilteredCollisionSystem::filter(IterationBuffer& buffer) {
	string f1 = "";
	string f2 = "";
	string f3 = "";
	string f4 = "";

	int n = buffer.state[0].length();

	for (int i = 0; i < n; i++) {
		f1 = buffer.state[0].at(i);
		f1 += buffer.state[0].at((i + 1) % n);
		f1 += buffer.state[0].at((i + 2) % n);
		f1 += buffer.state[0].at((i + 3) % n);

		f2 = buffer.state[1].at(i);
		f2 += buffer.state[1].at((i + 1) % n);
		f2 += buffer.state[1].at((i + 2) % n);
		f2 += buffer.state[1].at((i + 3) % n);

		f3 = buffer.state[2].at(i);
		f3 += buffer.state[2].at((i + 1) % n);
		f3 += buffer.state[2].at((i + 2) % n);
		f3 += buffer.state[2].at((i + 3) % n);

		f4 = buffer.state[3].at(i);
		f4 += buffer.state[3].at((i + 1) % n);

		if (f1.compare("1111") == 0 && f2.compare("1000") == 0 && f3.compare("1001") == 0 && f4.compare("10") == 0) {
			buffer.filter[0][i] = '1';
			buffer.filter[0][(i + 1) % n] = '1';
			buffer.filter[0][(i + 2) % n] = '1';
			buffer.filter[0][(i + 3) % n] = '1';

			buffer.filter[1][i] = '1';
			buffer.filter[1][(i + 1) % n] = '2';
			buffer.filter[1][(i + 2) % n] = '2';
			buffer.filter[1][(i + 3) % n] = '2';

			buffer.filter[2][i] = '1';
			buffer.filter[2][(i + 1) % n] = '2';
			buffer.filter[2][(i + 2) % n] = '2';
			buffer.filter[2][(i + 3) % n] = '1';

			buffer.filter[3][i] = '1';
			buffer.filter[3][(i + 1) % n] = '2';
		}
	}
}

void FilteredCollisionSystem::filterAll() {
	auto leftLambda = [&]() {
		filter(leftBuffer);
	};
	auto rightLambda = [&]() {
		filter(rightBuffer);
	};
	auto centralLambda = [&]() {
		filter(centralBuffer);
	};

	std::thread leftThread(leftLambda);
	std::thread rightThread(rightLambda);
	std::thread centralThread(centralLambda);

	leftThread.join();
	rightThread.join();
	centralThread.join();
}
