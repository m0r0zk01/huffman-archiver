#include <gtest/gtest.h>
#include <iostream>
#include <fstream>

#include "../reader.h"

TEST(ReaderTest, Test1) {
    std::ifstream f("./mock/test1.bin", std::ios::binary);
    Reader reader(f);

    ASSERT_EQ(reader.GetNextBit(), 0);
    ASSERT_EQ(reader.GetNextBit(), 1);
    ASSERT_EQ(reader.GetNextBit(), 1);
    ASSERT_EQ(reader.GetNextBit(), 0);
    ASSERT_EQ(reader.GetNextBit(), 0);
    ASSERT_EQ(reader.GetNextBit(), 0);
    ASSERT_EQ(reader.GetNextBit(), 0);
    ASSERT_EQ(reader.GetNextBit(), 1);
    ASSERT_TRUE(reader.ReachedEOF());
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}