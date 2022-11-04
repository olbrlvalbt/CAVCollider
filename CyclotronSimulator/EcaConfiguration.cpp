#include "EcaConfiguration.h"

EcaConfiguration::EcaConfiguration(EcaController* _ecaController)
	: ecaController(_ecaController){
}

EcaConfiguration::~EcaConfiguration() {
	//delete ecaController;
}

EcaController& EcaConfiguration::getEca() {
	return *ecaController;
}
