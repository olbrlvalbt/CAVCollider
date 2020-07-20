#pragma once

#include <regex>
#include <map>

#include "Rule110Glider.h"
#include "Rule110GliderSet.h"

using namespace std;

class Rule110Composite {
public:
	static string GetComposite(string _token);
	static string GetGlider(int _multiple, string _gliderId, char _gliderPhase, size_t _gliderPhaseNum, size_t _etherPhase);
	static string GetGliderSet(string _gliderSetId, char _gliderPhase, size_t _gliderPhaseNum, size_t _etherPhase);

	static bool IsComposite(string& _s);

	static bool IsGliderName(string _s);

private:
	static void processGlider(int& multiple, string& gliderId, string& _s);
	static void processPhase(char& gliderPhase, size_t& gliderPhaseNum, size_t& etherPhase, string _s);
};