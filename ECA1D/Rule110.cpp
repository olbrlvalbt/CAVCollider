#include "Rule110.h"

string Rule110::Translate(string _s) {
	string translatedExpression = "";

	istringstream iss(_s);
	string temp;
	while (getline(iss, temp, '-')) {
		translatedExpression += GetExpression(temp);
	}

	return translatedExpression;
}

string Rule110::GetExpression(string _token) {
	Trim(_token);

	if (IsBinaryString(_token)) {
		return _token;
	}

	if (IsEther(_token)) {
		return getEther(_token);
	}

	if (Rule110Composite::IsComposite(_token)) {
		return Rule110Composite::GetComposite(_token);
	}

	return "";
}

string Rule110::getEther(string _expression) {
	int multiple = 1;

	auto it = _expression.cbegin();
	if (*it >= '0' && *it <= '9') {
		multiple = *it - '0';
		it++;

		while (*it >= '0' && *it <= '9') {
			multiple = multiple * 10 + *it - '0';
			it++;
		}
	}

	return GetEther(multiple);
}

string Rule110::GetEther(int _multiple) {
	return GetMultiple(ETHER_F1_1, _multiple);
}

string Rule110::GetMultiple(string _expression, int _multiple) {
	if (!IsBinaryString(_expression)) {
		return "";
	}

	string multipleString = "";
	for (int i = 0; i < _multiple; i++) {
		multipleString += _expression;
	}

	return multipleString;
}

bool Rule110::IsBinaryString(string& _s) {
	return regex_match(_s, REGEX_BINARY);
}

bool Rule110::IsEther(string& _s) {
	return regex_match(_s, REGEX_ETHER);
}

void Rule110::Trim(string& _s) {
	_s.erase(remove_if(_s.begin(), _s.end(), isspace), _s.end());
}

void Rule110::ToLower(string & _s) {
	transform(_s.begin(), _s.end(), _s.begin(), tolower);
}


void Rule110::ToUpper(string & _s) {
	transform(_s.begin(), _s.end(), _s.begin(), toupper);
}
