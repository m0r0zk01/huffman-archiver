#include "../archiver/compressor.h"
#include "../archiver/decompressor.h"

#include <iostream>

#include <gtest/gtest.h>

TEST(TestArchvier, ArchiveSingleFile) {
    Reader reader("./mock/sample/amogus.txt");
    Writer writer("./arch");
    Compressor compressor(&writer);
    compressor.AddFile(&reader);
    compressor.EndArchive();
    reader.SetInputStream("./arch");
    std::cout << "HERE\n";
    Decompressor decompressor(&reader);
    std::cout << "HERE\n";
    decompressor.Decompress();

    std::ifstream file1("./mock/sample/amogus.txt");
    std::ifstream file2("./amogus.txt");

    char c1, c2;
    while (file1.get(c1)) {
        ASSERT_TRUE(file2.get(c2));
        ASSERT_EQ(c1, c2);
    }
    ASSERT_TRUE(file2.get(c2));
    ASSERT_TRUE(file1.bad());
    ASSERT_TRUE(file2.bad());
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}