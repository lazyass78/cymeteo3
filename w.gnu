#!/usr/bin/gnuplot
unset pm3d
set terminal pngcairo transparent enhanced font "arial,10" fontscale 1.0 size 600,400
set output 'wind_vector_plot.png'

set grid nopolar
set grid xtics mxtics ytics mytics noztics nomztics nortics nomrtics \
nox2tics nomx2tics noy2tics nomy2tics nocbtics nomcbtics
set grid layerdefault lt 0 linecolor 0 linewidth 0.500, lt 0 linecolor 0 linewidth 0.500

set xlabel "Longitude"
set ylabel "Latitude"
set title "Diagramme de données des vents sous forme de vecteurs (flèches orientées)"

set arrow from first 0,0 to first 1,1 nohead lc rgb "black"

plot 'w.dat' using 4:5:($2-$1):($3-$2) with vectors nohead filled lc rgb "black"
