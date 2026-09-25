// ============================================================================
// estadisticas_torneo.h
// Estadisticas por estrategia y ranking final.
// ============================================================================
#ifndef ESTADISTICAS_TORNEO_H
#define ESTADISTICAS_TORNEO_H

#include "tipos_torneo.h"

// Calcula victorias, derrotas y empates (comparando los puntos de cada
// partida) y los porcentajes de cooperacion y traicion de cada estrategia.
void calcularEstadisticas(Estrategia estrategias[]);

// Llena ranking[] con los indices de las estrategias ordenados de mayor a
// menor puntajeTotal. ranking[0] es la ganadora del torneo.
void ordenarRanking(const Estrategia estrategias[], int ranking[]);

#endif // ESTADISTICAS_TORNEO_H
