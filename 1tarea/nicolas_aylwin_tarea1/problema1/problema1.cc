#include<iostream>
using namespace std;

int main()
{
	cout<<"¿Cuantas particulas?"<<endl; //Pregunto cuantas particulas, almaceno ese valor en n.
	int n;
	cin>>n;
	double a[n][3],x,y,masa; //Creo el arreglo donde guardo la informacion, n vectores de 3 dimensiones (x,y,m), y variables para el "cin".
	cout<<"\n";

	for (int h = 0; h < n; ++h) //Bucle que permite registrar las coordenadas y las masas en el arreglo "a"
	{
		cout<<"¿Coordenadas de particula "<<h+1<<"?"<<endl;
		cin>>x>>y;
		a[h][0]=x;
		a[h][1]=y;
		cout<<"¿Su masa? ";
		cin>>masa;
		a[h][2]=masa;
		cout<<"-----------"<<endl;
	}
	//Reutilizo las variables limpiandolas primero, ahora se usaran como acumuladoras en la suma.
	masa=0;x=0;y=0;
	
	//Ciclo que calcula x_i*m_i,y_i*m_i y masa total
	for(int i=0;i<n;++i)
	{
		x+=a[i][0]*a[i][2];
		y+=a[i][1]*a[i][2];
		masa+=a[i][2];
	}

	//Entrego la informacion requerida
	cout<<"La masa total del sistema es "<<masa<<endl;
	cout<<"La posicion del centro de masa es ("<<x/masa<<","<<y/masa<<")\n";
	
	return 0;
}