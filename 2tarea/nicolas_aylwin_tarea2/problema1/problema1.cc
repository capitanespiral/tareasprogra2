#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

//funcion que realiza la iteracion para obtener las funciones de bessel (segun algoritmo de miller)
//Recibe el x donde se evalua J y el n correspondiente a la funcion que busco (Jn)
//Opcionalmente, desde donde partir (N)
double iter_bessel_dec(double x,int n,int N=-1){
	//Variable donde se almacenara el valor final
	double Jn;
	//Establezco condicion si x=0
	if(x==0){
		if(n==0)
			Jn=1;
		else
			Jn=0;
	}
	//De no ser ese el caso, itero
	else{
		//Primero fijo desde donde partir, de no indicarse N, este entra negativo y se autoasigna
		//De ser menor que 20 se ajusta a 20
		if(N<0)
			N=n+int(sqrt(10*n)+1);
		if(N<20)
			N=20;
		//Asigno los valores iniciales Ji_1=J_(i+1) y Ji_2=J_(i+2)
		double Ji_1=1;double Ji_2=1;
		//Creo la variable donde se guarda el valor de cada iteracion
		double Ji;
		//sum como resultado de la seria para normalizar, parte en uno pues contiene a Ji_1 o Ji_2 iniciales.
		double sum=1;
		//Realizo la iteracion desde N hasta cero, guardando en sum el valor de J_0 y 2*Jn con n par distinto de cero
		for(int i=N;i>=0;--i){
			Ji=(2*(i+1)/x)*Ji_1-Ji_2;
			Ji_2=Ji_1;
			if(i%2==0){
				if(i==0)
					sum+=Ji;
				else
					sum+=2*Ji;
			}
			//Al encontrar el n que busco lo almaceno
			if(i==n){
				Jn=Ji;
			}
			Ji_1=Ji;
		}
		//Finalmente divido el Jn que tenia por la suma (aqui normalizamos)
		Jn/=sum;
	}
	//Devuelvo tal valor como la evaluacion de Jn en el x (funcion de bessel)
	return Jn;
}

//Todas las funciones Jn con n entero desde 0 hasta M, evaluadas para un x en especifico
vector<double> Jn_s(double x, int M,int N=-1){
	vector<double> v;
	for(int i=0;i<=M;++i)
		v.push_back(iter_bessel_dec(x,i,N));
	return v;
}

//Funcion que separa los Jn pares de los impares (recibe lo entregado por la funcion anterior)
//0 da los pares, 1 da los impares
vector<double> par_impar(vector<double> v,int i=0){
	vector<double> w;
	for(int j=0;j<v.size();j+=2)
		if(j+i<v.size())
			w.push_back(v[j+i]);
	return w;
}

//La funcion f descrita en la tarea, recibe el vector que contiene los Jn pares
double f(vector<double> v){
	double res=0;
	int m=1;
	for(int i=0;i<v.size();++i){
		if(i==0)
			res+=v[i];
		else 
			res+=2*v[i]*m;
		m=-m;
	}
	return res;
}

//La funcion g descrita en la tarea, recibe el vector que contiene los Jn impares
double g(vector<double> v){
	double res=0;
	int m=1;
	for(int i=0;i<v.size();++i){
		res+=2*v[i]*m;
		m=-m;
	}
	return res;
}

//Comienzo del programa
int main(){
	//Creo dos archivos donde almacenar los datos
	ofstream grafico_f ("grafico_f.dat");
	ofstream grafico_g ("grafico_g.dat");
	//Un vector para guardar los J
	vector<double> v;
	//Variable para guardar el valor resultanto de f y g
	double y;
	//Itero desde 0 hasta 2pi subiendo 2pi/100 a cada paso (osea pi/50)
	for(double i=0;i<=2*M_PI;i+=M_PI/50){
		//Almaceno todas las Jn evaluadas en i con n entero desde 0 hasta 70.
		//Intente usar 100 pero algunas se iban a cero y en las siguientes iteraciones presentaba "nan", aqui funcionan todas en este rango de x 
		v=Jn_s(i,70);
		//Evaluo f entregandole los Jn pares
		y=f(par_impar(v));
		//Guardo x y f(x) en el grafico_f
		grafico_f<<i<<" "<<y<<endl;
		//Evaluo g entregandole los Jn impares
		y=g(par_impar(v,1));
		//Guardo x y g(x) en el grafico_g
		grafico_g<<i<<" "<<y<<endl;
	}
	//Cierro ambos graficos
	grafico_f.close();
	grafico_g.close();
	//Doy un msje de desarrollo exitoso!
	cout<<"Se han creado exitosamente \"grafico_f.dat\" y \"grafico_g.dat\""<<endl;
	return 0;
}