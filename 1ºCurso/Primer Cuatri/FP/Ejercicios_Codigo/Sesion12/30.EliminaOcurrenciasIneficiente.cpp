//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programaci�n
// ETS Inform�tica y Telecomunicaciones
// Universidad de Granada
// Autor: Don Oreo
//
//////////////////////////////////////////////////////////////////////////

// Secuencia de caracteres

// IMPORTANTE:
// La clase SecuenciaCaracteres es "at�pica" en el sentido de que es una clase
// con muchos m�todos. El principio de responsabilidad �nica nos dice que
// las clases deben tener una �nica responsabilidad y, por tanto, no suelen tener
// un n�mero elevado de m�todos.
// Sin embargo, a veces nos encontramos con este tipo de clases "gen�ricas"
// En este caso, la responsabilidad es manejar una secuencia de caracteres
// lo que conlleva la definici�n de numerosos m�todos
// La librer�a est�ndar STL contiene una clase (plantilla para ser m�s exactos)
// similar a esta clase: es la plantilla denominada "vector"

#include <iostream>
#include <string>
using namespace std;

class SecuenciaCaracteres{
private:
   static const int TAMANIO = 2e6;  // 2e6 es un real (dos millones)
                                    // -> casting autom�tico a int

                                    // Para poder dimensionar con un tama�o
                                    // tan grande, hay que cambiar unos par�metros
                                    // del compilador:
                                    // Herramientas -> Opciones del Compilador ->
                                    // Compilador -> A�adir las siguientes opciones
                                    // -Wl,--stack,26000000
   char v[TAMANIO];
   int util;

   void IntercambiaComponentesDirectamente(int pos_izda, int pos_dcha){
      char intercambia;

      intercambia = v[pos_izda];
      v[pos_izda] = v[pos_dcha];
      v[pos_dcha] = intercambia;
   }

   bool EsCorrectaPosicion(int indice){
      return 0 <= indice && indice < util;
   }
public:
   SecuenciaCaracteres()
      :util(0) {
   }

   int Utilizados(){
      return util;
   }

   int Capacidad(){
      return TAMANIO;
   }

   void EliminaTodos(){
      util = 0;
   }

   void Aniade(char nuevo){
      if (util < TAMANIO){
         v[util] = nuevo;
         util++;
      }
   }

   void Modifica(int posicion, char nuevo){
      if (EsCorrectaPosicion(posicion))
         v[posicion] = nuevo;
   }

   char Elemento(int indice){
      return v[indice];
   }

   string ToString(){
      // Si el n�mero de caracteres en memoria es muy grande,
      // es mucho m�s eficiente reservar memoria previamente
      // y usar push_back

      string cadena;

      cadena.reserve(util);

      for (int i=0; i < util; i++)
         cadena.push_back(v[i]);
         //cadena = cadena + v[i]  <- Evitarlo. Muy ineficiente para tama�os grandes;

      return cadena;
   }

   int PrimeraOcurrenciaEntre (int pos_izda, int pos_dcha, char buscado){
      int i = pos_izda;
      bool encontrado = false;

      while (i <= pos_dcha  &&  !encontrado)
         if (v[i] == buscado)
            encontrado = true;
         else
            i++;

      if (encontrado)
         return i;
      else
         return -1;
   }

   int PrimeraOcurrencia (char buscado){
      return PrimeraOcurrenciaEntre (0, util - 1, buscado);
   }


   /////////////////////////////////////////////////////////////
   // B�squedas

   // Precond: 0 <= izda <= dcha < util
   int PosMinimoEntre(int izda, int dcha){
      int pos_minimo = -1;
      char minimo;

      minimo = v[izda];
      pos_minimo = izda;

      for (int i = izda+1 ; i <= dcha ; i++)
         if (v[i] < minimo){
            minimo = v[i];
            pos_minimo = i;
         }

      return pos_minimo;
   }

   int PosMinimo(){
      return PosMinimoEntre(0, util - 1);
   }

   int BusquedaBinaria (char buscado){
      int izda, dcha, centro;
      bool encontrado = false;

      izda = 0;
      dcha = util - 1;
      centro = (izda + dcha) / 2;

      while (izda <= dcha  &&  !encontrado){
         if (v[centro] == buscado)
            encontrado = true;
         else if (buscado < v[centro])
            dcha = centro - 1;
         else
            izda = centro + 1;

         centro = (izda + dcha) / 2;
      }

      if (encontrado)
         return centro;
      else
         return -1;
   }


   /////////////////////////////////////////////////////////////
   // Recorridos que modifican las componentes

   // Inserta un valor en la posici�n especificada
   void Inserta(int pos_insercion, char nuevo){
      if (util < TAMANIO  &&  pos_insercion >= 0
         &&  pos_insercion <= util){

         for (int i = util ; i > pos_insercion ; i--)
            v[i] = v[i-1];

         v[pos_insercion] = nuevo;
         util++;
      }
   }

   /*
   Tipos de borrados:
      - L�gico
         Usar un valor de componente especial y marcar la componente con dicho valor
         Un vector de edades -> valor -1
         Un vector de caracteres alfab�ticos -> '@'
         Ventajas: Muy r�pido

         Inconvenientes: Cualquier procesado posterior del vector
         debe tratar las componentes marcadas de una forma especial

      - F�sico
         Implica desplazar 1 posici�n a la izquierda, todas las componentes que hay a la derecha de
         la que queremos borrar.

         Tiene justo las ventajas e incovenientes contrarias que el m�todo anterior.

       En esta versi�n, implementamos el borrado f�sico.
   */

   // Elimina una componente, dada por su posici�n
   void Elimina (int posicion){
      /*
      Algoritmo:

         Recorremos de izquierda a derecha toda las componentes
         que hay a la derecha de la posici�n a eliminar
            Le asignamos a cada componente la que hay a su derecha
      */
      if (posicion >= 0 && posicion < util){
         int tope = util-1;

         for (int i = posicion ; i < tope ; i++)
            v[i] = v[i+1];

         util--;
      }

      // Nota:

      // En vez de usar la asignaci�n
      //    v[i] = v[i+1];
      // tambi�n podr�amos haber puesto lo siguiente:
      //    Modifica(i, Elemento(i+1));
      // Hemos preferido acceder directamente a las componentes con la notaci�n en corchete
      // para aumentar la eficiencia del m�todo Elimina, ya que si el vector es muy grande
      // tendr� que realizar muchos desplazamientos y, por tanto, muchos accesos al m�todo
      // Elemento. En general, desde dentro de la clase, los m�todos de la clase Secuencia
      // acceder�n directamente a las componentes con la notaci�n corchete

      // Adem�s, cuando entramos en la funci�n Elimina, comprobamos con el condicional
      // que los accesos a los �ndices son correctos.
      // Si usamos el m�todo Modifica, volver�amos a comprobar lo mismo.

      // Nota:

      // �Y si en vez de asignar v[i] = v[i+1];
      // llamamos a IntercambiaComponentesDirectamente(i, i+1) ?
      // La componente se eliminar�a pero realizando el doble de asignaciones
      // Obviamente, no es necesario intercambiar las componentes.
      // �nicamente debemos ir asignando v[i] = v[i+1] de izquierda a derecha.
   }

   void EliminaOcurrencias(char a_borrar){
      for(int i = util; i >= 0; i--)
         if(v[i] == a_borrar)
            Elimina(i);

      cout << "El vector sin a_borrar: ";
      for(int i = 0; i < util; i++)
         cout << v[i];
   }

   /////////////////////////////////////////////////////////////
   // Algoritmos de ordenaci�n

   void Ordena_por_Seleccion(){
      int pos_min;

      for (int izda = 0 ; izda < util ; izda++){
         pos_min = PosMinimoEntre(izda, util - 1);
         IntercambiaComponentesDirectamente(izda, pos_min);
      }
   }

   void Ordena_por_Insercion(){
      int izda, i;
      char a_desplazar;

      for (izda=1; izda < util; izda++){
         a_desplazar = v[izda];

         for (i=izda; i > 0 && a_desplazar < v[i-1]; i--)
            v[i] = v[i-1];

         v[i] = a_desplazar;
      }
   }

   void InsertaOrdenadamente(char nuevo){
        int i;

        if (util > TAMANIO){
           for (i=util; i>0 && nuevo < v[i-1]; i--)
                v[i] = v[i-1];

           v[i] = nuevo;
           util++;
        }
   }


   void Ordena_por_Burbuja(){
      int izda, i;

      for (izda = 0; izda < util; izda++)
        for (i = util-1 ; i > izda ; i--)
          if (v[i] < v[i-1])
             IntercambiaComponentesDirectamente(i, i-1);
   }

   void Ordena_por_BurbujaMejorado(){
      int izda, i;
      bool cambio;

      cambio= true;

      for (izda=0; izda < util && cambio; izda++){
        cambio=false;

        for (i=util-1 ; i>izda ; i--)
          if (v[i] < v[i-1]){
             IntercambiaComponentesDirectamente(i, i-1);
             cambio=true;
          }
      }
   }

   void AniadeVarios(SecuenciaCaracteres nuevos){
      int totales_a_aniadir = nuevos.Utilizados();

      for (int i = 0; i < totales_a_aniadir; i++)
         Aniade(nuevos.Elemento(i)); // Es importante entender
   }


   SecuenciaCaracteres ToUpper(){
      SecuenciaCaracteres en_mayuscula;

      for(int i = 0; i < util; i++)
         en_mayuscula.Aniade(toupper(v[i]));

      return en_mayuscula;
   }
};

int main(){
   SecuenciaCaracteres cadena;
   char car,a_borrar;

   car = cin.get();
   while(car != '#'){     //Pide caracteres hasta introducir '#'
      cadena.Aniade(car);
      car = cin.get();
   }

   a_borrar = cin.get();

   cadena.EliminaOcurrencias(a_borrar);

   return 0;
}

