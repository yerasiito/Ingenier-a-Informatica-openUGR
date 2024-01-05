//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programaci�n
// ETS Inform�tica y Telecomunicaciones
// Universidad de Granada
// // Don Oreo
//
//////////////////////////////////////////////////////////////////////////

/* ENUNCIADO:
   29. [Secuencia de temperaturas] Construya un programa que calcule cu�ndo se produjo
   la mayor secuencia de d�as consecutivos con temperaturas crecientes. El programa
   leer� una secuencia de reales representando temperaturas. Una temperatura es correcta
   si su valor est� en el intervalo [-90, 60] (los extremos representan las temperaturas
   extremas registradas en la Tierra). La entrada de datos terminar� cuando
   se introduzca una temperatura fuera del rango anterior. El programa debe calcular la
   subsecuencia de n�meros ordenada, de menor a mayor, de mayor longitud.
   El programa nos debe decir la posici�n donde comienza la subsecuencia y su longitud.
   Por ejemplo, ante la entrada siguiente:

   17.2 17.3 16.2 16.4 17.1 19.2 18.9 100

   El programa nos debe indicar que la mayor subsecuencia empieza en la posici�n 3 (en
   el 16.2) y tiene longitud 4 (termina en 19.2)
   Considere los siguientes consejos:
      -Tendr� que leer sobre dos variables anterior y actual, para as� poder comparar
      el valor actual con el anterior.
      -Se recomienda que use la t�cnica de lectura anticipada, por lo que tendr� que
      leer un primer valor y comprobar si est� en el rango adecuado:

   cin >> anterior;
   final_entrada_datos = anterior < MIN_TEMP
                                 ||
                                 anterior > MAX_TEMP;
   while (! final_entrada_datos){
      cin >> actual;
      ......
   }

   Dentro del cuerpo del bucle tendr� que comparar el valor actual con los extremos
   del rango de temperaturas, tal y como se hizo antes de entrar al bucle
   con el valor anterior. Esto hace que repitamos un c�digo muy parecido. Lo
   resolveremos cuando veamos las funciones.
   Ejemplo de entrada: 17.2 17.3 16.2 16.4 17.1 19.2 18.9 100
      -Salida correcta: Inicio: 3 Longitud: 4
   Ejemplo de entrada: 17.2 17.3 16.2 16.4 17.1 19.2 100
      -Salida correcta: Inicio: 3 Longitud: 4
   Ejemplo de entrada: 17.2 17.3 100
      -Salida correcta: Inicio: 1 Longitud: 2
   Ejemplo de entrada: 17.2 15.3 100
      -Salida correcta: Inicio: 2 Longitud: 1
   Ejemplo de entrada: 17.2 100
      -Salida correcta: Inicio: 1 Longitud: 1
   Ejemplo de entrada: 100
      -Salida correcta: Inicio: 1 Longitud: 0
   Finalidad: Trabajar con bucles que comparan un valor actual con otro anterior. Dificultad
   Media.
   */

#include <iostream>
#include <cmath>

using namespace std;

int main(){
   /*Intervalo v�lido de temperatura [-90,60]
   L�mite de registro de temperaturas de 100
   El terminador ser� true y false en funci�n del intervalo [-90,60]
   */
   double temperatura;
   const int MIN_TEMP=-90, MAX_TEMP=60;
   const int LIM_TEMP=100;
   double registro_temp[LIM_TEMP];
   bool terminador;
   double minimo=MAX_TEMP;


//Entrada de datos...

   cout << "Introduce las temperaturas: ";

   /*sale del bucle cuando el numero de temperaturas excede el limite del vector o cuando una temperatura sale del rango [-90,60]
   Cada vez que metemos una temperatura, comprobamos que sea valida([-90,60]) con el bool terminador
   */
   int i=0;
   int contador=-1;
   int posicion;

   while(contador<=LIM_TEMP && terminador==false){
      cin >> temperatura;
      terminador = (temperatura< MIN_TEMP || temperatura > MAX_TEMP);
      registro_temp[i]=temperatura;
      contador++;                      //Cuenta el numero de temperaturas para guardarlo en la variable util despu�s
      i++;
      if(temperatura<minimo){          //con el condicional guardamos la menor temperatura y su posicion gracias al contador
         minimo = temperatura;
         posicion = contador + 1 ;
      }
   }


//C�lculo de datos...
   /*guardamos el valor del contador en la variable util*/

   int util = contador;
   int longitud=1;
   int anterior, actual;
   //anterior y actual son los valores que utilizamos para comparar las variables del vector(en el bucle posterior)

   //si util es 0 es porque hemos metido una temperatura invalida y entonces su longitud y posicion son 0
   if(util>0){
      for(i=posicion;i<=util;i++){
         anterior=registro_temp[i];
         actual=registro_temp[i+1];
         if(anterior<actual){
            longitud++;
         }
      }
   }
   else
   {
      longitud=0;
      posicion=0;
   }

//Salida de datos...

   cout << endl << "Inicio: " << posicion << " Longitud: " << longitud << endl;




}


