#include "stdafx.h"
#include "Rule110Composite.h"

Rule110Composite::Rule110Composite(GliderMap _gliderMap, GliderSetMap _gliderSetMap)
	: gliderMap(_gliderMap),
	gliderSetMap(_gliderSetMap) {
}

string Rule110Composite::GetComposite(string _token) {
	Rule110Basic::Trim(_token);

	if (!IsComposite(_token)) {
		throw InvalidTokenException(_token);
	}

	string name = "";

	auto it = _token.cbegin();
	while (*it != '(') {
		name += *it;
		it++;
	}
	it++;

	char gliderPhase = 'a';
	size_t gliderPhaseNum = 1;
	size_t etherPhase = 1;

	processPhase(gliderPhase, gliderPhaseNum, etherPhase, _token.substr(it - _token.cbegin()));


	int multiple = 1;
	string compositeId = name;

	if (IsGliderName(name)) {
		processGlider(multiple, compositeId, name);
		return GetGlider(multiple, compositeId, gliderPhase + to_string(gliderPhaseNum), etherPhase);
	}

	return GetGliderSet(compositeId, gliderPhase + to_string(gliderPhaseNum), etherPhase);
}

string Rule110Composite::GetGlider(int _multiple, string _gliderId, string _gliderPhaseKey, size_t _phase) {
	return Rule110Basic::GetMultiple(gliderMap.get(_gliderId, _gliderPhaseKey, _phase), _multiple);
}

string Rule110Composite::GetGliderSet(string _gliderSetId, string _gliderSetPhaseKey, size_t _phase) {
	return gliderSetMap.get(_gliderSetId, _gliderSetPhaseKey, _phase);
}

void Rule110Composite::processGlider(int & multiple, string & gliderId, string & _s) {
	auto it = _s.cbegin();

	if (*it >= '0' && *it <= '9') {
		multiple = *it - '0';
		it++;

		while (*it >= '0' && *it <= '9') {
			multiple = multiple * 10 + *it - '0';
			it++;
		}

		gliderId = _s.substr(it - _s.cbegin());
	}
}

void Rule110Composite::processPhase(char & gliderPhase, size_t & gliderPhaseNum, size_t & etherPhase, string _s) {
	auto it = _s.cbegin();

	if (*it >= '1' && *it <= '4') {
		// (i), (i_1)
		etherPhase = *it - '0';
	}
	else {
		gliderPhase = *it;
		it++;

		if (*it == '_') {
			// (f_i), (f_i_1)
			it++;

			gliderPhase = 'a';
			etherPhase = *it - '0';
		}
		else if (*it >= '0' && *it <= '9') {
			gliderPhaseNum = *it - '0';
			it++;

			while (*it >= '0' && *it <= '9') {
				gliderPhaseNum = gliderPhaseNum * 10 + *it - '0';
				it++;
			}

			if (*it == ',') {
				it++;

				if (*it >= '1' && *it <= '4') {
					// (an,i), (an,i_1)
					etherPhase = *it - '0';
				}
				else {
					it++;

					if (*it == '_') {
						// (an,f_i), (an,f_i_1)
						it++;
					}
					// else (an,fi), (an,fi_1)
					etherPhase = *it - '0';
				}
			}
			else {
				// (fi), (fi_1)
				gliderPhase = 'a';
				etherPhase = gliderPhaseNum;
				gliderPhaseNum = 1;
			}
		}
		else if (*it == ',') {
			gliderPhaseNum = 1;

			it++;

			if (*it >= '1' && *it <= '4') {
				// (a,i), (a,i_1)
				etherPhase = *it - '0';
			}
			else {
				it++;

				if (*it == '_') {
					// (a,f_i), (a,f_i_1)
					it++;
				}
				// else (a,fi), (a,fi_1)
				etherPhase = *it - '0';
			}
		}
	}
}

bool Rule110Composite::IsComposite(string& _s) {
	return regex_match(_s, Rule110Constants::singleton().REGEX_COMPOSITE);
}

bool Rule110Composite::IsGliderName(string _s) {
	return regex_match(_s, Rule110Constants::singleton().REGEX_GLIDERNAME);
}