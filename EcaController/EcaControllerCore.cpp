#include "pch.h"
#include "EcaControllerCore.h"

const int EcaControllerCore::CHUNK_BITSIZE = 16;

string EcaControllerCore::ToBinaryString(int n) {
	if (n < 0) {
		throw exception("N cannot be negative");
	}
	string r = "";
	do {
		r = (n % 2 == 0 ? '0' : '1') + r;
		n /= 2;
	} while (n != 0);

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

string EcaControllerCore::FormatBinaryString(int k, int n) {
	return EcaControllerCore::FormatBinaryString(EcaControllerCore::ToBinaryString(k), n);
}

string EcaControllerCore::FormatBinaryString(string s, int n) {
	if (n < 0) {
		throw exception("N cannot be negative");
	}
	if (!EcaControllerCore::IsBinaryString(s) && !s.empty()) {
		string ex = "String is not binary: " + s;
		throw exception(ex.c_str());
	}
	if (n < s.length()) {
		string ex = "Desired length (" + to_string(n); +
			") cannot be less than string length (" +
			to_string(s.length()) + ")";
		throw exception(ex.c_str());
	}

	int i;
	for (i = s.length(); i < n; i++) {
		s = '0' + s;
	}

	return s;
}

string EcaControllerCore::CreateRandomBinaryString(int n) {
	if (n < 0) {
		throw exception("N cannot be negative");
	}

	srand(time(NULL));

	string s = "";
	int i;
	for (i = 0; i < n; i++) {
		s += rand() % 2 ? '0' : '1';
	}

	return s;
}