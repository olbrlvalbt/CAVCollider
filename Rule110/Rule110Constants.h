#pragma once

#include "Rule110DLL.h"

#include <string>
#include <regex>
#include <map>

class RULE110_DLL Rule110Constants {
private:
	static const std::string STRING_MULTIPLE;
	static const std::string STRING_BINARY;
	static const std::string STRING_ETHER;
	static const std::string STRING_COMPOSITENAME;
	static const std::string STRING_GLIDERNAME;
	static const std::string STRING_COMPOSITEPHASE;
	static const std::string STRING_COMPOSITE;
	static const std::string STRING_EXPRESSION;

public:
	static Rule110Constants& singleton() {
		static Rule110Constants instance;
		return instance;
	}

	static const std::regex REGEX_BINARY;
	static const std::regex REGEX_ETHER;
	static const std::regex REGEX_COMPOSITENAME;
	static const std::regex REGEX_GLIDERNAME;
	static const std::regex REGEX_COMPOSITEPHASE;
	static const std::regex REGEX_COMPOSITE;
	static const std::regex REGEX_EXPRESSION;


	static const std::string ETHER[4];

	static const std::string ETHER_F1_1;
};
