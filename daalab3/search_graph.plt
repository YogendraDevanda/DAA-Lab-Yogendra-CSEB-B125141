set terminal png size 1000,600
set output 'search_graph.png'
set title 'Binary Search vs Ternary Search'
set xlabel 'Input Size (n)'
set ylabel 'Number of Comparisons'
set grid
plot 'search_data.txt' using 1:2 with linespoints title 'Binary Search', 'search_data.txt' using 1:3 with linespoints title 'Ternary Search'
