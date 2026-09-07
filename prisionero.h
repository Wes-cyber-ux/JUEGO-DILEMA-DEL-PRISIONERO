#ifndef PRISIONERO_H
#define PRISIONERO_H

const int NUM_ESTRATEGIAS = 8;
const int NUM_RONDAS = 500;

const int E_SIEMPRE_COOPERAR   = 0;
const int E_SIEMPRE_TRAICIONAR = 1;
const int E_ALEATORIA          = 2;
const int E_TIT_FOR_TAT        = 3;
const int E_VENGATIVA          = 4;
const int E_OJO_POR_DOS_OJOS   = 5;
const int E_DETECTIVE          = 6;
const int E_UMBRAL_CONFIANZA   = 7;

const int PUNTOS_AMBOS_COOPERAN   = 3;
const int PUNTOS_TRAICIONA_GANA   = 5;
const int PUNTOS_COOPERA_PIERDE   = 0;
const int PUNTOS_AMBOS_TRAICIONAN = 1;

const int NUM_ENFRENTAMIENTOS =
    (NUM_ESTRATEGIAS * (NUM_ESTRATEGIAS - 1)) / 2;

#endif