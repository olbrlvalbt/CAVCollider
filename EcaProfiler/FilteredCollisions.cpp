#include "pch.h"

#include <iostream>
#include <fstream>

#include "FilteredCollisionSystem.h"

using namespace std;

TEST(FilteredCollision, TestCP) {
	string leftIc = "111110001001101111100010011011111000100110";
	string centralIc = "1111100010011011111000100110111110001001101111100010011011111000100110111110001001101111100010011011111000010001111101011111000100110";
	string rightIc = "11111000100110111110001001101111100010011011111000100110";

	string actions = "14-CONTACT_DISABLE_LEFT\n70-CONTACT_disable_right";

	FilteredCollisionSystem system(leftIc, rightIc, centralIc,
		13, centralIc.length() - 1, 13, 4 * 14 - 1, actions);
	system.setAllContactsEnabled(true);

	ofstream leftFile("../ParticleEnciclopedia/Rings/left.txt");
	ofstream rightFile("../ParticleEnciclopedia/Rings/right.txt");
	ofstream centralFile("../ParticleEnciclopedia/Rings/central.txt");
	
	for(int i = 0; i < 10000; i++) {
		leftFile << system.getLeftState() << endl;
		rightFile << system.getRightState() << endl;
		centralFile << system.getCentralState() << endl;

		system.execute();
	}

	leftFile.close();
	rightFile.close();
	centralFile.close();
	
	EXPECT_EQ(1, 1);
}