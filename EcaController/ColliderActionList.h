#pragma once

#include <vector>
#include <map>

#include "EcaControllerCore.h"

enum class ECACONTROLLER_DLL ColliderAction {
	RING_DISABLE_LEFT,
	RING_DISABLE_RIGHT,
	RING_DISABLE_CENTRAL,
	RING_ENABLE_LEFT,
	RING_ENABLE_RIGHT,
	RING_ENABLE_CENTRAL,
	CONTACT_DISABLE_LEFT,
	CONTACT_DISABLE_RIGHT,
	CONTACT_ENABLE_LEFT,
	CONTACT_ENABLE_RIGHT
};

class ECACONTROLLER_DLL ColliderActionList {
private:
	std::multimap<long, ColliderAction> actions;
	
	ColliderAction parseAction(std::string s);
	std::map<std::string, ColliderAction> table;
	
public:
	ColliderActionList(std::string _actions);
	ColliderActionList(std::vector<std::string> _actions);
	const std::multimap<long, ColliderAction>& getActions();
	static int validate(std::vector<std::string> _actions);
	static std::string getActionsRegexStr();
	static std::map<std::string, ColliderAction> getActionTable();
};