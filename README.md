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
<br>`./archiver.sh -c archive_name file1 [file2 ...]` - compress files <file1>, <file2>, ... and store them into archive <archive_name>
<br>`./archiver.sh -d archive_name` - decompress files from archive <archive_name> to current directory
<br>`./archiver.sh -h` - show help (this message)


## Benchmarks

- Benchmark files are located in [`benchmarks`](/benchmarks) folder
- You can add there your own files
- Run benchmarks with `run_benchmarks.sh` script

My files benchmark ([log.txt](./benchmarks/log.txt)):
```
file               WarAndPeace.txt
time               0.383 s
initial size       4067 Kb
final size         1141 Kb
% of initial size  28.05%

file               skull.jpg
time               0.015 s
initial size       81 Kb
final size         80 Kb
% of initial size  98.76%
```