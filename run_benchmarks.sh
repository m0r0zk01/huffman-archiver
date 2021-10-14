#!/bin/bash

echo "Starting benchmark..."

log_file='benchmarks/log.txt'
rm $log_file

for filename in ./benchmarks/*; do
#  echo "Processing $(basename "$filename")..."
  initial_size=$(stat -c%s "$filename")
  initial_size=$((initial_size / 1024))

  exec 3>&1 4>&2
  exec_time=$(TIMEFORMAT="%R"; { time ./archiver.sh -c arch "$filename" 1>&3 2>&4; } 2>&1)
  exec 3>&- 4>&-

  final_size=$(stat -c%s "arch")
  final_size=$((final_size / 1024))
  percent=$(echo "scale=2; 100 * $final_size / $initial_size" | bc -l)

  read -r -d '' log_text << EOM
file | $(basename "$filename")
time | $exec_time s
initial size | $initial_size Kb
% of initial size | $percent%
EOM

  log_text=$(echo "$log_text" | column -t -s'|')  ;
  echo -e "$log_text \n";
  echo -e "$log_text \n" >> $log_file;
done
rm arch
echo -e "\033[1m\033[0;36m Log written to benchmarks/log.txt \033[0m \n"
