#pragma once

#include <string>
#include <regex>

#include "Rule110Constants.h"

using namespace std;

class Rule110Basic
{
public:
	static string GetEther(int _multiply);
	static string GetMultiple(string _expression, int _multiple);

	static bool IsBinaryString(string& _s);
	static bool IsEther(string& _s);

	static void Trim(string& _s);
	static void ToLower(string& _s);
	static void ToLower(char& _c);
	static void ToUpper(string& _s);
	static void ToUpper(char& _c);
};

