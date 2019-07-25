#include "duales.h"
using namespace std;

//programa a modo de ejemplo de la clase de duales
int main()
{
	cout<<"Creamos un dual cualquiera, sea este {5,1}"<<endl;
	dual x(5,1);
	cout<<x<<endl;
	cout<<"Primero probamos que [] y () funcionen de la misma forma"<<endl;
	cout<<"Con [], primero solo leyendo y luego asignando, probemos cambiar la parte real por 2"<<endl;
	cout<<"La parte real es "<<x[0]<<endl;
	x[0]=2;
	cout<<"Cambiandola el dual queda "<<x<<endl;
	cout<<"Ahora intentando con ()"<<endl;
	cout<<"Leamos el valor de la parte dual"<<endl;
	cout<<x(1)<<endl;
	cout<<"Ahora cambiemos este por -3, e imprimamos el dual"<<endl;
	x(1)=-3;
	cout<<x<<endl;
	cout<<"Volvamos la parte dual 1 para poder derivar ahora"<<endl;
	x(1)=1;
	cout<<x<<endl;
	cout<<"Derivemos ahora cosh(log(sin(x)))*sinh(x*x*x) con x=2"<<endl;
	cout<<"El valor numerico entregado por Wolfram es aproximadamente: 18031.6181244"<<endl;
 	dual d=cosh(log(sin(x)))*sinh(x*x*x);
	cout<<d<<endl;
	cout<<"Aumentando la precision para la parte dual tenemos:"<<endl;
	cout<<setprecision(10)<<d(1)<<endl;
	cout<<"Podemos notar claramente, que funciona muy bien"<<endl;
	return 0;
}
//Para compilar algo_main.exe algo_main.cc algo.cc

//Sobrecargar todo cmath!!
//Definir para tarea, derivadas parciales -> duales con dos grados de libertad (ver fotito)
//Mandar correo prueba 12 de abril (viernes) -> bloque azul (hacer todo el codigo esta vez) Parte azul (en el programa  -> HACER OBJETOS DUALES, NOS VAN A PREGUNTAR. DERIVAR COSAS CERDAS Y ESO)
