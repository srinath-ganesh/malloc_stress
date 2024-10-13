echo "#Size(bytes) MeanAllocTime(cycles) MeanFreeTime(cycles) MeanFreeTimeRFlag(cycles)" > ./mem_timing_data.txt

for size in $(seq 8 10 10000); do
    output=$(./mstress -n 1000 -s $size -i 1)
    mean_alloc_time=$(echo "$output" | awk '/Allocated Chunk/ {alloc_total+=$(NF-1); count++} END {if(count > 0) print alloc_total/count}')
    mean_free_time=$(echo "$output" | awk '/Freed Chunk/ {free_total+=$(NF-1); count++} END {if(count > 0) print free_total/count}')

    output_r=$(./mstress -n 1000 -s $size -i 1 -r)
    mean_free_time_r=$(echo "$output_r" | awk '/Freed Chunk/ {free_total+=$(NF-1); count++} END {if(count > 0) print free_total/count}')

    echo "$size $mean_alloc_time $mean_free_time $mean_free_time_r" >> mem_timing_data.txt
done
