#pragma once

#include "EcaControllerCore.h"
#include "CollisionSystem.h"
#include "IterationBuffer.h"

class ECACONTROLLER_DLL FilteredCollisionSystem : public CollisionSystem {
public:
	FilteredCollisionSystem(int leftN, string leftIC, int rightN, string rightIC, int centralN, string centralIC,
		int leftToCentralIP, int centralToLeftIP, int rightToCentralIP, int centralToRightIP);
	
	bool setLeftEnabled(bool enabled);
	bool setRightEnabled(bool enabled);
	void setAllEnabled(bool enabled);

	const string& getLeftState() override;
	const string& getRightState() override;
	const string& getCentralState() override;

	const string& getLeftFilter();
	const string& geRightFilter();
	const string& getCentralFilter();
	
	void execute() override;
	void restart() override;

private:
	IterationBuffer leftBuffer;
	IterationBuffer rightBuffer;
	IterationBuffer centralBuffer;

	void resetLeftBuffers();
	void resetRightBuffers();
	void resetAllBuffers();

	void filter(IterationBuffer& buffer);
	void filterAll();
};

