#ifndef MATRIZ_H
#define MATRIZ_H
#include<iostream>
#include<vector>

//Mi clase de matrices, dejare arribita solo lo usado en la tarea
using namespace std;

template <class T>
class matriz{
 private:
  int f,c;
  vector<T> mat;
 public:
  matriz();
  matriz(int,int,T=0);//filas columnas y con que llenarlo
  matriz(int,const vector<T>&);
  matriz(vector<vector<T>>);
  matriz(const matriz&);
  matriz operator=(const matriz&);
  T& operator()(int,int);
  T operator()(int,int) const;
  int fila() const {return f;}
  int colu() const {return c;}
  matriz tras() const;
  matriz fila(int);
  matriz colu(int);
};

//Formas de asignar o llamar a valores de la matriz (Se ve rara porque la matriz se construye naturalmente a partir de un solo vector)
template <class T>
T& matriz<T>::operator()(int a,int b){
  if(a<=f&&b<=c) return mat[c*(a)+(b)];
}

template <class T>
T matriz<T>::operator()(int a,int b) const{
  if(a<=f&&b<=c) return mat[c*(a)+(b)];
}

//Constructor de copia
template <class T>
matriz<T>::matriz(const matriz<T> &m){
  f=m.f;
  c=m.c;
  mat=m.mat;
}

//Constructor con numero de filas y vector
template <class T>
matriz<T>::matriz(int a,const vector<T> &v){
  if(v.size()%a!=0){
    //Incluye un mensja en caso de que no calcen los elementos del vector con la cantidad de filas.
    cout<<"Cuidado, incorrecta cantidad de elementos, se rellenará con ceros"<<endl;
    vector<T> h=v;
    while(h.size()%a!=0)
      h.push_back(0);
    f=a;c=h.size()/a;mat=h;
  }
  else{
    f=a;c=v.size()/a;mat=v;
  } 
}

//Impresion de la matriz, originalmente imprimia parentesis al principio y al final pero eso "jodió" un poco a gnuplot, por eso los comandos comentados entremedio
template <class T>
ostream & operator<<(ostream &os,const matriz<T> &m){
  for(int i=0;i<m.fila();++i){
    //  if(i==0) os<<'(';else os<<' ';
    for(int j=0;j<m.colu();++j){
      //if((i==m.fila()-1) && (j==m.colu()-1)) os<<m(i,j);
      //else os<<m(i,j)<<' ';
      os<<m(i,j)<<' ';
      }
    //if(i == m.fila()-1) os<<')';
    //else os<<endl;
    os<<endl;
    }
    return os;
}


/////////////////////////////////////////////////////////////////////
///////////NADA DE ACA HACIA ABAJO IMPORTA EN EL PROGRAMA////////////
/////////////////////////////////////////////////////////////////////


template <class T>
matriz<T> matriz<T>::fila(int a){
  matriz<T> m(1,c);
  for(int i=0;i<c;++i)
    m(0,i)=(*this)(a,i);
  return m;
}

template <class T>
matriz<T> matriz<T>::colu(int a){
  matriz<T> m(f,1);
  for(int i=0;i<f;++i)
    m(i,0)=(*this)(i,a);
  return m;
}



template <class T>
matriz<T> matriz<T>::operator=(const matriz<T> &m){
  if(this!=&m){
    f=m.f;
    c=m.c;
    mat=m.mat;
  }
  return *this;
}

template <class T>
matriz<T>::matriz(vector<vector<T>> v){
  vector<T> h;
  for(int i=0;i<v.size();++i)
    for(int j=0;j<v[i].size();++j)
      h.push_back(v[i][j]);
  f=v.size();
  c=v[0].size();
  mat=h;
}


template <class T>
matriz<T>::matriz(): f(1),c(1),mat({0}){}

template <class T>
matriz<T>::matriz(int a,int b, T h){
  f=a;
  c=b;
  for(int i=0;i<a*b;++i)
     mat.push_back(h);
}


template <class T>
matriz<T> matriz<T>::tras() const{
  matriz<T> m(c,f);
  for(int i=0;i<f;++i){
    for(int j=0;j<c;++j){
      m(j,i)=(*this)(i,j);
    }
  }
  return m;
}

template <class T>
matriz<T> operator+(const matriz<T> &m, const matriz<T> &n){
  if(m.fila() == n.fila() && m.colu() == n.colu() ){
    matriz<T> res(m.fila(),m.colu());
    for(int i=0;i<res.fila();++i){
      for(int j=0;j<res.colu();++j){
	res(i,j)=m(i,j)+n(i,j);
      }
    }
    return res;
    }
  else{
    cout<<"Por favor, suma/resta matrices de las mismas dimensiones"<<endl;
    matriz<T> res;
    return res;
      }
}

template <class T>
matriz<T> operator*(T a,const matriz<T> &m){
  matriz<T> res(m.fila(),m.colu());
  for(int i=0;i<m.fila();++i){
    for(int j=0;j<m.colu();++j){

      res(i,j)=m(i,j)*a;
    }
  }
  return res;
}

template <class T>
matriz<T> operator-(const matriz<T> &m, const matriz <T> &n){
  matriz<T> res=m+(T(-1)*n);
  return res;
}

//Ojo con esta, TALVEZ se pueda mas eficiente :c
template <class T>
matriz<T> operator*(const matriz<T> &m,const matriz<T> &n){
  if(m.colu() == n.fila()){
    matriz<T> res(m.fila(),n.colu());
    T acum;
    int k=-1;
    do{
      ++k;
      for(int i=0;i<m.fila();++i){
	acum=0;
	for(int j=0;j<n.fila();++j){
	  acum+=m(i,j)*n(j,k);
	}
	res(i,k)=acum;
      }
    }
    while(k!=n.colu()-1);
    return res;
  }
  else{
    cout<<"Por favor multiplica dos matrices con las dimensiones correcta"<<endl;
    matriz<T> res;
    return res;
  }
}

#endif
