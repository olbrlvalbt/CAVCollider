#pragma once

#include <wx/wx.h>

#include "FilteredCollisionSystem.h"

class ColliderConfig {
protected:
	std::unique_ptr<FilteredCollisionSystem> collisionSystem;

	wxColour deadCellColor;
	wxColour aliveCellColor;

	int centralRingRadius;
	int leftRingRadius;
	int rightRingRadius;

	//All relative with respect to the central ring center
	wxPoint relativeLeftContactPos;
	wxPoint relativeRightContactPos;
	wxPoint relativeLeftRingCenter;
	wxPoint relativeRightRingCenter;

	double centralAlphaRad;
	double leftAlphaRad;
	double rightAlphaRad;

	double leftRingContactPointAngle;
	double rightRingContactPointAngle;

	double leftRingRotationOffsetAngle;
	double rightRingRotationOffsetAngle;

public:
	ColliderConfig(FilteredCollisionSystem* collisionSystem, int centralRingRadius);
	ColliderConfig(FilteredCollisionSystem* collisionSystem, int centralRingRadius,
		wxColour deadColor, wxColour aliveColor);
	~ColliderConfig();

	FilteredCollisionSystem& getCollisionSystem() const;

	const wxColour& getDeadCellColor() const;
	const wxColour& getAliveCellColor() const;

	int getCentralRingRadius() const;
	int getLeftRingRadius() const;
	int getRightRingRadius() const;

	const wxPoint& getRelativeLeftContactPos() const;
	const wxPoint& getRelativeRightContactPos() const;
	const wxPoint& getRelativeLeftRingCenter() const;
	const wxPoint& getRelativeRightRingCenter() const;
	double getCentralAlphaRad() const;
	double getLeftAlphaRad() const;
	double getRightAlphaRad() const;

	long getCurrentIteration();

	double getCentralAngleForPos(int i);
	double getLeftAngleForPos(int i);
	double getRightAngleForPos(int i);
};

