#include "stdafx.h"
#include "GliderMap.h"

GliderMap::GliderMap() {
	compositeMap["A"] = Composite("A", {
		"111110",
		"11111000111000100110",
		"11111000100110100110",
		"111110"
		});

	compositeMap["A4"] = Composite("A4", {
		"1111101110",
		"111110001110111000100110",
		"111110001001101110100110",
		"1111101110"
		});

	compositeMap["B"] = Composite("B", {
		"11111010",
		"11111000",
		"1111100010011000100110",
		"11100110"
		});

	compositeMap["Bbar"] = Composite("Bbar", {
		"1111100010110111100110",
		"111110001001111111001011111000100110",
		"111110001001101100000101111000100110",
		"1111110000111100100110",

		"1111100001000110010110",
		"111110001000110011101111111000100110",
		"111110001001100111011011100000100110",
		"1110110111111010000110",

		"1111101111110000111000",
		"111110001110000100011010011000100110",
		"111110001001101000110011111011100110",
		"1111100111011000111010"
		});

	compositeMap["Bcirc"] = Composite("Bcirc", {
		"111110001011011110011001111111000100110",
		"111110001001111111001011101100000100110",
		"111110001001101100000101111011110000110",
		"1111110000111100111001000",

		"111110000100011001011010110011000100110",
		"111110001000110011101111111111011100110",
		"111110001001100111011011100000000111010",
		"1110110111111010000000110",

		"111110111111000011100000011111000100110",
		"111110001110000100011010000011000100110",
		"111110001001101000110011111000011100110",
		"1111100111011000100011010"
		});

	compositeMap["C1"] = Composite("C1", {
		"111110000",
		"11111000100011000100110",
		"11111000100110011100110",
		"111011010",

		"11111011111111000100110",
		"11111000111000000100110",
		"11111000100110100000110",
		"111110000"
		});

	compositeMap["C2"] = Composite("C2", {
		"11111000000100110",
		"11111000100000110",
		"11111000100110000",
		"11100011000100110",

		"11111010011100110",
		"11111000111011010",
		"1111100010011011111111000100110",
		"11111000000100110"
		});

	compositeMap["C3"] = Composite("C3", {
		"11111011010",
		"1111100011111111000100110",
		"1111100010011000000100110",
		"11100000110",

		"11111010000",
		"1111100011100011000100110",
		"1111100010011010011100110",
		"11111011010"
		});

	compositeMap["D1"] = Composite("D1", {
		"11111000010",
		"1111100010001111000100110",
		"1111100010011001100100110",
		"11101110110",

		"1111101110111111000100110",
		"1111100011101110000100110",
		"1111100010011011101000110",
		"11111011100",

		"11111011100",
		"1111100011101011000100110",
		"1111100010011011111100110",
		"11111000010"
		});

	compositeMap["D2"] = Composite("D2", {
		"1111101011000100110",
		"1111100011111100110",
		"1111100010011000010",
		"1110001111000100110",

		"1111101001100100110",
		"1111100011101110110",
		"111110001001101110111111000100110",
		"1111101110000100110",

		"1111101110000100110",
		"1111100011101000110",
		"1111100010011011100",
		"1111101011000100110"
		});

	compositeMap["E"] = Composite("E", {
		"1111100000000100110",
		"1111100010000000110",
		"1111100010011000000",
		"1110000011000100110",

		"1111101000011100110",
		"1111100011100011010",
		"111110001001101001111111000100110",
		"1111101100000100110",

		"1111101100000100110",
		"1111100011110000110",
		"1111100010011001000",
		"1110110011000100110",

		"1111101111011100110",
		"1111100011100111010",
		"1111100010011010110",
		"1111111111000100110"
		});

	compositeMap["E2"] = Composite("E2", {
		"111110000000010011000100110",
		"",
		"",
		"",

		"",
		"",
		"",
		"",

		"",
		"",
		"",
		"",

		"",
		"111110001110011100000100110",
		"",
		""
		});

	compositeMap["E3"] = Composite("E3", {
		"111110000000010011010",
		"",
		"",
		"",

		"",
		"",
		"",
		"",

		"",
		"",
		"",
		"",

		"",
		"",
		"",
		""
		});

	compositeMap["E4"] = Composite("E4", {
		"11111000000001001101011100110",
		"",
		"",
		"",

		"",
		"",
		"",
		"",

		"",
		"",
		"",
		"",

		"",
		"",
		"",
		""
		});

	compositeMap["E5"] = Composite("E5", {
		"1111100000000100110101110011000100110",
		"",
		"",
		"",

		"",
		"",
		"",
		"",

		"",
		"",
		"",
		"",

		"",
		"",
		"",
		""
		});

	compositeMap["Ebar"] = Composite("Ebar", {
		"111110000100011111010",
		"111110001000110011000",
		"11111000100110011101110011000100110",
		"111011011101011100110",

		"111110111111011111010",
		"111110001110000111000",
		"11111000100110100011010011000100110",
		"111110011111011100110",

		"111110001011000111010",
		"111110001001111100110",
		"11111000100110110001011111000100110",
		"111111001111000100110",

		"111110000101100100110",
		"111110001000111110110",
		"11111000100110011000111111000100110",
		"111011100110000100110",

		"111110111010111000110",
		"111110001110111110100",
		"11111000100110111000111011000100110",
		"111110100110111100110",

		"111110100110111100110",
		"111110001110111110010",
		"11111000100110111000101111000100110",
		"111110100111100100110",

		"111110100111100100110",
		"111110001110110010110",
		"11111000100110111101111111000100110",
		"111110011100000100110",

		"111110001011010000110",
		"111110001001111111000",
		"11111000100110110000010011000100110",
		"111111000011011100110"
		});

	compositeMap["F"] = Composite("F", {
		"111110001011010",
		"11111000100111111111000100110",
		"11111000100110110000000100110",
		"111111000000110",

		"111110000100000",
		"11111000100011000011000100110",
		"11111000100110011100011100110",
		"111011010011010",

		"11111011111101111111000100110",
		"11111000111000011100000100110",
		"11111000100110100011010000110",
		"111110011111000",

		"11111000101100010011000100110",
		"11111000100111110011011100110",
		"11111000100110110001011111010",
		"111111001111000",

		"11111000010110010011000100110",
		"11111000100011111011011100110",
		"11111000100110011000111111010",
		"111011100110000",

		"11111011101011100011000100110",
		"11111000111011111010011100110",
		"11111000100110111000111011010",
		"11111010011011111111000100110",

		"11111010011011111111000100110",
		"11111000111011111000000100110",
		"11111000100110111000100000110",
		"111110100110000",

		"111110100110000",
		"11111000111011100011000100110",
		"11111000100110111010011100110",
		"111110111011010",

		"111110111011010",
		"11111000111011111111000100110",
		"11111000100110111000000100110",
		"111110100000110",

		"111110100000110",
		"111110001110000",
		"11111000100110100011000100110",
		"111110011100110"
		});

	compositeMap["G"] = Composite("G", {
		"111110100111110011100110",
		"111110001110110001011010",
		"11111000100110111100111111111000100110",
		"111110010110000000100110",

		"111110001011111000000110",
		"111110001001111000100000",
		"11111000100110110010011000011000100110",
		"111111011011100011100110",

		"111110000111111010011010",
		"11111000100011000011101111111000100110",
		"11111000100110011100011011100000100110",
		"111011010011111010000110",

		"111110111111011000111000",
		"11111000111000011110011010011000100110",
		"11111000100110100011001011111011100110",
		"111110011101111000111010",

		"111110001011011100100110",
		"11111000100111111101011011111000100110",
		"11111000100110110000011111111000100110",
		"111111000011000000100110",

		"111110000100011100000110",
		"11111000100011001101000011111000100110",
		"11111000100110011101111100011000100110",
		"111011011100010011100110",

		"111110111111010011011010",
		"11111000111000011101111111111000100110",
		"11111000100110100011011100000000100110",
		"111110011111010000000110",

		"111110001011000111000000",
		"11111000100111110011010000011000100110",
		"11111000100110110001011111000011100110",
		"111111001111000100011010",

		"11111000010110010011001111111000100110",
		"11111000100011111011011101100000100110",
		"11111000100110011000111111011110000110",
		"111011100110000111001000",

		"11111011101011100011010110011000100110",
		"11111000111011111010011111111011100110",
		"11111000100110111000111011000000111010",
		"111110100110111100000110",

		"111110100110111100000110",
		"11111000111011111001000011111000100110",
		"11111000100110111000101100011000100110",
		"111110100111110011100110"
		});

	compositeMap["H"] = Composite("H", {
		"11111000101100000000111110001001101001111111000100110",
		"11111000100111110000000110001001101111101100000100110",
		"11111000100110110001000000111001101111100011110000110",
		"111111001100000110101111100010011001000",

		"11111000010111000011111110001001101110110011000100110",
		"11111000100011110100011000001001101111101111011100110",
		"11111000100110011001110011100001101111100011100111010",
		"111011101101011010001111100010011010110",

		"11111011101111111111100110001001101111111111000100110",
		"11111000111011100000000010111001101111100000000100110",
		"11111000100110111010000000011110101111100010000000110",
		"111110111000000011001111100010011000000",

		"111110111000000011001111100010011000000",
		"11111000111010000001110110001001101110000011000100110",
		"11111000100110111000001101111001101111101000011100110",
		"111110100001111100101111100011100011010",

		"111110100001111100101111100011100011010",
		"11111000111000110001011110001001101001111111000100110",
		"11111000100110100111001111001001101111101100000100110",
		"111110110101100101101111100011110000110",

		"111110110101100101101111100011110000110",
		"111110001111111110111111100010011001000",
		"11111000100110000000111000001001101110110011000100110",
		"111000000110100001101111101111011100110",

		"111110100000111110001111100011100111010",
		"111110001110000110001001100010011010110",
		"11111000100110100011100110111001101111111111000100110",
		"111110011010111110101111100000000100110",

		"111110001011111110001111100010000000110",
		"111110001001111000001001100010011000000",
		"11111000100110110010000110111001101110000011000100110",
		"111111011000111110101111101000011100110",

		"111110000111100110001111100011100011010",
		"11111000100011001011100110001001101001111111000100110",
		"11111000100110011101111010111001101111101100000100110",
		"111011011100111110101111100011110000110",

		"111110111111010110001111100010011001000",
		"11111000111000011111100110001001101110110011000100110",
		"11111000100110100011000010111001101111101111011100110",
		"111110011100011110101111100011100111010",

		"111110001011010011001111100010011010110",
		"11111000100111111101110110001001101111111111000100110",
		"11111000100110110000011101111001101111100000000100110",
		"111111000011011100101111100010000000110",

		"111110000100011111010111100010011000000",
		"11111000100011001100011111001001101110000011000100110",
		"11111000100110011101110011000101101111101000011100110",
		"111011011101011100111111100011100011010",

		"11111011111101111101011000001001101001111111000100110",
		"11111000111000011100011111100001101111101100000100110",
		"11111000100110100011010011000010001111100011110000110",
		"111110011111011100011001100010011001000",

		"11111000101100011101001110111001101110110011000100110",
		"11111000100111110011011101101110101111101111011100110",
		"11111000100110110001011111011111101111100011100111010",
		"111111001111000111000011100010011010110",

		"11111000010110010011010001101001101111111111000100110",
		"11111000100011111011011111001111101111100000000100110",
		"11111000100110011000111111000101100011100010000000110",
		"111011100110000100111110011010011000000",

		"11111011101011100011011000101111101110000011000100110",
		"11111000111011111010011111100111100011101000011100110",
		"11111000100110111000111011000010110010011011100011010",
		"11111010011011110001111101101111101001111111000100110",

		"11111010011011110001111101101111101001111111000100110",
		"11111000111011111001001100011111100011101100000100110",
		"11111000100110111000101101110011000010011011110000110",
		"111110100111111101011100011011111001000",

		"111110100111111101011100011011111001000",
		"11111000111011000001111101001111100010110011000100110",
		"11111000100110111100001100011101100010011111011100110",
		"111110010001110011011110011011000111010",

		"111110001011001101011111001011111100110",
		"11111000100111110111111100010111100001011111000100110",
		"11111000100110110001110000010011110010001111000100110",
		"111111001101000011011001011001100100110",

		"111110000101111100011111101111101110110",
		"11111000100011110001001100001110001110111111000100110",
		"11111000100110011001001101110001101001101110000100110",
		"111011101101111101001111101111101000110",

		"111110111011111100011101100011100011100",
		"11111000111011100001001101111001101001101011000100110",
		"11111000100110111010001101111100101111101111111100110",
		"111110111001111100010111100011100000010",

		"111110111001111100010111100011100000010",
		"11111000111010110001001111001001101000001111000100110",
		"11111000100110111111001101100101101111100001100100110",
		"111110000101111110111111100010001110110",

		"111110000101111110111111100010001110110",
		"11111000100011110000111000001001100110111111000100110",
		"11111000100110011001000110100001101110111110000100110",
		"111011101100111110001111101110001000110",

		"111110111011110110001001100011101001100",
		"11111000111011100111100110111001101110111011000100110",
		"11111000100110111010110010111110101111101110111100110",
		"111110111111011110001111100011101110010",

		"111110111111011110001111100011101110010",
		"11111000111000011100100110001001101110101111000100110",
		"11111000100110100011010110111001101111101111100100110",
		"111110011111111110101111100011100010110"
		});

	compositeMap["GUN"] = Composite("GUN", {
		"11111010110011101001100101111100000100110",
		"11111000111111011011101110111100010000110",
		"11111000100110000111111011101110010011000",
		"11100011000011101110101101110011000100110",

		"11111010011100011011101111111101011100110",
		"11111000111011010011111011100000011111010",
		"11111000100110111111011000111010000011000",
		"11111000011110011011100001110011000100110",

		"11111000011110011011100001110011000100110",
		"11111000100011001011111010001101011100110",
		"11111000100110011101111000111001111111010",
		"111011011100100110101100000",

		"11111011111101011011111111000011000100110",
		"11111000111000011111111000000100011100110",
		"11111000100110100011000000100000110011010",
		"11111001110000011000011101111111000100110",

		"11111000101101000011100011011100000100110",
		"11111000100111111100011010011111010000110",
		"11111000100110110000010011111011000111000",
		"11111100001101100011110011010011000100110",

		"11111000010001111110011001011111011100110",
		"11111000100011001100001011101111000111010",
		"11111000100110011101110001111011100100110",
		"11101101110100110011101011011111000100110",

		"11111011111101110111011011111111000100110",
		"11111000111000011101110111111000000100110",
		"11111000100110100011011101110000100000110",
		"11111001111101110100011000011111000100110",

		"11111000101100011101110011100011000100110",
		"11111000100111110011011101011010011100110",
		"11111000100110110001011111011111111011010",
		"11111100111100011100000011111111000100110",

		"11111000010110010011010000011000000100110",
		"11111000100011111011011111000011100000110",
		"11111000100110011000111111000100011010000",
		"11101110011000010011001111100011000100110",

		"11111011101011100011011101100010011100110",
		"11111000111011111010011111011110011011010",
		"1111100010011011100011101100011100101111111111000100110",
		"11111010011011110011010111100000000100110",

		"11111010011011110011010111100000000100110",
		"11111000111011111001011111110010000000110",
		"11111000100110111000101111000001011000000",
		"11111010011110010000111110000011000100110",

		"11111010011110010000111110000011000100110",
		"11111000111011001011000110001000011100110",
		"11111000100110111101111100111001100011010",
		"11111001110001011010111001111111000100110",

		"11111000101101001111111110101100000100110",
		"11111000100111111101100000001111110000110",
		"11111000100110110000011110000001100001000",
		"11111100001100100000111000110011000100110",

		"11111000010001110110000110100111011100110",
		"11111000100011001101111000111110110111010",
		"11111000100110011101111100100110001111110",
		"11101101110001011011100110000111000100110",

		"11111011111101001111111010111000110100110",
		"11111000111000011101100000111110100111110",
		"1111100010011010001101111000011000111011000111000100110",
		"11111001111100100011100110111100110100110",

		"11111000101100010110011010111110010",
		"1111100010011111001111101111111000101111000100110",
		"1111100010011011000101100011100000100111100100110",
		"11111100111110011010000110110010110",

		"1111100001011000101111100011111101111111000100110",
		"1111100010001111100111100010011000011100000100110",
		"1111100010011001100010110010011011100011010000110",
		"11101110011111011011111010011111000",

		"1111101110101100011111100011101100010011000100110",
		"1111100011101111110011000010011011110011011100110",
		"1111100010011011100001011100011011111001011111010",
		"11111010001111010011111000101111000",

		"11111010001111010011111000101111000",
		"1111100011100110011101100010011110010011000100110",
		"1111100010011010111011011110011011001011011100110",
		"11111110111111001011111101111111010",

		"11111000001110000101111000011100000",
		"1111100010000110100011110010001101000011000100110",
		"1111100010011000111110011001011001111100011100110",
		"11100110001011101111101100010011010",

		"1111101011100111101110001111001101111111000100110",
		"",
		"",
		""
		});

	idMap["A"] = "A";
	idMap["A4"] = "A4";
	idMap["B"] = "B";
	idMap["BBAR"] = "Bbar";
	idMap["BB"] = "Bbar";
	idMap["B_"] = "Bbar";
	idMap["BCIRC"] = "Bcirc";
	idMap["BC"] = "Bcirc";
	idMap["B^"] = "Bcirc";
	idMap["C1"] = "C1";
	idMap["C2"] = "C2";
	idMap["C3"] = "C3";
	idMap["D1"] = "D1";
	idMap["D2"] = "D2";
	idMap["E"] = "E";
	idMap["E2"] = "E2";
	idMap["E3"] = "E3";
	idMap["E4"] = "E4";
	idMap["E5"] = "E5";
	idMap["EBAR"] = "Ebar";
	idMap["EB"] = "Ebar";
	idMap["E_"] = "Ebar";
	idMap["F"] = "F";
	idMap["G"] = "G";
	idMap["H"] = "H";
	idMap["GUN"] = "GUN";
	idMap["GLIDERGUN"] = "GUN";
	idMap["GLIDER_GUN"] = "GUN";
}
