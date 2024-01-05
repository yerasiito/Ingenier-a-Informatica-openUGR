//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programaci�n
// ETS Inform�tica y Telecomunicaciones
// Universidad de Granada
// Departamento de Ciencias de la Computaci�n e Inteligencia Artificial
// Autor: Juan Carlos Cubero
//
//////////////////////////////////////////////////////////////////////////

// Tablero EsHeterogeneo y EsHeterogeneoCompleto

#include <iostream>
#include <string>

using namespace std;


/*
Explicaci�n de la soluci�n:
   
   clase SecuenciaEnteros:
      A�adimos el m�todo Suma()

   clase Tablero:
      Las cabeceras de los m�todos son:
         bool EsHeterogeneo()
         bool EsHeterogeneoCompleto()
      
   Para implementar los m�todos anteriores 
   usamos una secuencia de enteros 
      sumas_col
   que contiene las sumas de las columnas
   
   a) Versi�n ineficiente -> Se calculan las sumas de TODAS las columnas
   
      bool EsHeterogeneo()
         for -i-
            suma = Columna(i).Suma()
            sumas_col.Aniade(suma)
            
         Si hay alg�n repetido en sumas_col,
            es_heterogeneo = false
      
      bool EsHeterogeneoCompleto()
         for -i- 
            suma = Columna(i).Suma()
            sumas_col.Aniade(suma)
         
         sumas_col.Ordena()
         Si hay alg�n elemento no consecutivo en sumas_col,
            es_heterogeneo = false
      
      Podemos apreciar que la primera parte de EsHeterogeneoCompleto es
      la misma que EsHeterogeneo:
      
         for -i-
            suma = Columna(i).Suma()
            sumas_col.Aniade(suma)
      
      Lo que hace el anterior c�digo es calcular una secuencia
      con las sumas de cada columna. Por lo tanto, para no repetir
      dicho c�digo, debemos construir dentro de la clase Tablero
      un m�todo que devuelva dicha secuencia:
      
         class Tablero{
            ...
            SecuenciaEnteros SumasCol() {
               SecuenciaEnteros sumas_col
               
               for -i-
                  suma = Columna(i).Suma()
                  sumas_col.Aniade(suma)
               
               return sumas_col
            }

      El m�todo puede ser privado o p�blico:
         
         int main(){
            ...
            SecuenciaEnteros sumas_columnas(tablero.SumasCol());  // :-)
 
      Nos quedar�a:
      
         bool EsHeterogeneo()
            sumas_col = SumasCol()
            
            Si hay alg�n repetido en sumas_col,
               es_heterogeneo = false
         
         bool EsHeterogeneoCompleto()
            sumas_col = SumasCol()
            sumas_col.Ordena()
            Si hay alg�n elemento no consecutivo en sumas_col,
               es_heterogeneo = false


   b) Versi�n eficiente -> Paramos de sumar columnas cuando 
                           una suma sea igual a alguna ya generada 
                           previamente      
      
      La idea es similar a lo visto en a)
      Pero ahora debemos parar en cuanto encontremos una suma
      ya generada previamente. 
      Para no repetir c�digo en los m�todos EsHeterogeneo y EsHeterogeneoCompleto, 
      seguimos necesitando un m�todo
         SecuenciaEnteros SumasCol()
      pero ahora el m�todo s�lo contendr� las sumas de las primeras
      columnas que sean distintas.
      En este caso ya no tiene sentido que sea p�blico ya que es 
      un m�todo muy espec�fico que hemos dise�ado para no repetir
      c�digo. 
      Ser� un tablero heterog�neo si el tama�o SumasCol es igual 
      a la dimensi�n del tablero
      
      Nos quedar�a:
         private:
         SecuenciaEnteros SumasCol() {     
            SecuenciaEnteros sumas_col
            
            for -i- && son_distintos
               suma = Columna(i).Suma()
               
               if (-1 == sumas_col.PrimeraOcurrencia(suma))
                  son_distintos = true
                  sumas_col.Aniade(suma)
            
            return sumas_col 
         }
   
         public:
         bool EsHeterogeneo()
            es_heterogeneo = SumasCol().Utilizados() == dimension
         
         bool EsHeterogeneoCompleto()
            sumas_col = SumasCol()
            es_heterogeneo = sumas_col.Utilizados() == dimension
            
            if (es_heterogeneo)
               sumas_col.Ordena()
               Si hay alg�n elemento no consecutivo en sumas_col,
                  es_heterogeneo = false
*/

class SecuenciaEnteros{
private:
   static const int TAMANIO = 50;
   int v[TAMANIO];
   int utilizados;
public:
   SecuenciaEnteros()
      :utilizados(0) {
   }
   
   int Utilizados(){
      return utilizados;
   }
   
   int Capacidad(){
      return TAMANIO;
   }
   
   void Aniade(int nuevo){
      if (utilizados < TAMANIO){
         v[utilizados] = nuevo;
         utilizados++;
      }

   }
   int Elemento(int indice){
      return v[indice];
   }
   
   void EliminaTodos(){
      utilizados = 0;
   }

   int Suma(){
      int suma = 0;
      
      for (int i=0; i<utilizados; i++)
         suma += v[i];
      
      return suma;
   }
   
   void Ordena(){
      int izda, i;
      long a_desplazar;

      for (izda=1; izda < utilizados; izda++){
         a_desplazar = v[izda];

         for (i=izda; i > 0 && a_desplazar < v[i-1]; i--)
            v[i] = v[i-1];

         v[i] = a_desplazar;
      }
   }
   
   int PrimeraOcurrenciaEntre (int pos_izda, int pos_dcha, long buscado){
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
   
   int PrimeraOcurrencia (long buscado){
      return PrimeraOcurrenciaEntre (0, utilizados - 1, buscado);
   }
   
};


class Tablero{
private:
   static const int MAX = 40;
   int t[MAX][MAX];
   int dimension;
   
   // Calcula las sumas de las columnas, 
   // mientras �stas sean distintas
   SecuenciaEnteros SumasCol(){
      SecuenciaEnteros sumas_col;
      int suma;
      
      bool son_distintos = true;
      
      for (int col=0; col<dimension && son_distintos; col++){
         suma = Columna(col).Suma();
         son_distintos = -1 == sumas_col.PrimeraOcurrencia(suma);
         
         if (son_distintos)
            sumas_col.Aniade(suma); 
      }
      
      return sumas_col;
   }
   
public:
   // Prec: 0 < numero_de_columnas <= MAX(40)
   Tablero(int dimension_tablero)
      :dimension(dimension_tablero)
   { 
   }

   int Dimension(){
      return dimension;
   }
   
   int Elemento(int fil, int col){
      return t[fil][col];
   }
   
   void Modifica(int fil, int col, int valor){
      t[fil][col] = valor;
   }
   
   SecuenciaEnteros Fila(int fil){
      SecuenciaEnteros fila;

      for (int col = 0; col < dimension; col++)
         fila.Aniade(t[fil][col]);

      return fila;
   }
   
   SecuenciaEnteros Columna(int col){
      SecuenciaEnteros columna;

      for (int fil = 0; fil < dimension; fil++)
         columna.Aniade(t[fil][col]);

      return columna;
   }
   
   
   bool EsHeterogeneo(){
      return SumasCol().Utilizados() == dimension; 
   }
   
   bool EsHeterogeneoCompleto(){
      bool es_heterogeneo;
      SecuenciaEnteros sumas_col(SumasCol());
      
      es_heterogeneo = sumas_col.Utilizados() == dimension; 
      
      if (es_heterogeneo){
         sumas_col.Ordena();
         
         for (int i=0; i<dimension-1 && es_heterogeneo; i++)
            es_heterogeneo = sumas_col.Elemento(i)+1
                             == 
                             sumas_col.Elemento(i+1);
      }
      
      return es_heterogeneo;
   }
   
   SecuenciaEnteros DiagonalInversa(){
      SecuenciaEnteros diagonal;
      
      for (int i=0; i<dimension; i++)
         diagonal.Aniade(t[dimension - i - 1][i]);
         
      return diagonal;   
   }
   
   SecuenciaEnteros Diagonal(){
      SecuenciaEnteros diagonal;
      
      for (int i=0; i<dimension; i++)
         diagonal.Aniade(t[i][i]);
         
      return diagonal;   
   }
   
   string ToString(){
      string cadena;
      
      cadena.reserve(dimension * dimension);
      
      for (int i = 0; i < dimension; i++){
         cadena.push_back('\n');

         for (int j = 0; j < dimension; j++){
            cadena.append(to_string(t[i][j]));
            cadena.append(" ");
         }
      }

      return cadena;
   }
};

int main(){
   int dimension;
   int casilla;
   
   cin >> dimension;

   Tablero tablero(dimension);

   for (int i = 0; i < dimension; i++){
      for (int j = 0; j < dimension; j++){
         cin >> casilla;
         tablero.Modifica(i, j, casilla);
      }  
   }

   cout << "\n\n";
   cout << "Tabla original:\n";
   cout << tablero.ToString();
   cout << "\n\n";
   
   if (tablero.EsHeterogeneo()){
      cout << "\nEs heterog�neo";
      
      if (tablero.EsHeterogeneoCompleto())
         cout << "\nAdem�s, es completo";
   }
   else
      cout << "\nNo es heterog�neo";
}
// 4     15 2 12 4   1 14 10 5   8 9 3 16   11 13 6 7
// Heterog�neo pero no completo

// 3     9 8 6   0 2 3   3 2 5
// No es heterog�neo

// 3     9 8 6   0 2 3   2 2 1
// Heterog�neo completo
