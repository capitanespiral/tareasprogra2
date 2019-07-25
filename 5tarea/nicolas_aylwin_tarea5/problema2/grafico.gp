set terminal png
set output "spline_periodico.png"
plot "spline_periodico.dat" w l,"datos.txt" pt 4 ps 2
