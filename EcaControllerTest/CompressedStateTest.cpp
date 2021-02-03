#include "pch.h"

#include "CompressedState.h"

TEST(ChunkArray_Constructor1Param,
    ICLength1_HasMostSignificativeChunkShouldBeTrue) {
    CompressedState arr("1");
    EXPECT_EQ(arr.hasAdjustedMostSignificativeChunk(), true);
}

TEST(ChunkArray_Constructor2Param,
    ICLengthCHUNKSIZE_HasMostSignificativeChunkShouldBeFalse) {
    CompressedState arr(CHUNK_BITSIZE, "1");
    EXPECT_EQ(arr.hasAdjustedMostSignificativeChunk(), false);
}

TEST(ChunkArray_Constructor2Param,
    ICLength1_NCHUNKSIZE_ChunkArrayLengthShouldBe1) {
    CompressedState arr(CHUNK_BITSIZE, "1");
    EXPECT_EQ(arr.getChunkArrayLength(), 1);
}

TEST(ChunkArray_Constructor2Param,
    ICLength1_NCHUNKSIZEPlus1_ChunkArrayLengthShouldBe2) {
    CompressedState arr(CHUNK_BITSIZE + 1, "1");
    EXPECT_EQ(arr.getChunkArrayLength(), 2);
}

TEST(ChunkArray_At,
    IC10_NCHUNKSIZEPlus1_At0ShouldBe2At1ShouldBe0) {
    CompressedState arr(CHUNK_BITSIZE + 1, "10");
    EXPECT_EQ(arr.at(0), 2);
    EXPECT_EQ(arr.at(1), 0);
}

/*TEST(ChunkArray_At,
    IC10_NCHUNKSIZEPlus1_At2Throws) {
    EXPECT_THROW({
        CompressedState arr(CHUNK_BITSIZE + 1, "10");
        arr.at(2);
        }, exception);
}*/

TEST(ChunkArray_Reset,
    IC0NewIC1_At0ShouldBe1) {
    CompressedState arr("0");
    arr.reset("1");
    EXPECT_EQ(arr.at(0), 1);
}

TEST(ChunkArray_Restart,
    IC0NewIC1_At0ShouldBe1) {
    CompressedState arr("0");
    arr.reset("1");
    EXPECT_EQ(arr.at(0), 1);
}