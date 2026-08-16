set terminal png size 1000,600
set output 'selection_graph.png'
set title 'Selection Sort - Order of Growth'
set xlabel 'Input Size (n)'
set ylabel 'Number of Comparisons'
set grid
plot 'selection_data.txt' using 1:2 with linespoints title 'Actual Comparisons', 'selection_data.txt' using 1:3 with lines title 'n(n-1)/2'
