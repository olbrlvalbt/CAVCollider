#include "pch.h"
#include "InteractionController.h"

InteractionController::InteractionController(int _N, int _rule)
	: NaiveController(_N, _rule) {
}

InteractionController::InteractionController(int _N, int _rule, string _initialCondition)
	: NaiveController(_N, _rule, _initialCondition) {
}

void InteractionController::hardReset(const string& newIc) {
	currentState = newIc;
	auxState = currentState;

	currentIteration = 0;
}

bool InteractionController::isInteractionPoint(int position) const {
	return !(interactionPoints.find(position) == interactionPoints.end());
}

bool InteractionController::isEnabledInteractionPoint(int position) const {
	return isInteractionPoint(position) && interactionPoints.at(position).isEnabled();
}

void InteractionController::setEnabled(int position, bool enable) {
	if (!isInteractionPoint(position)) {
		throw exception("Position for interaction point not found");
	}

	interactionPoints[position].setEnabled(enable);
}

void InteractionController::enableAll() {
	for (auto& val : interactionPoints) {
		val.second.enable();
	}
}

void InteractionController::disableAll() {
	for (auto& val : interactionPoints) {
		val.second.enable();
	}
}

void InteractionController::addInteractionPoint(int position, bool enabled) {
	if (isInteractionPoint(position)) {
		throw exception("Position for interaction point already registered");
	}

	interactionPoints[position] = InteractionPoint(position, enabled);
}

bool InteractionController::removeInteractionPoint(int position) {
	if (!isInteractionPoint(position)) {
		return false;
	}
	
	interactionPoints.erase(position);
	
	return true;
}

void InteractionController::updateInteractionPoint(int position, char leftVal, char rightVal) {
	if (!isInteractionPoint(position)) {
		throw exception("Position for interaction point not found");
	}

	interactionPoints[position].updateValues(leftVal, rightVal);
}

void InteractionController::getNeighbors(int i, char& prev, char& cur, char& next) {
	if (isEnabledInteractionPoint(i)) {
		prev = currentState.at((i - 1 + N) % N);
		cur = currentState.at(i);
		next = interactionPoints[i].getRightValue();
	}
	else if (isEnabledInteractionPoint((i - 1 + N) % N)) {
		prev = interactionPoints[(i - 1 + N) % N].getLeftValue();
		cur = currentState.at(i);
		next = currentState.at((i + 1) % N);
	}
	else {
		prev = currentState.at((i - 1 + N) % N);
		cur = currentState.at(i);
		next = currentState.at((i + 1) % N);
	}
}
