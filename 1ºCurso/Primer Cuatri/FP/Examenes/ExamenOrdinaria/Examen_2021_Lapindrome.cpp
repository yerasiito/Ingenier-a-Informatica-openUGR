//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programaci�n
// ETS Inform�tica y Telecomunicaciones
// Universidad de Granada
// Departamento de Ciencias de la Computaci�n e Inteligencia Artificial
// Autor: Juan Carlos Cubero
//
//////////////////////////////////////////////////////////////////////////

// Examen 2021 Enero. Palisim�trica o Lap�ndrome

/*
Explicaci�n de la soluci�n:
   
   C�mo calcular fin_izda e ini_dcha:
   
      mitad = utilizados/2;
      fin_izda = mitad - 1;

      if (utilizados % 2 == 0)
         ini_dcha = mitad;
      else
         ini_dcha = mitad + 1;
      
   El procesamiento de la parte izquierda y derecha lo podemos
   hacer de dos formas -a) y b)- Ambas son completamente v�lidas:
   
   a) Podemos trabajar con dos secuencias izda, dcha
      (obviamente, ser�n locales al m�todo EsLapindrome):
    
      izda = Subsecuencia(0, fin_izda)
      dcha = Subsecuencia(ini_dcha + 1 , utilizados - 1)
      
      for (int i=0 ; i<=fin_izda && es_lap; i++)           
         char a_buscar = izda.Elemento(i);

         es_lap = izda.NumOcurrencias(a_buscar) 
                  == 
                  dcha.NumOcurrencias(a_buscar);
   
      Es obvio que NumOcurrencias es un m�todo necesario para 
      as� no repetir el c�digo que cuenta el n�mero de ocurrencias
      de un car�cter en una secuencia.
            
   b) En vez de construir las secuencias izda y dcha
      podemos definir el m�todo NumOcurrencias
      para que trabaje s�lo en una parte de la secuencia.
      Para ello, basta definirlo pas�ndole como par�metros
      los �ndices inicial y final que delimitan la parte 
      de la secuencia en la que voy a buscar:
 
      for (int i=0 ; i<=fin_izda && es_lap; i++)
         es_lap = NumOcurrencias(v[i], 0, fin_izda)
                  ==
                  NumOcurrencias(v[i], ini_dcha, utilizados-1);    
   
   Independientemente de si es a) o b), para no volver a contar 
   la frecuencia de un car�cter que ya se hubiese contado anteriormente,
   podemos hacer lo siguiente:
   
   1) O bien usamos un vector de bool en el que el �ndice 
      de la componente a modificar se obtiene a partir 
      del orden del car�cter actual

      const int NUM_CAR = 256;
      bool procesados[NUM_CAR];
      
      procesados[0] ser� true si 'a' ha sido procesada
      procesados[1] ser� true si 'b' ha sido procesada
      ...

      'a' -> 0
      'b' -> 1
      ...
      
      En general:
      
      car -> car - 'a'
   
   2) O bien usamos una secuencia de caracteres que almacene los 
      caracteres que ya hayan sido procesados 
      
      SecuenciaCaracteres procesados;
      
      Si ya han sido procesadas la 'g' y la 'k', 
      la secuencia procesados contendr� {'g', 'k'}
   
   Podemos combinar a) y b) con 1) y 2) como queramos.
   Por ejemplo, la combinaci�n de a) con 1) ser�a:
   
      izda = Subsecuencia(0, fin_izda)
      dcha = Subsecuencia(ini_dcha + 1 , utilizados - 1)
      
      for (int i...
         char a_buscar = izda.Elemento(i);
         int indx = a_buscar - 'a';

         if (!procesados[indx])
            es_lap = izda.NumOcurrencias(a_buscar) 
                     == 
                     dcha.NumOcurrencias(a_buscar);
            procesados[indx] = true;   
              
              
   La combinaci�n de b) con 2) ser�a:
   
      for (int i...
         char a_buscar = v[i];
         
         if (-1 == procesados.PrimeraOcurrencia(a_buscar)) {
            es_lap = NumOcurrencias(v[i], 0, fin_izda)
                     ==
                     NumOcurrencias(v[i], ini_dcha, utilizados-1); 
            procesados.Aniade(a_buscar);


   Como detalle final, la ejecuci�n de NumOcurrencias podr�a realizarse
   en la parte izquierda desde la posici�n i (en vez desde cero)
   Incluso podr�amos empezar la ejecuci�n de NumOcurrencias en la parte
   derecha desde una posici�n m�s avanzada de la mitad: 
   podr�amos empezar desde ini_dcha + el n�mero de elementos 
   que ya han sido a�adidos a la secuencia procesados.
   En cualquier caso, es una mejora muy marginal que no merece la pena
   implementarla.
*/
     
#include <iostream>
#include <string>
using namespace std;

class SecuenciaCaracteres{
private:
   static const int TAMANIO = 500;  
   char v[TAMANIO];
   int utilizados;
   
   bool EsCorrectaPos(int indice){
      return 0 <= indice && indice < utilizados;
   }
public:
   SecuenciaCaracteres()
      :utilizados(0) {
   }
   
   int Utilizados(){
      return utilizados;
   }
   
   int Capacidad(){
      return TAMANIO;
   }
   
   void EliminaTodos(){
      utilizados = 0;
   }
   
   void Aniade(char nuevo){
      if (utilizados < TAMANIO){
         v[utilizados] = nuevo;
         utilizados++;
      }
   }
   
   void Modifica(int posicion, char nuevo){
      if (EsCorrectaPos(posicion))      
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

      cadena.reserve(utilizados);

      for (int i=0; i < utilizados; i++)
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
      return PrimeraOcurrenciaEntre (0, utilizados - 1, buscado);
   }
   
   //////////////////////////////////////////////////////////////////
   // EXAMEN
   //////////////////////////////////////////////////////////////////

   
   SecuenciaCaracteres Subsecuencia(int pos_ini, int pos_fin){
      SecuenciaCaracteres Subsecuencia;
      
      for (int i=pos_ini; i<=pos_fin; i++)
         Subsecuencia.Aniade(v[i]);
      
      return Subsecuencia;
   }
   
   int NumOcurrencias(char car, int desde, int hasta){
      int num_ocurrencias;
            
      num_ocurrencias = 0;

      for (int i=desde; i<=hasta; i++)
         if (v[i]==car)
            num_ocurrencias++;
         
      return num_ocurrencias;
   }

   int NumOcurrencias(char car){
      return NumOcurrencias(car, 0, utilizados - 1);
   }
   
   
   bool EsLapindrome_vs_a_1(){
      bool es_lap = true;
      const int NUM_CAR = 256;
      bool procesados[NUM_CAR];
      int mitad, fin_izda, ini_dcha;
      SecuenciaCaracteres izda, dcha;
         
      for (int i=0; i<NUM_CAR; i++)
         procesados[i] = false;
      
      mitad = utilizados/2;
      fin_izda = mitad - 1;

      if (utilizados % 2 == 0)
         ini_dcha = mitad;
      else
         ini_dcha = mitad + 1;
      
      izda = Subsecuencia(0, fin_izda);
      dcha = Subsecuencia(ini_dcha, utilizados - 1);
      
      for (int i=0 ; i<=fin_izda && es_lap; i++){
         char a_buscar = izda.Elemento(i);
         int indx = a_buscar - 'a';

         if (!procesados[indx]){
            es_lap = izda.NumOcurrencias(a_buscar) 
                     == 
                     dcha.NumOcurrencias(a_buscar);
                     
            procesados[indx] = true;     
         } 
      }    
      
      return es_lap;
   }
   
   
   bool EsLapindrome_vs_b_2(){
      bool es_lap = true;
      SecuenciaCaracteres procesados;
      int mitad = utilizados/2;
      int fin_izda, ini_dcha;
      
      fin_izda = mitad - 1;

      if (utilizados % 2 == 0)
         ini_dcha = mitad;
      else
         ini_dcha = mitad + 1;
         
      
      for (int i=0 ; i<=fin_izda && es_lap; i++){
         char a_buscar = v[i];
         
         if (-1 == procesados.PrimeraOcurrencia(a_buscar)) {         
            es_lap = NumOcurrencias(a_buscar, 0, fin_izda)
                     ==
                     NumOcurrencias(a_buscar, ini_dcha, utilizados-1);
                     
            procesados.Aniade(a_buscar);
         }    
      }
      
      return es_lap;
   }
};


class LectorSecuenciaCaracteres{
private:
   char terminador;
   int tope;
   int capacidad_maxima;

   bool FlujoAbierto(){
      return !cin.fail();
   }
   
public:
   LectorSecuenciaCaracteres(){
      ResetRestricciones();
   }
   
   void SetTerminador (char terminador_entrada){
      terminador = terminador_entrada;
   }
   
   void SetTope(int num_valores_a_leer){
      if (0 < num_valores_a_leer && num_valores_a_leer <= capacidad_maxima)
         tope = num_valores_a_leer;
   }
   
   void ResetRestricciones(){
      SecuenciaCaracteres cualquiera;
      
      capacidad_maxima = cualquiera.Capacidad();
      tope = capacidad_maxima;
      terminador = '\n';
   }
   
   SecuenciaCaracteres Lee(){   
      SecuenciaCaracteres a_leer;
      char caracter;      
      bool parar_lectura;
      bool es_terminador;
      int total_leidos = 0;
      
      do{            
         if (FlujoAbierto()){            
            caracter = cin.get();  
            total_leidos++;
            es_terminador = caracter == terminador;
                                  
            if (!es_terminador) 
               a_leer.Aniade(caracter); 
            
            parar_lectura = es_terminador || total_leidos == tope;                           
         }
      }while (!parar_lectura);
      
      return a_leer;
   }
};



int main(){
   SecuenciaCaracteres sec;
   LectorSecuenciaCaracteres lector;
   
   lector.SetTerminador('#');
   sec = lector.Lee(); 
   
   if (sec.EsLapindrome_vs_b_2())
      cout << "\nEs Lap�ndrome";
   else
      cout << "\nNo es lap�ndrome";    
     
   cout << "\n\n";   
   
   // acbbababac#  SI
   // acbbagbabac#  SI
   // acbbaaabac#  NO
}
