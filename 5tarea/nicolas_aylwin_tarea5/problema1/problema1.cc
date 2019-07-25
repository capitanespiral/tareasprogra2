#include "odeint.h"
#include <cmath>

using namespace std;

//Fuerza de coulomb. Entrega aceleracion en theta pero guarda en la matriz que no es const la aceleracion total en r (que es la misma que la fuerza).
matriz<double> coulomb(double, const matriz<double> &,const matriz<double> &,matriz<double> &);

//Funcion que distribuye las cargas segun la cantidad de estas. Asumo que si se entrega n, habian n+1 particulas en equilibrio. Por defecto saco la carga con tetha=0.
matriz<double> pos(int);

//Funcion que entrega la energia total a todo tiempo.
matriz<double> energia(const matriz<matriz<double>> &);

//Funcion que exporta a un archivo de nombre string lo pedido por la tarea
void pasos_20(string,const matriz<matriz<double>> &,double); 

//Main
int main(int argc, char* argv[]){
  //Almaceno la cantidad de particulas, el tiempo final y el paso.
  int n=atoi(argv[1]);
  double tf=atof(argv[2]);
  double h=atof(argv[3]);
  //Creo la matriz de posiciones iniciales
  matriz<double> posi=pos(n);//n filas, 1 columna (cantidad de particulas y posicion en tetha respectivamente)
  matriz<double> ceros=posi;clean(ceros);//misma dimension que posi pero rellena de ceros, pues son las velocidades iniciales
  matriz<double> fuer_r(n,2); //matriz donde guardare la fuerza en r, pero en cartesianas.
  //Creo el objeto "integrador"
  odeint anillo(0,h,posi,ceros,fuer_r);
  //Realizo los distintos metodos numericos y guardo resultado en matriz de matrices (de 5 filas, tiempo, posiciones, velocidades, aceleraciones, fuerza sobre el anillo). cada columna es un paso distinto.
  matriz<matriz<double>> eul_cro=anillo.euler_cromer(coulomb,tf);//Cada metodo recibe solo la funcion de aceleracion y el tiempo final (lo demas esta en el objeto odeint.
  matriz<matriz<double>> rk=anillo.rk4(coulomb,tf);
  matriz<matriz<double>> velver=anillo.vel_velver(coulomb,tf);
  matriz<matriz<double>> pefr=anillo.pefrl(coulomb,tf);
  //Creo los archivos pedidos en la tarea
  pasos_20("euler_cromer",eul_cro,h);
  pasos_20("rk4",rk,h);
  pasos_20("vel-velver",velver,h);
  pasos_20("pefrl",pefr,h);
  return 0;
}

////////DEFINICIONES DE FUNCIONES USADAS///////////

matriz<double> coulomb(double t, const matriz<double> &x,const matriz<double> &v,matriz<double> &q){
  //Trabajo con arbitrarias particulas pero solo con una coordenada (filas y columnas respectivamente)
  matriz<double> res(x.fila(),1);//aceleracion final en tetha
  matriz<double> temp(1,2);//para acumular ambas aceleraciones (identicas a la fuerza en este caso)
  matriz<double> temp1(temp);
  double div,ang;
  //Itero en todas las posiciones y analizo cuando son distintas (para evitar autointeraccion)
  for(int i=0;i<x.fila();++i){
    for(int j=0;j<x.fila();++j){
      //Calculamos la interaccion de todas las cargas j sobre la carga i
      if(i!=j){
	//Diferencia de angulos y modulo de la diferencia de vectores al cubo
	ang=x(i,0)-x(j,0);
	div=8*abs(sin(ang/2)*sin(ang/2)*sin(ang/2));
	//calculo ambas aceleraciones (columna 1 radial, columna 2 en tetha)
	temp1(0,0)=1-cos(ang);temp1(0,1)=sin(ang);
	temp=temp+temp1/div;
      }
    }
    //Guardo la aceleracion en tetha en la matriz que devolvere, y las componentes cartesianas de la aceleracion en r.
    res(i,0)=temp(0,1);
    q(i,0)=(temp(0,0)+v(i,0)*v(i,0))*cos(x(i,0));
    q(i,1)=(temp(0,0)+v(i,0)*v(i,0))*sin(x(i,0));
    clean(temp);
  }
  return res;
}
  
matriz<double> pos(int n){
  matriz<double> res(n,1);
  for(int i=0;i<res.fila();++i)
    res(i,0)=(2*M_PI/(n+1))*(i+1);//Se distribuye equidistantes imaginando que esta la carga n+1 en tetha=0
  return res;
}

matriz<double> energia(const matriz<matriz<double>> &m){
  double cin=0;
  double pot=0;
  matriz<double> res(1,m.colu());
  //primera iteracion sobre todos los pasos
  for(int i=0;i<m.colu();++i){
    //Ahora sobre cantidad de cargas
    for(int j=0;j<m(1,0).fila();++j){
      //Calculo la cinetica de cada una
      cin+=(m(2,i)(j,0)*m(2,i)(j,0))/2;
      for(int k=0;k<m(1,0).fila();++k){//lo mismo para energia pot
	if(j!=k){
	  pot+=1/(2*abs(sin((m(1,i)(j,0)-m(1,i)(k,0))/2)));
	}
      }
    }
    res(0,i)=cin+pot/2;//divido dos por considerar cada distancia en la potencial dos veces 
    cin=0;pot=0;
  }
  return res;
}

//Recibo la matriz de matrices resultante de los metodos
void pasos_20(string s,const matriz<matriz<double>> &m,double h){
  ofstream archivo(s+".dat");//creo el archivo
  double f_anix=0;//fuerza sobre el anillo en X y en Y
  double f_aniy=0;
  matriz<double> ener=energia(m);//calculo la energia
  int trozos=(m.colu()-1)/20;//el momento inicial no cuenta como paso.
  for(int i=0;i<=trozos;++i){
    archivo<<m(0,i*20)(0,0)<<"\t"; //mando el tiempo
    archivo<<h<<"\t";//el paso
    for(int j=0;j<m(1,0).fila();++j){//para mandar posicion
      archivo<<m(1,i*20)(j,0)<<' ';
    }
    archivo<<"\t";//espacio extra
    for(int j=0;j<m(1,0).fila();++j){//para mandar velocidad
      archivo<<m(2,i*20)(j,0)<<' ';
    }
    archivo<<"\t"<<ener(0,i*20)<<"\t";;//mando la energia
    for(int j=0;j<m(1,0).fila();++j){ //calculo fuerza total sobre el anillo y la mando al archivo
      f_anix+=m(4,i*20)(j,0);
      f_aniy+=m(4,i*20)(j,1);
      }
    archivo<<f_anix<<' '<<f_aniy<<endl;//Cambio de linea y vamos al siguiente "trozo"
    f_anix=0;f_aniy=0;
  }
  archivo.close();//cierro el archivo

} 
