set terminal png size 1000,600
set output 'maxmin_graph.png'
set title 'Maximum and Minimum using Divide and Conquer'
set xlabel 'Input Size (n)'
set ylabel 'Number of Comparisons'
set grid
plot 'maxmin_data.txt' using 1:2 with linespoints title 'Actual Comparisons', 'maxmin_data.txt' using 1:3 with lines title '3n/2 - 2'
