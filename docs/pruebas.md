# Cómo compilar y probar el programa

## Compilación

Con `make` (Linux / WSL / MinGW con make instalado):

```bash
make          # genera ./torneo_dilema
make run      # compila y ejecuta
make clean
```

Sin `make`, con g++ directamente (sirve igual en Windows con MinGW):

```bash
g++ -std=c++11 -Wall -o torneo_dilema main_torneo.cpp lectura_rondas.cpp estrategias_juego.cpp matriz_pagos.cpp partida_iterada.cpp torneo_round_robin.cpp estadisticas_torneo.cpp reporte_resultados.cpp
./torneo_dilema
```

## 1. Validación de la entrada

Probar que el programa vuelve a preguntar cuando la entrada no es válida:

| Entrada | Resultado esperado |
|---|---|
| `abc` | "Entrada invalida. Debe ingresar un numero entero." |
| `100` o `200` | "El numero de rondas debe ser mayor a 200..." |
| `250` | Se acepta y el torneo se ejecuta |
| `5000` o `100000000` | Se acepta (no hay máximo). Con 100 000 000 rondas tarda unos 26 s |
| `99999999999` | "Entrada invalida..." (no cabe en un `int`) |

## 2. Partidas deterministas (con 250 rondas)

Todos los enfrentamientos que no incluyen a la estrategia **Aleatoria** dan siempre el mismo resultado,
así que se pueden calcular a mano y comparar con la salida del programa
(sección "Contra X: N puntos"):

| Partida | Cálculo a mano | Esperado |
|---|---|---|
| Siempre Traicionar vs Siempre Cooperar | 250 × 5 / 250 × 0 | **1250 / 0** |
| Tit for Tat vs Siempre Cooperar | 250 × 3 | **750 / 750** |
| Tit for Tat vs Siempre Traicionar | ronda 1: 0/5, luego 249 × 1 | **249 / 254** |
| Vengativa vs Siempre Traicionar | igual que Tit for Tat | **249 / 254** |
| Ojo por Dos Ojos vs Siempre Traicionar | rondas 1-2: 0/5, luego 248 × 1 | **248 / 258** |
| Pavlov vs Siempre Traicionar | alterna C, T, C, T… → 125 × 0 + 125 × 1 | **125 / 750** |
| Sonda vs Siempre Cooperar | 5 + 3 + 3 + 247 × 5 | **1246 / 6** |
| Sonda vs Tit for Tat | 5 + 0 + 248 × 3 (luego cooperan) | **749 / 749** |
| Sonda vs Vengativa | 5 + 0 + 0 + 247 × 1 | **252 / 257** |
| Cualquier par de "amables" (TFT, Vengativa, Ojo por Dos Ojos, Pavlov, Siempre Cooperar) | 250 × 3 | **750 / 750** |

## 3. Comprobaciones generales

- **Número de partidas:** con 8 estrategias hay 8 × 7 / 2 = **28 partidas**, así que cada estrategia juega 7 partidas:
  `ganadas + perdidas + empatadas = 7` en cada fila del ranking.
- **Total de jugadas:** `vecesC + vecesT = 7 × número de rondas` (con 250 rondas: 1750).
- **Porcentajes:** `% C + % T = 100`.
- **Siempre Cooperar** debe tener 100 % de C y **Siempre Traicionar** 100 % de T.
- **Siempre Traicionar** gana las 7 partidas (nunca saca menos puntos que su rival), pero queda en los
  últimos lugares del ranking porque contra las estrategias que se defienden solo consigue 1 punto por ronda.
- **Aleatoria** debe tener un % de cooperación cercano al 50 % y sus resultados cambian entre ejecuciones.
- **Tit for Tat** o Vengativa normalmente quedan en los primeros puestos: nunca ganan una partida
  individual, pero sacan 3 puntos por ronda contra casi todos.
- **Ranking:** los puntajes aparecen de mayor a menor y la ganadora anunciada es la primera fila.
