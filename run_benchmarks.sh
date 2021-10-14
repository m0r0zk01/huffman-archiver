#!/bin/bash

echo "Starting benchmark..."

log_file='benchmarks/log.txt'
rm $log_file

for filename in ./benchmarks/*; do
  echo "Processing $(basename "$filename")..."
  initial_size=$(stat -c%s "$filename")
  initial_size=$((initial_size / 1024))

  exec 3>&1 4>&2
  exec_time=$(TIMEFORMAT="%R"; { time ./archiver.sh -c arch "$filename" 1>&3 2>&4; } 2>&1)
  exec 3>&- 4>&-

  final_size=$(stat -c%s "arch")
  final_size=$((final_size / 1024))
  percent=$(echo "scale=2; 100 * $final_size / $initial_size" | bc -l)

  echo "It took $exec_time seconds"
  echo "Size changed from $initial_size Kb to $final_size Kb ($percent% of initial size)"
  echo ""

  {
  echo "file~$(basename "$filename")"
  echo "time~$exec_time s";
  echo "initial size~$initial_size Kb";
  echo "final size~$final_size Kb";
  echo "% of initial size~$percent%";
  echo "~";
  } | column -t -s'~' >> $log_file;
done
rm arch
echo -e "\033[1m\033[0;36m Log written to benchmarks/log.txt \033[0m \n"
