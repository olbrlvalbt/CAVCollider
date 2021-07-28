#pragma once

#include "Rule110DLL.h"

#include <regex>
#include <map>

#include "GliderMap.h"
#include "GliderSetMap.h"
#include "Rule110Glider.h"
#include "Rule110GliderSet.h"

using namespace std;

class RULE110_DLL Rule110Composite {
public:
	Rule110Composite(GliderMap _gliderMap, GliderSetMap _gliderSetMap);
	
	string GetComposite(string _token);
	string GetGlider(int _multiple, string _gliderId, string _gliderPhaseKey, size_t _phase);
	string GetGliderSet(string _gliderSetId, string _gliderSetPhaseKey, size_t _phase);

	bool IsComposite(string& _s);

	bool IsGliderName(string _s);

private:
	void processGlider(int& multiple, string& gliderId, string& _s);
	void processPhase(char& gliderPhase, size_t& gliderPhaseNum, size_t& etherPhase, string _s);

	GliderMap gliderMap;
	GliderSetMap gliderSetMap;
};