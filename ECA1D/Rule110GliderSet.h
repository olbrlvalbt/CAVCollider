#pragma once

#include "Rule110Glider.h"
#include "Rule110Basic.h"

#define GliderSet std::vector<std::array<std::string, 4>>

class Rule110GliderSet {
public:
	static Rule110GliderSet& singleton() {
		static Rule110GliderSet instance;
		return instance;
	}

	static const std::map<std::string, GliderSet> GLIDERSETMAP;


	static const GliderSet GLIDERSET_4_A4;
	static const GliderSet GLIDERSET_1ELE_C2;
	static const GliderSet GLIDERSET_0ELE_C2;
};