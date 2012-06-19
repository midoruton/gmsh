
#set terminal pdf font "Times-Roman,12" ; INTERACT = 0

set terminal aqua; INTERACT=-1
set terminal aqua 1

set style data line
set zeroaxis
set multiplot;          
 
set style function lines
set size 1.0, 1.0
set origin 0.0, 0.0

set multiplot
set grid

set title "Maximum skin temperature at different depths"
set size 0.5,0.5
set origin 0.0,0.5
set ylabel "Temperature [K]"
set xlabel "Time [s]"
plot "temp.txt" u 1:2 t "",\
     "temp.txt" u 1:9 t "",\
     "temp.txt" u 1:16 t "",\
     "temp.txt" u 1:23 t "",\
     "temp.txt" u 1:30 t "", \
     320 t "threshold "

set title "Surface temperature at t=Tlaser"
set size 0.5,0.5
set origin 0.5,0.5  
set xlabel "Radial coord [mm]"
plot "tempsurf.txt" u ($5)*1000:8 w linesp t ""

set title "Active surface "
set size 0.5,0.5
set origin 0.0,0.0
set xlabel "Skin Depth [mm]"
set ylabel "Active surface [mm^2]"
plot "activeMax.txt" u ($4)*0.05:($8)*10**6 w lp t ""

set title "Duration at threshold "
set size 0.5,0.5
set origin 0.5,0.0
set xlabel "Skin Depth [mm]"
set ylabel "Duration [s]"
plot "activeMax.txt" u ($4)*0.05:($8)*10**6 w lp t ""

unset multiplot


