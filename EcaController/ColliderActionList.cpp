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
	std::string sActionRegex = "(RING_DISABLE_LEFT|RING_DISABLE_RIGHT|RING_DISABLE_CENTRAL|";
	sActionRegex += "RING_ENABLE_LEFT|RING_ENABLE_RIGHT|RING_ENABLE_CENTRAL|";
	sActionRegex += "CONTACT_DISABLE_LEFT|CONTACT_DISABLE_RIGHT|CONTACT_ENABLE_LEFT|CONTACT_ENABLE_RIGHT)";
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

ColliderAction ColliderActionList::parseAction(std::string s) {
	static std::map<std::string, ColliderAction> const table = {
		{"RING_DISABLE_LEFT",ColliderAction::RING_DISABLE_LEFT},
		{"RING_DISABLE_RIGHT",ColliderAction::RING_DISABLE_RIGHT},
		{"RING_DISABLE_CENTRAL",ColliderAction::RING_DISABLE_CENTRAL},
		{"RING_ENABLE_LEFT",ColliderAction::RING_ENABLE_LEFT},
		{"RING_ENABLE_RIGHT",ColliderAction::RING_ENABLE_RIGHT},
		{"RING_ENABLE_CENTRAL",ColliderAction::RING_ENABLE_CENTRAL},
		{"CONTACT_DISABLE_LEFT",ColliderAction::CONTACT_DISABLE_LEFT},
		{"CONTACT_DISABLE_RIGHT",ColliderAction::CONTACT_DISABLE_RIGHT},
		{"CONTACT_ENABLE_LEFT",ColliderAction::CONTACT_ENABLE_LEFT},
		{"CONTACT_ENABLE_RIGHT",ColliderAction::CONTACT_ENABLE_RIGHT}
	};

	return table.at(s);
}

const std::multimap<long, ColliderAction>& ColliderActionList::getActions() {
	return actions;
}