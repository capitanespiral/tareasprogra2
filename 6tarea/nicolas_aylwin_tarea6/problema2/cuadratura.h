#ifndef CUADRATURA_H
#define CUADRATURA_H

#include "poli.h"
#include "ceros_poli.h"
#include "matriz.h"
using namespace std;

//integracion del trapezoide, recibe la funcion, de donde hasta donde integrar (a,b), en cuanto subdividir el intervalo y un error deseado
template <class T>
T trapezoide(T (*f)(T),T a,T b,int inicial=1000000,int paso=100000,double error=1e-6){
  T res=T(0);
  T res1=T(1);
  int N=inicial;
  //Bucle donde comienza, fijo un tope de trapecios
  while(abs(res-res1)>error && N<3000000){
    res1=res;
    res=0;
    for(int i=0;i<N;++i) res=res+(*f)(a+i*(b-a)/T(N));
    res=((b-a)/T(N))*((*f)(a)*0.5+(*f)(b)*0.5+res);
    N+=paso;
  }
  return res;
}

//Integracion gauss-legendre, recibe lo mismo pero el N es ahora que puntos tomar. Tambien valor auxiliar por el valor extra "S" que tiene la funcion pedida
template <class T>
T gauss_leg(T (*f)(T,T),T a, T b,int N,T aux){
  poli<T> p;
  //Obtengo legendre
  p=p.legendre(N);
  //Obtengo sus raices y limpio si hay "ceros"
  matriz<T> raices=raices_pol(p,'n',T(-1));
  for(int i=0;i<raices.fila();++i)
    if(abs(raices(i,0))<1e-15) raices(i,0)=0;
  //Calculo la derivada
  p=p.deriv();
  matriz<T> pesos(N,1);
  //Bucles para calcular la integral aproximada
  for(int i=0;i<pesos.fila();++i)
    pesos(i,0)=2/((1-raices(i,0)*raices(i,0))*p(raices(i,0))*p(raices(i,0)));
  T res=0;
  for(int i=0;i<N;++i)
    res=res+pesos(i,0)*(*f)((b-a)*0.5*raices(i,0)+(a+b)*0.5,aux);
  return (b-a)*0.5*res;
}

//Metodo de romberg, recibe funcion, valores donde integrar (incluyendo valor auxiliar por la funcion a integrar), tamaño de matriz maximo (matriz cuadrada) y error esperado
template <class T>
T romberg(T (*f)(T,T),T a,T b,T aux,int max=100,double error = 1e-8){
  T acum=0;
  //Valores que aparecen varias veces
  T hn,hm;
  bool flag=true;
  int I;
  //creo la matriz y guardo el primer elemento
  matriz<T> m(max,max);
  m(0,0)=0.5*(b-a)*((*f)(a,aux)+(*f)(b,aux));
  //Ciclo de filas
  for(int i=1;i<max;++i){
    //Calculo hn y la suma de la formula
    hn=(b-a)*pow(0.5,i);
    for(int k=1;k<=pow(2,i-1);++k) acum=acum+(*f)(a+(2*k-1)*hn,aux);
    m(i,0)=0.5*m(i-1,0)+hn*acum;//Elemento columna cero
    for(int j=1;j<=i;++j){
      hm=1/T(pow(4,j)-1);
      m(i,j)=m(i,j-1)+hm*(m(i,j-1)-m(i-1,j-1));//Todos los demas
    }
    acum=0;//Reinicio el acumulador
    //Si se cumple la condicion escapo del ciclo guardando el valor mas preciso. 
    if(abs(m(i,i)-m(i,i-1))<error) {flag=!flag;I=i;break;}
  }
  //Si se llego al max pero no se entro al if anterior se manda el mensaje de precacucion y se entrega un valor cualquiera.
  if(flag) {cout<<"No se alcanzó el error deseado"<<endl;return m(0,0);}
  return m(I,I);
}

#endif
