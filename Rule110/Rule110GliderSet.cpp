#include "stdafx.h"
#include "Rule110GliderSet.h"

const GliderSet Rule110GliderSet::GLIDERSET_4_A4 = {
	{
			Rule110Glider::singleton().GLIDER_A4[0][0] + Rule110Basic::GetEther(27) +
			Rule110Glider::singleton().GLIDER_A4[0][1] + Rule110Basic::GetEther(23) +
			Rule110Glider::singleton().GLIDER_A4[0][2] + Rule110Basic::GetEther(25) +
			Rule110Glider::singleton().GLIDER_A4[0][0]
		,
			Rule110Glider::singleton().GLIDER_A4[0][1] + Rule110Basic::GetEther(27) +
			Rule110Glider::singleton().GLIDER_A4[0][2] + Rule110Basic::GetEther(23) +
			Rule110Glider::singleton().GLIDER_A4[0][0] + Rule110Basic::GetEther(25) +
			Rule110Glider::singleton().GLIDER_A4[0][1]
		,
			Rule110Glider::singleton().GLIDER_A4[0][2] + Rule110Basic::GetEther(27) +
			Rule110Glider::singleton().GLIDER_A4[0][0] + Rule110Basic::GetEther(23) +
			Rule110Glider::singleton().GLIDER_A4[0][1] + Rule110Basic::GetEther(25) +
			Rule110Glider::singleton().GLIDER_A4[0][2]
		,
			""
	}
};
const GliderSet Rule110GliderSet::GLIDERSET_1ELE_C2 = {
	{
			Rule110Glider::singleton().GLIDER_C2[0][0] + Rule110Basic::GetEther(2) +
			Rule110Glider::singleton().GLIDER_C2[0][0] + Rule110Basic::GetEther(2) +
			Rule110Glider::singleton().GLIDER_C2[0][0] + Rule110Basic::GetEther(1) +
			Rule110Glider::singleton().GLIDER_C2[1][1]
		,
			""
		,
			""
		,
			""
	}
};

const GliderSet Rule110GliderSet::GLIDERSET_0ELE_C2 = {
	{
			Rule110Glider::singleton().GLIDER_C2[0][0] + Rule110Basic::GetEther(2) +
			Rule110Glider::singleton().GLIDER_C2[0][0] + Rule110Basic::GetEther(1) +
			Rule110Glider::singleton().GLIDER_C2[0][3] + Rule110Basic::GetEther(1) +
			Rule110Glider::singleton().GLIDER_C2[0][1]
		,
			""
		,
			""
		,
			""
	}
};

const GliderSet Rule110GliderSet::GLIDERSET_0BLO_E_ = {
	{
			Rule110Glider::singleton().GLIDER_Ebar[0][0] + Rule110Basic::GetEther(2) +
			Rule110Glider::singleton().GLIDER_Ebar[3][0] +
			Rule110Glider::singleton().GLIDER_Ebar[6][1] +
			Rule110Glider::singleton().GLIDER_Ebar[0][1] + Rule110Basic::GetEther(2) +
			Rule110Glider::singleton().GLIDER_Ebar[1][0] + Rule110Basic::GetEther(2) +
			Rule110Glider::singleton().GLIDER_Ebar[0][0] + Rule110Basic::GetEther(1) +
			Rule110Glider::singleton().GLIDER_Ebar[3][2] + Rule110Basic::GetEther(2) +
			Rule110Glider::singleton().GLIDER_Ebar[7][0] +
			Rule110Glider::singleton().GLIDER_Ebar[1][3] +
			Rule110Glider::singleton().GLIDER_Ebar[3][3] + Rule110Basic::GetEther(1) +
			Rule110Glider::singleton().GLIDER_Ebar[4][2] + Rule110Basic::GetEther(1) +
			Rule110Glider::singleton().GLIDER_Ebar[3][2]
		,
			""
		,
			""
		,
			""
	}
};

const GliderSet Rule110GliderSet::GLIDERSET_1BLOP_E_ = {
	{
			Rule110Glider::singleton().GLIDER_Ebar[0][0] +
			Rule110Glider::singleton().GLIDER_Ebar[1][2] + Rule110Basic::GetEther(1) +
			Rule110Glider::singleton().GLIDER_Ebar[1][3] +
			Rule110Glider::singleton().GLIDER_Ebar[3][3] + Rule110Basic::GetEther(1) +
			Rule110Glider::singleton().GLIDER_Ebar[4][2] + Rule110Basic::GetEther(1) +
			Rule110Glider::singleton().GLIDER_Ebar[3][2] +
			Rule110Glider::singleton().GLIDER_Ebar[6][0] + Rule110Basic::GetEther(2) +
			Rule110Glider::singleton().GLIDER_Ebar[1][0] +
			Rule110Glider::singleton().GLIDER_Ebar[3][3] +
			Rule110Glider::singleton().GLIDER_Ebar[6][1] + Rule110Basic::GetEther(2) +
			Rule110Glider::singleton().GLIDER_Ebar[7][0] + Rule110Basic::GetEther(2) +
			Rule110Glider::singleton().GLIDER_Ebar[6][0]
		,
			""
		,
			""
		,
			""
	}
};

const GliderSet Rule110GliderSet::GLIDERSET_1BLOS_E_ = {
	{
			Rule110Glider::singleton().GLIDER_Ebar[0][0] + Rule110Basic::GetEther(2) +
			Rule110Glider::singleton().GLIDER_Ebar[3][0] +
			Rule110Glider::singleton().GLIDER_Ebar[6][1] +
			Rule110Glider::singleton().GLIDER_Ebar[0][1] + Rule110Basic::GetEther(2) +
			Rule110Glider::singleton().GLIDER_Ebar[1][0] + Rule110Basic::GetEther(2) +
			Rule110Glider::singleton().GLIDER_Ebar[0][0] +
			Rule110Glider::singleton().GLIDER_Ebar[2][0] + Rule110Basic::GetEther(2) +
			Rule110Glider::singleton().GLIDER_Ebar[5][1] +
			Rule110Glider::singleton().GLIDER_Ebar[0][1] +
			Rule110Glider::singleton().GLIDER_Ebar[2][1] + Rule110Basic::GetEther(2) +
			Rule110Glider::singleton().GLIDER_Ebar[3][0] + Rule110Basic::GetEther(2) +
			Rule110Glider::singleton().GLIDER_Ebar[2][0]
		,
			""
		,
			""
		,
			""
	}
};

const GliderSet Rule110GliderSet::GLIDERSET_SEPINIT_EE_ = {
	{
			Rule110Glider::singleton().GLIDER_E5[0][0] +
			Rule110Glider::singleton().GLIDER_E2[3][1] + Rule110Basic::GetEther(3) +
			Rule110Glider::singleton().GLIDER_E4[0][0] + Rule110Basic::GetEther(1) +
			Rule110Glider::singleton().GLIDER_Ebar[6][1] + Rule110Basic::GetEther(1) +
			Rule110Glider::singleton().GLIDER_Ebar[7][1] + Rule110Basic::GetEther(2) +
			Rule110Glider::singleton().GLIDER_Ebar[0][1] +
			Rule110Glider::singleton().GLIDER_Ebar[7][2] + Rule110Basic::GetEther(1) +
			Rule110Glider::singleton().GLIDER_Ebar[6][2]
		,
			""
		,
			""
		,
			""
	}
};

const GliderSet Rule110GliderSet::GLIDERSET_1ADD_E_ = {
	{
			Rule110Glider::singleton().GLIDER_Ebar[0][0] + Rule110Basic::GetEther(7) +
			Rule110Glider::singleton().GLIDER_Ebar[1][3] + Rule110Basic::GetEther(5) +
			Rule110Glider::singleton().GLIDER_Ebar[2][0] + Rule110Basic::GetEther(7) +
			Rule110Glider::singleton().GLIDER_Ebar[3][3]
		,
			""
		,
			""
		,
			""
	}
};

const GliderSet Rule110GliderSet::GLIDERSET_0ADD_E_ = {
	{
			Rule110Glider::singleton().GLIDER_Ebar[0][0] + Rule110Basic::GetEther(7) +
			Rule110Glider::singleton().GLIDER_Ebar[1][3] + Rule110Basic::GetEther(6) +
			Rule110Glider::singleton().GLIDER_Ebar[3][2] + Rule110Basic::GetEther(6) +
			Rule110Glider::singleton().GLIDER_Ebar[4][2]
		,
			""
		,
			""
		,
			""
	}
};


const std::map<std::string, GliderSet> Rule110GliderSet::GLIDERSETMAP = {
   {"4_a4", Rule110GliderSet::singleton().GLIDERSET_4_A4},
   {"1ele_c2", Rule110GliderSet::singleton().GLIDERSET_1ELE_C2},
   {"0ele_c2", Rule110GliderSet::singleton().GLIDERSET_0ELE_C2},
   {"0blo_e_", Rule110GliderSet::singleton().GLIDERSET_0BLO_E_},
   {"1blop_e_", Rule110GliderSet::singleton().GLIDERSET_1BLOP_E_},
   {"1blos_e_", Rule110GliderSet::singleton().GLIDERSET_1BLOS_E_},
   {"sepinit_ee_", Rule110GliderSet::singleton().GLIDERSET_SEPINIT_EE_},
   {"1add_e_", Rule110GliderSet::singleton().GLIDERSET_1ADD_E_},
   {"0add_e_", Rule110GliderSet::singleton().GLIDERSET_0ADD_E_}
};