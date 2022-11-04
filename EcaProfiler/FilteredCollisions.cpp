#include "pch.h"

#include <iostream>
#include <fstream>

#include "FilteredCollisionSystem.h"
#include "Rule110.h"

using namespace std;

string filter(string state, string filter) {
	string s = "";
	for (int i = 0; i < state.length(); i++) {
		if (filter[i] == '1') {
			s += "*";
		}
		else if (filter[i] == '2') {
			s += "+";
		}
		else {
			s += state[i];
		}
	}
	
	return s;
}

TEST(FilteredCollision, TestCP) {
	string leftIc = "111110001110111000100110-2e-1111101110-2e-1110100110-2e-111110001110111000100110-4e-111110001110111000100110-2e-1111101110-2e-1110100110-2e-111110001110111000100110-2e";
	string centralIc = "40e";
	string rightIc = "10e";

	int leftToCentral = -28;
	int rightToCentral = 0;
	int centralToLeft = 70;
	int centralToRight = 0;

	string actions = "";

	int iterations = 2000;
	bool filtered = true;

	Rule110 r;

	string left = r.Translate(leftIc);
	string right = r.Translate(rightIc);
	string central = r.Translate(centralIc);

	int ltc = (leftToCentral - 1 + left.length()) % left.length();
	int rtc = (rightToCentral - 1 + right.length()) % right.length();
	int ctl = (centralToLeft - 1 + central.length()) % central.length();
	int ctr = (centralToRight - 1 + central.length()) % central.length();
	
	FilteredCollisionSystem system(left, right, central,
		ltc, ctl, rtc, ctr, actions);
	system.setAllContactsEnabled(true);

	ofstream leftFile("../ParticleEnciclopedia/Rings/left.txt");
	ofstream rightFile("../ParticleEnciclopedia/Rings/right.txt");
	ofstream centralFile("../ParticleEnciclopedia/Rings/central.txt");
	
	for(int i = 0; i < iterations; i++) {
		if (filtered) {
			leftFile << filter(system.getLeftState(), system.getLeftFilter()) << endl;
			rightFile << filter(system.getRightState(), system.getRightFilter()) << endl;
			centralFile << filter(system.getCentralState(), system.getCentralFilter()) << endl;
		}
		else {
			leftFile << system.getLeftState() << endl;
			rightFile << system.getRightState() << endl;
			centralFile << system.getCentralState() << endl;
		}

		system.execute();
	}

	leftFile.close();
	rightFile.close();
	centralFile.close();
	
	EXPECT_EQ(1, 1);
}