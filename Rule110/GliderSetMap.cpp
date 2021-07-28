#include "stdafx.h"
#include "GliderSetMap.h"
#include "Rule110Basic.h"

GliderSetMap::GliderSetMap(GliderMap& gliderMap) {
	compositeMap["4_A4"] = Composite("4_A4", {
			gliderMap.get("A4", "A", 1) + Rule110Basic::GetEther(27) +
			gliderMap.get("A4", "A", 2) + Rule110Basic::GetEther(23) +
			gliderMap.get("A4", "A", 3) + Rule110Basic::GetEther(25) +
			gliderMap.get("A4", "A", 1)
		,
			gliderMap.get("A4", "A", 2) + Rule110Basic::GetEther(27) +
			gliderMap.get("A4", "A", 3) + Rule110Basic::GetEther(23) +
			gliderMap.get("A4", "A", 1) + Rule110Basic::GetEther(25) +
			gliderMap.get("A4", "A", 2)
		,
			gliderMap.get("A4", "A", 3) + Rule110Basic::GetEther(27) +
			gliderMap.get("A4", "A", 1) + Rule110Basic::GetEther(23) +
			gliderMap.get("A4", "A", 2) + Rule110Basic::GetEther(25) +
			gliderMap.get("A4", "A", 3)
		,
			""
		});

	compositeMap["1ELE_C2"] = Composite("1ELE_C2", {
			gliderMap.get("C2", "A", 1) + Rule110Basic::GetEther(2) +
			gliderMap.get("C2", "A", 1) + Rule110Basic::GetEther(2) +
			gliderMap.get("C2", "A", 1) + Rule110Basic::GetEther(1) +
			gliderMap.get("C2", "A", 2)
		,
			""
		,
			""
		,
			""
		});

	compositeMap["0ELE_C2"] = Composite("0ELE_C2", {
			gliderMap.get("C2", "A", 1) + Rule110Basic::GetEther(2) +
			gliderMap.get("C2", "A", 1) + Rule110Basic::GetEther(1) +
			gliderMap.get("C2", "A", 4) + Rule110Basic::GetEther(1) +
			gliderMap.get("C2", "A", 2)
		,
			""
		,
			""
		,
			""
		});

	compositeMap["0BLO_E_"] = Composite("0BLO_E_", {
			gliderMap.get("E_", "A", 1) + Rule110Basic::GetEther(2) +
			gliderMap.get("E_", "D", 1) +
			gliderMap.get("E_", "G", 2) +
			gliderMap.get("E_", "A", 2) + Rule110Basic::GetEther(2) +
			gliderMap.get("E_", "B", 1) + Rule110Basic::GetEther(2) +
			gliderMap.get("E_", "A", 1) + Rule110Basic::GetEther(1) +
			gliderMap.get("E_", "D", 3) + Rule110Basic::GetEther(2) +
			gliderMap.get("E_", "H", 1) +
			gliderMap.get("E_", "B", 4) +
			gliderMap.get("E_", "D", 4) + Rule110Basic::GetEther(1) +
			gliderMap.get("E_", "E", 3) + Rule110Basic::GetEther(1) +
			gliderMap.get("E_", "D", 3)
		,
			""
		,
			""
		,
			""
		});

	compositeMap["1BLOP_E_"] = Composite("1BLOP_E_", {
			gliderMap.get("E_", "A", 1) +
			gliderMap.get("E_", "B", 3) + Rule110Basic::GetEther(1) +
			gliderMap.get("E_", "B", 4) +
			gliderMap.get("E_", "D", 4) + Rule110Basic::GetEther(1) +
			gliderMap.get("E_", "E", 3) + Rule110Basic::GetEther(1) +
			gliderMap.get("E_", "D", 3) +
			gliderMap.get("E_", "G", 1) + Rule110Basic::GetEther(2) +
			gliderMap.get("E_", "B", 1) +
			gliderMap.get("E_", "D", 4) +
			gliderMap.get("E_", "G", 2) + Rule110Basic::GetEther(2) +
			gliderMap.get("E_", "H", 1) + Rule110Basic::GetEther(2) +
			gliderMap.get("E_", "G", 1)
		,
			""
		,
			""
		,
			""
		});

	compositeMap["1BLOS_E_"] = Composite("1BLOS_E_", {
			gliderMap.get("E_", "A", 1) + Rule110Basic::GetEther(2) +
			gliderMap.get("E_", "D", 1) +
			gliderMap.get("E_", "G", 2) +
			gliderMap.get("E_", "A", 2) + Rule110Basic::GetEther(2) +
			gliderMap.get("E_", "B", 1) + Rule110Basic::GetEther(2) +
			gliderMap.get("E_", "A", 1) +
			gliderMap.get("E_", "C", 1) + Rule110Basic::GetEther(2) +
			gliderMap.get("E_", "F", 2) +
			gliderMap.get("E_", "A", 2) +
			gliderMap.get("E_", "C", 2) + Rule110Basic::GetEther(2) +
			gliderMap.get("E_", "D", 1) + Rule110Basic::GetEther(2) +
			gliderMap.get("E_", "C", 1)
		,
			""
		,
			""
		,
			""
		});

	compositeMap["SEPINIT_EE_"] = Composite("SEPINIT_EE_", {
			gliderMap.get("E5", "A", 1) +
			gliderMap.get("E2", "D", 2) + Rule110Basic::GetEther(3) +
			gliderMap.get("E4", "A", 1) + Rule110Basic::GetEther(1) +
			gliderMap.get("E_", "G", 2) + Rule110Basic::GetEther(1) +
			gliderMap.get("E_", "H", 2) + Rule110Basic::GetEther(2) +
			gliderMap.get("E_", "A", 2) +
			gliderMap.get("E_", "H", 3) + Rule110Basic::GetEther(1) +
			gliderMap.get("E_", "G", 3)
		,
			""
		,
			""
		,
			""
		});

	compositeMap["1ADD_E"] = Composite("1ADD_E", {
			gliderMap.get("E_", "A", 1) + Rule110Basic::GetEther(7) +
			gliderMap.get("E_", "B", 4) + Rule110Basic::GetEther(5) +
			gliderMap.get("E_", "C", 1) + Rule110Basic::GetEther(7) +
			gliderMap.get("E_", "D", 4)
		,
			""
		,
			""
		,
			""
		});

	compositeMap["0ADD_E"] = Composite("0ADD_E", {
			gliderMap.get("E_", "A", 1) + Rule110Basic::GetEther(7) +
			gliderMap.get("E_", "B", 4) + Rule110Basic::GetEther(6) +
			gliderMap.get("E_", "D", 3) + Rule110Basic::GetEther(6) +
			gliderMap.get("E_", "E", 3)
		,
			""
		,
			""
		,
			""
		});

	
	idMap["4_A4"] = "4_A4";
	idMap["4_A_4"] = "4_A4";
	idMap["4A_4"] = "4_A4";
	idMap["4A4"] = "4_A4";
	idMap["4A^4"] = "4_A4";
	idMap["4_A^4"] = "4_A4";
	
	idMap["1ELE_C2"] = "1ELE_C2";
	idMap["1ELEC2"] = "1ELE_C2";
	idMap["1_ELE_C2"] = "1ELE_C2";
	idMap["1_ELEC2"] = "1ELE_C2";
	
	idMap["0ELE_C2"] = "0ELE_C2";
	idMap["0ELEC2"] = "0ELE_C2";
	idMap["0_ELE_C2"] = "0ELE_C2";
	idMap["0_ELEC2"] = "0ELE_C2";

	idMap["0BLO_E_"] = "0BLO_E_";
	idMap["0_BLO_E_"] = "0BLO_E_";
	idMap["0BLOE_"] = "0BLO_E_";
	idMap["0_BLOE_"] = "0BLO_E_";
	idMap["0BLO_E"] = "0BLO_E_";
	idMap["0_BLO_E"] = "0BLO_E_";
	idMap["0BLOE"] = "0BLO_E_";
	idMap["0_BLOE"] = "0BLO_E_";

	idMap["1BLOP_E_"] = "1BLOP_E_";
	idMap["1_BLOP_E_"] = "1BLOP_E_";
	idMap["1BLOPE_"] = "1BLOP_E_";
	idMap["1_BLOPE_"] = "1BLOP_E_";
	idMap["1BLOP_E"] = "1BLOP_E_";
	idMap["1_BLOP_E"] = "1BLOP_E_";
	idMap["1BLOPE"] = "1BLOP_E_";
	idMap["1_BLOPE"] = "1BLOP_E_";

	idMap["1BLOS_E_"] = "1BLOS_E_";
	idMap["1_BLOS_E_"] = "1BLOS_E_";
	idMap["1BLOSE_"] = "1BLOS_E_";
	idMap["1_BLOSE_"] = "1BLOS_E_";
	idMap["1BLOS_E"] = "1BLOS_E_";
	idMap["1_BLOS_E"] = "1BLOS_E_";
	idMap["1BLOSE"] = "1BLOS_E_";
	idMap["1_BLOSE"] = "1BLOS_E_";

	idMap["SEPINIT_EE_"] = "SEPINIT_EE_";
	idMap["SEPINITEE_"] = "SEPINIT_EE_";
	idMap["SEPINIT_EE"] = "SEPINIT_EE_";
	idMap["SEPINITEE"] = "SEPINIT_EE_";

	idMap["1ADD_E_"] = "1ADD_E_";
	idMap["1_ADD_E_"] = "1ADD_E_";
	idMap["1ADDE_"] = "1ADD_E_";
	idMap["1_ADDE_"] = "1ADD_E_";
	idMap["1ADD_E"] = "1ADD_E_";
	idMap["1_ADD_E"] = "1ADD_E_";
	idMap["1ADDE"] = "1ADD_E_";
	idMap["1_ADDE"] = "1ADD_E_";

	idMap["0ADD_E_"] = "0ADD_E_";
	idMap["0_ADD_E_"] = "0ADD_E_";
	idMap["0ADDE_"] = "0ADD_E_";
	idMap["0_ADDE_"] = "0ADD_E_";
	idMap["0ADD_E"] = "0ADD_E_";
	idMap["0_ADD_E"] = "0ADD_E_";
	idMap["0ADDE"] = "0ADD_E_";
	idMap["0_ADDE"] = "0ADD_E_";
}
