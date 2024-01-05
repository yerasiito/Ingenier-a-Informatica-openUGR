//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programaci�n
// ETS Inform�tica y Telecomunicaciones
// Universidad de Granada
// // Don Oreo
//
//////////////////////////////////////////////////////////////////////////

/* [Aproximaci�n de PI por Wallis] Otra aproximaci�n de PI introducida en el siglo XVII por
el matem�tico ingl�s John Wallis viene dada por:

   pi/2 =2/1 � 2/3 � 4/3 � 4/5 � 6/5 � 6/7 ...

   Construya un programa que lea el valor tope obligando a que est� entre 1 y cien mil,
   calcule la aproximaci�n de PI mediante la anterior f�rmula (multiplicando un total de
   tope fracciones) e imprima el resultado en pantalla.
   Debe resolver este problema de dos formas distintas, a saber:
      --Observe que el numerador y el denominador var�an de forma alternativa (aunque
   ambos de la misma forma, a saltos de 2). Cuando a uno le toca cambiar, el otro
   permanece igual. Este comportamiento se puede controlar con una �nica variable
   de tipo de dato bool.
      --Otra forma de implementar los cambios en el numerador y denominador es observando
   que en cada iteraci�n, el numerador es el denominador de la iteraci�n
   anterior m�s 1 y el denominador es el numerador de la iteraci�n anterior m�s 1.
   Ejemplo de entrada: 1000 -- Salida correcta: 3.1400238186006
   Ejemplo de entrada: 100000 -- Salida correcta: 3.14157694582286
*/

#include <iostream>
#include <cmath>

using namespace std;

int main(){
   int tope;
   int i = 0.0;
   double numerador = 0.0;
   double denominador = 1.0;
   double serie;
   double acumulador = 1.0;
   double pi_aprox;
   bool cambio;

   do{
      cout << "Introduce el tope de calculo: ";
      cin >> tope;
   }
   while(tope<0 || tope>1e+5);

   for(i=0;i<tope;i++){
      cambio = (i%2==0);
      if(cambio){
         numerador = numerador + 2;
         serie = numerador/denominador;
      }
      else{
         denominador = denominador + 2;
         serie = numerador/denominador;
      }
   acumulador = serie * acumulador;

   }

   pi_aprox = 2*acumulador;         //Es porque se iguala a pi/2 por lo que para obtener pi, se le multiplica por 2
   cout.precision(15);
   cout << "Pi aproximado segun wallis es: " << pi_aprox << endl;

}

