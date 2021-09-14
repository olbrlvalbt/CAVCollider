#pragma once

#include <map>

#include "EcaControllerCore.h"
#include "NaiveController.h"
#include "InteractionPoint.h"

class ECACONTROLLER_DLL InteractionController : public NaiveController {
private:
	std::map<int, InteractionPoint> interactionPoints;

public:
	InteractionController(int _N, int _rule);
	InteractionController(int _N, int _rule, string _initialCondition);

	void hardReset(const string& newIc);
	
	void setEnabled(int position, bool enable);
	void enableAll();
	void disableAll();

	bool isInteractionPoint(int position) const;
	bool isEnabledInteractionPoint(int position) const;
	void addInteractionPoint(int position, bool enabled = false);
	bool removeInteractionPoint(int position);
	void updateInteractionPoint(int position, char leftVal, char rightVal);

	void getNeighbors(int i, char& prev, char& cur, char& next) override;
};
