#pragma once

#include "Rule110DLL.h"

#include <map>
#include <string>

#include "Composite.h"

class RULE110_DLL CompositeMap {
protected:
	CompositeMap();
	
	std::map<std::string, Composite> compositeMap;
	std::map<std::string, std::string> idMap;

public:
	Composite getComposite(std::string id);
	PhaseSet getPhaseSet(std::string id, std::string phaseKey);
	std::string get(std::string id, std::string phaseKey, int phase);
	std::string getByIndex(std::string id, int phaseKeyIndex, int phaseIndex);

	std::string getId(std::string id);
};

