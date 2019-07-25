//Incluyo los duales creados en clases, fstream y string.
#include "duales.h"
#include <fstream>
#include <string>

//Funcion que calcula el potencial, recibe un dual, el n y L. Entrega dual claramente
dual potencial(dual x, double n, double L){
	//Creo un doble correspondiente a la constante que acompaña a x en cada caso
	double c=(2*M_PI*n)/L;
	//Multiplico ambas partes del dual por c (cambio de variable)
	x[0]*=c;
	x[1]*=c;
	//Creo el dual resultado de evaluar la funcion (el potencial), y lo devuelvo.
	dual res=x*cosh(x)*cosh(x)*cosh(x)*cos(x)*cos(x)*sinh(x)*sinh(x)*sinh(x)*sinh(x)*sin(x)*exp(x);
	if(abs((2*x[0]/M_PI)/int(2*x[0]/M_PI)-1)<1e-15){//Esta condicion transforma en cero el potencial si es que se usa un multiplo de pi/2 (son cero por sin y cos^2) sinh también se hace cero, pero en cero que ya está contabilizado.
		res[0]=0;
		}
	return res;
	}


//Comienzo del programa
int main(){
	//Crea dos dobles y el dual
	double L,n; dual x;
	//Pido los valores
	cout<<"Ingrese su n: ";cin>>n;
	cout<<"Ahora su L: ";cin>>L;
	//Transformo a string la parte entera de n para asignarlo al nombre de los archivos
	string s=to_string(int(n));
	//Creo el nombre y los archivos en si (uno almacena los x junto al potencial evaluado y otro los x junto a la derivada del potencial evaluada)
	string archivito="Potencial_"+s+".dat";
	string archivote="Potencial_"+s+"_.dat";
	ofstream archivo(archivito);
	ofstream archivo_(archivote);
	//Realizo la iteracion con la parte real de x entre -L/2 y L/2
	//Use 10000 en vez de mil porque los graficos se ven mas lindos (que no son necesarios pero use para corroborar que me daban bien las funciones)
	for(int i=0;i<=10000;++i){
		x={(-L/2)+(i*L)/10000,1};
		archivo<<x[0]<<" "<<potencial(x,n,L)[0]<<endl;
		archivo_<<x[0]<<" "<<potencial(x,n,L)[1]<<endl;
	}
	//Pequeño mensaje de exito
	cout<<"El archivo "+archivito+" ha sido creado, con el potencial evaluado."<<endl;
	cout<<"También se creó "+archivote+" con la derivada evaluada del mismo."<<endl;
	//Fin!
	return 0;
}