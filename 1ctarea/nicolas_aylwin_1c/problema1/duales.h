#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
//archivo header
//Definimos la clase de los duales
class dual 
{
private:
	double r,e;

public:
	dual(); //constructor por defecto 
	dual(double,double=1); //constructor asignando valores, definimos por defecto la parte dual igual a 1 para que "derive" sin escalar por alguna constante
	~dual();//destructor (solo por completitud)
	dual(const dual&); //constructor de copia, shallow copy
	dual & operator=(const dual&);//deep copy 
	double operator[](int) const; //sobrecarga de [] para leer r o e (constante por miedo a que cambie)
	double & operator[](int);	//sobrecarga de [] para escribir r o e (por referencia pues buscamos cambiar efectivamente los miembros privados del dual)
	double operator()(int) const; //Este y el siguiente identicos a los anteriores
	double & operator()(int);	
}; 

//declaramos las funciones a usar.
ostream & operator<<(ostream &os,const dual &d);

dual operator+(const dual &x,const dual &y);

dual operator-(const dual &x,const dual &y);

dual operator*(const dual &x,const dual &y);

dual sin(const dual&d);

dual sinh(const dual&d);

dual cos(const dual&d);

dual cosh(const dual&d);

dual log(const dual&d);
