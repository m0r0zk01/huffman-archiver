#include "../writer.h"

#include <gtest/gtest.h>
#include <fstream>

TEST(WriterTest, Test1) {
    std::ofstream out("./mock/test1.bin");
    Writer writer(out);

    writer.WriteBit(0);
    writer.WriteBit(1);
    writer.WriteBit(1);
    writer.WriteBit(0);
    writer.WriteBit(0);
    writer.WriteBit(0);
    writer.WriteBit(0);
    writer.WriteBit(1);

    writer.Close();
    out.close();

    std::ifstream in("./mock/test1.bin");

    unsigned char byte;
    in >> byte;

    ASSERT_EQ(byte, 97);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}