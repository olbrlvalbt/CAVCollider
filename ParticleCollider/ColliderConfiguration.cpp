#include "ColliderConfiguration.h"


ColliderConfiguration::ColliderConfiguration(CollisionSystem* collisionSystem, int centralRingRadius)
	: ColliderConfiguration(collisionSystem, centralRingRadius, 
		wxColour(245, 245, 245),
		wxColour(255, 255, 255)) {
}


ColliderConfiguration::ColliderConfiguration(CollisionSystem* collisionSystem, int centralRingRadius,
	wxColour deadColor, wxColour aliveColor)
	: collisionSystem(collisionSystem),
	deadCellPen(wxPen(deadColor)),
	aliveCellPen(wxPen(aliveColor)),
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
}

ColliderConfiguration::~ColliderConfiguration() {
	delete collisionSystem;
}

CollisionSystem& ColliderConfiguration::getCollisionSystem() const {
	return *collisionSystem;
}

const wxPen& ColliderConfiguration::getDeadCellPen() const {
	return deadCellPen;
}

const wxPen& ColliderConfiguration::getAliveCellPen() const {
	return aliveCellPen;
}

int ColliderConfiguration::getCentralRingRadius() const {
	return centralRingRadius;
}

int ColliderConfiguration::getLeftRingRadius() const {
	return leftRingRadius;
}

int ColliderConfiguration::getRightRingRadius() const {
	return rightRingRadius;
}

const wxPoint& ColliderConfiguration::getRelativeLeftContactPos() const {
	return relativeLeftContactPos;
}

const wxPoint& ColliderConfiguration::getRelativeRightContactPos() const {
	return relativeRightContactPos;
}

const wxPoint& ColliderConfiguration::getRelativeLeftRingCenter() const {
	return relativeLeftRingCenter;
}

const wxPoint& ColliderConfiguration::getRelativeRightRingCenter() const {
	return relativeRightRingCenter;
}

double ColliderConfiguration::getCentralAlphaRad() const {
	return centralAlphaRad;
}

double ColliderConfiguration::getLeftAlphaRad() const {
	return leftAlphaRad;
}

double ColliderConfiguration::getRightAlphaRad() const {
	return rightAlphaRad;
}

long ColliderConfiguration::getCurrentIteration() {
	return collisionSystem->getCurrentIteration();
}
