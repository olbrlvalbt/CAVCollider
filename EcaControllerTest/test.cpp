#include "pch.h"

#include "CompressedStateChunkLUT.h"

TEST(_CompressedStateChunkLUT, _constructor_zerochunklength_throws) {
    EXPECT_THROW({
            CompressedStateChunkLUT lut("00000000", 0);
        }, exception);
}