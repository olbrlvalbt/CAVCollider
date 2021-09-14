#include "pch.h"
#include "CollisionSystem.h"

#include <thread>

CollisionSystem::CollisionSystem(int leftN, string leftIC, int rightN, string rightIC, int centralN, string centralIC,
                                 int leftToCentralIP, int centralToLeftIP, int rightToCentralIP, int centralToRightIP)
		: currentIteration(0),
		leftRing(leftN, rule, leftIC),
		rightRing(rightN, rule, rightIC),
		centralRing(centralN, rule, centralIC),
		leftInteractionAgent(leftRing, leftToCentralIP, centralRing, centralToLeftIP),
		rightInteractionAgent(rightRing, rightToCentralIP, centralRing, centralToRightIP) {

}

bool CollisionSystem::setLeftEnabled(bool enabled) {
	return leftInteractionAgent.setEnabled(enabled);
}

bool CollisionSystem::setRightEnabled(bool enabled) {
	return rightInteractionAgent.setEnabled(enabled);
}

void CollisionSystem::setAllEnabled(bool enabled) {
	leftInteractionAgent.setEnabled(enabled);
	rightInteractionAgent.setEnabled(enabled);
}

bool CollisionSystem::isLeftEnabled() const {
	return leftInteractionAgent.isEnabled();
}

bool CollisionSystem::isRightEnabled() const {
	return rightInteractionAgent.isEnabled();
}

void CollisionSystem::execute() {
	executeAllInteractions();
	applyAll();
}

void CollisionSystem::restart() {
	leftRing.restart();
	rightRing.restart();
	centralRing.restart();
	
	currentIteration = 0;
}

int CollisionSystem::getLeftN() {
	return leftRing.getN();
}

int CollisionSystem::getRightN() {
	return rightRing.getN();
}

int CollisionSystem::getCentralN() {
	return centralRing.getN();
}

const string& CollisionSystem::getLeftState() {
	return leftRing.getCurrentState()[0];
}

const string& CollisionSystem::getRightState() {
	return rightRing.getCurrentState()[0];
}

const string& CollisionSystem::getCentralState() {
	return centralRing.getCurrentState()[0];
}

long CollisionSystem::getCurrentIteration() {
	return currentIteration;
}

int CollisionSystem::getLeftToCentralInteractionPos() const {
	return leftInteractionAgent.getInteractionPositionFor(1);
}

int CollisionSystem::getCentralToLeftInteractionPos() const {
	return leftInteractionAgent.getInteractionPositionFor(2);
}

int CollisionSystem::getRightToCentralInteractionPos() const {
	return rightInteractionAgent.getInteractionPositionFor(1);
}

int CollisionSystem::getCentralToRightInteractionPos() const {
	return rightInteractionAgent.getInteractionPositionFor(2);
}

void CollisionSystem::executeAllInteractions() {
	if (leftInteractionAgent.isEnabled()) {
		leftInteractionAgent.executePoint();
	}
	if (rightInteractionAgent.isEnabled()) {
		rightInteractionAgent.executePoint();
	}
}

void CollisionSystem::applyAll() {
	auto leftLambda = [&]() {
		leftRing.applyRule();
	};
	auto rightLambda = [&]() {
		rightRing.applyRule();
	};
	auto centralLambda = [&]() {
		centralRing.applyRule();
	};

	std::thread leftThread(leftLambda);
	std::thread rightThread(rightLambda);
	std::thread centralThread(centralLambda);

	leftThread.join();
	rightThread.join();
	centralThread.join();
	
	/*leftRing.applyRule();
	rightRing.applyRule();
	centralRing.applyRule();*/

	currentIteration++;
}
