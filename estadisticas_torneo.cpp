// ============================================================================
// estadisticas_torneo.cpp
// ============================================================================
#include "estadisticas_torneo.h"

void calcularEstadisticas(Estrategia estrategias[])
{
    for (int i = 0; i < NUM_ESTRATEGIAS; i++)
    {
        estrategias[i].victorias = 0;
        estrategias[i].derrotas  = 0;
        estrategias[i].empates   = 0;

        // Se compara lo que i saco contra j con lo que j saco contra i
        for (int j = 0; j < NUM_ESTRATEGIAS; j++)
        {
            if (j == i)
            {
                continue;   // no hubo partida contra si misma
            }

            long long misPuntos   = estrategias[i].puntosContra[j];
            long long puntosRival = estrategias[j].puntosContra[i];

            if (misPuntos > puntosRival)
            {
                estrategias[i].victorias++;
            }
            else if (misPuntos < puntosRival)
            {
                estrategias[i].derrotas++;
            }
            else
            {
                estrategias[i].empates++;
            }
        }

        // Porcentajes sobre el total de jugadas hechas en el torneo
        long long totalJugadas = estrategias[i].vecesC + estrategias[i].vecesT;
        if (totalJugadas > 0)
        {
            estrategias[i].porcentajeC = 100.0 * estrategias[i].vecesC / totalJugadas;
            estrategias[i].porcentajeT = 100.0 * estrategias[i].vecesT / totalJugadas;
        }
    }
}

void ordenarRanking(const Estrategia estrategias[], int ranking[])
{
    // Se ordenan los indices y no las estructuras, asi estrategias[] no cambia
    // y cada id sigue en su misma posicion.
    for (int i = 0; i < NUM_ESTRATEGIAS; i++)
    {
        ranking[i] = i;
    }

    // Ordenamiento burbuja de mayor a menor puntaje
    for (int pasada = 0; pasada < NUM_ESTRATEGIAS - 1; pasada++)
    {
        for (int k = 0; k < NUM_ESTRATEGIAS - 1 - pasada; k++)
        {
            long long puntajeActual    = estrategias[ranking[k]].puntajeTotal;
            long long puntajeSiguiente = estrategias[ranking[k + 1]].puntajeTotal;

            if (puntajeActual < puntajeSiguiente)
            {
                int temporal    = ranking[k];
                ranking[k]      = ranking[k + 1];
                ranking[k + 1]  = temporal;
            }
        }
    }
}
