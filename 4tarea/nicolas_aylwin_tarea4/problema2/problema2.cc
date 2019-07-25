#include "matriz.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;

//Funcion para aplicar un modulo selectivo (así imponer periodicidad)
int mod(int i,int m){//Dado esto funciona solo para matrices cuadradas (periodicidad fija pero facilmente adaptable)
  if(i<m && i>=0) return i; //Caso regular
  else if(i>=m) return i%m; //si supera a m
  else if(i<m) return m+i; //si es neg
}

//Funcion que avanza de generacion, recibe la matriz del estado anterior, dos valores para sobrevivir y dos para nacer
matriz<int> next_gen(const matriz<int> &m,int s1,int s2,int n1,int n2){
  //3 int importantes para mirar a los vecinos y copio la matriz entregada
  int I;int J;int acum=0;
  matriz<int> res(m);
  //Los dos primeros for solo se encargan de recorrer cada elemento
  for(int i=0;i<m.fila();++i){
    for(int j=0;j<m.colu();++j){
      //Este observa a los vecinos, usando la funcion mod
      for(int k=0;k<=2;++k){
	I=i-1;I=mod(I,m.fila()); //fila de arriba
	J=j-1+k;J=mod(J,m.fila());//columna de toda fila de arriba
	acum+=m(I,J); //Suma fila de arriba
	I=i+1;I=mod(I,m.fila()); //fila de abajo
	acum+=m(I,J); //Suma fila de abajo
	if(k==0) acum+=m(i,J);//lado izq
	if(k==2) acum+=m(i,J);//lado derecho
      }
      //Veo si es necesario cambiar algo segun las reglas, de no ser así lo dejo tal cual (pues res es copia de la original)
      if(m(i,j)==0){
	if(acum==n1 || acum==n2) res(i,j)=1;}
      else {
	if(acum!=s1 && acum!=s2) res(i,j)=0;
      }
      //Reinicio acum
      acum=0;
    }
  }
  //Devuelvo matriz resultante
  return res;
}

//Empieza el programa!
int main (int argc, char* argv[]){
  //Recibo la matriz como archivo de main
  ifstream archivo(argv[1]);
  //Guardo los valores del archivo en un vector
  vector<int> v;
  int x;
  while(archivo>>x){
    v.push_back(x);
  }
  archivo.close();
  //Creo la matriz a partir de este vector, y la carpeta donde guardare los resultados
  matriz<int> ini(32,v);
  system ("mkdir juego_de_la_vida");
  //Ciclo que avanza las 700 generaciones
  for(int i=0;i<=700;++i){
    //Fijo el nombre de cada archivo, procuro que un 'ls' los llame en orden
    string s;
    if(i<=9) s="Gen00"+to_string(i)+".dat";
    else if(i<=99) s="Gen0"+to_string(i)+".dat";
    else s="Gen"+to_string(i)+".dat";
    //Creo el archivo en si
    ofstream archivote("./juego_de_la_vida/"+s);
    //Guardo estado anterior, cierro el archivo y avanzo de generacion
    archivote<<ini<<endl;
    archivote.close();
    ini=next_gen(ini,2,3,3,6);
  }
  return 0;


}
