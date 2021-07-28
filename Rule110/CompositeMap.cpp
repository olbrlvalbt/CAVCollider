#include "stdafx.h"
#include "CompositeMap.h"

CompositeMap::CompositeMap() {
}

std::string CompositeMap::getId(std::string id) {
	for (auto& c : id) c = toupper(c);
	
	if (idMap.find(id) == idMap.end()) {
		throw CompositeNotFoundException(id);
	}
	
	return idMap[id];
}

Composite CompositeMap::getComposite(std::string id) {
	return compositeMap[getId(id)];
}

PhaseSet CompositeMap::getPhaseSet(std::string id, std::string phaseKey) {
	return compositeMap[getId(id)].getPhaseSet(phaseKey);
}

std::string CompositeMap::get(std::string id, std::string phaseKey, int phase) {
	return compositeMap[getId(id)].getPhase(phaseKey, phase);
}

std::string CompositeMap::getByIndex(std::string id, int phaseKeyIndex, int phaseIndex) {
	return compositeMap[getId(id)].getByIndex(phaseKeyIndex, phaseIndex);
}