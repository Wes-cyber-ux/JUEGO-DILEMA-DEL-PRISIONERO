// ============================================================================
// estrategias_juego.h
// Las 8 estrategias del torneo. Todas siguen la firma FuncionDecision
// (ver tipos_torneo.h) y devuelven 'C' o 'T'.
//
// Convencion de indices: la ronda N esta guardada en historial[N - 1],
// por lo tanto la jugada de la ronda anterior es historial[numeroRonda - 2].
// ============================================================================
#ifndef ESTRATEGIAS_JUEGO_H
#define ESTRATEGIAS_JUEGO_H

#include "tipos_torneo.h"

// ---- Estrategias obligatorias ----
char decidirSiempreCooperar  (int numeroRonda, const char historialPropio[], const char historialOponente[]);
char decidirSiempreTraicionar(int numeroRonda, const char historialPropio[], const char historialOponente[]);
char decidirAleatoria        (int numeroRonda, const char historialPropio[], const char historialOponente[]);
char decidirTitForTat        (int numeroRonda, const char historialPropio[], const char historialOponente[]);
char decidirVengativa        (int numeroRonda, const char historialPropio[], const char historialOponente[]);
char decidirOjoPorDosOjos    (int numeroRonda, const char historialPropio[], const char historialOponente[]);

// ---- Estrategias propias ----
char decidirPavlov           (int numeroRonda, const char historialPropio[], const char historialOponente[]);
char decidirSonda            (int numeroRonda, const char historialPropio[], const char historialOponente[]);

// Llena el arreglo con las 8 estrategias (id, nombre, funcion de decision)
// y deja todos sus contadores y puntajes en cero.
void inicializarEstrategias(Estrategia estrategias[]);

#endif // ESTRATEGIAS_JUEGO_H
