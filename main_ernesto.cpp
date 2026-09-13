#include "ernesto.h"
#include <iso646.h>

int main() {
    string nombres[8] = {
        "Siempre Cooperar", "Siempre Traicionar", "Aleatoria", "Tit for Tat",
        "Vengativa", "Ojo por Dos Ojos", "Ganar-mantener Perder-cambiar", "Sonda"
    };

    // --- Pedir numero de rondas, validado, mayor a 200 ---
    int numRondas;
    do {
        cout << "Ingrese el numero de rondas por partida (mayor a 200): ";
        cin >> numRondas;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida. Debe ingresar un numero entero.\n";
            numRondas = 0; // fuerza a repetir el bucle
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (numRondas <= 200) {
            cout << "El numero de rondas debe ser mayor a 200.\n";
        }
    } while (numRondas <= 200);

    // --- Arrays de resultados del torneo ---
    int puntajesTotales[8], victorias[8], derrotas[8], empates[8], vecesC[8], vecesT[8];

    ejecutar_torneo(numRondas, puntajesTotales, victorias, derrotas, empates, vecesC, vecesT);

    // --- Ordenar por puntaje (mayor a menor) sin perder la correspondencia ---
    int indicesOrdenados[8] = {0, 1, 2, 3, 4, 5, 6, 7};
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8 - i - 1; j++) {
            if (puntajesTotales[indicesOrdenados[j]] < puntajesTotales[indicesOrdenados[j + 1]]) {
                int temp = indicesOrdenados[j];
                indicesOrdenados[j] = indicesOrdenados[j + 1];
                indicesOrdenados[j + 1] = temp;
            }
        }
    }

    mostrar_resultados(nombres, puntajesTotales, victorias, derrotas, empates, vecesC, vecesT, indicesOrdenados);

    return 0;
}