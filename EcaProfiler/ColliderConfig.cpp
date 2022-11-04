#include "ColliderConfig.h"

ColliderConfig::ColliderConfig(FilteredCollisionSystem* collisionSystem, int centralRingRadius)
	: ColliderConfig(collisionSystem, centralRingRadius,
		wxColour(245, 245, 245),
		wxColour(255, 255, 255)) {
}

ColliderConfig::ColliderConfig(FilteredCollisionSystem* collisionSystem, int centralRingRadius,
	wxColour deadColor, wxColour aliveColor)
	: collisionSystem(collisionSystem),
	deadCellColor(deadColor),
	aliveCellColor(aliveColor),
	centralRingRadius(centralRingRadius),
	centralAlphaRad((2 * M_PI) / (double)(collisionSystem->getCentralN())),
	leftAlphaRad((2 * M_PI) / (double)(collisionSystem->getLeftN())),
	rightAlphaRad((2 * M_PI) / (double)(collisionSystem->getRightN())) {
	const double ratio = (double)centralRingRadius / (double)collisionSystem->getCentralN();
	leftRingRadius = collisionSystem->getLeftN() * ratio;
	rightRingRadius = collisionSystem->getRightN() * ratio;

	relativeLeftContactPos = wxPoint(centralRingRadius * std::cos(collisionSystem->getCentralToLeftInteractionPos() * centralAlphaRad),
		centralRingRadius * std::sin(collisionSystem->getCentralToLeftInteractionPos() * centralAlphaRad));
	relativeRightContactPos = wxPoint(centralRingRadius * std::cos(collisionSystem->getCentralToRightInteractionPos() * centralAlphaRad),
		centralRingRadius * std::sin(collisionSystem->getCentralToRightInteractionPos() * centralAlphaRad));

	relativeLeftRingCenter = wxPoint((centralRingRadius + leftRingRadius) * std::cos(collisionSystem->getCentralToLeftInteractionPos() * centralAlphaRad),
		(centralRingRadius + leftRingRadius) * std::sin(collisionSystem->getCentralToLeftInteractionPos() * centralAlphaRad));
	relativeRightRingCenter = wxPoint((centralRingRadius + rightRingRadius) * std::cos(collisionSystem->getCentralToRightInteractionPos() * centralAlphaRad),
		(centralRingRadius + rightRingRadius) * std::sin(collisionSystem->getCentralToRightInteractionPos() * centralAlphaRad));

	double prevLeftAngle = collisionSystem->getLeftToCentralInteractionPos() * leftAlphaRad;
	leftRingContactPointAngle = (collisionSystem->getCentralToLeftInteractionPos() * centralAlphaRad) - M_PI;
	while (leftRingContactPointAngle < 0) {
		leftRingContactPointAngle += 2 * M_PI;
	}
	leftRingRotationOffsetAngle = leftRingContactPointAngle - prevLeftAngle;

	double prevRightAngle = collisionSystem->getRightToCentralInteractionPos() * rightAlphaRad;
	rightRingContactPointAngle = (collisionSystem->getCentralToRightInteractionPos() * centralAlphaRad) - M_PI;
	while (rightRingContactPointAngle < 0) {
		rightRingContactPointAngle += 2 * M_PI;
	}
	rightRingRotationOffsetAngle = rightRingContactPointAngle - prevRightAngle;
}

ColliderConfig::~ColliderConfig() {
	//delete collisionSystem;
}

FilteredCollisionSystem& ColliderConfig::getCollisionSystem() const {
	return *collisionSystem;
}

const wxColour& ColliderConfig::getDeadCellColor() const {
	return deadCellColor;
}

const wxColour& ColliderConfig::getAliveCellColor() const {
	return aliveCellColor;
}

int ColliderConfig::getCentralRingRadius() const {
	return centralRingRadius;
}

int ColliderConfig::getLeftRingRadius() const {
	return leftRingRadius;
}

int ColliderConfig::getRightRingRadius() const {
	return rightRingRadius;
}

const wxPoint& ColliderConfig::getRelativeLeftContactPos() const {
	return relativeLeftContactPos;
}

const wxPoint& ColliderConfig::getRelativeRightContactPos() const {
	return relativeRightContactPos;
}

const wxPoint& ColliderConfig::getRelativeLeftRingCenter() const {
	return relativeLeftRingCenter;
}

const wxPoint& ColliderConfig::getRelativeRightRingCenter() const {
	return relativeRightRingCenter;
}

double ColliderConfig::getCentralAlphaRad() const {
	return centralAlphaRad;
}

double ColliderConfig::getLeftAlphaRad() const {
	return leftAlphaRad;
}

double ColliderConfig::getRightAlphaRad() const {
	return rightAlphaRad;
}

long ColliderConfig::getCurrentIteration() {
	return collisionSystem->getCurrentIteration();
}

double ColliderConfig::getCentralAngleForPos(int i) {
	return i * centralAlphaRad;
}

double ColliderConfig::getLeftAngleForPos(int i) {
	return 2 * leftRingContactPointAngle - (i * leftAlphaRad + leftRingRotationOffsetAngle);
}

double ColliderConfig::getRightAngleForPos(int i) {
	return 2 * rightRingContactPointAngle - (i * rightAlphaRad + rightRingRotationOffsetAngle);
}
