// ============================================================================
// torneo_round_robin.h
// Torneo "todos contra todos": cada par de estrategias juega una sola vez.
// ============================================================================
#ifndef TORNEO_ROUND_ROBIN_H
#define TORNEO_ROUND_ROBIN_H

#include "tipos_torneo.h"

// Juega todas las partidas del torneo (E1 vs E2, pero no E2 vs E1, y nunca
// una estrategia contra si misma). Guarda los puntos de cada partida en
// puntosContra y acumula el puntajeTotal de cada estrategia.
void ejecutarTorneo(Estrategia estrategias[], int numeroRondas);

#endif // TORNEO_ROUND_ROBIN_H
