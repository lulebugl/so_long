#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 rows cols"
    exit 1
fi

rows=$1
cols=$2
filename="map_${rows}x${cols}.ber"

# Create top border
printf "1%.0s" $(seq 1 $cols) > $filename
printf "\n" >> $filename

# Create middle rows
for ((i=2; i<$rows; i++)); do
    printf "1" >> $filename
    for ((j=2; j<$cols; j++)); do
        if [ $i -eq $(($rows/2)) ] && [ $j -eq 2 ]; then
            printf "P" >> $filename
        elif [ $i -eq $(($rows/3)) ] && [ $j -eq $(($cols/2)) ]; then
            printf "C" >> $filename
        elif [ $i -eq $(($rows-2)) ] && [ $j -eq $(($cols-2)) ]; then
            printf "E" >> $filename
        elif [ $(($RANDOM % 3)) -eq 0 ]; then
            printf "1" >> $filename
        else
            printf "0" >> $filename
        fi
    done
    printf "1\n" >> $filename
done

# Create bottom border
printf "1%.0s" $(seq 1 $cols) >> $filename

echo "Map generated in $filename"