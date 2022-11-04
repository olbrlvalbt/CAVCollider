#pragma once

#include "InteractionController.h"
#include "EcaControllerCore.h"

class ECACONTROLLER_DLL InteractionAgent {
private:
	InteractionController& controller1;
	int interactionPosition1;
	
	InteractionController& controller2;
	int interactionPosition2;

	bool enabled;

public:
	InteractionAgent(InteractionController& controller1, int interactionPosition1, InteractionController& controller2, int interactionPosition2);

	InteractionController& getController(int i);

	int getInteractionPositionFor(InteractionController* controller) const;
	int getInteractionPositionFor(int i) const;

	bool executePoint();

	void enable();
	void disable();
	void toggle();
	bool setEnabled(bool _enabled);

	bool isEnabled() const;
};


