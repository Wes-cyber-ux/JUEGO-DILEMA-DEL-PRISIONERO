// ============================================================================
// tipos_torneo.h
// Constantes globales y la estructura Estrategia que comparten todos los
// modulos del torneo del Dilema del Prisionero Iterado.
// ============================================================================
#ifndef TIPOS_TORNEO_H
#define TIPOS_TORNEO_H

#include <string>

// Cantidad de estrategias que compiten (6 obligatorias + 2 propias)
const int NUM_ESTRATEGIAS = 8;

// Limites del numero de rondas por partida.
// El enunciado exige mas de 200 rondas; el maximo define el tamano de los
// arreglos de historial que se usan en cada partida.
const int MIN_RONDAS = 201;
const int MAX_RONDAS = 1000;

// Tipo "puntero a funcion de decision".
// Todas las estrategias tienen esta misma firma, asi la partida puede llamar
// a cualquiera de ellas sin saber cual es.
//   numeroRonda       : ronda actual (empieza en 1)
//   historialPropio   : jugadas anteriores de la estrategia (posicion 0 = ronda 1)
//   historialOponente : jugadas anteriores del oponente
// Devuelve 'C' (cooperar) o 'T' (traicionar).
typedef char (*FuncionDecision)(int numeroRonda,
                                const char historialPropio[],
                                const char historialOponente[]);

// Toda la informacion de una estrategia dentro del torneo
struct Estrategia
{
    int             id;        // posicion de la estrategia en el arreglo
    std::string     nombre;
    FuncionDecision decidir;   // funcion que elige 'C' o 'T' en cada ronda

    int puntajeTotal;                     // suma de puntos de todas sus partidas
    int puntosContra[NUM_ESTRATEGIAS];    // puntos obtenidos contra cada rival

    int vecesC;                // total de veces que eligio cooperar
    int vecesT;                // total de veces que eligio traicionar

    int victorias;             // partidas con mas puntos que el rival
    int derrotas;              // partidas con menos puntos que el rival
    int empates;               // partidas con los mismos puntos

    double porcentajeC;        // % de cooperacion en todo el torneo
    double porcentajeT;        // % de traicion en todo el torneo
};

#endif // TIPOS_TORNEO_H
