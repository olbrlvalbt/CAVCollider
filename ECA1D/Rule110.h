#pragma once

#include <string>
#include <sstream>
#include <regex>

#include "Rule110Constants.h"
#include "Rule110Glider.h"

using namespace std;

class Rule110 {
public:
	Rule110();
	static string TranslateExpression(string _expression);
	static string GetToken(string _token);
	static string GetEtherMultiple(string _token);
};
