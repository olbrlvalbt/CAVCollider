#pragma once

#include <string>
#include <sstream>
#include <regex>

#include "Rule110Constants.h"
#include "Rule110Glider.h"
#include "Rule110Composite.h"

using namespace std;

class Rule110 {
public:
	static string Translate(string _s);
	static string GetExpression(string _token);

	static string GetEther(int _multiply);
	static string GetMultiple(string _expression, int _multiple);

	static bool IsBinaryString(string& _s);
	static bool IsEther(string& _s);

	static void Trim(string& _s);
	static void ToLower(string& _s);
	static void ToUpper(string& _s);

private:
	static string getEther(string _expression);
};
