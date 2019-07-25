set terminal png
set output "x1_x2.png"
set title "x1 y x2"
plot "cuerpo1.dat" u 1:2 w l,"cuerpo2.dat" u 1:2 w l
set output "y1_y2.png"
set title "y1 y y2"
plot "cuerpo1.dat" u 1:3 w l,"cuerpo2.dat" u 1:3 w l
set output "z1_z2.png"
set title "z1 y z2"
plot "cuerpo1.dat" u 1:4 w l,"cuerpo2.dat" u 1:4 w l
