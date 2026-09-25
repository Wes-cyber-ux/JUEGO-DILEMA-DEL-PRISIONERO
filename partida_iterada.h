// ============================================================================
// partida_iterada.h
// Una partida: dos estrategias juegan numeroRondas rondas seguidas.
// ============================================================================
#ifndef PARTIDA_ITERADA_H
#define PARTIDA_ITERADA_H

#include "tipos_torneo.h"

// Enfrenta a estrategiaA contra estrategiaB durante numeroRondas rondas.
// Devuelve en puntosPartidaA / puntosPartidaB los puntos de cada una en esta
// partida, y suma a cada estrategia las veces que eligio C y T.
void ejecutarPartida(Estrategia &estrategiaA, Estrategia &estrategiaB, int numeroRondas,
                     int &puntosPartidaA, int &puntosPartidaB);

#endif // PARTIDA_ITERADA_H
