// ============================================================================
// reporte_resultados.h
// Funciones que muestran en consola los resultados del torneo.
// ============================================================================
#ifndef REPORTE_RESULTADOS_H
#define REPORTE_RESULTADOS_H

#include "tipos_torneo.h"

// Muestra los puntos de una estrategia contra cada rival, sus puntos totales
// y sus estadisticas.
void mostrarDetalleEstrategia(const Estrategia estrategias[], int indice);

// Muestra el detalle de todas las estrategias, en el orden del ranking.
void mostrarDetalleTorneo(const Estrategia estrategias[], const int ranking[]);

// Muestra la tabla final ordenada de mayor a menor puntaje.
void mostrarRanking(const Estrategia estrategias[], const int ranking[], int numeroRondas);

// Anuncia la estrategia ganadora (o las ganadoras, si empatan en el primer lugar).
void mostrarGanador(const Estrategia estrategias[], const int ranking[]);

#endif // REPORTE_RESULTADOS_H
