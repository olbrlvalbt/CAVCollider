#include "pch.h"
#include "InteractionPoint.h"

InteractionPoint::InteractionPoint(int position, bool enabled)
	: position(position),
	leftValue('0'),
	rightValue('0'),
	enabled(enabled) {
}

void InteractionPoint::updateValues(char _leftValue, char _rightValue) {
	leftValue = _leftValue;
	rightValue = _rightValue;
}

void InteractionPoint::enable() {
	enabled = true;
}

void InteractionPoint::disable() {
	enabled = false;
}

void InteractionPoint::toggle() {
	enabled = !enabled;
}

bool InteractionPoint::isEnabled() const {
	return enabled;
}

void InteractionPoint::setEnabled(bool _enabled) {
	enabled = _enabled;
}

int InteractionPoint::getPosition() const {
	return position;
}

void InteractionPoint::setPosition(int _position) {
	position = _position;
}

char InteractionPoint::getLeftValue() const {
	return leftValue;
}

void InteractionPoint::setLeftValue(char _leftValue) {
	leftValue = _leftValue;
}

char InteractionPoint::getRightValue() const {
	return rightValue;
}

void InteractionPoint::setRightValue(char _rightValue) {
	rightValue = _rightValue;
}