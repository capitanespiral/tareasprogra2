#ifndef POLI_
#define POLI_

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;


//Clase de template de polinomios
template <class T>
class poli{
  //grado y coeficientes como miembros privados
 private:
  int grado;
  vector<T> coef;
			
 public:
  //Los no obvios de aca se explicaran en su implementacion
  poli();
  poli(int, vector<T>);
  poli(int,T=0,T=1);
  poli(const poli&);
  poli& operator=(const poli&);
  T operator[](int) const;
  T& operator[](int);
  int grad() const;
  poli operator+(const poli&);
  poli operator-();
  poli operator-(poli);
  void b_grad();
  T operator()(T);
  poli deriv();
  T deriv(T);
  poli integ(T=0);
  T integ(T,T);
};

//Constructor por defecto
template <class T>
poli<T>::poli(){
  grado=0;
  vector<T> v={0};
  coef=v;
}

//Constructor mas usado (regalón)
template <class T>
poli<T>::poli(int i, vector<T> v){//grado de mayor a menor en el vector entregado
  //Primero fijo el grado
  grado=i;
  //En caso de que entreguen vector vacio.
  if(v.size()==0)
    v.push_back(0);
  //Relleno de ceros si no entregan todos los coeficintes
  if(i+1!=v.size()){
    for(int j=0;j<=i-v.size();++j)
      coef.push_back(0);
  }
  //Almaceno los valores como coeficientes (quedan de menor a mayor ahora)
  for(int j=1;j<=v.size();++j)
    coef.push_back(v[v.size()-j]);
  //Medida de seguridad, si el (o los) grado mayor son cero.
  //Lo quito y voy bajando el grado
  if(coef.back()==0 && coef.size()>1){
    for(int j=0;j<coef.size();++j){
      if(coef.back()==0 && coef.size()>1){
	int s=coef.size()-1;
	coef.erase(coef.begin()+s);
	grado-=1;
      }
      else break;
    }
  }
}

//Constructor con grado y un elemento. Opcion para llenar todos los grados con el valor o solo el coeficiente del maximo grado.
template <class T>
poli<T>::poli(int a,T b,T c){
  if(c==1){
    grado=a;
    vector<T> v(a+1,b);
    coef=v;
  }
  else{
    grado=a;
    vector<T> v(a,0);
    v.push_back(b);
    coef=v;
  }
}

//Constructor de copia
template <class T>
poli<T>::poli(const poli<T> &p){
  grado=p.grado;
  coef=p.coef;
}

//Deep copy
template <class T>
poli<T>& poli<T>:: operator=(const poli<T> &p){
  if(this!=&p){
    grado=p.grado;
    coef=p.coef;
  }
  return *this;
}

//Operadores para obtener (o cambiar) algun coeficiente
template <class T>
T poli<T>::operator[](int i) const {
  return coef[i];
}

template <class T>
T& poli<T>:: operator[](int i){
  return coef[i];
}

//Devuelvo el grado (para dar su acceso a funciones externas)
template <class T>
int poli<T>::grad() const{
  return grado;
}

//Suma de polinomios 
template <class T>
poli<T> poli<T>::operator+(const poli<T> &p){
  if(this->grado==p.grado){
    vector<T> v;
    for(int i=0;i<=p.grado;++i)
      v.push_back((*this)[i]+p[i]);
    reverse(v.begin(),v.end());
    poli<T> h(v.size()-1,v);
    return h;
  }
  else if(this->grado>p.grado){
    vector<T> v;
    for(int i=0;i<=p.grado;++i)
      v.push_back((*this)[i]+p[i]);
    for(int i=p.grado+1;i<=this->grado;++i)
      v.push_back((*this)[i]);
    reverse(v.begin(),v.end());
    poli<T> h(v.size()-1,v);
    return h;
  }
  else{
    vector<T> v;
    for(int i=0;i<=this->grado;++i)
      v.push_back((*this)[i]+p[i]);
    for(int i=this->grado+1;i<=p.grado;++i)
      v.push_back(p[i]);
    reverse(v.begin(),v.end()); 
    poli<T> h(v.size()-1,v);
    return h;
  }
   
}

//'Negar' el polinomio (cambiarle el signo)
template <class T>
poli<T> poli<T>::operator-(){
  poli<T> h(this->grado);
  for(int i=0;i<=this->grado;++i)
    h[i]=-(*this)[i];
  return h;
}

//Resta como suma mas el polinomio 'negado'
template <class T>
poli<T> poli<T>::operator-(poli<T> p){
  return (*this)+(-p);
}

//Bajo grado
template <class T>
void poli<T>::b_grad(){
  coef.pop_back();
  grado-=1;
}

//Evaluacion del polinomio
template <class T>
T poli<T>::operator()(T a){
  T acum=0;
  for(int i=0;i<=this->grado;++i)
    acum+=(*this)[i]*pow(a,i);
  return acum;
}

//Derivada
template <class T>
poli<T> poli<T>::deriv(){
  if(grado==0){
    vector<T> v={0};
    poli<T> p(0,v);
    return p;
  }
  else{
    vector<T> v;
    for(int i=1;i<=grado;++i){
      v.push_back(coef[i]*i);
    }
    reverse(v.begin(),v.end());
    poli<T> p(grado-1,v);
    return p;
  }
}

//Derivada evaluada
template <class T>
T poli<T>::deriv(T a){
  poli<T> p=this->deriv();
  return p(a);
}

//Integral, permite agregar la cte.
template <class T>
poli<T> poli<T>::integ(T a){
  vector<T> v;
  for(int i=0;i<=grado+1;++i){
    if(i==0)
      v.push_back(a);
    else
      v.push_back(coef[i-1]/(i));
     
  }
  reverse(v.begin(),v.end());
  poli<T> p(grado+1,v);
  return p;
}

//Integral evaluada
template <class T>
T poli<T>::integ(T a,T b){
  poli<T> p=this->integ();
  return p(b)-p(a);
}

//Ahora las funciones externas


//Impresion de polinomios. Se imprimen de mayor a menor, omitiendo +-, y otras cosas esteticas. A futuro, que no se vean los unos.
template <class T>
ostream& operator<<(ostream &os,const poli<T> &p){
  for(int i=p.grad();i>=0;--i){
    if(i==p.grad() && i!=0){
      os<<p[i]<<"x^"<<i;
    }
    else if(p[i]<0){
      if(i!=0)
	os<<p[i]<<"x^"<<i;
      else
	os<<p[i];
    }
    else if(p[i]>0){
      if(i!=0)
	os<<'+'<<p[i]<<"x^"<<i;
      else
	os<<'+'<<p[i];	
    }
    else if(p[i]==0 && p.grad()==0)
      os<<0;
  }
  return os;
}

//Multiplicacion entre polinomios
template <class T>
poli<T> operator*(const poli<T> &p, const poli<T> &q){
  vector<T> v(p.grad()+q.grad()+1,0);
  for(int i=0;i<=p.grad();++i){
    for(int j=0;j<=q.grad();++j){
      v[i+j]+=p[i]*q[j];
    }
  }
  reverse(v.begin(),v.end());
  poli<T> h(p.grad()+q.grad(),v);
  return h;
}

//Multiplicacion con escalar (o lo que sea que sea T)
template <class T>
poli<T> operator*(const poli<T> &p,T a){
  vector<T> v(p.grad()+1,0);
  for(int i=0;i<=p.grad();++i)
    v[i]+=a*p[i];
  reverse(v.begin(),v.end());
  poli<T> h(p.grad(),v);
  return h;
}

//Conmutatividad de lo anterior
template <class T>
poli<T> operator*(T a,const poli<T> &p){
  vector<T> v(p.grad()+1,0);
  for(int i=0;i<=p.grad();++i)
    v[i]+=a*p[i];
  reverse(v.begin(),v.end());
  poli<T> h(p.grad(),v);
  return h;
}

//Division por escalar (o lo que sea T)
template <class T>
poli<T> operator/(const poli<T> &p,T a){
  vector<T> v(p.grad()+1,0);
  for(int i=0;i<=p.grad();++i)
    v[i]+=p[i]/a;
  reverse(v.begin(),v.end());
  poli<T> h(p.grad(),v);
  return h;
}


//Division de polinomios (la tenia definida desde antes, claramente no se usa para que te la saltes)
template <class T>
poli<T> div(const poli<T> &p,const poli<T>&q, char c='q'){
  vector<T> cuo;
  if(q.grad()>p.grad()){
    cout<<"El divisor no puede tener mayor grado que el dividendo"<<endl;
    poli<T> p;
    return p;
  }

  poli<T> aux1(p);poli<T> aux2(q);
  for(int i=0;i<=p.grad()-q.grad();++i){
    if(aux1.grad()+i!=p.grad()){
      cuo.push_back(0);continue;
    }
    T a = aux1[aux1.grad()]/q[q.grad()];
    cuo.push_back(a);
    poli<T> bla(aux1.grad()-aux2.grad(),a,0);
    aux1.b_grad();aux2.b_grad();
    aux1=aux1-(aux2*bla);
    aux2=q;
  }
  if(c=='q'){
    poli<T> Cuo(cuo.size()-1,cuo);
    return Cuo;
  }
  else return aux1;
}

//Devuelvo el cuociente
template <class T>
poli<T> operator/(const poli<T> &p,const poli<T> &q){
  return div(p,q);
}

//Devuelvo el resto
template <class T>
poli<T> operator%(const poli<T> &p,const poli<T> &q){
  return div(p,q,'r');
}
#endif
