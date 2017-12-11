gnuplot <<EOF
set terminal pdf
set output 'plots.pdf'
set xlabel 'RGB Value'
set ylabel 'Frequency'


set title "test1"
plot "test1-RED.txt" smooth unique lc rgb "red", "test1-GREEN.txt" smooth unique lc "green", "test1-BLUE.txt" smooth unique lc "blue"

set title "test2"
plot "test2-RED.txt" smooth unique lc rgb "red", "test2-GREEN.txt" smooth unique lc "green", "test2-BLUE.txt" smooth unique lc "blue"

set yrange[0:15000]
set xrange[0:255]

set title "landscape1"
plot "landscape1-RED.txt" smooth unique lc rgb "red", "landscape1-GREEN.txt" smooth unique lc "green", "landscape1-BLUE.txt" smooth unique lc "blue"

set yrange[0:2000]
set xrange[0:255]

set title "landscape2"
plot "landscape2-RED.txt" smooth unique lc rgb "red", "landscape2-GREEN.txt" smooth unique lc "green", "landscape2-BLUE.txt" smooth unique lc "blue"


set yrange[0:20000]
set xrange[0:255]

set title "yosemite"
plot "yosemite-RED.txt" smooth unique lc rgb "red", "yosemite-GREEN.txt" smooth unique lc "green", "yosemite-BLUE.txt" smooth unique lc "blue"

EOF
