#include <iostream>
#include <complex>
#include <fstream>
#include <string>

using namespace std;

//Creo la unica funcion externa a main. Esta realiza la iteracion descrita en la tarea
//Recibe un complejo constante (por miedo a modificarlo) y por referencia (para aumentar la velocidad de computo)
//Ademas el m al cual elevar, y devuelve un entero dependiendo de si convergio o no
int itera(const complex<double> &c,int m){
	//Creo dos complejos para le iteracion y un contador
	complex<double> zn,zn1;
	zn={0,0};
	int cont=0;
	//Hago la iteracion mientras el valor absoluto de zn sea menor o igual a dos
	while(abs(zn)<2){
		//Evaluo la potencia
		zn=pow(zn,m);
		//creo zn1 y lo asigno a zn
		zn1=zn+c;
		zn=zn1;
		//Aumento el contador
		cont+=1;
		//Si el contador llega a 100 sin romper la condicion del while asumo que convergio
		if(cont==100)
			return 0;
	}
	return 1;
}

//Comienzo del programa
int main(){
	//Pido y recibo el m
	cout<<"Ingrese su m: ";
	//Creo ademas algo que evalue la convergencia (res) y un complejo
	int m,res;cin>>m;
	complex<double> c;
	//Creo el archivo en funcion de m donde se guardaran los resultados
	string M = to_string(m);
	ofstream no_divergen ("no_divergen_"+M+".txt");
	//Hago dos for para iterar en toda la grilla solicitada
	for(int j=0;j<=10000;++j){
		for(int i=0;i<=10000;++i){
			//Creo el complejo, lo imprimo (para tener nocion de que el programa corre, claramente se demora)
			c={-2+4*(float(i)/10000),-2+4*(float(j)/10000)};
			cout<<c<<endl;
			//Lo evaluo y de converger mando el valor real y el imaginario al archivo
			res=itera(c,m);
			if(res==0)
				no_divergen<<real(c)<<" "<<imag(c)<<endl;
		}
	}
	return 0;
}