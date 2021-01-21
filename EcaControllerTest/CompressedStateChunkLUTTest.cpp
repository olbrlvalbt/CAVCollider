#include "pch.h"

#include "CompressedStateChunkLUT.h"

TEST(CompressedStateChunkLUT_ConstructorInt,
     ChunkLength0_Throws) {
    EXPECT_THROW({
        CompressedStateChunkLUT lut(0, 0);
    }, exception);
}

TEST(CompressedStateChunkLUT_ConstructorInt,
    Rule_Negative_BiggerThan255_Empty_LongerThan8__Throws) {
    EXPECT_THROW({
        CompressedStateChunkLUT lut(-1, 1);
        }, exception);
    EXPECT_THROW({
        CompressedStateChunkLUT lut(256, 1);
        }, exception);
}

TEST(CompressedStateChunkLUT_ConstructorString,
    RuleStringEmptyOrLongerThan8_Throws) {
    EXPECT_THROW({
        CompressedStateChunkLUT lut("", 1);
        }, exception);
    EXPECT_THROW({
        CompressedStateChunkLUT lut("000000000", 1);
        }, exception);
}

TEST(CompressedStateChunkLUT_ConstructorString,
     RuleStringNotBinary_Throws) {
    EXPECT_THROW({
        CompressedStateChunkLUT lut("0000000a", 1);
    }, exception);
}

TEST(CompressedStateChunkLUT_ConstructorInt,
    RuleLength1_RuleLengthShouldBe8) {
    CompressedStateChunkLUT lut(0, 1);
    string rule = lut.getRule();
    EXPECT_EQ(rule.length(), 8);
}

TEST(CompressedStateChunkLUT_ConstructorInt,
    ChunkSizeDefault_LutSizeShouldBe65536) {
    CompressedStateChunkLUT lut(0);
    EXPECT_EQ(lut.getLutSize(), 65536);
}

TEST(CompressedStateChunkLUT_ApplyRule,
    Rule110_ExpectedValues) {
    string rule110 = "1101110";
    CompressedStateChunkLUT lut(rule110);
    EXPECT_EQ(lut.applyRule(0, 0, 0), 0);
    EXPECT_EQ(lut.applyRule(1, 0, 0), 3);
    EXPECT_EQ(lut.applyRule(3, 0, 0), 7);
    EXPECT_EQ(lut.applyRule(7, 0, 0), 13);
    EXPECT_EQ(lut.applyRule(13, 0, 0), 31);
}

TEST(CompressedStateChunkLUT_ApplyRule,
    StateNegativeOrMoreThanOrEqualToLutSize_Throws) {
    EXPECT_THROW({
        int chunkSize = 2;
        CompressedStateChunkLUT lut(0, chunkSize);
        lut.applyRule(-1, 0, 0);
        }, exception);
    EXPECT_THROW({
        int chunkSize = 2;
		int lutSize = pow(2, chunkSize);
        CompressedStateChunkLUT lut(0, chunkSize);
        lut.applyRule(lutSize, 0, 0);
        }, exception);
}