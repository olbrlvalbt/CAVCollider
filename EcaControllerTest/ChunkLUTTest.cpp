#include "pch.h"

#include "ChunkLUT.h"

TEST(ChunkLUT_Constructor,
    ChunkSizeDefault_LutSizeShouldBe65536) {
    ChunkLUT lut("00000000");
    EXPECT_EQ(lut.getLutSize(), 65536);
}

TEST(ChunkLUT_Get,
    Rule110_ExpectedValues) {
    string rule110 = "01101110";
    ChunkLUT lut(rule110);
    EXPECT_EQ(lut.get(0, 0, 0), 0);
    EXPECT_EQ(lut.get(1, 0, 0), 3);
    EXPECT_EQ(lut.get(3, 0, 0), 7);
    EXPECT_EQ(lut.get(7, 0, 0), 13);
    EXPECT_EQ(lut.get(13, 0, 0), 31);
}

/*TEST(ChunkLUT_Get,
    StateNegativeOrMoreThanOrEqualToLutSize_Throws) {
    EXPECT_THROW({
        int chunkSize = 2;
        ChunkLUT lut(0, chunkSize);
        lut.get(-1, 0, 0);
        }, exception);
    EXPECT_THROW({
        int chunkSize = 2;
		int lutSize = pow(2, chunkSize);
        ChunkLUT lut(0, chunkSize);
        lut.get(lutSize, 0, 0);
        }, exception);
}*/