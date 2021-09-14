#pragma once

#include "EcaControllerCore.h"
#include "InteractionAgent.h"
#include "InteractionController.h"

class ECACONTROLLER_DLL CollisionSystem {
protected:
	int rule = 110;

	long currentIteration;
	
	InteractionController leftRing;
	InteractionController rightRing;
	InteractionController centralRing;

	InteractionAgent leftInteractionAgent;
	InteractionAgent rightInteractionAgent;

public:
	CollisionSystem(int leftN, string leftIC, int rightN, string rightIC, int centralN, string centralIC,
					 int leftToCentralIP, int centralToLeftIP, int rightToCentralIP, int centralToRightIP);

	bool setLeftEnabled(bool enabled);
	bool setRightEnabled(bool enabled);
	void setAllEnabled(bool enabled);
	bool isLeftEnabled() const;
	bool isRightEnabled() const;
	
	virtual void execute();
	virtual void restart();

	int getLeftN();
	int getRightN();
	int getCentralN();

	virtual const string& getLeftState();
	virtual const string& getRightState();
	virtual const string& getCentralState();

	virtual long getCurrentIteration();

	int getLeftToCentralInteractionPos() const;
	int getCentralToLeftInteractionPos() const;
	int getRightToCentralInteractionPos() const;
	int getCentralToRightInteractionPos() const;

	void executeAllInteractions();
	void applyAll();
};
