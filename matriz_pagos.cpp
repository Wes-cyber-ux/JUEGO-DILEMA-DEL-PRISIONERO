// ============================================================================
// matriz_pagos.cpp
// ============================================================================
#include "matriz_pagos.h"

// Puntos de la matriz de pagos, con nombre para no dejar "numeros magicos"
const int PUNTOS_COOPERACION_MUTUA = 3;   // C-C
const int PUNTOS_TRAICION_EXITOSA  = 5;   // yo T, el C
const int PUNTOS_ENGANADO          = 0;   // yo C, el T
const int PUNTOS_TRAICION_MUTUA    = 1;   // T-T

void calcularPuntosRonda(char jugadaA, char jugadaB, int &puntosA, int &puntosB)
{
    if (jugadaA == 'C' && jugadaB == 'C')
    {
        puntosA = PUNTOS_COOPERACION_MUTUA;
        puntosB = PUNTOS_COOPERACION_MUTUA;
    }
    else if (jugadaA == 'C' && jugadaB == 'T')
    {
        puntosA = PUNTOS_ENGANADO;
        puntosB = PUNTOS_TRAICION_EXITOSA;
    }
    else if (jugadaA == 'T' && jugadaB == 'C')
    {
        puntosA = PUNTOS_TRAICION_EXITOSA;
        puntosB = PUNTOS_ENGANADO;
    }
    else
    {
        puntosA = PUNTOS_TRAICION_MUTUA;
        puntosB = PUNTOS_TRAICION_MUTUA;
    }
}
