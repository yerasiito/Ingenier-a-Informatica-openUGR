//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programaci�n
// ETS Inform�tica y Telecomunicaciones
// Universidad de Granada
// // Don Oreo
//
//////////////////////////////////////////////////////////////////////////

// top_k: Calcula los k mayores valores de un vector - versi�n ineficiente -

/*
Se dispone de una serie de enteros enteros positivos y se
quiere calcular los k mayores, ordenados de mayor a menor. Construya un programa
que vaya leyendo enteros desde teclado hasta que se introduzca -1. A continuaci�n lea
el n�mero k y aplique el siguiente algoritmo:
Vector original: v
Vector que contendr� los k mayores valores: topk
   Copiar v en topk
   Ordenar topk de MAYOR a MENOR <-- Atenci�n!!!
      (se recomienda modificar el algoritmo de ordenaci�n
      por inserci�n)
   Seleccionar los k primeros elementos de topk
Finalmente, imprima los k primeros valores del vector topk en pantalla.
Ejemplo de entrada: 2 0 3 2 12 -1 2
-- Salida correcta: 12 3
*/

#include <iostream>
using namespace std;

int main(){
   const int TERMINADOR = -1;
   int entero;
   const int TAMANIO                 =  1e6;
   int vector[TAMANIO], topk[TAMANIO];
   int utilizados_vector, k;

   //////////////////////////////////////////////////////////////////
   // Lectura de los datos:


   cout << "Topk.\n\n"
        << "Introduzca enteros con terminador "
        << TERMINADOR << "\n"
        << "Luego introduzca el valor de k.\n\n";

   utilizados_vector = 0;
   cin >> entero;

   while (entero != TERMINADOR && utilizados_vector < TAMANIO){
      vector[utilizados_vector] = entero;
      utilizados_vector++;
      cin >> entero;
   }

   cin >> k;

   /*
   Algoritmo ineficiente:
      Copiar el vector en topk
      Ordenar topk
      Seleccionar los k primeros de topk
   */


   for (int i = 0; i < utilizados_vector; i++)
      topk[i] = vector[i];

   int i;
   double a_insertar;
	int j;
   
	for (i = 1; i < utilizados_vector; i++){
      a_insertar = topk[i];

      for (j = i; j > 0 && a_insertar > topk[j-1]; j--)   // Ordenaci�n de mayor a menor
         topk[j] = topk[j-1];

      topk[j] = a_insertar;
   }

   for (int i = 0; i < k; i++){
      cout << topk[i] << " ";
   }
}

