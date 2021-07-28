#include "stdafx.h"
#include "PhaseSet.h"


PhaseSet::PhaseSet()
	: phases({"", "", "", ""}){
}

PhaseSet::PhaseSet(std::string phase1, std::string phase2, std::string phase3, std::string phase4)
	: phases( {phase1, phase2, phase3, phase4} ){
}

std::string PhaseSet::getPhase(int i) {
	if (i < 1 || i > 4) {
		throw exception("Phase must be 1 - 4");
	}

	string phase = phases[i - 1];
	if (phase.length() == 0) {
		throw PhaseNotFoundException(std::to_string(i));
	}
	
	return phase;
}
