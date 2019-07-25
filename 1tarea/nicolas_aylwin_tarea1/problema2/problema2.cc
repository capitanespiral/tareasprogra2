#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <iomanip>
using namespace std;

//Fijo la gravedad como variable global
int g=10;

//Entrega vector con ambos vectores unitarios del plano inclinado (respecto a unitarios clasicos, i y j)
vector<vector<double>> ref_pl_incl(double x) 
{
	double alfa,i,j; //i,j vectores unitarios clasicos
	alfa=-atan(cos(x));//Obtengo angulo de inclinacion del plano (recta tangente al punto en x donde impacta la pelota)
	if(abs(alfa)<1e-15) //Si es muy cercano a cero (algun valor), digo que sea cero
	{
		alfa=0;
	}
	if(abs(cos(alfa))<1e-15) 
	{
		i=0;
	}
	else
	{
		i=cos(alfa);
	}
	if(abs(sin(alfa))<1e-15)
	{
		j=0;
	}
	else
	{
		j=sin(alfa);
	}
	//Asigno los valores a mis vectores
	vector<double> x_pl(2);x_pl[0]=i;x_pl[1]=-j;//vector tangente al plano (cos(x),-sen(x))
	vector<double> y_pl(2);y_pl[0]=-j;y_pl[1]=-i;//vector perpendicular al plano (-sen(x),-cos(x))
	vector<vector<double>> ref_incl(2);ref_incl[0]=x_pl;ref_incl[1]=y_pl; //Almaceno ambos vectores en un vector
	return ref_incl;
}

//Entrega la proyeccion de v_1 sobre v_2 con direccion en v_2 (producto punto direccionado)
vector<double> prod_punto_dir(vector<double> v_1, vector<double> v_2) 
{
	double a=(v_1[0]*v_2[0]+v_1[1]*v_2[1])/(v_2[0]*v_2[0]+v_2[1]*v_2[1]);
	vector<double> v(2);v={a*v_2[0],a*v_2[1]};
	return v;
}

//Devuelve posicion en x de la pelota (usado para newton-raphson)
double pos(double x_i,vector<double> v,double x_n)
{
	return sin(x_i)-sin(x_n)+(v[1]/v[0])*(x_n-x_i)-(::g/2)*(((x_n-x_i)*(x_n-x_i))/(v[0]*v[0]));
}

//Derivada de la funcion anterior (claramente para newton-raphson)
double pos_der(double x_i,vector<double> v,double x_n)
{
	return (v[1]/v[0])-(::g/(v[0]*v[0]))*(x_n-x_i)-cos(x_n);
}

//Metodo de newton-raphson que entrega valor aproximado de la posicion de la pelota en x.
double newton_raphson(double x_i,vector<double> v,int semilla)
{
	double x_n=1;
	double x_n1=semilla;
	while(abs(x_n-x_n1)>1e-14)
	{
		x_n=x_n1;
		x_n1=x_n-(pos(x_i,v,x_n)/pos_der(x_i,v,x_n));
	}
	return x_n1;
}

//Donde todo sucede
int main()
{
	//Creo y almaceno la posicion inicial
	double x_0,y_0;
	x_0=3;y_0=10;
	//Comento los datos iniciales y lugar de primer rebote
	cout<<"\nCon una grevadad de "<<::g<<" y un punto inicial ("<<x_0<<","<<y_0<<")\n";
	cout<<"Cae inicialmente en el punto ("<<x_0<<","<<sin(x_0)<<")\n";
	//Almaceno la rapidez (obtenida por la diferencia de energia), asi compongo la velocidad (respecto i,j) justo antes de chocar
	double rap_1=sqrt(2*::g*(y_0-sin(x_0)));
	vector<double> vel_1(2);vel_1={0,-rap_1}; 
	//Le muestro esta velocidad al usuario
	cout<<"En el que choca con una velocidad ("<<vel_1[0]<<","<<vel_1[1]<<")\n";
	//Obtengo los vectores unitarios del plano inclinado en x_0 (x inicial=x primer rebote)
	vector<vector<double>> ref_incl(2);ref_incl=ref_pl_incl(x_0);
	//Cambio al sist de referencia del plano inclinado, X tangente al plano e Y perpendicular.
	vector<double> v_1X(2);v_1X=prod_punto_dir(vel_1,ref_incl[0]);
	vector<double> v_1Y(2);v_1Y=prod_punto_dir(vel_1,ref_incl[1]);
	//Por conservacion de la energia y momentum se preserva la componente tangencial y la perpendicular se invierte.
	//Asi compongo la velocidad con que sale despedida del primer rebote pero respecto a i y j.
	vector<double> v_2(2);v_2={v_1X[0]-v_1Y[0],v_1X[1]-v_1Y[1]};
	//Muestro esta velocidad
	cout<<"Y sale despedida del primer rebote con una velocidad ("<<v_2[0]<<","<<v_2[1]<<")\n";

	//Creo una variable para almacenar el resultado de newton-raphson (x del segundo rebote).
	double x_1;
	//La semilla se escoge segun la unica raiz con sentido dentro del problema
	x_1=newton_raphson(x_0,v_2,9);
	//Muestro la posicion del segundo rebote
	cout<<"Con lo que el segundo rebote resulta en el punto ("<<x_1<<","<<sin(x_1)<<")\n";
	//Obtengo y almaceno la velocidad con que llega al segundo rebote (cinematica basica)
	vector<double> vel_3(2);vel_3={v_2[0],v_2[1]-(::g*(x_1-x_0))/v_2[0]};
	//Informo de esta velocidad al usuario
	cout<<"Al cual llega con una velocidad ("<<vel_3[0]<<","<<vel_3[1]<<")\n";

	//Ahora repetimos el proceso
	//Obtengo los vectores unitarios del plano inclinado en x_1 (x segundo rebote)
	ref_incl=ref_pl_incl(x_1);
	//Cambio al sist de referencia del plano inclinado, X tangente al plano e Y perpendicular.
	vector<double> v_3X(2);v_3X=prod_punto_dir(vel_3,ref_incl[0]);
	vector<double> v_3Y(2);v_3Y=prod_punto_dir(vel_3,ref_incl[1]);
	//Por el mismo argumento de conservacion, compongo la velocidad con que sale despedida la pelota del segundo rebote (respecto a i y j)
	vector<double> v_3(2);v_3={v_3X[0]-v_3Y[0],v_3X[1]-v_3Y[1]};
	//Informo de esta velocidad
	cout<<"Y sale despedida con una velocidad ("<<v_3[0]<<","<<v_3[1]<<")\n";

	//Creo una variable para almacenar el resultado de newton-raphson (x del tercer rebote).
	double x_2;
	//La semilla (nuevamente) se escoge segun la unica raiz con sentido dentro del problema
	x_2=newton_raphson(x_1,v_3,2);
	//Entrego la posicion del tercer rebote, y fin.
	cout<<"\n\033[1;4mY así el tercer y último rebote ocurre en el punto ("<<x_2<<","<<sin(x_2)<<")\033[m \n";
	//PD: Me refiero a ultimo rebote pues es el ultimo pedido a calcular, claramente sigue rebotando.
	return 0;
}

