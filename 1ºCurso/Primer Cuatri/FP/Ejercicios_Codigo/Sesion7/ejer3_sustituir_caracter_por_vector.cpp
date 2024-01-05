//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programaci�n
// ETS Inform�tica y Telecomunicaciones
// Universidad de Granada
// // Don Oreo
//
//////////////////////////////////////////////////////////////////////////
/*
3. [Sustituir car�cter por vector (con vector auxiliar)] Tenga en cuenta la observaci�n al
inicio de esta relaci�n de problemas sobre la lectura de los caracteres (ver p�gina RPIII.1).
Para poder leer caracteres, incluyendo los espacios en blanco, hay que usar caracter = cin.get(),
en vez de cin >> caracter.

Dado un vector de caracteres, queremos sustituir todas las apariciones de un car�cter
y poner en su lugar el contenido de otro vector.

Por ejemplo, si tenemos el vector [u n o a d o s a a], el resultado de
sustituir las apariciones del car�cter 'a' por el nuevo vector [T T U] ser�a
[u n o T T U d o s T T U T T U]

Resolveremos este problema de varias formas a lo largo de esta Relaci�n de Problemas.
En este ejercicio, se construir� un tercer vector sustituido con el resultado
pedido.

Construya un programa que lea caracteres hasta que se introduzca # lo que formar�
el primer vector (v). A continuaci�n lea el car�cter a_borrar que se va a eliminar de
v. Finalmente, el programa leer� los caracteres que formar�n el vector a_insertar
que sustituir�n cada aparici�n de a_borrar. El terminador de entrada de caracteres
para el vector a_insertar es tambi�n el car�cter #

El programa construir� e imprimir� en pantalla un tercer vector sustituido que
contendr� los caracteres de v pero reemplazando todas las apariciones de a_borrar
por los caracteres del vector a_insertar. Si el vector a_insertar contuviese el
car�cter a_borrar, dichas apariciones no se eliminan, tal y como puede apreciarse
en el �ltimo ejemplo que aparece al final de este enunciado.

Para realizar la tarea pedida, se recomienda que implemente el siguiente algoritmo:

Recorrer las componentes -i- del vector v
   Si v[i] == a_borrar
      A�adir a sustituido todas las componentes del vector a_insertar
   si no
      A�adir a sustituido la componente v[i]

Puede utilizar el esbozo del programa disponible en el siguiente enlace:
http://decsai.ugr.es/jccubero/FP/III_SustituyeCaracterVectorEsbozo.cpp

Ejemplo de entrada: u n o a d o s a a # T T U # a
-- Salida correcta: u n o T T U d o s T T U T T U
Ejemplo de entrada: u n o a d o s a a # T a U # a
-- Salida correcta: u n o T a U d o s T a U T a U
Finalidad: Trabajar con vectores auxiliares. Dificultad Baja.
*/
#include <iostream>
#include <cmath>

using namespace std;

int main(){
   int k=0;
   int util_v = 0;
   int util_a_insertar = 0;
   int util_total;
   const int TAMANIO=100;
   char v[TAMANIO];
   char a_insertar[TAMANIO];
   char sustituido[TAMANIO];
   char caracter;
   char caracter_a_borrar;
   const char TERMINADOR = '#';

//Entrada de Datos...

   cout << "Introduce el vector inicial: ";
   caracter = cin.get();

   while (caracter != TERMINADOR && util_v < TAMANIO){
      v[util_v] = caracter;
      util_v++;
      caracter = cin.get();
   }
   cout << "Introduce el caracter a borrar: ";
   cin >> caracter_a_borrar;
   caracter = cin.get();

   caracter=0;   //o cualquier otra cosa diferente a TERMINADOR

   cout << "Introduce el vector a insertar: ";
   caracter = cin.get();

   while (caracter != TERMINADOR && util_a_insertar < TAMANIO){
      a_insertar[util_a_insertar] = caracter;
      util_a_insertar++;
      caracter = cin.get();
   }

//C�mputo...

   util_total=util_v;

   for(int i=0;i<util_total;i++){
      if(v[i]!=caracter_a_borrar){
         sustituido[k]=v[i];
         k++;
      }
      else{
         util_total+=util_a_insertar-1;
         for(int j=0;j<util_a_insertar;j++){
            sustituido[k]=a_insertar[j];
            k++;
         }
      }
   }
//Salida de Datos...

   for (int i = 0; i < util_total; i++)
      cout  << sustituido[i];




}

