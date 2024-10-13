for size in $(seq 8 100 10000); do
    output=$(./mstress -n 1000 -s $size -i 1)
    mean_alloc_time=$(echo "$output" | awk '
        /Allocated Chunk/ {alloc_total+=$(NF-1); count++}
        END {if(count > 0) print alloc_total/count}')
    echo "Chunk Size: $size bytes, Mean Allocation Time: $mean_alloc_time cycles"
done