set title "Memory Allocation and Free Times"
set xlabel "Chunk Size (bytes)"
set ylabel "Time (cycles)"
set key outside

# Set terminal to PNG
set terminal pngcairo

# Define output file
set output 'mem_timing_plot.png'

# Define data source
plot "mem_timing_data.txt" using 1:2 with lines title "Mean Allocation Time", \
     "mem_timing_data.txt" using 1:3 with lines title "Mean Free Time", \
     "mem_timing_data.txt" using 1:4 with lines title "Mean Free Time (-r flag)"

# Finalize the plot
unset output
