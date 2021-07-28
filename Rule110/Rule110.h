#pragma once

#include "Rule110DLL.h"

#include <string>
#include <sstream>
#include <regex>
#include <exception>

#include "GliderMap.h"
#include "GliderSetMap.h"
#include "Rule110Basic.h"
#include "Rule110Composite.h"

using namespace std;

class RULE110_DLL Rule110 {
public:
	string Translate(string _s);
	string GetExpression(string _token);

	Rule110();

private:
	string translateNested(string& _s, string::const_iterator& it);
	string getEther(string _expression);

	GliderMap* gliderMap;
	GliderSetMap* gliderSetMap;

	Rule110Composite* rule110Composite;
};
