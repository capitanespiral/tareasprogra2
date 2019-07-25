#!/bin/bash
cd ./juego_de_la_vida/

for i in `ls Gen*.dat`;
do
    echo "unset key" >> plot.gp
    echo "set terminal png size 800,600 enhanced font \"Helvetica,20\"" > plot.gp
    echo "set output \"$(basename "$i" .dat ).png\"" >> plot.gp
    echo "set style increment default" >> plot.gp
    echo "set view map scale 1" >> plot.gp
    echo "set style data lines" >> plot.gp
    echo "set xtics border in scale 0,0 mirror norotate autojustify" >> plot.gp
    echo "set ytics border in scale 0,0 mirror norotate autojustify" >> plot.gp
    echo "set ztics border in scale 0,0 nomirror norotate autojustify" >> plot.gp
    echo "unset cbtics" >> plot.gp
    echo "set rtics axis in scale 0,0 nomirror norotate autojustify" >> plot.gp
    echo "set title '$i' " >> plot.gp
    echo "set xrange [ -0.500000 : 31.50000 ] noreverse nowriteback" >> plot.gp
    echo "set x2range [ * : * ] noreverse writeback" >> plot.gp
    echo "set yrange [ -0.500000 : 31.50000 ] noreverse nowriteback" >> plot.gp
    echo "set y2range [ * : * ] noreverse writeback" >> plot.gp
    echo "set zrange [ * : * ] noreverse writeback" >> plot.gp
    echo "set cbrange [ 0.00000 : 5.00000 ] noreverse nowriteback" >> plot.gp
    echo "set rrange [ * : * ] noreverse writeback" >> plot.gp
    echo "set pal gray" >> plot.gp
    echo "splot '$i' matrix with image" >> plot.gp
    gnuplot < plot.gp
done

mencoder *.png -mf w=800:h=600:fps=5:type=png -ovc copy -oac copy -o ../movie.avi
ffmpeg -i ../movie.avi -c:v libtheora -c:a libvorbis -q:v 6 -q:a 5 ../movie.ogv
exit 0


