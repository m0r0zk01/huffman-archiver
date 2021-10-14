#include "../archiver/compressor.h"
#include "../archiver/decompressor.h"
#include "../reader/file_reader.h"
#include "../writer/file_writer.h"
#include <gtest/gtest.h>

#include <cstdio>
#include <iostream>
#include <memory>

TEST(TestArchvier, ArchiveSingleFile) {
    {
        std::unique_ptr<BaseReader> reader = std::make_unique<FileReader>("./mock/sample/watermelon.mp3");
        std::unique_ptr<BaseWriter> writer = std::make_unique<FileWriter>("./mock/arch");
        Compressor compressor(std::move(writer));
        compressor.AddFile(std::move(reader));
        compressor.EndArchive();
    }
    {
        std::unique_ptr<BaseReader> reader = std::make_unique<FileReader>("./mock/arch");
        Decompressor decompressor(std::move(reader));
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
        std::unique_ptr<BaseWriter> writer = std::make_unique<FileWriter>("./mock/arch");
        Compressor compressor(std::move(writer));

        for (const auto& filename : files) {
            std::unique_ptr<BaseReader> reader = std::make_unique<FileReader>("./mock/sample/" + filename);
            compressor.AddFile(std::move(reader));
        }

        compressor.EndArchive();
    }
    {
        std::unique_ptr<BaseReader> reader = std::make_unique<FileReader>("./mock/arch");
        Decompressor decompressor(std::move(reader));
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