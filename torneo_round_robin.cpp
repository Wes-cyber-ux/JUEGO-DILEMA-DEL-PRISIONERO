// ============================================================================
// torneo_round_robin.cpp
// ============================================================================
#include "torneo_round_robin.h"
#include "partida_iterada.h"

void ejecutarTorneo(Estrategia estrategias[], int numeroRondas)
{
    // j empieza en i + 1: asi cada par se juega una sola vez y ninguna
    // estrategia juega contra si misma. Con 8 estrategias son 28 partidas.
    for (int i = 0; i < NUM_ESTRATEGIAS; i++)
    {
        for (int j = i + 1; j < NUM_ESTRATEGIAS; j++)
        {
            long long puntosI;
            long long puntosJ;
            ejecutarPartida(estrategias[i], estrategias[j], numeroRondas, puntosI, puntosJ);

            // Se guarda el resultado desde el punto de vista de ambas
            estrategias[i].puntosContra[j] = puntosI;
            estrategias[j].puntosContra[i] = puntosJ;

            estrategias[i].puntajeTotal += puntosI;
            estrategias[j].puntajeTotal += puntosJ;
        }
    }
}
