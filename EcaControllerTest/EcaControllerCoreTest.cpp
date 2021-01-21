#include "pch.h"

#include "EcaControllerCore.h"

using namespace EcaControllerCore;

TEST(EcaControllerCore_FormatBinaryString,
     SEmpty_ReturnsNZeros) {
    int n = 2;
    EXPECT_EQ(FormatBinaryString("", n), "00");
}

TEST(EcaControllerCore_FormatBinaryString,
    NNegative_Throws) {
    EXPECT_THROW({
        FormatBinaryString("", -1);
        }, exception);
}

TEST(EcaControllerCore_ToBinaryString,
    0_Returns0) {
    EXPECT_EQ(ToBinaryString(0), "0");
}

TEST(EcaControllerCore_ToBinaryString,
    1_Returns1) {
    EXPECT_EQ(ToBinaryString(1), "1");
}

TEST(EcaControllerCore_ToBinaryString,
    2_Returns10) {
    EXPECT_EQ(ToBinaryString(2), "10");
}

TEST(EcaControllerCore_ToBinaryString,
    3_Returns11) {
    EXPECT_EQ(ToBinaryString(3), "11");
}