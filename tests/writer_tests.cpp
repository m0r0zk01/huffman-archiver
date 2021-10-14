#include "../writer/file_writer.h"

#include <gtest/gtest.h>
#include <fstream>

TEST(WriterTest, Test1) {
    {
        FileWriter writer("./mock/test1.bin");

        writer.WriteBit(0);
        writer.WriteBit(1);
        writer.WriteBit(1);
        writer.WriteBit(0);
        writer.WriteBit(0);
        writer.WriteBit(0);
        writer.WriteBit(0);
        writer.WriteBit(1);

        writer.WriteBit(0);
        writer.WriteBit(1);
        writer.WriteBit(1);
        writer.WriteBit(1);
        writer.End();
    }

    std::ifstream in("./mock/test1.bin");
    unsigned char byte;
    in >> byte;
    ASSERT_EQ(byte, 97);
    in >> byte;
    ASSERT_EQ(byte, 112);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}