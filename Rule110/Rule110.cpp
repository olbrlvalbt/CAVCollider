#include "stdafx.h"
#include "Rule110.h"

#include <sstream>
#include <vector>

Rule110::Rule110()
	: gliderSets(gliders),
	delimiter('-'){

	initRegexes();
}

string Rule110::Translate(string s) {
	s.erase(remove_if(s.begin(), s.end(), [](unsigned char c) {
		return isspace(c);
		}), s.end());
	
	stringstream ss(s);
	string item;
	vector<string> elems;
	while (getline(ss, item, delimiter)) {
		elems.push_back(item);
	}

	string translated = "";

	for (int i = 0; i < elems.size(); i++) {
		string e = elems[i];

		if (e.length() != 0) {
			if (regex_match(e, rMultipleExpression)) {
				translated += translate(e);
			}
			else {
				string ex = "Invalid expression: " + elems[i];
				
				if (regex_search(e, rCompositeName)) {
					if (!regex_search(e, rPhaseNum)) {
						ex = "Invalid phase number in expression: " + elems[i];
					}
					else if (!regex_search(e, rPhase)) {
						ex = "Invalid phase in expression: " + elems[i];
					}
				}
				else if (regex_search(e, rParams)) {
					ex = "Composite id not found for expression: " + elems[i];
				}
				
				throw exception(ex.c_str());
			}
		}
	}

	return translated;
}

string Rule110::translate(const string& s) {
	string translated;
	int multiple = 1;
	smatch match;

	string trimmed = s;

	if (regex_search(trimmed, rMultiple)) {
		regex_search(trimmed, match, rNum);
		multiple = stoi(match[0]);
		trimmed = trimmed.substr(match[0].length() + 1);
	}

	if (regex_search(trimmed, rComposite)) {
		bool isSet = true;

		string compositeName = trimmed.substr(0, trimmed.find("("));
		
		if (regex_match(compositeName, rGliderName)) {
			isSet = false;
		}
		
		trimmed = trimmed.substr(compositeName.length() + 1);

		string phase = "A";
		if (regex_search(trimmed, rPhaseParam)) {
			regex_search(trimmed, match, rPhase);
			phase = match[0];
			trimmed = trimmed.substr(phase.length() + 1);
		}
		regex_search(trimmed, match, rNum);
		int phaseNum = stoi(match[0]);
		
		try {
			if (isSet) {
				translated = gliderSets.get(compositeName, phase, phaseNum);
			}
			else {
				translated = gliders.get(compositeName, phase, phaseNum);
			}
		}
		catch(exception& e) {
			string ex = " Expression " + s + " - " + e.what();
			throw exception(ex.c_str());
		}
	}
	else if (regex_search(trimmed, rEther)) {
		int etherMult = 1;
		if (regex_search(trimmed, rNum)) {
			regex_search(trimmed, match, rNum);
			etherMult = stoi(match[match.size() - 1]);
		}
		translated = multiply("11111000100110", etherMult);
	}
	else {
		regex_search(trimmed, match, rBin);
		translated = match[match.size() - 1];
	}
	

	return multiply(translated, multiple);
}

string Rule110::multiply(const string& s, int multiple) {
	string multiplied = "";

	for (int i = 0; i < multiple; i++) {
		multiplied += s;
	}

	return multiplied;
}


void Rule110::initRegexes() {
	string sBin = "[01]+";
	string sNum = "[1-9][0-9]*";
	string sEther = "(" + sNum + ")?E";

	string sPhaseNum = "(F_?)?[1-4](_1)?";
	string sPhase = "[A-H](" + sNum + ")?";
	string sPhaseParam = sPhase + ",";
	string sParams = "\\((" + sPhaseParam + ")?" + sPhaseNum + "\\)";

	string sGliderName = "";
	const auto& gliderIds = gliders.getIds();
	for (int i = 0; i < gliderIds.size(); i++) {
		if (i != 0) {
			sGliderName += "|";
		}
		sGliderName += gliderIds[i];
	}

	string sGliderSetName = "";
	const auto& gliderSetIds = gliderSets.getIds();
	for (int i = 0; i < gliderSetIds.size(); i++) {
		if (i != 0) {
			sGliderSetName += "|";
		}
		sGliderSetName += gliderSetIds[i];
	}

	string sCompositeName = sGliderName + "|" + sGliderSetName;
	string sComposite = "(" + sCompositeName + ")" + sParams;

	string sExpression = "(" + sComposite + ")|(" + sEther + ")|(" + sBin + ")";
	string sMultiple = sNum + "\\*";
	string sMultipleExpression = "(" + sMultiple + ")?(" + sExpression + ")";

	rBin = regex(sBin, regex_constants::icase);
	rNum = regex(sNum, regex_constants::icase);
	rEther = regex(sEther, regex_constants::icase);
	rPhaseNum = regex(sPhaseNum, regex_constants::icase);
	rPhase = regex(sPhase, regex_constants::icase);
	rPhaseParam = regex(sPhaseParam, regex_constants::icase);
	rParams = regex(sParams, regex_constants::icase);
	rGliderName = regex(sGliderName, regex_constants::icase);
	rGliderSetName = regex(sGliderSetName, regex_constants::icase);
	rCompositeName = regex(sCompositeName, regex_constants::icase);
	rComposite = regex(sComposite, regex_constants::icase);
	rExpression = regex(sExpression, regex_constants::icase);
	rMultiple = regex(sMultiple, regex_constants::icase);
	rMultipleExpression = regex(sMultipleExpression, regex_constants::icase);
}
