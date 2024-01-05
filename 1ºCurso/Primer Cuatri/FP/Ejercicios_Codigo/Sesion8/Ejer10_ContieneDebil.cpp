//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programaci�n
// ETS Inform�tica y Telecomunicaciones
// Universidad de Granada
// // Don Oreo
//
//////////////////////////////////////////////////////////////////////////

/*

. [Contiene d�bil] (Examen Enero 2018) Dados dos vectores grande y peque de
tipo char, queremos comprobar si el primero contiene al segundo de la siguiente forma: todos los caracteres de peque tienen que aparecer en grande en el
mismo orden, aunque no tienen por qu� estar consecutivos. Por ejemplo, el vector grande = {'d','e','s','t','i','n','o'} contiene d�bilmente al vector
peque = {'s','i'} pero no a peque = {'i','s'}.
Construya un programa que lea desde teclado los caracteres del vector grande, parando la entrada cuando se introduzca el car�cter #. Haga lo mismo para introducir los
caracteres del vector peque. El programa indicar� si el vector grande contiene o no al vector peque.
Si lo desa puede usar el esbozo del programa que se encuentra en el siguiente enlace:
http://decsai.ugr.es/jccubero/FP/III_ContieneDebilEsbozo.cpp
Ejemplo de entrada: destino#si#
 Salida correcta: S� lo contiene
Ejemplo de entrada: destino#is#
 Salida correcta: No lo contiene
Ejemplo de entrada: destino#no#
 Salida correcta: S� lo contiene
Finalidad: Recorrido de las componentes de un vector. Dificultad Media.

*/

#include <iostream>
using namespace std;

int main(){
   const char TERMINADOR = '#';
   const int MAX_NUM_CARACT = 200;
   char grande[MAX_NUM_CARACT],
        peque[MAX_NUM_CARACT];
   char car;
   int util_grande, util_peque;
   int num_leidos;
   bool encontrado;


   cout << "B�squeda -d�bil- de un vector de caracteres dentro de otro\n"
        << "Introduzca los car�cteres del vector grande, con terminador "
        << TERMINADOR << "\n"
        << "A continuaci�n introduzca  los caracteres del vector peque�o,"
        << " usando el mismo terminador.\n\n";

   // Lectura

   car = cin.get();
   num_leidos = 0;

   while (car != TERMINADOR && num_leidos < MAX_NUM_CARACT){
      grande[num_leidos] = car;
      car = cin.get();
      num_leidos++;
   }

   util_grande = num_leidos;

   car = cin.get();
   num_leidos = 0;

   while (car != TERMINADOR && num_leidos < MAX_NUM_CARACT){
      peque[num_leidos] = car;
      car = cin.get();
      num_leidos++;
   }

   util_peque = num_leidos;



   ///////////////////////////////////////////////////////////
   encontrado=false;
   num_leidos=0;
   int j=0;

      for(int i=0;i<util_grande && encontrado==false;i++){
         if(grande[i]==peque[j]){
            num_leidos++;
            j++;

         if(num_leidos==util_peque)
            encontrado=true;
         }
      }
   ///////////////////////////////////////////////////////////



   cout << "\n";

   if (encontrado)
      cout << "\nEl vector peque�o est� dentro del grande";
   else
      cout << "\nEl vector peque�o NO est� dentro del grande";

/*
aaabbbccc#abc#
Si

abc#a#
Si

cba#a#
Si

azbzcz#abc#
Si

abz#abc#
No
*/
}



