#pragma once

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

static const map<string, vector<array<string, 4>>> GLIDERMAP = {
   {"a", GLIDER_A},
   {"a4", GLIDER_A4},
   {"b", GLIDER_B},
   {"b_", GLIDER_Bbar},
   {"bb", GLIDER_Bbar},
   {"bbar", GLIDER_Bbar},
   {"b^", GLIDER_Bcirc},
   {"bc", GLIDER_Bcirc},
   {"bcirc", GLIDER_Bcirc},
   {"c1", GLIDER_C1},
   {"c2", GLIDER_C2},
   {"c3", GLIDER_C3},
   {"d1", GLIDER_D1},
   {"d2", GLIDER_D2},
   {"e", GLIDER_E},
   {"e2", GLIDER_E2},
   {"e3", GLIDER_E3},
   {"e4", GLIDER_E4},
   {"e5", GLIDER_E5},
   {"e_", GLIDER_Ebar},
   {"eb", GLIDER_Ebar},
   {"ebar", GLIDER_Ebar},
   {"f", GLIDER_F},
   {"g", GLIDER_G},
   {"h", GLIDER_H},
   {"gun", GLIDER_GUN}
};
