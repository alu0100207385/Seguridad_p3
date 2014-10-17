//ALUMNO: Aaron Socas Gaspar
//Seguridad curso 2013-2014
//Practica 3: A5

#include "a5.hpp"
#include <stdlib.h>

using namespace std;

bool check_fich (char fichero[])
{
  ifstream flujo;
  flujo.open(fichero);
  if (flujo.is_open())
  {
      flujo.close();
      return true;
  }
  else
    return false;
}

string mostrar (vector<int> v)
{
    stringstream s;
    s<<"Cifrado = [";
    for (int i =0; i<v.size();i++)
	s<<v[i]<<" ";
    s<<"]";
    return s.str();
}

int main (int argc, char* argv[])
{
  if (argc==2)
  {
      if (check_fich(argv[1]))
      {
	A5 a;
	a.cargar_fichero1(argv[1]);
	cout<<"Fichero cargado: "<<argv[1]<<endl;
	cout<<"¿Cuantos bits de secuencia cifrante quieres generar?[enter=228]"<<endl;
	string n;
	getline (cin,n);
	vector<int> Z;
	if (n.empty())
	  Z= a.generar();
	else
	{
	  int m = atoi(n.c_str());
	  Z= a.generar(m);
	}
	do{
	    cout<<"¿Desea ver toda la secuencia cifrante?[s/n]"<<endl;
	    getline(cin,n);
	}while ((n!="s")&&(n!="n"));
	if (n=="s")
	  cout<<mostrar(Z)<<endl;
      }
      else
	cout<<"Error en la carga del fichero, compruebe nombre y/o ruta."<<endl;
  }      
  else
    cout<<"Error de argumentos. Introduzca ./a5 nombre_fichero"<<endl;
  return 0;
}
