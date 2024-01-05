//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programaci�n
// ETS Inform�tica y Telecomunicaciones
// Universidad de Granada
// Departamento de Ciencias de la Computaci�n e Inteligencia Artificial
// Autor: Don Oreo
//
//////////////////////////////////////////////////////////////////////////

// Frecuencias
 /*
   Algoritmo:

      Recorrer -i- el vector texto
         actual = texto[i]

         Si actual no est� en el vector procesados:
            - A�adir actual a procesados
            - Contar el n�mero de ocurrencias de actual
              en el vector texto -a partir de la posici�n i+1-
   */
#include <iostream>
using namespace std;

int main(){
   const char TERMINADOR = '@';
   const int NUM_CARACT_ASCII = 256;
   const int MAX_NUM_CARACT = 1e4;  // diez mil

   char a_buscar[NUM_CARACT_ASCII];
   int frecuencias[NUM_CARACT_ASCII] {};
   char texto[MAX_NUM_CARACT];
   int contador;
   char car;
   int util_a_buscar, util_texto;

   cout << "Frecuencias\n"
        << "Introduzca los caracteres del vector a buscar, con terminador "
        << TERMINADOR << "\n"
        << "A continuaci�n introduzca  los caracteres del texto,"
        << " usando el mismo terminador.\n\n";

   // Introduccion de Datos

   car = cin.get();
   util_a_buscar = 0;

   while (car != TERMINADOR && util_a_buscar < NUM_CARACT_ASCII){
      a_buscar[util_a_buscar] = car;
      car = cin.get();
      util_a_buscar++;
   }

   car = cin.get();
   util_texto = 0;

   while (car != TERMINADOR && util_texto < MAX_NUM_CARACT){
      texto[util_texto] = car;
      car = cin.get();
      util_texto++;
   }


   //Computo de Datos

   /*//Metodo 1:
   for(int i=0;i<NUM_CARACT_ASCII;i++){
         car=i;
         for(int j=0;j<util_texto;j++)
            if(car==texto[j])
               frecuencias[i]++;
   }

   //Salida de Datos

   for(int j=0;j<util_a_buscar;j++)
      for(int i=0;i<NUM_CARACT_ASCII;i++)
         if(a_buscar[j]==i)
            cout << i << " : " << frecuencias[i] << endl;

   */
   //Metodo 2:

   for(int j=0;j<util_a_buscar;j++)
         for(int i=0;i<util_texto;i++)
            if(a_buscar[j]==texto[i])
               frecuencias[j]++;

   //Salida de Datos

   for(int j=0;j<util_a_buscar;j++)
      cout << j << " : " << frecuencias[j] << endl;

   /*
   Ja@Juan Carlos Cubero@�

   J: 1
   a: 2
   */
}


