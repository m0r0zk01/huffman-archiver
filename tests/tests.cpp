#include "../archiver/compressor.h"
#include "../archiver/decompressor.h"

#include <cstdio>
#include <iostream>

#include <gtest/gtest.h>

TEST(TestArchvier, ArchiveSingleFile) {
    {
        Reader reader("./mock/sample/watermelon.mp3");
        Writer writer("./mock/arch");
        Compressor compressor(&writer);
        compressor.AddFile(&reader);
        compressor.EndArchive();
    }
    {
        Reader reader("./mock/arch");
        Decompressor decompressor(&reader);
        decompressor.Decompress();
    }
    {
        std::ifstream file1("./mock/sample/watermelon.mp3");
        std::ifstream file2("./watermelon.mp3");

        char c1, c2;
        while (file1.get(c1)) {
            ASSERT_TRUE(file2.get(c2));
            ASSERT_EQ(c1, c2);
        }
        ASSERT_FALSE(file2.get(c2));
        ASSERT_TRUE(file1.eof());
        ASSERT_TRUE(file2.eof());
        std::remove("watermelon.mp3");
    }
}

TEST(TestArchvier, ArchiveMultipleFiles) {
    std::vector<std::string> files {"amogus.txt", "test.pdf", "a", "asd.png"};
    {
        Writer writer("./mock/arch");
        Compressor compressor(&writer);

        Reader reader;
        for (const auto& filename : files) {
            reader.SetInputStream("./mock/sample/" + filename);
            compressor.AddFile(&reader);
        }

        compressor.EndArchive();
    }
    {
        Reader reader("./mock/arch");
        Decompressor decompressor(&reader);
        decompressor.Decompress();
    }
    {
        for (const auto& filename : files) {
            std::ifstream file1("./mock/sample/" + filename);
            std::ifstream file2("./" + filename);

            char c1, c2;
            while (file1.get(c1)) {
                ASSERT_TRUE(file2.get(c2));
                ASSERT_EQ(c1, c2);
            }
            ASSERT_FALSE(file2.get(c2));
            ASSERT_TRUE(file1.eof());
            ASSERT_TRUE(file2.eof());

            std::remove(filename.data());
        }
    }
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}