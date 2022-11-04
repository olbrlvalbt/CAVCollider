#pragma once

#include "EcaControllerCore.h"
#include "CollisionSystem.h"
#include "IterationBuffer.h"

class ECACONTROLLER_DLL FilteredCollisionSystem : public CollisionSystem {
public:
	FilteredCollisionSystem(int leftN, string leftIC, int rightN, string rightIC, int centralN, string centralIC,
		int leftToCentralIP, int centralToLeftIP, int rightToCentralIP, int centralToRightIP);

	FilteredCollisionSystem(string leftIC, string rightIC, string centralIC,
		int leftToCentralIP, int centralToLeftIP, int rightToCentralIP, int centralToRightIP,
		string actionList);
	
	FilteredCollisionSystem(string leftIC, string rightIC, string centralIC,
		int leftToCentralIP, int centralToLeftIP, int rightToCentralIP, int centralToRightIP,
		vector<string> actionList);
	
	bool setLeftContactEnabled(bool enabled) override;
	bool setRightContactEnabled(bool enabled) override;
	void setAllContactsEnabled(bool enabled) override;

	const string& getLeftState() override;
	const string& getRightState() override;
	const string& getCentralState() override;

	const string& getLeftFilter();
	const string& getRightFilter();
	const string& getCentralFilter();
	
	void execute() override;
	void restart() override;

	void jumpToIteration(long it, function<void(int)>& lambda) override;

private:
	IterationBuffer leftBuffer;
	IterationBuffer rightBuffer;
	IterationBuffer centralBuffer;

	void resetLeftBuffers();
	void resetRightBuffers();
	void resetAllBuffers(bool firstRun = false);

	void filter(IterationBuffer& buffer);
	void filterAll();
};

