#include "pch.h"

#include "NaiveController.h"

#include <string>
#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

void printGliderSet(string gliderSetName, string gliderSet) {
	int n = 1000;
	int leftEthers = 30;
	int rightEthers = 10;
	const string ether = "11111000100110";
	regex regStart("\n(1000100110|100110|10|1110001001101|0110|00100110|111000100110)?(11111000100110)+");
	regex regEnd("(11111000100110)+(11111000|11|1111100010|111110|111110001001|1111)?\n");

	string leftEthersString = "";
	string rightEthersString = "";

	int i;

	for (i = 0; i < leftEthers; i++) {
		leftEthersString += ether;
	}

	for (i = 0; i < rightEthers; i++) {
		rightEthersString += ether;
	}

	string controllerIC = leftEthersString + gliderSet + rightEthersString;

	NaiveController ecaController = NaiveController(controllerIC.length(), 110, controllerIC);

	ofstream file("../ParticleEnciclopedia/GliderSets/" + gliderSetName + ".txt");

	string buf = "";
	int comp = 0;

	for (i = 0; i < n; i++) {
		const vector<string>& ref = ecaController.getCurrentState();

		buf = "\n";
		for (const auto& e : ref) {
			buf += e;
		}
		buf += "\n";

		buf = regex_replace(regex_replace(buf, regStart, ""), regEnd, "");


		if (gliderSet.compare(buf) == 0 && i != 0) {
			break;
		}
		
		file << buf << endl;

		ecaController.applyRule();
	}

	if (i >= n) {
		file << "Incomplete";
	}

	file.close();
}

TEST(GetA3Descriptor, Descriptor) {
	string ga3 = "111110111000100110";

	printGliderSet("A3", ga3);

	EXPECT_EQ(1, 1);
}

TEST(Get1EleC2Descriptor, Descriptor) {	
	string g1elec2 = "11111000000100110111110001001101111100010011011111000000100110";
	g1elec2 += "1111100010011011111000100110111110000001001101111100010011011111000111011010";

	printGliderSet("1EleC2", g1elec2);
	
	EXPECT_EQ(1, 1);
}

TEST(Get0EleC2Descriptor, Descriptor) {
	string g0elec2 = "11111000000100110111110001001101111100010011011111000000100110";
	g0elec2 += "11111000100110111000110001001101111100010011011111000100000110";

	printGliderSet("0EleC2", g0elec2);

	EXPECT_EQ(1, 1);
}

TEST(GetSepInitDescriptor, Descriptor) {
	string sepInit = "1111100000000100110101110011000100110111110001110011100000100110";
	sepInit += "11111000100110111110001001101111100010011011111000000001001101011100110";
	sepInit += "1111100010011011111000111011001011011111000100110111110001001111111000";
	sepInit += "111110001001101111100010011011111000100011001100011111000100110110000010011000100110";
	sepInit += "11111000100110111110001001101111011";

	printGliderSet("SepInitEEb", sepInit);

	EXPECT_EQ(1, 1);
}