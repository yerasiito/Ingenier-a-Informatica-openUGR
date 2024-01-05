//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programaci�n
// ETS Inform�tica y Telecomunicaciones
// Universidad de Granada
// // Don Oreo
//
//////////////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;

int LeeIntMayorIgual(int min) {
   int a_leer;
   do
      cin >> a_leer;
   while (min > a_leer);

   return a_leer;
}

int LeeIntRango(int min,int max){
   int dato = min -1;   //Para que siempre est� fuera del intervalo y entre en el bucle

   while(min > dato || max < dato)
      cin >> dato;

   return dato;

}

int main(){

   long min, max, dato;

   cout << "\nIntroduzca el valor m�nimo y el m�ximo"
        << "\nA continuaci�n introduzca enteros en el rango anterior\n";

   cin >> min;

   max = LeeIntMayorIgual(min);

   dato = LeeIntRango(min,max);

   cout << dato << " est� en el intervalo [" << min << "," << max << "]" << endl;
}
