#include <iostream>
#include <cmath>
using namespace std;

/*17. [Variaci�n porcentual: lectura de varios valores] Recupere la soluci�n del ejercicio 5
[Variaci�n porcentual] de la Relaci�n de Problemas I. Modif�quelo para realizar una
lectura de m�ltiples pares de valores. La entrada de datos se interrumpir� cuando
se introduzca cualquier valor negativo. Para simplificar, supondremos que si el primer
valor introducido es positivo, el usuario tambi�n introducir� un positivo como segundo
valor.
Por cada par de valores, el programa mostrar� la correspondiente variaci�n porcentual.
En este ejercicio puede mezclar entradas de datos con salidas y c�mputos, dentro
del mismo bucle.
*/

int main()
{
   double valor1,valor2, variacion;
   cout << "Este programa calcula la variacion porcentual de dos valores"
        << "(si el primero es positivo, el segundo tambien)\n hasta introducir un valor negativo\n" << endl;
   do{
      cout << "Introduce el primer valor: ";
      cin >> valor1;
      if(valor1>=0){
         cout << "Ahora introduce el segundo: ";
         cin >> valor2;
         variacion = abs(100*((valor1 - valor2)/valor1));
         cout << "La variacion porcentual es " << variacion << "%" << endl;
         cout << "------------------------------" << endl;
      }
   }
   while(valor1>=0);


}
