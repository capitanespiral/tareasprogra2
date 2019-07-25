#include "odeint.h"

using namespace std;

matriz<double> f1(double ,const matriz<double> &,const matriz<double> &);

int main(){
  //posiciones iniciales
  vector<double> ini={1,1,1,1,1,1};
  matriz<double> m(2,ini);//matriz de dos filas con el vector ini
  odeint rossler_lorenz(0,0.001,m,m);//tiempo inicial paso y datos iniciales (ultima matriz de compatibilidad)
  matriz<matriz<double>> res=rossler_lorenz.rk4(f1,100);//Que funcion y hasta que tiempo
  file("ejercicio1",res,1,'t');//creo un archivo por cuerpo de las posiciones.
  return 0;
}

//m es la posicion de ambos cuerpos (n solo para compatibilidad con la funcion)
matriz<double> f1(double t,const matriz<double> &m,const matriz<double> &n){
  matriz<double> res(2,3);
  res(0,0)=-m(0,1)-m(0,2)-0.01*m(1,2);
  res(0,1)=m(0,0)+0.2*m(0,1);
  res(0,2)=0.2+m(0,2)*(m(0,0)-5.7);
  res(1,0)=10*(m(1,1)-m(1,0))+0.01*m(0,2);
  res(1,1)=m(1,0)*(28-m(1,2))-m(1,1);
  res(1,2)=m(1,0)*m(1,1)-(8.0/3)*m(1,2);
  return res;
}
