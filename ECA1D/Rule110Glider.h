#pragma once

#include <string>
#include <regex>
#include <map>

#include "Rule110GliderConstants.h"

using namespace std;

class Rule110Glider {
public:
	static string GetGlider(string _expression);
	static string GetGlider(int _multiple, string _gliderId, int _etherPhase);
	static string GetGlider(int _multiple, string _gliderId, string _gliderPhase, int _etherPhase);
	static string GetGlider(int _multiple, string _gliderId, char _gliderPhaseChar, int _gliderPhaseNum, int _etherPhase);
};



static const map<string, std::vector<std::array<std::string, 4>>> gliderMap = {
   {"a", GLIDER_A}
};
