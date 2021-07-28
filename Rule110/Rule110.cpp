#include "stdafx.h"
#include "Rule110.h"

string Rule110::Translate(string _s) {
	string translatedExpression = "";
	string temp = "";

	Rule110Basic::Trim(_s);
	string::const_iterator it = _s.cbegin();

	for (; it != _s.cend(); it++) {
		if (*it == '-') {
			translatedExpression += GetExpression(temp);
			temp = "";
		}
		else if (*it == '{') {
			it++;

			Rule110Basic::Trim(temp);

			int multiple = 1;
			if (!temp.empty()) {
				try {
					multiple = stoi(temp);
				}
				catch (exception e) {
					throw InvalidTokenException(temp);
				}
			}

			string::const_iterator nestStart = it;
			translatedExpression += Rule110Basic::GetMultiple(translateNested(_s, it), multiple);

			if (it != _s.cend() && *it != '}' && *it != '-') {
				throw InvalidTokenException(_s.substr(nestStart - _s.cbegin(), it - nestStart));
			}

			temp = "";
			it--;
		}
		else if (*it == '}') {
			throw ParseException(std::to_string((it - _s.begin())));
		}
		else {
			temp += *it;
		}
	}

	if (it != _s.cend()) {
		throw ParseException(std::to_string((it - _s.begin())));
	}

	return translatedExpression + GetExpression(temp);
}

string Rule110::GetExpression(string _token) {
	Rule110Basic::Trim(_token);

	if (Rule110Basic::IsBinaryString(_token)) {
		return _token;
	}

	if (Rule110Basic::IsEther(_token)) {
		return getEther(_token);
	}

	if (rule110Composite->IsComposite(_token)) {
		return rule110Composite->GetComposite(_token);
	}
	if (_token.empty()) {
		return "";
	}
	throw InvalidTokenException(_token);
}

Rule110::Rule110() {
	gliderMap = new GliderMap();
	gliderSetMap = new GliderSetMap(*gliderMap);

	rule110Composite = new Rule110Composite(*gliderMap, *gliderSetMap);
}

string Rule110::translateNested(string& _s, string::const_iterator& it) {
	string translatedExpression = "";
	string temp = "";

	for (; it != _s.cend(); it++) {
		if (*it == '-') {
			translatedExpression += GetExpression(temp);
			temp = "";
		}
		else if (*it == '{') {
			it++;

			Rule110Basic::Trim(temp);

			int multiple = 1;
			if (!temp.empty()) {
				try {
					multiple = stoi(temp);
				}
				catch (exception e) {
					throw InvalidTokenException(temp);
				}
			}

			string::const_iterator nestStart = it;
			translatedExpression += Rule110Basic::GetMultiple(translateNested(_s, it), multiple);

			if (it != _s.cend() && *it != '}' && *it != '-') {
				throw InvalidTokenException(_s.substr(nestStart - _s.cbegin(), it - nestStart));
			}

			temp = "";
			it--;
		}
		else if (*it == '}') {
			it++;
			translatedExpression += GetExpression(temp);

			return translatedExpression;
		}
		else {
			temp += *it;
		}
	}

	throw ParseException(std::to_string((it - _s.begin())));
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
