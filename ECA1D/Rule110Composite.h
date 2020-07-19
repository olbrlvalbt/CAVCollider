#pragma once

#include <regex>
#include <map>

#include "Rule110Glider.h"
#include "Rule110CompositeMaps.h"

using namespace std;

class Rule110Composite {
public:
	static string GetComposite(string _token);
	static string GetGlider(int _multiple, string _gliderId, char _gliderPhase, int _gliderPhaseNum, int _etherPhase);
	static string GetGliderSet(string _gliderSetId, char _gliderPhase, int _gliderPhaseNum, int _etherPhase);

	static bool IsComposite(string& _s);

	static bool IsGliderName(string _s);

private:
	static void processGlider(int& multiple, string& gliderId, string& _s);
	static void processPhase(char& gliderPhase, int& gliderPhaseNum, int& etherPhase, string _s);
};