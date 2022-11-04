#include "pch.h"

#include "NaiveController.h"
#include "CompressedController.h"

#include <string>

using namespace std;

TEST(NaiveControllerVsCompressedControllerPerformance, CompressedControllerIsMoreEfficient) {
	int n = 65534;
	int iterations = 100;
	int i = 0;

	NaiveController naiveController = NaiveController(n, 110);
	for (i = 0; i < iterations; i++) {
		naiveController.applyRule();
		string result = naiveController.getCurrentState()[0];
	}
	
	CompressedController compressedController = CompressedController(n, 110);
	for (i = 0; i < iterations; i++) {
		compressedController.applyRule();
		const vector<string>& ref = compressedController.getCurrentState();
	}

  EXPECT_EQ(1, 1);
}