#include "interpol.h"
#include <iostream>
#include <fstream>
using namespace std;
 
int main(int argc, char* argv[]){
	vector<double> v;
	double x;
	ifstream archivo(argv[1]);
	while(archivo>>x) v.push_back(x);
	matriz<double> m(v,2);
	i_pol interpolador(m);
	matriz<poli<double>> h=interpolador.spline('p');
	matriz<double> res=puntos(h,interpolador,atoi(argv[2]));
	file("spline_periodico",res);
	return 0;
}
