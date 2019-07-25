#include "duales.h"

dual::dual():r(0),e(1)
{
}

dual::dual(double x, double y):r(x),e(y)
{	
}

dual::~dual(){
}

dual::dual(const dual &d){
	r=d.r;
	e=d.e;
}

dual &dual:: operator=(const dual &d){
	if(this!=&d) //this es puntero especial que apunta a la izq
	{
		r=d.r;
		e=d.e;
	}
	return *this;
}

double dual::operator[](int i) const //todo dentro del siguiente scope sera solo mirado, nunca modificado 
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

dual dual::operator()(int j) {
	if(j==0 || j==-0){
		dual d(1,0);
		return d;
	}
	if(j>0){
	dual d(r,e);
	dual res(r,e);
		for(int i=1;i<j;++i)
			res=res*d;
			return res;
		}
	if(j<0 && r!=0){
		dual d(1/r,-e/(r*r));
		dual res(1/r,-e/(r*r));
		for(int i=-1;i>j;--i)
			res=res*d;
			return res;
		
	}


}

ostream & operator<<(ostream &os,const dual &d)
{
	os<<"{"<<d[0]<<" , "<<d[1]<<"}";
}

dual operator+(const dual &x,const dual &y){
	return dual(x[0]+y[0],x[1]+y[1]);
}

dual operator-(const dual &x,const dual &y){
	return dual(x[0]-y[0],x[1]-y[1]);
}

dual operator*(const dual &x,const dual &y){
	return dual(x[0]*y[0],x[1]*y[0]+x[0]*y[1]); //Esto define la gracia de los duales
}

//sin(x+e)=sinx + cos(x)e  = (sinx,cosx*1) -> escrito en dual, ver bien porqueeee el uno por cadena, osea la derivada de x
//Mandar solucion general y problema agregado en loque mando el toledo (cual es la condicion que puso toledo? segun simetria del sistema)
dual sin(const dual&d){
	return dual(sin(d[0]),cos(d[0])*d[1]);
}

dual sinh(const dual&d){
	return dual(sinh(d[0]),cosh(d[0])*d[1]);
}

dual cos(const dual&d){
	return dual(cos(d[0]),-sin(d[0])*d[1]);
}

dual cosh(const dual&d){
	return dual(cosh(d[0]),sinh(d[0])*d[1]);
}

dual log(const dual&d){//Devolvemos constructor
	return dual(log(d[0]),d[1]/d[0]);
}

dual exp(const dual&d){
	return dual(exp(d[0]),exp(d[0])*d[1]);
}

