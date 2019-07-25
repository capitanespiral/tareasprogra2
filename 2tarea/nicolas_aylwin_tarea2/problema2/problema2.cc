#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

//Defino las 3 constantes a usar
double const gammma=0.577215664;
double const e=2.718281828;
//El (1+raiz(5))/2 es el numero aureo phi
double const phi=1.618033988;

//Creo una funcion que me entrega la fila de una matriz (será usada al definir la multiplicacion de matrices)
vector<double> fila(vector<vector<double>> v,int i){
	vector<double> filita;
	for(int j=0;j<v[0].size();++j){
		filita.push_back(v[i][j]);
	}
	return filita;
}

//Lo mismo pero para columna
vector<double> columna(vector<vector<double>> v,int i){
	vector<double> columnita;
	for(int j=0;j<v.size();++j){
		columnita.push_back(v[j][i]);
	}
	return columnita;
}


//Defino el producto punto entre dos vectores (se usará para la multiplicación entre matrices)
double operator*(vector<double> a,vector<double> b){
	double res=0;
	for(int i=0;i<a.size();++i)
		res+=a[i]*b[i];
	return res;
}

//Defino la multiplicacion entre matrices
vector<vector<double>> operator*(vector<vector<double>> a,vector<vector<double>> b){
	//Primero creo una matriz del tamaño resultante llena de ceros
	vector<vector<double>> res;
	for(int i=0;i<a.size();++i){
		vector<double> v(b[0].size());
		res.push_back(v);
	}
	//Almaceno los resultados en cada espacio usando las funciones descritas arriba.
	for(int i=0;i<a.size();++i){
		for(int j=0;j<b[0].size();++j){
			res[i][j]=(fila(a,i)*columna(b,j));
		}
	}
	//devuelvo la matriz resultante
	return res;
}

//Defino la "impresión" de una matriz
ostream& operator<<(ostream&os,vector<vector<double>> a)
{
	os<<"(";
	for(int i=0;i<a.size();++i)
	{
		for(int j=0;j<a[0].size();++j){
			if(i==0)
				os<<a[i][j]<<" ";
			else
				os<<" "<<a[i][j];
		}	
		if(i+1==a.size())
			os<<")";
		else
			os<<"\n";
	}
	return os;
}
//Defino la matriz que rota el angulo psi
vector<vector<double>> rot_psi(double psi){
	vector<vector<double>> v={{cos(psi),sin(psi),0},{-sin(psi),cos(psi),0},{0,0,1}};
	return v;
}

//Lo mismo para tetha
vector<vector<double>> rot_tetha(double tetha){
	vector<vector<double>> v={{1,0,0},{0,cos(tetha),sin(tetha)},{0,-sin(tetha),cos(tetha)}};
	return v;
}

//Lo mismo para phi (se que es igual a la de psi, pero soy obsesivo)
vector<vector<double>> rot_phi(double phi){
	vector<vector<double>> v={{cos(phi),sin(phi),0},{-sin(phi),cos(phi),0},{0,0,1}};
	return v;
}

//A correr el programa!
int main(){
	//Creo el vector especificado (como una matriz, pues un vector al fin y al cabo es una matriz)
	vector<vector<double>> v={{-2.7254},{4.18527},{-0.2361}};
	//Expongo el vector inicial
	cout<<"El vector inicial es \n"<<v<<endl;
	//Lo roto en phi y expongo el resultado
	cout<<"Rotado con phi resulta \n"<<rot_phi(::gammma)*v<<endl;
	//Lo mismo con tetha
	cout<<"Luego con tetha \n"<<rot_tetha(::phi)*(rot_phi(::gammma)*v)<<endl;
	//Guardo en una variable la rotacion con psi (rotacion final)
	vector<vector<double>> v_rot=rot_psi(::e)*(rot_tetha(::phi)*(rot_phi(::gammma)*v));
	//Muestro el resultado final
	cout<<"Finalmente con psi\n"<<v_rot<<endl;
    //Realizo la rotación inversa y expongo el vector con que partimos.
	cout<<"\n"<<"Y rotando este ultimo a la inversa volvemos a \n"<<rot_phi(-::gammma)*(rot_tetha(-::phi)*(rot_psi(-::e)*v_rot))<<endl;
	//Fin!
	return 0;
}