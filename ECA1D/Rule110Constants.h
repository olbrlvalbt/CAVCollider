#pragma once

#include <string>
#include <regex>
#include <map>

class Rule110Constants {
public:
	static Rule110Constants& singleton() {
		static Rule110Constants instance;
		return instance;
	}

	static const std::regex REGEX_BINARY;
	static const std::regex REGEX_ETHER;
	static const std::regex REGEX_COMPOSITE;
	static const std::regex REGEX_GLIDER;


	static const std::string ETHER[4];

	static const std::string ETHER_F1_1;
};
