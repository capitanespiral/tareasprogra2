#include "poli.h"
#include <iostream>
#include <cmath>

using namespace std;

//Defino el producto interno
template <class T>
T prod_interno(const poli<T> &p,const poli<T> &q){
  poli<T> r=p*q;
  T a=r.integ(-1,1);
  return a;
}

//Defino la proyeccion de q sobre p
template <class T>
poli<T> proy(const poli<T> &p,const poli<T> &q){
  T num=prod_interno(p,q);
  T den=prod_interno(p,p);
  poli<T> r(p);
  return r*(num/den);
}


int main(){
  double c; //para normalizar
  //Construyo los dos primeros (entregados por usté)
  vector<double> v={1};
  poli<double> p0(0,v);
  poli<double> p1(1,v);
  //Contenedor de todos los que consiga
  vector<poli<double>> w= {p0,p1};
  cout<<"Los polinomios de Legendre encontrados son:\n"<<endl;
  //Ciclo que los crea
  for(int i=2;i<=20;++i){
    //Polinomio de grado i
    poli<double> p_i(i,v);
    //polinomio donde acumulo lo necesario para el algoritmo
    poli<double> acum;
    for(int j=0;j<w.size();++j){
      //Acumulo lo necesario para gram-schmidt(segun todos los polinomios ya guardados)
      acum=acum+proy(w[j],p_i);
    }
    //Lo resto al que esta por nacer
    p_i=p_i-acum;
    //normalizo segun la condicion de la norma al cuadrado (ergo, el prod. interno)
    c=(2.0/(2*i+1))/prod_interno(p_i,p_i);
    p_i=p_i*sqrt(c);
    //Lo almaceno, lo imprimo y vamos de nuevo.
    w.push_back(p_i);
    cout<<p_i<<endl;
  }
  //Los polinomios de legendre segun mathematica, los almaceno en otro vector (reciclo v)
  vector<poli<double>> p={p0,p1};
  v={3,0,-1};poli<double> p2(2,v);p2=p2/2.0;
  p.push_back(p2);
  v={5,0,-3,0};poli<double> p3(3,v);p3=p3/2.0;
  p.push_back(p3);
  v={35,0,-30,0,3};poli<double> p4(4,v);p4=p4/8.0;
  p.push_back(p4);
  v={63,0,-70,0,15,0};poli<double> p5(5,v);p5=p5/8.0;
  p.push_back(p5);
  v={231,0,-315,0,105,0,-5};poli<double> p6(6,v);p6=p6/16.0;
  p.push_back(p6);
  v={429,0,-693,0,315,0,-35,0};poli<double> p7(7,v);p7=p7/16.0;
  p.push_back(p7);
  v={6435,0,-12012,0,6930,0,-1260,0,35};poli<double> p8(8,v);p8=p8/128.0;
  p.push_back(p8);
  v={12155,0,-25740,0,18018,0,-4620,0,315,0};poli<double> p9(9,v);p9=p9/128.0;
  p.push_back(p9);
  v={46189,0,-109395,0,90090,0,-30030,0,3465,0,-63};poli<double> p10(10,v);p10=p10/256.0;
  p.push_back(p10);
  v={88179,0,-230945,0,218790,0,-90090,0,15015,0,-693,0};poli<double> p11(11,v);p11=p11/256.0;
  p.push_back(p11);
  v={676039,0,-1939938,0,2078505,0,-1021020,0,225225,0,-18018,0,231};poli<double> p12(12,v);p12=p12/1024.0;
  p.push_back(p12);
  v={1300075,0,-4056234,0,4849845,0,-2771340,0,765765,0,-90090,0,3003,0};poli<double> p13(13,v);p13=p13/1024.0;
  p.push_back(p13);
  v={5014575,0,-16900975,0,22309287,0,-14549535,0,4849845,0,-765765,0,45045,0,-429};poli<double> p14(14,v);p14=p14/2048.0;
  p.push_back(p14);
  v={9694845,0,-35102025,0,50702925,0,-37182145,0,14549535,0,-2909907,0,255255,0,-6435,0};poli<double> p15(15,v);p15=p15/2048.0;
  p.push_back(p15);
  v={300540195,0,-1163381400,0,1825305300,0,-1487285800,0,669278610,0,-162954792,0,19399380,0,-875160,0,6435};poli<double> p16(16,v);p16=p16/32768.0;
  p.push_back(p16);
  v={583401555,0,-2404321560,0,4071834900,0,-3650610600,0,1859107250,0,-535422888,0,81477396,0,-5542680,0,109395,0};poli<double> p17(17,v);p17=p17/32768.0;
  p.push_back(p17);
  v={2268783825,0,-9917826435,0,18032411700,0,-17644617900,0,10039179150,0,-3346393050,0,624660036,0,-58198140,0,2078505,0,-12155};poli<double> p18(18,v);p18=p18/65536.0;
  p.push_back(p18);
  v={4418157975,0,-20419054425,0,39671305740,0,-42075627300,0,26466926850,0,-10039179150,0,2230928700,0,-267711444,0,14549535,0,-230945,0};poli<double> p19(19,v);p19=p19/65536.0;
  p.push_back(p19);
  v={34461632205,0,-167890003050,0,347123925225,0,-396713057400,0,273491577450,0,-116454478140,0,30117537450,0,-4461857400,0,334639305,0,-9699690,0,46189};poli<double> p20(20,v);p20=p20/262144.0;
  p.push_back(p20);
  //Imprimo el error (uno menos el otro al cuadrado y su integral entre -1 y 1)
  cout<<"\n\nY sus errores con los originales son respectivamente:\n"<<endl;
  for(int i=0;i<=20;++i)
    cout<<((p[i]-w[i])*(p[i]-w[i])).integ(-1,1)<<endl;
  return 0;
}
