# Huffman Archiver

---

Educational project for HSE programming course.
The program uses Huffman algorithm to compress/decompress given files

## Installation

- Clone the repository
- Run build.sh script (make sure CMake is installed on your system)

## Usage

- build.sh will generate archiver.sh executable
- Usage:
```
./archiver.sh -c archive_name file1 [file2 ...] - compress files <file1>, <file2>, ... and store them into archive <archive_name>
./archiver.sh -d archive_name - decompress files from archive <archive_name> to current directory
./archiver.sh -h - print help (this message)
```

## Benchmarks
