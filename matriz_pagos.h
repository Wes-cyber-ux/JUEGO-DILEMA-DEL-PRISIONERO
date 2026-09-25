// ============================================================================
// matriz_pagos.h
// Matriz de puntos del Dilema del Prisionero.
// ============================================================================
#ifndef MATRIZ_PAGOS_H
#define MATRIZ_PAGOS_H

// Calcula los puntos que gana cada jugador en una ronda segun sus jugadas.
//   C-C -> 3 y 3     C-T -> 0 y 5
//   T-C -> 5 y 0     T-T -> 1 y 1
void calcularPuntosRonda(char jugadaA, char jugadaB, int &puntosA, int &puntosB);

#endif // MATRIZ_PAGOS_H
