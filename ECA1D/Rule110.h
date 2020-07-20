#pragma once

#include <string>
#include <sstream>
#include <regex>

#include "Rule110Basic.h"
#include "Rule110Composite.h"

using namespace std;

class Rule110 {
public:
	static string Translate(string _s);
	static string GetExpression(string _token);


private:
	static string getEther(string _expression);
};
