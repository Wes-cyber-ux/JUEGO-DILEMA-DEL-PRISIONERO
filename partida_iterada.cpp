// ============================================================================
// partida_iterada.cpp
// ============================================================================
#include "partida_iterada.h"
#include "matriz_pagos.h"

// Suma una jugada al contador de C o de T de la estrategia
void registrarJugada(Estrategia &estrategia, char jugada)
{
    if (jugada == 'C')
    {
        estrategia.vecesC++;
    }
    else
    {
        estrategia.vecesT++;
    }
}

void ejecutarPartida(Estrategia &estrategiaA, Estrategia &estrategiaB, int numeroRondas,
                     long long &puntosPartidaA, long long &puntosPartidaB)
{
    // Historial de jugadas de esta partida. Se crea de nuevo en cada partida,
    // asi ninguna estrategia "recuerda" lo que paso contra otro rival.
    // Como el numero de rondas no tiene maximo, su tamano se conoce recien
    // al ejecutar: por eso se reservan con new (memoria dinamica) y se
    // liberan con delete[] al terminar la partida.
    char *historialA = new char[numeroRondas];
    char *historialB = new char[numeroRondas];

    puntosPartidaA = 0;
    puntosPartidaB = 0;

    for (int ronda = 1; ronda <= numeroRondas; ronda++)
    {
        // Cada estrategia decide mirando su historial y el del rival.
        // Ambas deciden antes de guardar nada, asi ninguna ve la jugada
        // actual del otro (las decisiones son simultaneas).
        char jugadaA = estrategiaA.decidir(ronda, historialA, historialB);
        char jugadaB = estrategiaB.decidir(ronda, historialB, historialA);

        historialA[ronda - 1] = jugadaA;
        historialB[ronda - 1] = jugadaB;

        registrarJugada(estrategiaA, jugadaA);
        registrarJugada(estrategiaB, jugadaB);

        int puntosRondaA;
        int puntosRondaB;
        calcularPuntosRonda(jugadaA, jugadaB, puntosRondaA, puntosRondaB);

        puntosPartidaA += puntosRondaA;
        puntosPartidaB += puntosRondaB;
    }

    delete[] historialA;
    delete[] historialB;
}
