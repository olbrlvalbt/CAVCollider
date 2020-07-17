#pragma once

#include <string>
#include <regex>


static const std::regex REGEX_BINARY = std::regex("[01]+");
static const std::regex REGEX_ETHER = std::regex("[0-9]*(e|E)");
static const std::regex REGEX_COMPOSITE = std::regex("[0-9a-zA-Z_\\^]+\\(([a-hA-H]([1-9][0-9]*)?,)?((f|F)_?)?[1-4](_1)?\\)");
static const std::regex REGEX_GLIDER = std::regex("[0-9]*([a-hA-H]([1-9][0-9]*|b(ar)?|c(irc)?|_|\\^)?)|((GUN|Gun|gun)([1-9][0-9]*)?)");


static const std::string ETHER[4] = {
	"11111000100110",
	"10001001101111",
	"10011011111000",
	"10111110001001"
};

static const std::string ETHER_F1_1 = ETHER[0];