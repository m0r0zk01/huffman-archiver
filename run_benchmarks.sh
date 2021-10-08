#!/bin/bash

echo "Starting benchmark..."

for filename in ./benchmarks/*; do
    START=$(date +%s%3N)
    echo "Processing $filename..."
    INITIAL_SIZE=$(stat -c%s "$filename")
    INITIAL_SIZE=$((INITIAL_SIZE / 1024))
    ./archiver.sh -c arch "$filename";
    END=$(date +%s%3N)
    DIFF=$(((END - START) / 1000))
    FINAL_SIZE=$(wc -c < "arch")
    FINAL_SIZE=$((FINAL_SIZE / 1024))
    echo "Done!"
    echo "It took $DIFF seconds"
    echo "Filesize changed from $INITIAL_SIZE Kb to $FINAL_SIZE Kb"
    echo ""
    rm arch
done

