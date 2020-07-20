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


const std::map<std::string, GliderSet> Rule110GliderSet::GLIDERSETMAP = {
   {"4_A4", Rule110GliderSet::singleton().GLIDERSET_4_A4},
   {"1Ele_C2", Rule110GliderSet::singleton().GLIDERSET_1ELE_C2},
   {"0Ele_C2", Rule110GliderSet::singleton().GLIDERSET_0ELE_C2}
};