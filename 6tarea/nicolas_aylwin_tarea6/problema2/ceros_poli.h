#ifndef CEROS_H
#define CEROS_H

#include "poli.h"
#include "matriz.h"
#include "complejos.h"
#include <cmath>


typedef unsigned int uint;
//Funciones para sacar ceros de funciones

//newton con polinomios (es necesario dar una semilla con parte imaginaria si quiero raiz compleja), recibo polinomio semilla y error
template <class T,class U>
T newton(const poli<U> &p,T seed=T(1),double error=1e-10){
  T err(1);
  T xn=seed;
  T xn1;
  //Derivo el polinomio
  poli<U> q=p.deriv();
  int i=0;
  //Realizo el bucle
  while(err>error && err!=0){
    xn1=xn-(eval(p,xn)/eval(q,xn));
    err=abs(xn-xn1);
    xn=xn1;
    ++i;
    //Medida de emergencia si se ha demorado demasiado en converger
    if(i>1000) {cout<<"No convergió"<<endl;break;}
  }
  return xn;
}


//biseccion para polinomios, recibo polinomio intervalo y error
template <class T,class U>
T biseccion(const poli<U> &p,T a=T(-10),T b=T(10),double error=1e-10){
  //Evaluo si tiene sentido el intervalo entregado
  if(eval(p,a)*eval(p,b)<0){
    T err(1);
    T medio;
    //Realizo el bucle
    while(err!=0 && abs(err)>error){
      medio=(a+b)/2;
      err=p(medio);
      if(err*eval(p,a)<0) b=medio;
      else a=medio;
    }
    return medio;
  }
  //Si el intervalo no cumple la minima condicion aviso al respecto
  else{
    cout<<"Mal definición de intervalo"<<endl;
    return 0;
  }
}

//durand (solo funcionara si T es complejo), recibo polinomio, matriz con valores iniciales y error
template <class T,class U>
matriz<T> durand(const poli<U> &p,matriz<T> &m,double error=1e-10){
  complejo<double> uno(1,0);
  //Si la matriz inicial es la que tengo por default (1x1), la lleno de las raices de la unidad (complejas)
  if(m.fila()==1 && m.colu()==1){
    matriz<complejo<double>> start(p.grad(),1,uno);
    for(uint i=0;i<p.grad();++i) start(i,0)=raiz(uno,p.grad(),i+1);
    m=start;
  }
  complejo<double> unoo(uno);
  //El polinomio debe ser monico, normalizo
  poli<double> q=p/p[p.grad()];
  double err;
  bool flag=true;
  int k=0;
  while(true){
    //Realizo una iteracion para cada valor
    for(int i=0;i<m.fila();++i){
      for(int j=0;j<m.fila();++j){
	if(i!=j) uno=uno*(m(i,0)-m(j,0));
      }
      m(i,0)=m(i,0)-(eval(q,m(i,0))/uno);
      uno=unoo;
    }
    //Los evaluo a todos, solo me salgo del bucle externo (while) si es que todos estan muy cerca de ser raices (acorde a mi error)
    for(int i=0;i<m.fila();++i){
      err=eval(q,m(i,0)).mod();
      if(err>error){flag=false;break;}
    }
    if(flag) return m;
    flag=true;
    ++k;
    //Medida de seguridad si tarda demasiado en conveger
    if(k>1000){cout<<"No convergió"<<endl;break;}
  }
  return m;
}

//Decidir intervalo (específico para legendre), fijo a y devuelvo un b tentativo (que cumpla la diferencia de signos). Trozo son los trozos en que corto en el intervalo entregado (inicialmente). 
template <class T,class U>
T int_legendre(const poli<U> &p,T a, T b,int trozo = 3){
  //Si sirve, de inmediato lo devuelvo
  if(eval(p,a)*eval(p,b)<0) return b;
  else{
    double temp;
    bool flag=true;
    int j=0;
    //Voy cortando el intervalo y evaluando en cada corte.
    while(flag && j<100){
      for(int i=trozo;i>=1;--i){
	temp=(i*(b-a)/double(trozo)+a);
	if(eval(p,a)*eval(p,temp)<0) {flag=!flag;break;}
      }
      //Si ninguno sirvio realizo cortes mas pequeños
      ++j;trozo+=j;
    }
    //Medida de seguridad si nunca funciono
    if(j>=100) cout<<"Cuidado, intervalo talvez no sirva"<<endl;
    return temp;
  }
}



//Encontrar todos las raices de un polinomio modo newton y modo biseccion, usare a de semilla si es metodo de newton. Biseccion no está bien hecho para complejos. Recibo polinomio, char que indica que metodo usar, intervalo (o semilla) y error.
template <class T,class U>
matriz<T> raices_pol(const poli<U> &p,char m,T a=T(-1),T b=T(1),double error=1e-10){
  T llenar = T(1);
  //Creo matriz resultante
  matriz<T> res(p.grad(),1,llenar);
  if(m =='n'){
    //Aplico newton y divido por (x-raizresultante)
    //Asi puedo obtener todas las raices
    poli<T> aux(1,llenar);
    poli<T> temp=cambia_tipo(p,llenar);
    for(uint i=0;i<p.grad();++i){
      llenar=newton(temp,a,error);
      res(i,0)=llenar;
      aux[0]=-1*llenar;
      temp=temp/aux;
    }
    return res;
  }
  else if(m == 'b'){
    poli<T> temp(p);
    poli<T> aux(1,llenar);
    //Encuentro intervalo, fijo a en -1 y parto con b=1
    for(uint i=0;i<p.grad();++i){
      //Si es de grado impar definitivamente habrá un cambio de signo
      if(temp.grad()%2!=0){
	a=-1;b=1;
      }
      //Si no, uso la funcion anterior
      else{
	a=-1;b=int_legendre(temp,a,double(1));
      }
      //Misma logica, voy dividiendo por (x-raizresultante)
      llenar=biseccion(temp,a,b,error);
      res(i,0)=llenar;
      aux[0]=-1*llenar;
      temp=temp/aux;
    }
    return res;
  }
  //Si se ingresa una opcion no valida
  else{cout<<"Opcion no existente"<<endl; return res;}
}

#endif
