#include <iostream>

double capital;
double interes;
double total;

int main()
{
    cout <<"Este programa calcula el capital total dado un interes bancario\n\n";

    cout << "Introduzca su capital: ";
    cin >> capital;
    cout << "introduzca el interes: ";
    cin >> interes;

    total = capital + capital*(interes/100);
    cout << "Su capital total es de " << total;

    /*En la asignaci�n que calcula la variable total, �se podr�a sustituir dicha variable por capital?*/

    /**Si cambiamos la variable por capital, el c�digo NO funcionar�. Si queremos ahorrarnos la variable total,
    *debemos introducir los calculos dentro del cout.*/

}
