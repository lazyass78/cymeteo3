#!/usr/bin/gnuplot

set terminal pngcairo transparent enhanced font "arial,10" fontscale 1.0 size 600,400
set output 'barre_erreur_temperature.png'

set grid nopolar
set grid xtics mxtics ytics mytics noztics nomztics nortics nomrtics \
nox2tics nomx2tics noy2tics nomy2tics nocbtics nomcbtics
set grid layerdefault lt 0 linecolor 0 linewidth 0.500, lt 0 linecolor 0 linewidth 0.500

set style data lines
set xlabel "Identifiant"
set ylabel "Température (en °C)"
set title "Graphique barre d'erreur"

set yrange [ * : * ] noreverse writeback
set y2range [ * : * ] noreverse writeback

Shadecolor = "#80E0A080"

plot 't1.dat' using 1:2:($2-$3):($2-$4) with yerrorfill below fc rgb Shadecolor notitle, \
 	'' using 1:2 with lines lw 2 title "Température moyenne"