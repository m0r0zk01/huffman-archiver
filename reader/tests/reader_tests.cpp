#include "../file_reader.h"

#include <gtest/gtest.h>
#include <iostream>
#include <fstream>

TEST(ReaderTest, Test1) {
    FileReader reader("./mock/test1.bin");

    ASSERT_FALSE(reader.ReachedEOF());
    ASSERT_EQ(reader.ReadNextBit(), 0);
    ASSERT_EQ(reader.ReadNextBit(), 1);
    ASSERT_EQ(reader.ReadNextBit(), 1);
    ASSERT_EQ(reader.ReadNextBit(), 0);
    ASSERT_EQ(reader.ReadNextBit(), 0);
    ASSERT_EQ(reader.ReadNextBit(), 0);
    ASSERT_EQ(reader.ReadNextBit(), 0);
    ASSERT_EQ(reader.ReadNextBit(), 1);
    ASSERT_TRUE(reader.ReachedEOF());
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}