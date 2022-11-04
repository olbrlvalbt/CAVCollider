#pragma once

#include "EcaControllerCore.h"

class ECACONTROLLER_DLL InteractionPoint {
private:
	int position;
	char leftValue;
	char rightValue;
	
	bool enabled;

public:
	InteractionPoint(int position = 0, bool enabled = false);

	void updateValues(char _leftValue, char _rightValue);

	void enable();
	void disable();
	void toggle();

	bool isEnabled() const;
	void setEnabled(bool _enabled);


	int getPosition() const;
	void setPosition(int _position);
	char getLeftValue() const;
	void setLeftValue(char _leftValue);
	char getRightValue() const;
	void setRightValue(char _rightValue);
};

