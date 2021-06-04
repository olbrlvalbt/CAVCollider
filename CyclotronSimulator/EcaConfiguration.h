#pragma once

#include <wx/wx.h>

#include "EcaController.h"

class EcaConfiguration {
protected:
	EcaController* ecaController;

public:
	EcaConfiguration(EcaController* _ecaController);
	~EcaConfiguration();

	EcaController* getEca();
};

