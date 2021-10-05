# Huffman Archiver

---

Educational project for HSE programming course.

The program uses Huffman algorithm to compress/decompress given files

## Installation

- Clone the repository
- Run build.sh script(make sure CMake is installed on your system)

## Usage

- build.sh will generate archiver.sh executable
```
./archiver.sh -c archive_name file1 [file2 ...] - заархивировать файлы fil1, file2, ... в архив archive_name
./archiver.sh -d archive_name - разархивировать файлы из архива archive_name в текущую директорию
./archiver.sh -h - вывести справку по использованию программы(данное сообщение)
```

## Benchmarks

