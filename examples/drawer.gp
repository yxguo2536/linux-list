reset
set key left
set ylabel 'time(ns)'
set xlabel 'nodes'
set title 'Performance Comparision'
set terminal png font "Times_New_Roman,12"
set output OUTFILE


if(!exist("NAME3")){
	plot [:3001][:]\
	INFILE using 1:2 with linespoints linewidth 2 title NAME1, \
	''     using 1:3 with linespoints linewidth 2 title NAME2  \
}else{
	plot [:3001][:]\
	INFILE using 1:2 with linespoints linewidth 2 title NAME1, \
	''     using 1:3 with linespoints linewidth 2 title NAME2, \
	''     using 1:4 with linespoints linewidth 2 title NAME3
}
