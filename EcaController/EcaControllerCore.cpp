#include "pch.h"
#include "EcaControllerCore.h"

string EcaControllerCore::ToBinaryString(unsigned int n) {
	string r = "";
	while (n != 0) {
		r = (n % 2 == 0 ? '0' : '1') + r;
		n /= 2;
	}
	return r;
}

bool EcaControllerCore::IsBinaryString(string& s) {
	if (s.empty()) {
		return false;
	}

	for (char& c : s) {
		if (c != '0' && c != '1') {
			return false;
		}
	}

	return true;
}

string EcaControllerCore::FormatBinaryString(string s, unsigned int n) {
	if (!EcaControllerCore::IsBinaryString(s) && !s.empty()) {
		string ex = "String is not binary: " + s;
		throw exception(ex.c_str());
	}
	if (n < s.length()) {
		string ex = "Desired length (";
		ex += n;
		ex += ") cannot be less than string length (";
		ex += s.length();
		ex += ")";
		throw ex;
	}

	int i;
	for (i = s.length(); i < n; i++) {
		s = '0' + s;
	}

	return s;
}