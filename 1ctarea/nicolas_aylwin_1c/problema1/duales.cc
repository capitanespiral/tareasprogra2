#include "duales.h"

//constructor por defecto
dual::dual():r(0),e(1)
{
}

//constructor asignando direcdtamente valores
dual::dual(double x, double y):r(x),e(y)
{	
}

//destructor (por completitud)
dual::~dual(){
}

//shallow copy
dual::dual(const dual &d){
	r=d.r;
	e=d.e;
}

//deep copy
dual &dual:: operator=(const dual &d){
	if(this!=&d) //nos aseguramos de que no se copie consigo mismo
	{
		r=d.r;
		e=d.e;
	}
	return *this;
}

//sobrecarga para leer r y e
double dual::operator[](int i) const 
{
	switch(i){
		case 0:
			return r;break;
		case 1:
			return e;break;
		default:
			cout<<"elemento no definido :c\n";
	}
}

//sobrecarga para reasignar r y e (se exponen por referencia)
double & dual::operator[](int i) {
	switch(i){
		case 0:
			return r;break;
		case 1:
			return e;break;
		default:
			cout<<"elemento no definido :c\n";
	}
}

//Este y el siguiente equivalente a los dos anteriores
double dual::operator()(int i) const //todo dentro del siguiente scope sera solo mirado, nunca modificado 
{
	switch(i){
		case 0:
			return r;break;
		case 1:
			return e;break;
		default:
			cout<<"elemento no definido :c\n";
	}
}

double& dual::operator()(int i) {
	switch(i){
		case 0:
			return r;break;
		case 1:
			return e;break;
		default:
			cout<<"elemento no definido :c\n";
	}
}

//sobrecarga de << para poder imprimir los duales
ostream & operator<<(ostream &os,const dual &d)
{
	os<<"{"<<d[0]<<" , "<<d[1]<<"}";
}

//definimos la suma entre duales
dual operator+(const dual &x,const dual &y){
	return dual(x[0]+y[0],x[1]+y[1]);
}

//definimos la resta entre duales
dual operator-(const dual &x,const dual &y){
	return dual(x[0]-y[0],x[1]-y[1]);
}

//definimos la multiplicacion (aqui empieza la magia de los duales)
dual operator*(const dual &x,const dual &y){
	return dual(x[0]*y[0],x[1]*y[0]+x[0]*y[1]);
}

//definimos el seno de un dual, para esta y todas las funciones se entrega el dual constante por miedo a que cambie
dual sin(const dual&d){
	return dual(sin(d[0]),cos(d[0])*d[1]);
}

//seno hiperbolico
dual sinh(const dual&d){
	return dual(sinh(d[0]),cosh(d[0])*d[1]);
}

//coseno
dual cos(const dual&d){
	return dual(cos(d[0]),-sin(d[0])*d[1]);
}

//coseno hiperbolico
dual cosh(const dual&d){
	return dual(cosh(d[0]),sinh(d[0])*d[1]);
}

//logaritmo
dual log(const dual&d){
	return dual(log(d[0]),d[1]/d[0]);
}


