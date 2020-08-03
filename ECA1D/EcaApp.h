#pragma once

#include <wx/wx.h>
#include "EcaMenu.h"

class EcaApp : public wxApp {
public:
	EcaMenu* mainFrame = nullptr;

	virtual bool OnInit();
};
