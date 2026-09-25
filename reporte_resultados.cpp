// ============================================================================
// reporte_resultados.cpp
// ============================================================================
#include "reporte_resultados.h"

#include <iostream>
#include <iomanip>

using namespace std;

// Imprime una linea separadora de guiones
void mostrarSeparador()
{
    cout << "------------------------------------------------------------------------------\n";
}

void mostrarDetalleEstrategia(const Estrategia estrategias[], int indice)
{
    const Estrategia &estrategia = estrategias[indice];

    cout << "\nEstrategia: " << estrategia.nombre << "\n\n";

    // Puntos contra cada rival (se salta a si misma)
    for (int j = 0; j < NUM_ESTRATEGIAS; j++)
    {
        if (j == indice)
        {
            continue;
        }
        cout << "  Contra " << left << setw(22) << (estrategias[j].nombre + ":")
             << right << setw(6) << estrategia.puntosContra[j] << " puntos\n";
    }

    cout << "\n  " << left << setw(29) << "PUNTOS TOTALES:"
         << right << setw(6) << estrategia.puntajeTotal << "\n\n";

    cout << "  Partidas ganadas:    " << estrategia.victorias << "\n";
    cout << "  Partidas perdidas:   " << estrategia.derrotas  << "\n";
    cout << "  Partidas empatadas:  " << estrategia.empates   << "\n";
    cout << "  Veces que eligio C:  " << estrategia.vecesC    << "\n";
    cout << "  Veces que eligio T:  " << estrategia.vecesT    << "\n";
    cout << fixed << setprecision(2);
    cout << "  % de cooperacion:    " << estrategia.porcentajeC << " %\n";
    cout << "  % de traicion:       " << estrategia.porcentajeT << " %\n";
    mostrarSeparador();
}

void mostrarDetalleTorneo(const Estrategia estrategias[], const int ranking[])
{
    cout << "\n==================== DETALLE POR ESTRATEGIA ====================\n";
    mostrarSeparador();
    for (int puesto = 0; puesto < NUM_ESTRATEGIAS; puesto++)
    {
        mostrarDetalleEstrategia(estrategias, ranking[puesto]);
    }
}

void mostrarRanking(const Estrategia estrategias[], const int ranking[], int numeroRondas)
{
    cout << "\n======================== RANKING FINAL ========================\n";
    cout << "(" << NUM_ESTRATEGIAS << " estrategias, " << numeroRondas
         << " rondas por partida)\n\n";

    cout << left << setw(6) << "Pos" << setw(22) << "Estrategia"
         << right << setw(8) << "Puntos"
         << setw(5) << "G" << setw(5) << "P" << setw(5) << "E"
         << setw(10) << "% C" << setw(10) << "% T" << "\n";
    mostrarSeparador();

    cout << fixed << setprecision(2);
    for (int puesto = 0; puesto < NUM_ESTRATEGIAS; puesto++)
    {
        const Estrategia &estrategia = estrategias[ranking[puesto]];

        cout << left << setw(6) << (puesto + 1) << setw(22) << estrategia.nombre
             << right << setw(8) << estrategia.puntajeTotal
             << setw(5) << estrategia.victorias
             << setw(5) << estrategia.derrotas
             << setw(5) << estrategia.empates
             << setw(10) << estrategia.porcentajeC
             << setw(10) << estrategia.porcentajeT << "\n";
    }
    mostrarSeparador();
    cout << "G = partidas ganadas, P = perdidas, E = empatadas\n";
}

void mostrarGanador(const Estrategia estrategias[], const int ranking[])
{
    int puntajeMaximo = estrategias[ranking[0]].puntajeTotal;

    cout << "\n*** GANADORA DEL TORNEO: ";

    // Si varias estrategias tienen el puntaje maximo, se muestran todas
    cout << estrategias[ranking[0]].nombre;
    for (int puesto = 1; puesto < NUM_ESTRATEGIAS; puesto++)
    {
        if (estrategias[ranking[puesto]].puntajeTotal == puntajeMaximo)
        {
            cout << " y " << estrategias[ranking[puesto]].nombre;
        }
    }

    cout << " con " << puntajeMaximo << " puntos ***\n\n";
}
