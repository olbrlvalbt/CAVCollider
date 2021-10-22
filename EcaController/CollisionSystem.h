#pragma once

#include "ColliderActionList.h"
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

	bool leftRingEnabled;
	bool rightRingEnabled;
	bool centralRingEnabled;

	ColliderActionList* actionList;

public:
	CollisionSystem(int leftN, string leftIC, int rightN, string rightIC, int centralN, string centralIC,
					 int leftToCentralIP, int centralToLeftIP, int rightToCentralIP, int centralToRightIP);
	
	CollisionSystem(string leftIC, string rightIC, string centralIC,
		int leftToCentralIP, int centralToLeftIP, int rightToCentralIP, int centralToRightIP,
		string actionList);

	virtual bool setLeftContactEnabled(bool enabled);
	virtual bool setRightContactEnabled(bool enabled);
	virtual void setAllContactsEnabled(bool enabled);
	
	bool isLeftContactEnabled() const;
	bool isRightContactEnabled() const;

	bool setLeftRingEnabled(bool enabled);
	bool setRightRingEnabled(bool enabled);
	bool setCentralRingEnabled(bool enabled);
	bool isLeftRingEnabled() const;
	bool isRightRingEnabled() const;
	bool isCentralRingEnabled() const;
	
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
	
	void executeActions();
	void executeAllInteractions();
	void applyAll(bool cancelIterationIncrement = false);
};