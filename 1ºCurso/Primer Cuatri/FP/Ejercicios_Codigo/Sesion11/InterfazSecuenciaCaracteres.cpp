//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programaci�n
// ETS Inform�tica y Telecomunicaciones
// Universidad de Granada
// // Don Oreo
//
//////////////////////////////////////////////////////////////////////////

//Interfaz Secuencia Caracteres
/*
Se quiere definir una clase SecuenciaCaracteres similar a la clase string para
manipular secuencias de caracteres (de datos de tipo char).
Esto es una secuencia de caracteres
Como dato miembro privado, se recomienda usar un vector de caracteres. Ya sabemos
que debemos reservar memoria suficiente. Supondremos que el m�ximo ser� 100. En
vez de usar el literal 100, mejor usamos una constante. En ese caso, C++ obliga a que
sea una constante est�tica (si a�n no ha visto las constantes est�ticas en clase de
Teor�a, no se preocupe ya que no se le pide que el programa compile). Nos quedar�a
lo siguiente:

private:
   static const int TAM = 100;
   char caracteres[TAM];
Se proponen dos alternativas para marcar el bloque del vector que se va a usar:
� Usar un terminador fijo, por ejemplo, #, al final del bloque usado. En el ejemplo
anterior, el vector caracteres contendr�a:
'E' 's' 't' 'o' ' ' 'e' 's' .... 'r 'e' 's' '#' ? ? .... ?
� Usar un dato miembro privado utilizados que nos diga cu�ntos elementos
estamos usando en cada momento. En el ejemplo anterior, utilizados valdr�a
35.
�Qu� opci�n le parece m�s adecuada? �Por qu�?
El mejor es el segundo ya que el util es m�s manejable que el TERMINADOR
�Qu� m�todos definir�a para manipular la secuencia? Al menos debe definir las cabeceras de los m�todos para realizar lo siguiente:
a) M�todo Aniade para a�adir un car�cter al final de la secuencia.
Tenga en cuenta que a una variable cadena de tipo string se le puede asignar
directamente cadena = "Hola". Sin embargo, eso no lo sabemos hacer por
ahora con objetos de nuestras propias clases. Por lo tanto, la �nica forma de
a�adir caracteres a un objeto de la clase SecuenciaCaracteres ser�a hacerlo
de uno en uno. As� pues, llamando a un m�todo Aniade, a�adir�amos la 'H',
luego la 'o' y as� sucesivamente.
b) M�todo Utilizados para obtener la longitud actual de la secuencia (el n�mero
de caracteres que contiene)
c) M�todo Invierte para invertir la secuencia. En el ejemplo anterior, la secuencia
se quedar�a en:
seretcarac ed aicneuces anu se otsE
d) M�todo PrimeraOcurrencia para buscar la primera ocurrencia de un car�cter.
e) M�todo EliminaOcurrencias para eliminar las ocurrencias de un car�cter.
Por ejemplo, despu�s de eliminar el car�cter 'a', la secuencia quedar�a as�:
Esto es un secuenci de crcteres
*/
#include <iostream>
using namespace std;

class SecuenciaCaracteres{
private:
   static const int TAMANIO = 100;
   char caracteres[TAMANIO];
   int utilizados = 0;
public:
   void Aniade(char car){
      caracteres[utilizados] = car;
      utilizados++;
   }

   int Utilizados(){
      return utilizados;
   }

   char Elemento(int posicion){
      return caracteres[posicion];
   }

   void Invierte(){
      char secuencia[TAMANIO];
      int pos;
      for(int i = 0; i <= utilizados; i++)
         secuencia[i] = caracteres[i];

      pos = 0;
      for(int j = utilizados-1; j >= 0; j--){
         caracteres[pos] = secuencia[j];
         pos++;
      }
      cout << "\n";
      for(int i = 0; i < utilizados; i++)
         cout << caracteres[i];
   }

   int PrimeraOcurrencia(char car){
      bool encontrado = 0;
      int pos_ocurrencia = -1;
      for(int i = 0; i < utilizados && ! encontrado; i++){
         if(caracteres[i] == car){
            pos_ocurrencia = i+1;
            encontrado = true;
         }
      }
   return pos_ocurrencia;
   }
   void EliminaOcurrencias(char a_borrar){
      char secuencia[TAMANIO];
      int pos;

      pos = 0;
      for(int i = 0; i < utilizados; i++){
         if(caracteres[i] != a_borrar ){
            secuencia[pos] = caracteres[i];
            pos++;
         }
      }
      utilizados = pos;
      cout << "\n";
      for(int i = 0; i < utilizados; i++){
         caracteres[i] = secuencia[i];
         cout << caracteres[i];
      }
   }

   void ImprimeSecuencia(){
      for(int i=0; i<utilizados; i++)
         cout << caracteres[i];
   }

};

int main(){

   SecuenciaCaracteres Prueba;

   Prueba.Aniade('H');
   Prueba.Aniade('o');
   Prueba.Aniade('l');
   Prueba.Aniade('a');

   Prueba.ImprimeSecuencia();

   Prueba.EliminaOcurrencias('H');

   return 0;
}
