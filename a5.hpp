#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "colormod.hpp"

using namespace std;

const int MAX1= 19;
const int MAX2= 22;
const int MAX3= 23;

class A5
{
  private:
    vector <int> r1,r2,r3;
    vector<int> clock_check (void);
    bool buscar (vector<int> &v, int reg);
    int a_t (void);
    int b_t (void);
    int c_t (void);
    int z_t (void);
    void desplazar_r1 (void);
    void desplazar_r2 (void);
    void desplazar_r3 (void);
  public:
    A5 (void);
    inline ~A5(void){};
    void cargar_fichero1 (char fichero[]);
    void cargar_fichero (char fichero[]);
    string get_r1 (void);
    string get_r2 (void);
    string get_r3 (void);
    void set_r1 (string cad);
    void set_r2 (string cad);
    void set_r3 (string cad);
    vector<int> generar (int n=228);
};