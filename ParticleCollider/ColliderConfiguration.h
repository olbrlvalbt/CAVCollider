#pragma once

#include <wx/wx.h>

#include "CollisionSystem.h"
#include "FilteredCollisionSystem.h"

class ColliderConfiguration {
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
	ColliderConfiguration(FilteredCollisionSystem* collisionSystem, int centralRingRadius);
	ColliderConfiguration(FilteredCollisionSystem* collisionSystem, int centralRingRadius,
		wxColour deadColor, wxColour aliveColor);
	~ColliderConfiguration();

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

