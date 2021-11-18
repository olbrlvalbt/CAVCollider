#pragma once

#include "Rule110DLL.h"

#include "GliderMap.h"
#include "GliderSetMap.h"

#include <string>
#include <regex>

using namespace std;

class RULE110_DLL Rule110 {
public:
	string Translate(string s);

	Rule110();

private:
	GliderMap gliders;
	GliderSetMap gliderSets;

	char delimiter;
	
	regex rBin, rNum, rEther, rPhaseNum, rPhase, rPhaseParam,
		rParams, rGliderName, rGliderSetName, rCompositeName,
		rComposite, rExpression, rMultiple, rMultipleExpression;

	string multiply(const string& s, int multiple);
	string translate(const string& s);
	void initRegexes();
};