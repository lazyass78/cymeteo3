
set terminal png
set datafile separator " " 
set title "Altitude par station"
set xlabel "Longitude"
set ylabel "Latitude" 
set view map
set dgrid3d
set pm3d interpolate 7,7 
set output "hgraph.png"
set autoscale fix
splot "h.dat" using 3:4:2 with pm3d t "Altitude"



