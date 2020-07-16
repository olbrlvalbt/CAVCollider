#include "Rule110Glider.h"

string Rule110Glider::GetGlider(string _expression) {
	int multiple = 1;
	string gliderId = "";
	string gliderPhase = "";
	int gliderPhaseNum = 1;
	int etherPhase = 1;

	_expression.erase(remove_if(_expression.begin(), _expression.end(), isspace), _expression.end());
	transform(_expression.begin(), _expression.end(), _expression.begin(), tolower);

	regex gliderRegex("[0-9]*(gun|[a-h])([0-9]+|b(ar)?|c(irc)?|_|\\^)?\\(([a-h]([1-9][0-9]*)?,)?f[1-4]_1\\)");
	if (!regex_match(_expression, gliderRegex)) {
		return "";
	}

	auto it = _expression.cbegin();

	if (*it >= '0' && *it <= '9') {
		multiple = *it;
		it++;

		while (*it >= '0' && *it <= '9') {
			multiple = multiple * 10 + *it;
			it++;
		}
	}
	while (*it != '(') {
		gliderId += *it;
		it++;
	}
	it++;

	while (*it != ')' || *it != ',') {
		if (*it >= '0' && *it <= '9') {

		}
		else {
			gliderPhase += *it;

		}
		it++;
	}

	if (*it == ',') {
		it += 2;
		etherPhase = *it;

		return GetGlider(multiple, gliderId, gliderPhase, etherPhase);
	}
	else {
		// A or B glider
		etherPhase = stoi(gliderPhase);

		return GetGlider(multiple, gliderId, etherPhase);
	}
}

string Rule110Glider::GetGlider(int _multiple, string _gliderId, int _etherPhase) {
	return GetGlider(_multiple, _gliderId, 'a', 1, _etherPhase);
}

string Rule110Glider::GetGlider(int _multiple, string _gliderId, string _gliderPhase, int _etherPhase) {
	char gliderPhaseChar = _gliderPhase.at(0);
	int gliderPhaseNum = 1;
	if (_gliderPhase.length() > 1) {
		gliderPhaseNum = stoi(_gliderPhase.substr(1));
	}

	return GetGlider(_multiple, _gliderId, gliderPhaseChar, gliderPhaseNum, _etherPhase);
}

string Rule110Glider::GetGlider(int _multiple, string _gliderId, char _gliderPhaseChar, int _gliderPhaseNum, int _etherPhase)
{
	auto it = GLIDERMAP.find(_gliderId);
	if (it == GLIDERMAP.end()) {
		return "";
	}

	Glider g = it->second;
	int gliderPhase = (_gliderPhaseChar - 'a' + 1) + (8 * (_gliderPhaseNum - 1));

	if (g.size() <= gliderPhase) {
		return "";
	}

	string gliderString = g[gliderPhase][_etherPhase];

	string multipleString = "";
	for (int i = 0; i < _multiple; i++) {
		multipleString += gliderString;
	}

	return multipleString;
}
