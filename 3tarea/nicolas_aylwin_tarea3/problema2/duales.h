#include <iostream>
#include <cmath>
#include <iomanip>
#include <complex>
using namespace std;

class dual //Ahora existe, puede no hacer nada pero ya es reconocido
{
private:
	double r,e;

public:
	dual(); //constructor por defecto es como int a
	dual(double,double=1); //=1 para que derive por defecto,constructor mas bacan (generico) es como int a=1
	~dual();//destructor (esta por default, ahora no hace nada)
	dual(const dual&); //constructor de copia, shallow copy
	dual & operator=(const dual&);//deep copy
	dual operator()(int); 
	double operator[](int) const; //consistencia con como defini el const  double operator()(int,int,int..) const;
	double & operator[](int);	//Tarea, sobrecargar ()  double operator()(int, int , int..) const;
	//ostream & operator<<(ostream &os, const dual &); //objeto tipo outputstream, defini el operador (puedo el que quiera) (mejor solo sobrecargar)
}; //Termina en punto y coma


ostream & operator<<(ostream &os,const dual &d);

dual operator+(const dual &x,const dual &y);

dual operator-(const dual &x,const dual &y);

dual operator*(const dual &x,const dual &y);

dual sin(const dual&d);

dual sinh(const dual&d);

dual cos(const dual&d);

dual cosh(const dual&d);

dual log(const dual&d);

dual exp(const dual&d);