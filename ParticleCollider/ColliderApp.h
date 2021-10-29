#pragma once

#include <wx/wx.h>

#include "ColliderFrame.h"
#include "ColliderMenu.h"

class ColliderApp : public wxApp {
public:
	ColliderMenu* m;
	
	ColliderFrame* mainFrame;
	FilteredCollisionSystem* system;
	ColliderConfiguration* config;
	virtual bool OnInit();
	ColliderApp();
};
