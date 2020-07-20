#pragma once

#include <string>
#include <array>
#include <vector>
#include <map>

#define Glider std::vector<std::array<std::string, 4>>

class Rule110Glider {
public:
	static Rule110Glider& singleton() {
		static Rule110Glider instance;
		return instance;
	}


	static const Glider GLIDER_A;
	static const Glider GLIDER_A4;

	static const Glider GLIDER_B;
	static const Glider GLIDER_Bbar;
	static const Glider GLIDER_Bcirc;

	static const Glider GLIDER_C1;
	static const Glider GLIDER_C2;
	static const Glider GLIDER_C3;

	static const Glider GLIDER_D1;
	static const Glider GLIDER_D2;

	static const Glider GLIDER_E;
	static const Glider GLIDER_E2;
	static const Glider GLIDER_E3;
	static const Glider GLIDER_E4;
	static const Glider GLIDER_E5;
	static const Glider GLIDER_Ebar;

	static const Glider GLIDER_F;

	static const Glider GLIDER_G;

	static const Glider GLIDER_H;

	static const Glider GLIDER_GUN;


	static const std::map<std::string, Glider> GLIDERMAP;
};