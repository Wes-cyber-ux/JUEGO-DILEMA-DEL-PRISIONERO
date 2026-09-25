// ============================================================================
// main_torneo.cpp
// Torneo de Estrategias del Dilema del Prisionero Iterado
// Programacion II - Proyecto 1
//
// main() solo coordina los pasos del programa; toda la logica esta en los
// modulos incluidos abajo.
// ============================================================================
#include <cstdlib>
#include <ctime>

#include "tipos_torneo.h"
#include "lectura_rondas.h"
#include "estrategias_juego.h"
#include "torneo_round_robin.h"
#include "estadisticas_torneo.h"
#include "reporte_resultados.h"

int main()
{
    // La semilla se fija una sola vez para que la estrategia Aleatoria
    // juegue distinto en cada ejecucion.
    srand(time(0));

    Estrategia estrategias[NUM_ESTRATEGIAS];
    int ranking[NUM_ESTRATEGIAS];

    int numeroRondas = leerNumeroRondas();

    inicializarEstrategias(estrategias);
    ejecutarTorneo(estrategias, numeroRondas);
    calcularEstadisticas(estrategias);
    ordenarRanking(estrategias, ranking);

    mostrarDetalleTorneo(estrategias, ranking);
    mostrarRanking(estrategias, ranking, numeroRondas);
    mostrarGanador(estrategias, ranking);

    return 0;
}
