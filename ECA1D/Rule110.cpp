#include "Rule110.h"

Rule110::Rule110() {

}

string Rule110::TranslateExpression(string _expression) {
	string translatedExpression = "";

	_expression.erase(remove_if(_expression.begin(), _expression.end(), isspace), _expression.end());
	transform(_expression.begin(), _expression.end(), _expression.begin(), tolower);

	istringstream iss(_expression);
	string temp;
	while (getline(iss, temp, '-')) {
		translatedExpression += GetToken(temp);
	}

	return translatedExpression;
}

string Rule110::GetToken(string _token) {
	regex manual(REGEX_MANUAL);
	if (regex_match(_token, manual)) {
		return _token;
	}

	regex ether(REGEX_ETHER);
	if (regex_match(_token, ether)) {
		return GetEtherMultiple(_token);
	}

	regex glider(REGEX_GLIDER);
	if (regex_match(_token, glider)) {
		return Rule110Glider::GetGlider(_token);
	}

	return "";
}

string Rule110::GetEtherMultiple(string _token) {
	int multiple = 1;

	auto it = _token.cbegin();

	if (*it >= '0' && *it <= '9') {
		multiple = *it - '0';
		it++;

		while (*it >= '0' && *it <= '9') {
			multiple = multiple * 10 + *it - '0';
			it++;
		}
	}
	string multipleString = "";
	for (int i = 0; i < multiple; i++) {
		multipleString += ETHER[0];
	}

	return multipleString;
}
