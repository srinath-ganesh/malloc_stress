set title "Memory Allocation and Free Times"
set xlabel "Chunk Size (bytes)"
set ylabel "Time (cycles)"
set key outside

# Set terminal to PNG and increase the size (e.g., 1280x960 pixels)
set terminal pngcairo size 1280,960

# Define output file
set output 'mem_timing_plot_large.png'

# Define data source
plot "mem_timing_data.txt" using 1:2 with lines title "Mean Allocation Time", \
     "mem_timing_data.txt" using 1:3 with lines title "Mean Free Time", \
     "mem_timing_data.txt" using 1:4 with lines title "Mean Free Time (-r flag)"

# Finalize the plot
unset output