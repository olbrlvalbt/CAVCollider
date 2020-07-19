#include "Rule110Constants.h"


Rule110Constants::Rule110Constants() {
}

const std::regex Rule110Constants::REGEX_BINARY = std::regex("[01]+");
const std::regex Rule110Constants::REGEX_ETHER = std::regex("[0-9]*(e|E)");
const std::regex Rule110Constants::REGEX_COMPOSITE = std::regex("[0-9a-zA-Z_\\^]+\\(([a-hA-H]([1-9][0-9]*)?,)?((f|F)_?)?[1-4](_1)?\\)");
const std::regex Rule110Constants::REGEX_GLIDER = std::regex("[0-9]*([a-hA-H]([1-9][0-9]*|b(ar)?|c(irc)?|_|\\^)?)|((GUN|Gun|gun)([1-9][0-9]*)?)");


const std::string Rule110Constants::ETHER[4] = {
	"11111000100110",
	"10001001101111",
	"10011011111000",
	"10111110001001"
};

const std::string Rule110Constants::ETHER_F1_1 = Rule110Constants::ETHER[0];