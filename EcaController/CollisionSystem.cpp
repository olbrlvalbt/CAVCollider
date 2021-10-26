#include "pch.h"
#include "CollisionSystem.h"

#include <thread>

CollisionSystem::CollisionSystem(int leftN, string leftIC, int rightN, string rightIC, int centralN, string centralIC,
                                 int leftToCentralIP, int centralToLeftIP, int rightToCentralIP, int centralToRightIP)
		: currentIteration(0),
		leftRing(leftN, rule, leftIC),
		rightRing(rightN, rule, rightIC),
		centralRing(centralN, rule, centralIC),
		leftRingEnabled(true),
		rightRingEnabled(true),
		centralRingEnabled(true),
		leftInteractionAgent(leftRing, leftToCentralIP, centralRing, centralToLeftIP),
		rightInteractionAgent(rightRing, rightToCentralIP, centralRing, centralToRightIP),
		actionList(new ColliderActionList("")) {
	
}

CollisionSystem::CollisionSystem(string leftIC, string rightIC, string centralIC, int leftToCentralIP,
								 int centralToLeftIP, int rightToCentralIP, int centralToRightIP, string _actionList)
		: currentIteration(0),
		leftRing(leftIC.length(), rule, leftIC),
		rightRing(rightIC.length(), rule, rightIC),
		centralRing(centralIC.length(), rule, centralIC),
		leftRingEnabled(true),
		rightRingEnabled(true),
		centralRingEnabled(true),
		leftInteractionAgent(leftRing, leftToCentralIP, centralRing, centralToLeftIP),
		rightInteractionAgent(rightRing, rightToCentralIP, centralRing, centralToRightIP),
		actionList(new ColliderActionList(_actionList)) {

}

CollisionSystem::CollisionSystem(string leftIC, string rightIC, string centralIC, int leftToCentralIP,
	int centralToLeftIP, int rightToCentralIP, int centralToRightIP, vector<string> _actionList)
	: currentIteration(0),
	leftRing(leftIC.length(), rule, leftIC),
	rightRing(rightIC.length(), rule, rightIC),
	centralRing(centralIC.length(), rule, centralIC),
	leftRingEnabled(true),
	rightRingEnabled(true),
	centralRingEnabled(true),
	leftInteractionAgent(leftRing, leftToCentralIP, centralRing, centralToLeftIP),
	rightInteractionAgent(rightRing, rightToCentralIP, centralRing, centralToRightIP),
	actionList(new ColliderActionList(_actionList)) {

}

bool CollisionSystem::setLeftContactEnabled(bool enabled) {
	return leftInteractionAgent.setEnabled(enabled);
}

bool CollisionSystem::setRightContactEnabled(bool enabled) {
	return rightInteractionAgent.setEnabled(enabled);
}

void CollisionSystem::setAllContactsEnabled(bool enabled) {
	leftInteractionAgent.setEnabled(enabled);
	rightInteractionAgent.setEnabled(enabled);
}

bool CollisionSystem::isLeftContactEnabled() const {
	return leftInteractionAgent.isEnabled();
}

bool CollisionSystem::isRightContactEnabled() const {
	return rightInteractionAgent.isEnabled();
}

bool CollisionSystem::setLeftRingEnabled(bool enabled) {
	bool prev = leftRingEnabled;
	leftRingEnabled = enabled;
	return prev;
}

bool CollisionSystem::setRightRingEnabled(bool enabled) {
	bool prev = rightRingEnabled;
	rightRingEnabled = enabled;
	return prev;
}

bool CollisionSystem::setCentralRingEnabled(bool enabled) {
	bool prev = centralRingEnabled;
	centralRingEnabled = enabled;
	return prev;
}

bool CollisionSystem::isLeftRingEnabled() const {
	return leftRingEnabled;
}

bool CollisionSystem::isRightRingEnabled() const {
	return rightRingEnabled;
}

bool CollisionSystem::isCentralRingEnabled() const {
	return centralRingEnabled;
}

void CollisionSystem::execute() {
	executeActions();
	executeAllInteractions();
	applyAll();
}

void CollisionSystem::restart() {
	leftRing.restart();
	rightRing.restart();
	centralRing.restart();

	leftRingEnabled = true;
	rightRingEnabled = true;
	centralRingEnabled = true;
	
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
	if (leftRingEnabled && centralRingEnabled && leftInteractionAgent.isEnabled()) {
		leftInteractionAgent.executePoint();
	}
	if (rightRingEnabled && centralRingEnabled && rightInteractionAgent.isEnabled()) {
		rightInteractionAgent.executePoint();
	}
}

void CollisionSystem::applyAll(bool cancelIterationIncrement) {
	auto leftLambda = [&]() {
		if (leftRingEnabled)
			leftRing.applyRule();
	};
	auto rightLambda = [&]() {
		if (rightRingEnabled)
			rightRing.applyRule();
	};
	auto centralLambda = [&]() {
		if (centralRingEnabled)
			centralRing.applyRule();
	};

	std::thread leftThread(leftLambda);
	std::thread rightThread(rightLambda);
	std::thread centralThread(centralLambda);

	leftThread.join();
	rightThread.join();
	centralThread.join();

	if(!cancelIterationIncrement) {
		currentIteration++;
	}
}


void CollisionSystem::executeActions() {
	auto it = actionList->getActions().equal_range(currentIteration);

	for (auto itr = it.first; itr != it.second; ++itr) {
		switch (itr->second) {
		case ColliderAction::CONTACT_DISABLE_LEFT:
			setLeftContactEnabled(false);
			break;
		case ColliderAction::CONTACT_DISABLE_RIGHT:
			setRightContactEnabled(false);
			break;
		case ColliderAction::CONTACT_ENABLE_LEFT:
			setLeftContactEnabled(true);
			break;
		case ColliderAction::CONTACT_ENABLE_RIGHT:
			setRightContactEnabled(true);
			break;
		case ColliderAction::RING_DISABLE_LEFT:
			setLeftRingEnabled(false);
			break;
		case ColliderAction::RING_DISABLE_RIGHT:
			setRightRingEnabled(false);
			break;
		case ColliderAction::RING_DISABLE_CENTRAL:
			setCentralRingEnabled(false);
			break;
		case ColliderAction::RING_ENABLE_LEFT:
			setLeftRingEnabled(true);
			break;
		case ColliderAction::RING_ENABLE_RIGHT:
			setRightRingEnabled(true);
			break;
		case ColliderAction::RING_ENABLE_CENTRAL:
			setCentralRingEnabled(true);
			break;
		}
	}
}
