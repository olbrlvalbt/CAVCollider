#pragma once

#include <string>
#include <regex>
#include <exception>

#include "Rule110Constants.h"

using namespace std;

class Rule110Basic {
public:
	static string GetEther(int _multiply);
	static string GetMultiple(string _expression, int _multiple);

	static bool IsBinaryString(string& _s);
	static bool IsEther(string& _s);

	static void Trim(string& _s);
	static void ToLower(string& _s);
	static void ToLower(char& _c);
	static void ToUpper(string& _s);
	static void ToUpper(char& _c);
};


class TranslationException : public exception {
protected:
	string errorSource;
	string errorMessage;

public:
	TranslationException(const std::string& _errorSource) {
		errorSource = _errorSource;
		errorMessage = errorSource;
	}

	virtual const char* what() const noexcept override {
		return errorMessage.c_str();
	}
};

class ParseException : public TranslationException {
public:
	ParseException(const std::string& _errorSource) : TranslationException(_errorSource) {
		errorMessage = "Parsing error: " + _errorSource;
	}
};

class InvalidTokenException : public TranslationException {
public:
	InvalidTokenException(const std::string& _errorSource) : TranslationException(_errorSource) {
		errorMessage = "Invalid token: " + _errorSource;
	}
};

class CompositeNotFoundException : public TranslationException {
public:
	CompositeNotFoundException(const std::string& _errorSource) : TranslationException(_errorSource) {
		errorMessage = "Composite id not found: " + _errorSource;
	}
};

class PhaseNotFoundException : public TranslationException {
public:
	PhaseNotFoundException(const std::string& _errorSource) : TranslationException(_errorSource) {
		errorMessage = "Phase not found for composite id: " + _errorSource;
	}
};