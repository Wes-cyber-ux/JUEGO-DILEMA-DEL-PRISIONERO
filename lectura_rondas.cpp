// ============================================================================
// lectura_rondas.cpp
// ============================================================================
#include "lectura_rondas.h"
#include "tipos_torneo.h"

#include <iostream>
#include <limits>

using namespace std;

int leerNumeroRondas()
{
    int numeroRondas = 0;
    bool entradaValida = false;

    while (!entradaValida)
    {
        cout << "Ingrese el numero de rondas por partida (entre "
             << MIN_RONDAS << " y " << MAX_RONDAS << "): ";
        cin >> numeroRondas;

        if (cin.fail())
        {
            // Se escribio algo que no es un numero: se limpia el error de cin
            // y se descarta lo que quedo en la linea para volver a preguntar.
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida. Debe ingresar un numero entero.\n";
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (numeroRondas < MIN_RONDAS || numeroRondas > MAX_RONDAS)
            {
                cout << "El numero de rondas debe ser mayor a 200 y como maximo "
                     << MAX_RONDAS << ".\n";
            }
            else
            {
                entradaValida = true;
            }
        }
    }

    return numeroRondas;
}
