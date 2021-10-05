#include "archiver/compressor.h"
#include "archiver/decompressor.h"

#include <cstring>
#include <fstream>
#include <iostream>

void PrintHelp() {
    std::cout <<
        "Usage:\n"
        "\t- archiver -c archive_name file1 [file2 ...] - заархивировать файлы fil1, file2, ... в архив archive_name\n"
        "\t- archiver -d archive_name - разархивировать файлы из архива archive_name в текущую директорию\n"
        "\t- archiver -h - вывести справку по использованию программы(данное сообщение)\n";
}

int main(int argc, char** argv) {
    if (argc == 1) {
        PrintHelp();
        return 0;
    }
    if (!strcmp(argv[1], "-h")) {
        PrintHelp();
    } else if (!strcmp(argv[1], "-c")) {
        if (argc < 4) {
            std::cout << "Not enough arguments passed. Use 'archiver -h' to see help\n";
            return 1;
        }

        std::string archive_name(argv[2]);
        std::ofstream out(archive_name);
        Compressor compressor(out);
        for (size_t i = 3; i < static_cast<size_t>(argc); ++i) {
            compressor.AddFile(argv[i]);
        }
        compressor.EndArchive();
        out.close();
    } else if (!strcmp(argv[1], "-d")) {
        if (argc != 3) {
            std::cout << "Wrong amount of arguments passed. Use 'archiver -h' to see help\n";
            return 1;
        }

        std::string archive_name(argv[2]);
        std::ifstream in(archive_name);
        Decompressor decompressor(in);
        decompressor.Decompress();
        in.close();
    } else {
        std::cout << "Unknown command: " << argv[1] << '\n';
        return 1;
    }
    return 0;
}
