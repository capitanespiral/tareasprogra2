#include "cuadratura.h"
#include <iostream>
#include <cmath>

//Declaro las dos funciones a usar
double I(double);
double gamma(double,double);

int main(){
  //Variables importantes
  double x,s;
  double res=0;
  //Pido el valor para la primera integral
  cout<<"Ingrese valor de x para la primera integral: ";cin>>x;
  cout<<"Su valor según el método del Trapezoide es ";cout<<trapezoide(I,double(0),x)<<endl;//La calculo y entrego
  //Pido valores para la segunda integral
  cout<<"\nAhora ingrese s y x (respectivamente) para la segunda integral: ";cin>>s;cin>>x;//Guardo los valores
  //Reviso que no sea menos que uno (porque diverge), De ser asi permito ingresarlo de nuevo
  while(true){
    if(s<1) {
      cout<<"La integral diverge en x=0 para s menor que 1, por favor escoje nuevamente s: ";
      cin>>s;continue;
    }
    else break;
  }
  //Calculo y entrego el valor (uso polinomio grado 10)
  cout<<"Su valor según el método de Gauss-Legendre usando un polinomio de grado 10 es ";cout<<gauss_leg(gamma,double(0),x,10,s)<<endl;
  //Pido valor para la ultima integral, es la misma (solo que hasta infinito) asi que tambien estudio el "s"
  cout<<"\nPor último ingrese s para calcular la tercera integral: ";cin>>s;
  while(true){
    if(s<1) {
      cout<<"La integral diverge en x=0 para s menor que 1, por favor escoje nuevamente s: ";
      cin>>s;continue;
    }
    else break;
  }
  //Si es 1 calculo asi (caso facil de e^-t)
  if(s==1) res=romberg(gamma,0.0,20.0,s);
  //De no ser así fijo un punto inicial y voy avanzando hasta que los valores obtenidos esten suficientemente cerca (explicare esto en el informe)
  else{
    double res1=1;
    double paso=sqrt(s-1);
    double infl=(s-1)+paso;
    //Este 3 solo me tinco viendo los graficos
    int i=3;
    while(abs(res-res1)>1e-6){
      res1=res;
      res=romberg(gamma,0.0,infl+i*paso,s);
      ++i;
      //Si avanzo demasiado romberg diverge y se va muy cercano a cero, de pasar eso devuelvo el ultimo valor con sentido y salgo del ciclo
      if(res<1e-5) {res=res1;break;}
    }
  }
  //Entrego el valor
  cout<<"Su valor según el método de Romberg es ";cout<<res<<endl;
  return 0;
}

//Las funciones usadas
double I(double a){return exp(-a*a);}
double gamma(double a,double b){return pow(a,b-1)*exp(-a);}
