#pragma once

#include <wx/wx.h>

#include "CollisionSystem.h"

class ColliderConfiguration {
protected:
	CollisionSystem* collisionSystem;
	
	wxPen deadCellPen;
	wxPen aliveCellPen;

	int centralRingRadius;
	int leftRingRadius;
	int rightRingRadius;

	//All relative with respect to the central ring center
	wxPoint relativeLeftContactPos;
	wxPoint relativeRightContactPos;
	wxPoint relativeLeftRingCenter;
	wxPoint relativeRightRingCenter;

	const double centralAlphaRad;
	const double leftAlphaRad;
	const double rightAlphaRad;

public:
	ColliderConfiguration(CollisionSystem* collisionSystem, int centralRingRadius);
	ColliderConfiguration(CollisionSystem* collisionSystem, int centralRingRadius,
		wxColour deadColor, wxColour aliveColor);
	~ColliderConfiguration();

	CollisionSystem& getCollisionSystem() const;
	
	const wxPen& getDeadCellPen() const;
	const wxPen& getAliveCellPen() const;
	
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
};

