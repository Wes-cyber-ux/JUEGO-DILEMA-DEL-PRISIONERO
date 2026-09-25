#ifndef TORNEO_H
#define TORNEO_H
#include <iso646.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <iomanip>
#include <limits>
#include <string>
using namespace std;


//metodo de puntajes
void calcular_puntos(char decicionA, char decicionB, int &puntosA, int &puntosB)
{
    if (decicionA == 'C' and decicionB == 'C'){puntosA=3; puntosB=3;}
    else if (decicionA == 'C' and decicionB == 'T'){puntosA=0; puntosB=5;}
    else if (decicionA == 'T' and decicionB == 'C'){puntosA=5; puntosB=0;}
    else {puntosA=1; puntosB=1;}
}


//estrategias

char estrategia_siempre_cooperar(int ronda , const vector<char>& historial_del_oponente, const vector<char>& historial_del_propio)
{
    return 'C';
}

char estrategia_siempre_traicionar(int ronda , const vector<char>& historial_del_oponente, const vector<char>& historial_del_propio)
{
    return 'T';
}

char estrategia_aleatorio(int ronda , const vector<char>& historial_del_oponente, const vector<char>& historial_del_propio)
{

    char opcion1 = 'C';
    char opcion2 = 'T';

    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> distribucion(0, 1);
    char eleccion = (distribucion(gen) == 0) ? opcion1 : opcion2;
    return eleccion;
}

char estrategia_Tit_for_Tat(int ronda , const vector<char>& historial_del_oponente, const vector<char>& historial_del_propio)
{
    if (ronda == 1)
    {
        return 'C';
    }
    else
    {
        return historial_del_oponente.back();
    }
}

char estrategia_venganza(int ronda , const vector<char>& historial_del_oponente, const vector<char>& historial_del_propio)
{
    if (ronda == 1)
    {
        return 'C';
    }

    for (int  i = 0; i < historial_del_oponente.size(); i++)
    {
        if (historial_del_oponente[i] == 'T')
        {
            return 'T';
        }
    }
    return 'C';
}

char estrategia_ojo_por_dos_ojos(int ronda , const vector<char>& historial_del_oponente, const vector<char>& historial_del_propio)
{
    if (ronda < 3)
    {
        return 'C';
    }

    char ultima = historial_del_oponente.back();
    char penultima = historial_del_oponente[historial_del_oponente.size()-2];

    if (ultima == 'T' and penultima == 'T')
    {
        return 'T';
    }
    return 'C';
}

char estrategia_Ganar_mantener(int ronda , const vector<char>& historial_del_oponente, const vector<char>& historial_del_propio)
{
    if (ronda == 1)
    {
        return 'C';
    }

    char mi_ultima_jugada = historial_del_propio.back();
    char ultima_jugada_enemigo = historial_del_oponente.back();

    if (ultima_jugada_enemigo == mi_ultima_jugada)
    {
        return 'C';
    }
    else {return 'T';}

}

char estrategia_sonda(int ronda , const vector<char>& historial_del_oponente, const vector<char>& historial_del_propio)
{
    if (ronda == 1){return 'T';}
    if (ronda == 2){return 'C';}
    if (ronda == 3){return 'C';}

    bool defendio = historial_del_oponente[1] == 'T' or historial_del_oponente[2] == 'T';

    if (defendio)
    {
        return historial_del_oponente.back();
    }
    else {return 'T';}
}

//array para las funciones y evitar que genere problemas

typedef char (*funciones_estrategia)(int, const vector<char>&, const vector<char>&);

funciones_estrategia estrategias[8] = {
    estrategia_siempre_cooperar,
    estrategia_siempre_traicionar,
    estrategia_aleatorio,
    estrategia_Tit_for_Tat,
    estrategia_venganza,
    estrategia_ojo_por_dos_ojos,
    estrategia_Ganar_mantener,
    estrategia_sonda,
};

void ejecutar_partida(int indiceA, int indiceB, int numRondas, int &puntajeTotalA, int &puntajeTotalB,
                       int &vecesC_A, int &vecesT_A, int &vecesC_B, int &vecesT_B)
{
    puntajeTotalA = 0;
    puntajeTotalB = 0;
    vecesC_A = 0; vecesT_A = 0;
    vecesC_B = 0; vecesT_B = 0;

    vector<char> historialA;
    vector<char> historialB;

    for (int ronda = 1; ronda <= numRondas; ronda++)
    {
        char decisionA = estrategias[indiceA](ronda, historialB, historialA);
        char decisionB = estrategias[indiceB](ronda, historialA, historialB);

        if (decisionA == 'C') vecesC_A++; else vecesT_A++;
        if (decisionB == 'C') vecesC_B++; else vecesT_B++;

        int puntosA, puntosB;
        calcular_puntos(decisionA, decisionB, puntosA, puntosB);

        puntajeTotalA += puntosA;
        puntajeTotalB += puntosB;

        historialA.push_back(decisionA);
        historialB.push_back(decisionB);
    }
}

void ejecutar_torneo(int numRondas, int puntajesTotales[8], int victorias[8], int derrotas[8], int empates[8],
                      int vecesC[8], int vecesT[8])
{
    for (int i = 0; i < 8; i++)
    {
        puntajesTotales[i] = 0;
        victorias[i] = 0; derrotas[i] = 0; empates[i] = 0;
        vecesC[i] = 0; vecesT[i] = 0;
    }

    for (int i = 0; i < 8; i++)
    {
        for (int j = i + 1; j < 8; j++)
        {
            int puntosA, puntosB, cA, tA, cB, tB;
            ejecutar_partida(i, j, numRondas, puntosA, puntosB, cA, tA, cB, tB);

            puntajesTotales[i] += puntosA;
            puntajesTotales[j] += puntosB;
            vecesC[i] += cA; vecesT[i] += tA;
            vecesC[j] += cB; vecesT[j] += tB;

            if (puntosA > puntosB)
            {
                victorias[i]++;
                derrotas[j]++;
            }
            else if (puntosA < puntosB)
            {
                victorias[j]++;
                derrotas[i]++;
            }
            else
            {
                empates[i]++;
                empates[j]++;
            }
        }
    }
}

void mostrar_resultados(string nombres[8], int puntajesTotales[8], int victorias[8], int derrotas[8],
                         int empates[8], int vecesC[8], int vecesT[8], int indicesOrdenados[8])
{
    cout << fixed << setprecision(2); // para que los porcentajes salgan con 2 decimales

    cout << "RESULTADOS DEL TORNEO" << endl;


    for (int puesto = 0; puesto < 8; puesto++) {
        int i = indicesOrdenados[puesto]; // indice real de la estrategia en este puesto

        float total = vecesC[i] + vecesT[i];
        float porcentajeC = (vecesC[i] / total) * 100;
        float porcentajeT = (vecesT[i] / total) * 100;

        cout << "\nPuesto " << (puesto + 1) << ": " << nombres[i] << endl;
        cout << "  Puntos totales: " << puntajesTotales[i] << endl;
        cout << "  Victorias: " << victorias[i] << " | Derrotas: " << derrotas[i] << " | Empates: " << empates[i] << endl;
        cout << "  Veces coopero (C): " << vecesC[i] << " | Veces traiciono (T): " << vecesT[i] << endl;
        cout << "  Porcentaje cooperacion: " << porcentajeC << "%" << endl;
        cout << "  Porcentaje traicion: " << porcentajeT << "%" << endl;
    }

    cout << "\n";
    cout << "Ganador del torneo: " << nombres[indicesOrdenados[0]] << endl;

}

#endif // TORNEO_H
