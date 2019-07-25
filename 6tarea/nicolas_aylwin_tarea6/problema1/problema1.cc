#include <iostream>
#include "ceros_poli.h"

int main(int argc, char* argv[]){
  //Recibo grado de polinomio de legendre (como argumento de main)
  int n=atoi(argv[1]);
  poli<double> p;
  p=p.legendre(n);//creo este y lo imprimo
  cout<<"El polinomio de Legendre escogido es:"<<endl;
  cout<<p<<"\n"<<endl;
  //Por si se escoge de grado cero, aviso y salgo del programa
  if(n==0) {cout<<"No tiene raices"<<endl;return 0;}
  //Calculo segun newton
  matriz<double> m=raices_pol(p,'n',double(-1));
  //Reviso si algun valor es muy cercano a cero
  for(int i=0;i<m.fila();++i){
    if(abs(m(i,0))<1e-12) m(i,0)=0;
  }
  cout<<"Sus raices son:"<<"\n"<<endl;
  //Imprimo según newton
  cout<<"------Método de Newton-Raphson------"<<endl;
  cout<<m<<endl;
  //Los mismos pasos para biseccion
  m=raices_pol(p,'b',double(-1),double(1));
  for(int i=0;i<m.fila();++i){
    if(abs(m(i,0))<1e-12) m(i,0)=0;
  }
  cout<<"\n------Método de Bisección------"<<endl;
  cout<<m<<endl;
  //Para durand genero raices complejas
  matriz<complejo<double>> w;
  w=durand(p,w);
  //Pero conservo solo la parte real (pues se que los pols de legendre no tienen raices complejas)
  for(int i=0;i<w.fila();++i){
    m(i,0)=w(i,0)[0];
  }
  //Transformo en cero los muy cerca de cero e imprimo el resultado.
  for(int i=0;i<m.fila();++i){
    if(abs(m(i,0))<1e-12) m(i,0)=0;
  }
  cout<<"\n------Método de Durand-Kerner------"<<endl;
  cout<<m<<endl;
  return 0;
}
