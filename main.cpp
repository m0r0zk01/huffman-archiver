#include "archiver/compressor.h"
#include "archiver/decompressor.h"
#include "utils/command_line_arguments_parser.h"
#include "utils/exception.h"
#include "utils/extract_filename.h"

#include <cstring>
#include <iostream>

void PrintHelp() {
    std::cout <<
        "Usage:\n"
        "\t- archiver -c archive_name file1 [file2 ...] - заархивировать файлы fil1, file2, ... в архив archive_name\n"
        "\t- archiver -d archive_name - разархивировать файлы из архива archive_name в текущую директорию\n"
        "\t- archiver -h - вывести справку по использованию программы(данное сообщение)\n";
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
        std::ofstream out(values[0]);
        Writer writer(out);
        Compressor compressor(&writer);
        for (size_t i = 1; i < values.size(); ++i) {
            Reader reader(values[i]);
            compressor.AddFile(&reader);
        }
        compressor.EndArchive();
        out.close();
    } else if (parser.Exists("-d")) {
        const auto& values = parser.GetValues("-d");
        std::ifstream in(values[0]);
        Reader reader(in);
        Decompressor decompressor(&reader);
        decompressor.Decompress();
        in.close();
    } else {
        throw Exception("Unknown command. See -h for help");
    }
    return 0;
}
