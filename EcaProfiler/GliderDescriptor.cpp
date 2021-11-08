#include "pch.h"

#include "NaiveController.h"

#include <string>
#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

void printGliderSet(string gliderSetName, string gliderSet) {
	int n = 5000;
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

TEST(Get0BloEDescriptor, Descriptor) {
	string p = "1111100001000111110101111100010011011111000100110111110000101100100110";
	p += "1111100011101100101101111100010001100110001111100010011011111000100110";
	p += "1111101111110111110101111100010011011111000100110111110000100011111010";
	p += "11111000100110111110001001100110001111110001001101111100010011011111000100110";
	p += "11111000101101000011011111001111101110011011101110011000010011011111000100110";
	p += "111110001001101110001110110001001101111100010011011111000100110011000111111000100110";

	printGliderSet("0BloE", p);

	EXPECT_EQ(1, 1);
}

TEST(Get1BlopEDescriptor, Descriptor) {
	string g1blope = "1111100001000111110101111100010011010001101001100010011011111000100110";
	g1blope += "1111100111110111001101110111001100001001101111100010011011111000100110111000111011000100110";
	g1blope += "1111100010011011111000100110011000111111000100110111110100111100100110";
	g1blope += "1111100010011011111000100110111110111111011111010111011100110000100110";
	g1blope += "1111100011101100101101111100010011011111000100110111110001011010000110";
	g1blope += "1111100010011011111000100110111110100111100100110";

	printGliderSet("1BloPE", g1blope);

	EXPECT_EQ(1, 1);
}

TEST(Get1BlosEDescriptor, Descriptor) {
	string p = "1111100001000111110101111100010011011111000100110111110000101100100110";
	p += "1111100011101100101101111100010001100110001111100010011011111000100110";
	p += "1111101111110111110101111100010011011111000100110111110000100011111010";
	p += "1111100010110001110101111100010011011111000100110111110001110111110010";
	p += "1111100010001100110001111100010011111001101111100010011011111000100110";
	p += "1111100001011001001101111100010011011111000100110111110001011000111010";

	printGliderSet("1BloSE", p);

	EXPECT_EQ(1, 1);
}

TEST(Get4A4Descriptor, Descriptor) {
	string p = "11111011101111100010011011111000100110111110001001101111100010011011111000100110111110001001101111100010011011111000100110111110001001101111100010011011111000100110111110001001101111100010011011111000100110111110001001101111100010011011111000100110111110001001101111100010011011111000100110111110001001101111100010011011111000100110111110001001101111100010011011111000100110111110001001101111100010011011101001101111100010011011111000100110111110001001101111100010011011111000100110111110001001101111100010011011111000100110111110001001101111100010011011111000100110111110001001101111100010011011111000100110111110001001101111100010011011111000100110111110001001101111100010011011111000100110111110001001101111100010011011111000100110111110001110111000100110111110001001101111100010011011111000100110111110001001101111100010011011111000100110111110001001101111100010011011111000100110111110001001101111100010011011111000100110111110001001101111100010011011111000100110111110001001101111100010011011111000100110111110001001101111100010011011111000100110111110001001101111100010011011111000100110111110001001101111101110";


	printGliderSet("4A4", p);

	EXPECT_EQ(1, 1);
}