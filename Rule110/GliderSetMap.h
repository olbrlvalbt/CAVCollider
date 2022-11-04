#pragma once

#include "Rule110DLL.h"

#include "CompositeMap.h"
#include "GliderMap.h"

class RULE110_DLL GliderSetMap : public CompositeMap {
public:
	GliderSetMap(GliderMap& gliderMap);

private:
	std::string getEther(int multiple);
};

