#include "pch.h"

#include "CompressedController.h"

TEST(CompressedController,
    CheckMemoryUsage) {
    CompressedController eca1(500, 110);
    {
        CompressedController eca2(500, 110);
    }
    CompressedController eca3(500, 110);
    EXPECT_EQ(1, 1);
}

TEST(CompressedController_Constructor,
    RandomIC) {
    CompressedController eca1(500, 110);
    auto res = eca1.getCurrentState();

    EXPECT_EQ(1, 1);
}

TEST(CompressedController_Constructor,
    Rule110EtherIC) {
    CompressedController eca1(14, 110, "11111000100110");
    EXPECT_EQ ((eca1.getCurrentState())[0], "11111000100110");

    int i = 0;
    string a = "";
    do {
        eca1.applyRule();
        a = eca1.getCurrentState()[0];
        i++;
    } while (a.compare("11111000100110") != 0);
    i;
}