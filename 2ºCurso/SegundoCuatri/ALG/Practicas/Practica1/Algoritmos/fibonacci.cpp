/**
   @file C�lculo de la sucesi�n de Fibonacci
*/

   
#include <iostream>
using namespace std;
#include <ctime>

#include<chrono>
using namespace chrono;


high_resolution_clock::time_point tantes, tdespues;
duration<double> transcurrido;

/**
   @brief Calcula el t�rmino n-�simo de la sucesi�n de Fibonacci.

   @param n: n�mero de orden del t�rmino buscado. n >= 1.

   @return: t�rmino n-�simo de la sucesi�n de Fibonacci.
*/
int fibo(int n)
{
  if (n < 2)
    return 1;
  else
    return fibo(n-1) + fibo(n-2);
}


int main(int argc, char * argv[])
{

  int n;
  int f;
 
  //cout << "�N�mero del t�rmino: ";
  n = atoi(argv[1]);

  tantes = high_resolution_clock::now(); // Tiempo de inicio

  f = fibo(n);

  tdespues = high_resolution_clock::now();    // Anotamos el tiempo de finalizaci�n

  transcurrido = duration_cast<duration<double>>(tdespues - tantes); //Calculamos la diferencia

  //cout << "El t�rmino " << n << "-�simo es: " << f << endl;

  //Mostrar resultados
  cout << n << "\t" << transcurrido.count() << endl;

  return 0;
}
