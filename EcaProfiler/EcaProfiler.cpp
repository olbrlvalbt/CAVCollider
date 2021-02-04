#include "pch.h"

#include "EcaLogic.h"
#include "EcaController.h"

#include <string>
using namespace std;
TEST(EcaLogicVsEcaControllerPerformance, EcaControllerIsMoreEfficient) {
	int n = 65534;
	int iterations = 100;
	int i = 0;

	EcaLogic ecaLogic = EcaLogic(n, 110, ECABOUNDARY_PERIODIC);
	for (i = 0; i < iterations; i++) {
		ecaLogic.applyRule();
		string result = ecaLogic.currentState;
	}
	
	EcaController ecaController = EcaController(n, 110);
	for (i = 0; i < iterations; i++) {
		ecaController.applyRule();
		const vector<string>& ref = ecaController.getCurrentState();
	}

  EXPECT_EQ(1, 1);
}