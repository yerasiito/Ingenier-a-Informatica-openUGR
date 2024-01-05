//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programaci�n
// ETS Inform�tica y Telecomunicaciones
// Universidad de Granada
// // Don Oreo
//
//////////////////////////////////////////////////////////////////////////

// Sistema de D'Hondt

#include <iostream>
using namespace std;

int main (){
	const int NUM_MAX_PARTIDOS = 10;
	int total_escanios, total_partidos, posicion_mayor_cociente, i, j;
	double mayor_cociente = -1;
	double numero_votos[NUM_MAX_PARTIDOS];
	double numero_escanios[NUM_MAX_PARTIDOS] = {0};
	double cociente_dhondt[NUM_MAX_PARTIDOS];

	cout << "�N�mero total de esca�os a distribuir?: ";
	cin >> total_escanios;
	cout << "�C�antos partidos han participado en las elecciones?: ";
	cin >> total_partidos;
	cout << "Introduzca por orden el n�mero de votos que ha obtenido cada partido: ";

	for (int i = 0 ; i < total_partidos ; i++){
		cin >> numero_votos[i];
	}

	for (i = 0 ; i < total_escanios ; i++){
		for (j = 0 ; j < total_partidos ; j++){
			cociente_dhondt[j] = numero_votos[j] / (numero_escanios[j] + 1);

			if (cociente_dhondt[j] > mayor_cociente){
				mayor_cociente = cociente_dhondt[j];
				posicion_mayor_cociente = j;
			}

		}
		mayor_cociente = -1;
		numero_escanios[posicion_mayor_cociente]++;
	}

	for (i = 0 ; i < total_partidos ; i++){
		cout << " " << numero_escanios[i];
	}

}
