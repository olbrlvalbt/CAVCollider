#include "Rule110Constants.h"

const std::string Rule110Constants::STRING_MULTIPLE = "([0-9]*)";
const std::string Rule110Constants::STRING_BINARY = "([01]+)";
const std::string Rule110Constants::STRING_ETHER = "(" + Rule110Constants::STRING_MULTIPLE + "(e|E))";
const std::string Rule110Constants::STRING_COMPOSITENAME = "([0-9a-zA-Z_\\^]+)";
const std::string Rule110Constants::STRING_GLIDERNAME = "(" + Rule110Constants::STRING_MULTIPLE + "(([a-hA-H]([1-9][0-9]*|b(ar)?|c(irc)?|_|\\^)?)|((GUN|Gun|gun)([1-9][0-9]*)?)))";
const std::string Rule110Constants::STRING_COMPOSITEPHASE = "(\\(([a-hA-H]([1-9][0-9]*)?,)?((f|F)_?)?[1-4](_1)?\\))";
const std::string Rule110Constants::STRING_COMPOSITE = "(" + Rule110Constants::STRING_COMPOSITENAME + Rule110Constants::STRING_COMPOSITEPHASE + ")";
const std::string Rule110Constants::STRING_EXPRESSION = "(" + Rule110Constants::STRING_BINARY + "|" + Rule110Constants::STRING_ETHER + "|" + Rule110Constants::STRING_COMPOSITE + ")";

const std::regex Rule110Constants::REGEX_BINARY = std::regex(Rule110Constants::STRING_BINARY);
const std::regex Rule110Constants::REGEX_ETHER = std::regex(Rule110Constants::STRING_ETHER);
const std::regex Rule110Constants::REGEX_COMPOSITENAME = std::regex(Rule110Constants::STRING_COMPOSITENAME);
const std::regex Rule110Constants::REGEX_GLIDERNAME = std::regex(Rule110Constants::STRING_GLIDERNAME);
const std::regex Rule110Constants::REGEX_COMPOSITEPHASE = std::regex(Rule110Constants::STRING_COMPOSITEPHASE);
const std::regex Rule110Constants::REGEX_COMPOSITE = std::regex(Rule110Constants::STRING_COMPOSITE);
const std::regex Rule110Constants::REGEX_EXPRESSION = std::regex(Rule110Constants::STRING_EXPRESSION);


const std::string Rule110Constants::ETHER[4] = {
	"11111000100110",
	"10001001101111",
	"10011011111000",
	"10111110001001"
};

const std::string Rule110Constants::ETHER_F1_1 = Rule110Constants::ETHER[0];