#include "pch.h"
#include "InteractionAgent.h"

InteractionAgent::InteractionAgent(InteractionController& controller1, int interactionPosition1, InteractionController& controller2, int interactionPosition2)
	: controller1(controller1),
	interactionPosition1(interactionPosition1),
	controller2(controller2),
	interactionPosition2(interactionPosition2),
	enabled(false) {
	controller1.addInteractionPoint(interactionPosition1);
	controller2.addInteractionPoint(interactionPosition2);
}

InteractionController& InteractionAgent::getController(int i) {
	if (i == 1) {
		return controller1;
	}

	return controller2;
}

int InteractionAgent::getInteractionPositionFor(InteractionController* controller) const {
	if (controller == &controller1) {
		return interactionPosition1;
	}

	if (controller == &controller2) {
		return interactionPosition2;
	}

	return -1;
}

int InteractionAgent::getInteractionPositionFor(int i) const {
	if (i == 1) {
		return interactionPosition1;
	}

	return interactionPosition2;
}

bool InteractionAgent::executePoint() {
	if(isEnabled()) {
		int nextPoint1 = interactionPosition1 + 1 < controller1.getN() ? interactionPosition1 + 1 : 0;
		int nextPoint2 = interactionPosition2 + 1 < controller2.getN() ? interactionPosition2 + 1 : 0;
		
		char old1prev = controller1.getAtPosition(interactionPosition1);
		char old2prev = controller2.getAtPosition(interactionPosition2);
		char old1next = controller1.getAtPosition(nextPoint1);
		char old2next = controller2.getAtPosition(nextPoint2);

		controller1.updateInteractionPoint(interactionPosition1, old2prev, old2next);
		controller2.updateInteractionPoint(interactionPosition2, old1prev, old1next);

		return true;
	}
	
	return false;
}

void InteractionAgent::enable() {
	enabled = true;
	controller1.setEnabled(interactionPosition1, true);
	controller2.setEnabled(interactionPosition2, true);
}

void InteractionAgent::disable() {
	enabled = false;
	controller1.setEnabled(interactionPosition1, false);
	controller2.setEnabled(interactionPosition2, false);
}

void InteractionAgent::toggle() {
	enabled = !enabled;
	controller1.setEnabled(interactionPosition1, enabled);
	controller2.setEnabled(interactionPosition2, enabled);
}

bool InteractionAgent::setEnabled(bool _enabled) {
	bool oldEnabled = enabled;
	
	enabled = _enabled;
	controller1.setEnabled(interactionPosition1, enabled);
	controller2.setEnabled(interactionPosition2, enabled);
	
	return oldEnabled;
}

bool InteractionAgent::isEnabled() const {
	return enabled && controller1.isEnabledInteractionPoint(interactionPosition1) && controller2.isEnabledInteractionPoint(interactionPosition2);
}
