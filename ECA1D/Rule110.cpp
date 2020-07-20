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
	Rule110Basic::Trim(_token);

	if (Rule110Basic::IsBinaryString(_token)) {
		return _token;
	}

	if (Rule110Basic::IsEther(_token)) {
		return getEther(_token);
	}

	if (Rule110Composite::IsComposite(_token)) {
		return Rule110Composite::GetComposite(_token);
	}

	throw InvalidTokenException(_token);
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

	return Rule110Basic::GetEther(multiple);
}
