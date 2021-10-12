#include "archiver/compressor.h"
#include "archiver/decompressor.h"
#include "reader/file_reader.h"
#include "writer/file_writer.h"
#include "utils/command_line_arguments_parser.h"
#include "utils/exception.h"

#include <cstring>
#include <iostream>

void PrintHelp() {
    std::cout <<
        "Usage:\n"
        "\t- archiver -c archive_name file1 [file2 ...] - compress files <file1>, <file2>, ... and store them into archive <archive_name>\n"
        "\t- archiver -d archive_name - decompress files from archive <archive_name> to current directory\n"
        "\t- archiver -h - show help (this message)\n";
}

int main(int argc, char** argv) {
    Parser parser(argc, argv);
    parser.AddRule("-c", 2);
    parser.AddRule("-d", 1);
    parser.CheckRules();

    if (parser.ArgumentsAmount() == 1 || parser.Exists("-h")) {
        PrintHelp();
        return 0;
    } else if (parser.Exists("-c")) {
        const auto& values = parser.GetValues("-c");
        Compressor compressor(std::make_unique<FileWriter>(values[0]));
        for (size_t i = 1; i < values.size(); ++i) {
            compressor.AddFile(std::make_unique<FileReader>(values[i]));
        }
        compressor.EndArchive();
    } else if (parser.Exists("-d")) {
        const auto& values = parser.GetValues("-d");
        Decompressor decompressor(std::make_unique<FileReader>(values[0]));
        decompressor.Decompress();
    } else {
        throw Exception("Unknown command. See -h for help");
    }
    return 0;
}
