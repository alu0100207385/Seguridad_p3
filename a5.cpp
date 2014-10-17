#include "a5.hpp"

using namespace std;

A5::A5 (void)
{
  for (unsigned i=0; i<MAX1;i++)
    r1.push_back(0);
  for (unsigned i=0; i<MAX2;i++)
    r2.push_back(0);
  for (unsigned i=0; i<MAX3;i++)
    r3.push_back(0);
}

void A5::cargar_fichero1 (char fichero[]) //Carga directamente en los registros
{
  ifstream flujo;
  flujo.open(fichero);
  if (flujo.is_open())
  {
      string r_1,r_2,r_3;
      while (!flujo.eof())
      {
	flujo>>r_1;
	flujo>>r_2;
	flujo>>r_3;
      }
      set_r1(r_1);
      set_r2(r_2);
      set_r3(r_3);
  }   flujo.close();
}

void A5::cargar_fichero (char fichero[])//Carga K(64bits) y F(22bits)
{
  ifstream flujo;
  flujo.open(fichero);
  if (flujo.is_open())
  {
      string k, f; //recogemos los 64bits y Fn de 22bits
      while (!flujo.eof())
      {
	flujo>>k;
	flujo>>f;
// 	cout<<"K= "<<k<<endl;
// 	cout<<"F= "<<f<<endl;
      }
      flujo.close();
      int i,c;
      for (i=0; i<MAX1;i++)
	r1[i]= (r1[i] ^ (k[i]-'0'));
      c=MAX1;
      for (i=0; i<MAX2;i++)
      {
	r2[i]= (r2[i] ^ (k[c]-'0'));
	c++;
      }
      for (i=0; i<MAX3;i++)
      {
	r3[i]= (r3[i] ^ (k[c]-'0'));
	c++;
      }

      //desplazamiento: 64 ciclos
      for (int j = 0; j<64; j++)
      {
	desplazar_r1();
	desplazar_r2();
	desplazar_r3();
      }
      
      for (i=0; i<MAX1;i++)
	r1[i]= (r1[i] ^ (f[i]-'0'));

      for (i=0; i<MAX2;i++)
	r2[i]= (r2[i] ^ (f[i]-'0'));
      
      for (i=0; i<f.size();i++)
	r3[i]= (r3[i] ^ (f[i]-'0'));
      
      //desplazamiento: 22 ciclos
      for (int j = 0; j<22; j++)
      {
	desplazar_r1();
	desplazar_r2();
	desplazar_r3();
      }
  }
}

string A5::get_r1 (void)
{
    Color::Modifier def(Color::BG_DEFAULT);
    Color::Modifier green(Color::BG_GREEN);
    Color::Modifier blue(Color::BG_BLUE);
    stringstream aux;
    aux<<"R1: ";
    for (int i =0; i<r1.size();i++)
    {
	if ((i==0)||(i==1)||(i==2)||(i==5))  
	  aux<<blue<<r1[i]<<def<<" ";
	else{
	  if (i==10)
	    aux<<green<<r1[i]<<def<<" ";
	  else
	    aux<<r1[i]<<" ";
	}
    }aux<<"\n";
    return aux.str();
}

string A5::get_r2 (void)
{
    Color::Modifier def(Color::BG_DEFAULT);
    Color::Modifier green(Color::BG_GREEN);
    Color::Modifier blue(Color::BG_BLUE);
    stringstream aux;
    aux<<"R2: ";
    for (int i =0; i<r2.size();i++)
    {
	if ((i==0)||(i==1))
	  aux<<blue<<r2[i]<<def<<" ";
	else{
	  if (i==11)
	    aux<<green<<r2[i]<<def<<" ";
	  else
	    aux<<r2[i]<<" ";
	}
    }aux<<"\n";
    return aux.str();
}

string A5::get_r3 (void)
{
    Color::Modifier def(Color::BG_DEFAULT);
    Color::Modifier green(Color::BG_GREEN);
    Color::Modifier blue(Color::BG_BLUE);
    stringstream aux;
    aux<<"R3: ";
    for (int i =0; i<r3.size();i++)
    {
	if ((i==0)||(i==1)||(i==2)||(i==15))
	  aux<<blue<<r3[i]<<def<<" ";
	else{
	  if (i==12)
	    aux<<green<<r3[i]<<def<<" ";
	  else
	    aux<<r3[i]<<" ";
	}
    }aux<<"\n";
    return aux.str();
}

void A5::set_r1 (string cad)
{
  for (int i=0; i<MAX1; i++)
    r1[i]= cad[i]-'0';
}

void A5::set_r2 (string cad)
{
  for (int i=0; i<MAX2; i++)
    r2[i]= cad[i]-'0';
}

void A5::set_r3 (string cad)
{
  for (int i=0; i<MAX3; i++)
    r3[i]= cad[i]-'0';
}


vector<int> A5::clock_check (void)
{
    vector<int> aux;
//     int F = ((r1[8]*r2[10]) ^ (r1[8]*r3[10]) ^ (r2[10]*r3[10]));
    int F = ((r1[10]*r2[11]) ^ (r1[10]*r3[12]) ^ (r2[11]*r3[12]));
    cout<<"F (mayoria)= "<<F;
    if (r1[10]==F)
      aux.push_back(1);
    if (r2[11]==F)
      aux.push_back(2);
    if (r3[12]==F)
      aux.push_back(3);
    return aux;
}


int A5::a_t(void) {
//   return (r1[18] ^ r1[17] ^ r1[16] ^ r1[13]);
    return (r1[0] ^ r1[1] ^ r1[2] ^ r1[5]);
}

int A5::b_t(void) {
//   return (r2[21] ^ r2[20]);
     return (r2[0] ^ r2[1]);
}

int A5::c_t(void) {
//   return (r3[22] ^ r3[21] ^ r3[20] ^ r3[7]);
     return (r3[0] ^ r3[1] ^ r3[2] ^ r3[15]);
}

int A5::z_t(void) {
//   return (r1[18] ^ r2[21] ^ r3[22]);
     return (r1[0] ^ r2[0] ^ r3[0]);
}


void A5::desplazar_r1 (void)
{
  int aux = a_t();
//   cout<<"a(t)= "<<aux<<endl;
  for (unsigned i=0; i<MAX1; i++)
      r1[i]=r1[i+1];
  r1[MAX1-1]= aux;
}

void A5::desplazar_r2 (void)
{
  int aux = b_t();
//   cout<<"b(t)= "<<aux<<endl;
  for (unsigned i=0; i<MAX2; i++)
      r2[i]=r2[i+1];
  r2[MAX2-1]= aux;
}

void A5::desplazar_r3 (void)
{
  int aux = c_t();
//   cout<<"c(t)= "<<aux<<endl;
  for (unsigned i=0; i<MAX3; i++)
//   for (unsigned i=MAX3; i>0; i--)
      r3[i]=r3[i+1];
  r3[MAX3-1]= aux;
}

vector<int> A5::generar (int n)
{
  int z;
  vector<int> m;
/*  for (int i=0; i<100; i++)//descartamos la salida durante 100 ciclos
  {
    for (int j=0; j<m.size();j++)
    {
      m= clock_check();
      if (m[i]==1)
	desplazar_r1();
      if (m[i]==2)
	desplazar_r2();
      if (m[i]==3)
	desplazar_r3();
      m.clear();
    }
  }
*/
  vector<int> cifrado;
  for (int i=0; i<n; i++)//generamos la secuencia cifrada durante 228 ciclos
  {
      cout<<get_r1()<<endl;
      cout<<get_r2()<<endl;
      cout<<get_r3()<<endl;
      cout<<"Interacion "<<i<<": ";
      m= clock_check();
      z= z_t();
      cifrado.push_back(z);
      cout<<" ;; z= "<<z<<endl;

      if (buscar(m,1))
      {
// 	cout<<"desplazo r1"<<endl;
	desplazar_r1();
      }
      if (buscar(m,2))
      {
// 	cout<<"desplazo r2"<<endl;
	desplazar_r2();
      }
      if (buscar(m,3))
      {
// 	cout<<"desplazo r3"<<endl;
	desplazar_r3();
      }
      m.clear();
  }
  return cifrado;
}


bool A5::buscar (vector<int> &v, int reg)
{
  for (int i=0; i<v.size();i++)
  {
    if (v[i]==reg)
      return true;
  }
  return false;
}
