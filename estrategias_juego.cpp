// ============================================================================
// estrategias_juego.cpp
// Implementacion de las estrategias. Algunas no usan todos los parametros
// (por ejemplo Siempre Cooperar no mira el historial), pero todas reciben
// los mismos para poder guardarse en el mismo tipo de puntero a funcion.
// ============================================================================
#include "estrategias_juego.h"

#include <cstdlib>

using namespace std;

// ----------------------------------------------------------------------------
// 1. Siempre Cooperar: no importa lo que haga el oponente, siempre coopera.
// ----------------------------------------------------------------------------
char decidirSiempreCooperar(int numeroRonda, const char historialPropio[], const char historialOponente[])
{
    return 'C';
}

// ----------------------------------------------------------------------------
// 2. Siempre Traicionar: siempre traiciona.
// ----------------------------------------------------------------------------
char decidirSiempreTraicionar(int numeroRonda, const char historialPropio[], const char historialOponente[])
{
    return 'T';
}

// ----------------------------------------------------------------------------
// 3. Aleatoria: 50% de probabilidad de cooperar y 50% de traicionar.
// La semilla de rand() se fija una sola vez en main().
// ----------------------------------------------------------------------------
char decidirAleatoria(int numeroRonda, const char historialPropio[], const char historialOponente[])
{
    if (rand() % 2 == 0)
    {
        return 'C';
    }
    return 'T';
}

// ----------------------------------------------------------------------------
// 4. Tit for Tat: coopera en la ronda 1 y despues copia la jugada que hizo
// el oponente en la ronda anterior.
// ----------------------------------------------------------------------------
char decidirTitForTat(int numeroRonda, const char historialPropio[], const char historialOponente[])
{
    if (numeroRonda == 1)
    {
        return 'C';
    }
    return historialOponente[numeroRonda - 2];
}

// ----------------------------------------------------------------------------
// 5. Vengativa: coopera mientras el oponente nunca haya traicionado.
// Recorre todo el historial del oponente; si encuentra una sola 'T',
// traiciona (y como esa 'T' siempre seguira en el historial, traicionara
// en todas las rondas siguientes).
// ----------------------------------------------------------------------------
char decidirVengativa(int numeroRonda, const char historialPropio[], const char historialOponente[])
{
    for (int i = 0; i < numeroRonda - 1; i++)
    {
        if (historialOponente[i] == 'T')
        {
            return 'T';
        }
    }
    return 'C';
}

// ----------------------------------------------------------------------------
// 6. Ojo por Dos Ojos: coopera en las rondas 1 y 2. Desde la ronda 3 solo
// traiciona si el oponente traiciono en las DOS rondas anteriores; es mas
// tolerante que Tit for Tat porque perdona una traicion aislada.
// ----------------------------------------------------------------------------
char decidirOjoPorDosOjos(int numeroRonda, const char historialPropio[], const char historialOponente[])
{
    if (numeroRonda < 3)
    {
        return 'C';
    }

    char jugadaAnterior    = historialOponente[numeroRonda - 2];
    char jugadaAntepasada  = historialOponente[numeroRonda - 3];

    if (jugadaAnterior == 'T' && jugadaAntepasada == 'T')
    {
        return 'T';
    }
    return 'C';
}

// ----------------------------------------------------------------------------
// 7. ESTRATEGIA PROPIA: Ganar-Mantener, Perder-Cambiar (Pavlov)
//
// Descripcion: estrategia reactiva que evalua si su ultima jugada "le fue
//   bien" o "le fue mal". Si le fue bien, la repite; si le fue mal, la cambia.
//
// Reglas de comportamiento:
//   - Ronda 1: coopera.
//   - Desde la ronda 2 mira solo la ronda anterior:
//       Yo C, el C -> gane 3 (bien)  -> mantengo  -> C
//       Yo T, el C -> gane 5 (bien)  -> mantengo  -> T
//       Yo C, el T -> gane 0 (mal)   -> cambio    -> T
//       Yo T, el T -> gane 1 (mal)   -> cambio    -> C
//
// Algoritmo: las cuatro filas de la tabla se resumen en una sola regla:
//   si ambos jugaron lo mismo en la ronda anterior -> C
//   si jugaron distinto                           -> T
//
// Justificacion: a diferencia de Tit for Tat, Pavlov puede salir sola de un
//   ciclo de traiciones mutuas (T-T lleva a C) y tambien aprovecha a un
//   oponente que no castiga (si traiciona y el otro coopera, sigue
//   traicionando).
// ----------------------------------------------------------------------------
char decidirPavlov(int numeroRonda, const char historialPropio[], const char historialOponente[])
{
    if (numeroRonda == 1)
    {
        return 'C';
    }

    char miJugadaAnterior      = historialPropio[numeroRonda - 2];
    char jugadaAnteriorRival   = historialOponente[numeroRonda - 2];

    if (miJugadaAnterior == jugadaAnteriorRival)
    {
        return 'C';
    }
    return 'T';
}

// ----------------------------------------------------------------------------
// 8. ESTRATEGIA PROPIA: Sonda (Prober)
//
// Descripcion: estrategia mixta que primero "prueba" al oponente con una
//   secuencia fija y luego decide si lo trata como a un rival que se defiende
//   o como a uno que se deja explotar.
//
// Reglas de comportamiento:
//   - Rondas 1, 2 y 3: juega T, C, C (secuencia de exploracion).
//   - Desde la ronda 4:
//       * Si el oponente jugo T en la ronda 2 o en la ronda 3 (se defendio
//         de la traicion inicial), se comporta como Tit for Tat.
//       * Si el oponente jugo C en ambas rondas, lo explota traicionando
//         siempre.
//
// Algoritmo: la variable de estado "oponenteSeDefendio" se obtiene de
//   historialOponente[1] (ronda 2) y historialOponente[2] (ronda 3). Esas dos
//   jugadas ya no cambian despues de la ronda 3, asi que el valor calculado
//   en cada ronda es siempre el mismo: equivale a decidirlo una sola vez.
//   Se calcula a partir del historial en vez de guardarlo en una variable
//   static porque una static conservaria su valor de una partida a la
//   siguiente y mezclaria rivales distintos.
//
// Justificacion: frente a estrategias ingenuas (Siempre Cooperar) gana muchos
//   puntos, y frente a estrategias que castigan (Tit for Tat, Vengativa)
//   pasa a cooperar para no quedar atrapada en traiciones mutuas.
// ----------------------------------------------------------------------------
char decidirSonda(int numeroRonda, const char historialPropio[], const char historialOponente[])
{
    // Fase de exploracion
    if (numeroRonda == 1)
    {
        return 'T';
    }
    if (numeroRonda == 2 || numeroRonda == 3)
    {
        return 'C';
    }

    // Fase de decision (ronda 4 en adelante)
    bool oponenteSeDefendio = (historialOponente[1] == 'T' || historialOponente[2] == 'T');

    if (oponenteSeDefendio)
    {
        return historialOponente[numeroRonda - 2];   // modo Tit for Tat
    }
    return 'T';                                      // modo explotar
}

// ----------------------------------------------------------------------------
// Registra las 8 estrategias en el arreglo y pone sus contadores en cero.
// ----------------------------------------------------------------------------
void inicializarEstrategias(Estrategia estrategias[])
{
    string nombres[NUM_ESTRATEGIAS] = {
        "Siempre Cooperar",
        "Siempre Traicionar",
        "Aleatoria",
        "Tit for Tat",
        "Vengativa",
        "Ojo por Dos Ojos",
        "Pavlov",
        "Sonda"
    };

    FuncionDecision funciones[NUM_ESTRATEGIAS] = {
        decidirSiempreCooperar,
        decidirSiempreTraicionar,
        decidirAleatoria,
        decidirTitForTat,
        decidirVengativa,
        decidirOjoPorDosOjos,
        decidirPavlov,
        decidirSonda
    };

    for (int i = 0; i < NUM_ESTRATEGIAS; i++)
    {
        estrategias[i].id      = i;
        estrategias[i].nombre  = nombres[i];
        estrategias[i].decidir = funciones[i];

        estrategias[i].puntajeTotal = 0;
        for (int j = 0; j < NUM_ESTRATEGIAS; j++)
        {
            estrategias[i].puntosContra[j] = 0;
        }

        estrategias[i].vecesC      = 0;
        estrategias[i].vecesT      = 0;
        estrategias[i].victorias   = 0;
        estrategias[i].derrotas    = 0;
        estrategias[i].empates     = 0;
        estrategias[i].porcentajeC = 0.0;
        estrategias[i].porcentajeT = 0.0;
    }
}
