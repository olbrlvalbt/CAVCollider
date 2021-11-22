#include "pch.h"
#include "ColliderActionList.h"

#include <algorithm>
#include <regex>
#include <sstream>

ColliderActionList::ColliderActionList(std::string _actions) {
	transform(_actions.begin(), _actions.end(), _actions.begin(), [](unsigned char c) {
		return toupper(c);
		});
	
	std::stringstream ss(_actions);
	std::string item;
	std::vector<std::string> elems;
	while (std::getline(ss, item, '\n')) {
		elems.push_back(item);
	}
	std::string sNumRegex = "[0-9]+";
	std::string sActionRegex = getActionsRegexStr();
	std::string sFullRegex = sNumRegex + "-" + sActionRegex;

	std::regex numRegex(sNumRegex);
	std::regex actionEnumRegex(sActionRegex);
	std::regex fullRegex(sFullRegex);
	
	std::smatch match;

	for (std::string s : elems) {
		s.erase(remove_if(s.begin(), s.end(), [](unsigned char c) {
			return isspace(c);
			}), s.end());

		if (s.length() != 0) {
			if (std::regex_match(s, fullRegex)) {
				std::regex_search(s, match, numRegex);
				long iteration = std::stoi(match[0]);
				
				std::regex_search(s, match, actionEnumRegex);
				ColliderAction action = parseAction(match[0]);

				actions.insert({ iteration, action });
			}
			else {
				std::string exS = "Error de parseo: " + s;
				throw std::exception(exS.c_str());
			}
		}
	}
}

ColliderActionList::ColliderActionList(std::vector<std::string> _actions) {
	std::string sNumRegex = "[0-9]+";
	std::string sActionRegex = getActionsRegexStr();
	std::string sFullRegex = sNumRegex + "-" + sActionRegex;

	std::regex numRegex(sNumRegex);
	std::regex actionEnumRegex(sActionRegex);
	std::regex fullRegex(sFullRegex);

	std::smatch match;

	for (std::string s : _actions) {
		transform(s.begin(), s.end(), s.begin(), [](unsigned char c) {
			return toupper(c);
			});
		s.erase(remove_if(s.begin(), s.end(), [](unsigned char c) {
			return isspace(c);
			}), s.end());

		if (s.length() != 0) {
			if (std::regex_match(s, fullRegex)) {
				std::regex_search(s, match, numRegex);
				long iteration = std::stoi(match[0]);

				std::regex_search(s, match, actionEnumRegex);
				ColliderAction action = parseAction(match[0]);

				actions.insert({ iteration, action });
			}
			else {
				std::string exS = "Error de parseo: " + s;
				throw std::exception(exS.c_str());
			}
		}
	}
}

int ColliderActionList::validate(std::vector<std::string> _actions) {	
	std::string sNumRegex = "[0-9]+";
	std::string sActionRegex = getActionsRegexStr();
	std::string sFullRegex = sNumRegex + "-" + sActionRegex;
	
	std::regex fullRegex(sFullRegex);

	std::smatch match;

	
	for (int i = 0; i < _actions.size(); i++) {
		std::string s = _actions[i];
		transform(s.begin(), s.end(), s.begin(), [](unsigned char c) {
			return toupper(c);
			});
		s.erase(remove_if(s.begin(), s.end(), [](unsigned char c) {
			return isspace(c);
			}), s.end());

		if (s.length() != 0) {
			if (!std::regex_match(s, fullRegex)) {
				return i;
			}
		}
	}

	return -1;
}

ColliderAction ColliderActionList::parseAction(std::string s) {
	auto table = getActionTable();
	return table.at(s);
}

std::map<std::string, ColliderAction> ColliderActionList::getActionTable() {
	return {
		{"RING_DISABLE_LEFT",ColliderAction::RING_DISABLE_LEFT},
		{"RING_DISABLE_RIGHT",ColliderAction::RING_DISABLE_RIGHT},
		{"RING_DISABLE_CENTRAL",ColliderAction::RING_DISABLE_CENTRAL},
		{"RING_ENABLE_LEFT",ColliderAction::RING_ENABLE_LEFT},
		{"RING_ENABLE_RIGHT",ColliderAction::RING_ENABLE_RIGHT},
		{"RING_ENABLE_CENTRAL",ColliderAction::RING_ENABLE_CENTRAL},
		{"CONTACT_DISABLE_LEFT",ColliderAction::CONTACT_DISABLE_LEFT},
		{"CONTACT_DISABLE_RIGHT",ColliderAction::CONTACT_DISABLE_RIGHT},
		{"CONTACT_ENABLE_LEFT",ColliderAction::CONTACT_ENABLE_LEFT},
		{"CONTACT_ENABLE_RIGHT",ColliderAction::CONTACT_ENABLE_RIGHT},

		{"DISABLE_LEFT_RING",ColliderAction::RING_DISABLE_LEFT},
		{"DISABLE_RIGHT_RING",ColliderAction::RING_DISABLE_RIGHT},
		{"DISABLE_CENTRAL_RING",ColliderAction::RING_DISABLE_CENTRAL},
		{"ENABLE_LEFT_RING",ColliderAction::RING_ENABLE_LEFT},
		{"ENABLE_RIGHT_RING",ColliderAction::RING_ENABLE_RIGHT},
		{"ENABLE_CENTRAL_RING",ColliderAction::RING_ENABLE_CENTRAL},
		{"DISABLE_LEFT_CONTACT",ColliderAction::CONTACT_DISABLE_LEFT},
		{"DISABLE_RIGHT_CONTACT",ColliderAction::CONTACT_DISABLE_LEFT},
		{"ENABLE_LEFT_CONTACT",ColliderAction::CONTACT_ENABLE_LEFT},
		{"ENABLE_RIGHT_CONTACT",ColliderAction::CONTACT_ENABLE_LEFT},
	};
}

std::string ColliderActionList::getActionsRegexStr() {
	auto table = getActionTable();

	std::string s = "";

	for (std::map<std::string, ColliderAction>::iterator it = table.begin(); it != table.end(); ++it) {
		if (it == table.begin()) {
			s += "(";
		}
		else {
			s += "|";
		}
		
		s += it->first;
	}

	s += ")";

	return s;
}

const std::multimap<long, ColliderAction>& ColliderActionList::getActions() {
	return actions;
}