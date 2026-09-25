# Borrador del informe — Proyecto 1

> Andamiaje de contenido para el reporte PDF. Completar los campos entre corchetes
> y reemplazar los placeholders antes de exportar.

---

## 4.1 Portada

**UTEC — Universidad de Ingeniería y Tecnología**
**Curso:** Programación II — Laboratorio
**Periodo:** 2026-2
**Profesor:** Henry Gallegos
**Proyecto 1:** Torneo de Estrategias del Dilema del Prisionero

**Integrantes del grupo:**

| # | Nombre completo | Código | % de participación |
|---|---|---|---|
| 1 | [ ] | [ ] | [ ] % |
| 2 | [ ] | [ ] | [ ] % |
| 3 | [ ] | [ ] | [ ] % |
| 4 | [ ] | [ ] | [ ] % |
| 5 | [ ] | [ ] | [ ] % |

**Fecha de entrega:** [ ]

---

## 4.2 Introducción

El Dilema del Prisionero es un problema clásico de la teoría de juegos: dos participantes deciden,
sin comunicarse, si **cooperan** o **traicionan**. Traicionar siempre da más puntos que cooperar
en una sola ronda (5 contra 3 si el otro coopera, 1 contra 0 si el otro traiciona), pero si ambos
traicionan obtienen menos (1 cada uno) que si ambos hubieran cooperado (3 cada uno).

En el **Dilema del Prisionero Iterado** el juego se repite muchas rondas contra el mismo rival.
Como cada jugador puede recordar lo que hizo el otro, aparecen estrategias que premian la
cooperación y castigan la traición, y la mejor decisión deja de ser simplemente traicionar.

El objetivo de este proyecto es implementar en C++, con programación estructurada (funciones,
estructuras y arreglos, sin clases), una simulación de un torneo en el que 8 estrategias
(6 obligatorias y 2 diseñadas por el equipo) se enfrentan todas contra todas. El programa calcula
el puntaje de cada estrategia, sus estadísticas y el ranking final para determinar cuál es la
estrategia ganadora y analizar por qué.

---

## 4.3 Descripción de las estrategias

### Estrategias obligatorias

| # | Estrategia | Comportamiento |
|---|---|---|
| 1 | Siempre Cooperar | Juega C en todas las rondas. |
| 2 | Siempre Traicionar | Juega T en todas las rondas. |
| 3 | Aleatoria | Elige C o T con 50 % de probabilidad cada una (`rand() % 2`). |
| 4 | Tit for Tat | Coopera en la ronda 1; después copia la jugada anterior del oponente. |
| 5 | Vengativa | Coopera hasta que el oponente traicione una vez; desde ahí traiciona siempre. |
| 6 | Ojo por Dos Ojos | Coopera en las rondas 1 y 2; desde la 3 traiciona solo si el oponente traicionó en las dos rondas anteriores. |

### Estrategia propia 1: Ganar-Mantener, Perder-Cambiar (Pavlov)

- **Nombre:** Ganar-Mantener, Perder-Cambiar (Pavlov). Tipo: reactiva.
- **Descripción:** evalúa el resultado de su última jugada. Si le fue bien (obtuvo 3 o 5 puntos)
  la repite; si le fue mal (obtuvo 0 o 1 punto) la cambia.
- **Reglas:**

  | Ronda anterior (yo, oponente) | Puntos obtenidos | Evaluación | Jugada actual |
  |---|---|---|---|
  | C, C | 3 | Ganó → mantiene | **C** |
  | T, C | 5 | Ganó → mantiene | **T** |
  | C, T | 0 | Perdió → cambia | **T** |
  | T, T | 1 | Perdió → cambia | **C** |

  En la ronda 1 coopera.
- **Forma en que toma decisiones (algoritmo):** solo mira la ronda inmediatamente anterior
  (`historialPropio[numeroRonda - 2]` y `historialOponente[numeroRonda - 2]`). Las cuatro filas
  de la tabla se reducen a una regla: **si ambos jugaron lo mismo, coopera; si jugaron distinto,
  traiciona.**
- **Justificación del diseño:** es diferente de Tit for Tat porque no copia al oponente, sino que
  reacciona a su propio resultado. Esto le permite salir sola de una cadena de traiciones mutuas
  (después de T-T vuelve a cooperar) y, al mismo tiempo, seguir aprovechando a un rival que no
  castiga (después de T-C sigue traicionando).

### Estrategia propia 2: Sonda (Prober)

- **Nombre:** Sonda (Prober). Tipo: mixta.
- **Descripción:** empieza con una secuencia fija para "probar" al oponente y, según cómo
  reacciona, decide si coopera con él o si lo explota durante el resto de la partida.
- **Reglas:**
  1. Ronda 1: T. Ronda 2: C. Ronda 3: C.
  2. Desde la ronda 4, si el oponente jugó T en la ronda 2 o en la ronda 3 (es decir, se defendió
     de la traición inicial), la Sonda se comporta como Tit for Tat.
  3. Si el oponente jugó C en las rondas 2 y 3 (no se defendió), la Sonda traiciona siempre.
- **Forma en que toma decisiones (algoritmo):** tiene una variable de estado,
  `oponenteSeDefendio = (historialOponente[1] == 'T' || historialOponente[2] == 'T')`, que decide
  el modo de juego desde la ronda 4. Como esas dos jugadas ya no cambian después de la ronda 3,
  el modo queda fijado para el resto de la partida. Se calcula a partir del historial (y no con una
  variable `static`) para que cada partida empiece limpia.
- **Justificación del diseño:** busca sacar el máximo contra estrategias ingenuas, como Siempre
  Cooperar, sin perder demasiado contra estrategias que castigan, como Tit for Tat. Es diferente de
  todas las obligatorias porque tiene dos fases (exploración y decisión).

---

## 4.4 Diseño del programa

### Organización general

El programa está dividido en módulos `.h` / `.cpp`, cada uno con una sola responsabilidad.
`main()` solo llama a las funciones en orden y no tiene lógica del juego.

| Archivo | Responsabilidad |
|---|---|
| `tipos_torneo.h` | Constantes globales, tipo `FuncionDecision` y `struct Estrategia`. |
| `lectura_rondas.h/.cpp` | Lectura validada del número de rondas por teclado. |
| `estrategias_juego.h/.cpp` | Las 8 funciones de decisión y la inicialización del arreglo de estrategias. |
| `matriz_pagos.h/.cpp` | Puntos de una ronda según la matriz de pagos. |
| `partida_iterada.h/.cpp` | Una partida completa entre dos estrategias. |
| `torneo_round_robin.h/.cpp` | Torneo todos contra todos (cada par una sola vez). |
| `estadisticas_torneo.h/.cpp` | Victorias, derrotas, empates, porcentajes y ranking. |
| `reporte_resultados.h/.cpp` | Impresión del detalle, el ranking y la ganadora. |
| `main_torneo.cpp` | Función `main()`. |

### Principales funciones

| Función | Qué hace |
|---|---|
| `int leerNumeroRondas()` | Pide el número de rondas hasta que sea un entero mayor a 200 (no hay máximo). |
| `void inicializarEstrategias(Estrategia[])` | Asigna id, nombre y función a cada estrategia y pone sus contadores en 0. |
| `char decidirXxx(int, const char[], const char[])` | Una por estrategia; devuelve `'C'` o `'T'`. |
| `void calcularPuntosRonda(char, char, int&, int&)` | Aplica la matriz de pagos a una ronda. |
| `void ejecutarPartida(Estrategia&, Estrategia&, int, long long&, long long&)` | Juega todas las rondas entre dos estrategias, guarda el historial y cuenta las C y T. |
| `void ejecutarTorneo(Estrategia[], int)` | Doble bucle `i`, `j = i + 1`: 28 partidas sin repetir. Guarda `puntosContra` y el `puntajeTotal`. |
| `void calcularEstadisticas(Estrategia[])` | Calcula las victorias, derrotas y empates y los porcentajes de C y T. |
| `void ordenarRanking(const Estrategia[], int[])` | Ordena los índices por puntaje (burbuja, de mayor a menor). |
| `mostrarDetalleTorneo`, `mostrarDetalleEstrategia`, `mostrarRanking`, `mostrarGanador` | Salida por consola. |

### Estructuras de datos

- **`struct Estrategia`**: agrupa todo lo de una estrategia: `id`, `nombre`, `decidir` (puntero a
  su función de decisión), `puntajeTotal`, `puntosContra[NUM_ESTRATEGIAS]` (puntos contra cada
  rival), `vecesC`, `vecesT`, `victorias`, `derrotas`, `empates`, `porcentajeC` y `porcentajeT`.
  Los puntajes y los contadores de C y T son `long long`: como no hay límite de rondas, con `int`
  (máximo 2 147 483 647) podrían desbordarse.
- **`Estrategia estrategias[NUM_ESTRATEGIAS]`**: arreglo con los 8 participantes.
- **`int ranking[NUM_ESTRATEGIAS]`**: índices de las estrategias ordenados por puntaje. Se ordenan
  los índices, no las estructuras, para no perder la correspondencia con `puntosContra`.
- **`char *historialA = new char[numeroRondas]`, `char *historialB = new char[numeroRondas]`**:
  jugadas de cada estrategia dentro de una partida. Como no hay máximo de rondas, se crean con
  memoria dinámica del tamaño exacto al inicio de cada partida y se liberan con `delete[]` al
  terminarla. La ronda N está en la posición N − 1.
- **`typedef char (*FuncionDecision)(int, const char[], const char[])`**: permite guardar la
  función de cada estrategia en su estructura y llamarla desde `ejecutarPartida` sin usar
  `if`/`switch` por estrategia.

### Variables y constantes importantes

| Nombre | Valor | Uso |
|---|---|---|
| `NUM_ESTRATEGIAS` | 8 | Tamaño de los arreglos y límites de los bucles del torneo. |
| `MIN_RONDAS` | 201 | El enunciado exige más de 200 rondas por partida. No hay máximo. |
| `numeroRondas` | lo ingresa el usuario | Rondas de cada partida (mayor a 200, sin límite superior). También es el tamaño de los historiales. |
| `PUNTOS_COOPERACION_MUTUA`, `PUNTOS_TRAICION_EXITOSA`, `PUNTOS_ENGANADO`, `PUNTOS_TRAICION_MUTUA` | 3, 5, 0, 1 | Valores de la matriz de pagos. |

### Diagrama de módulos

```text
main()
├── leerNumeroRondas()                         [lectura_rondas]
├── inicializarEstrategias()                   [estrategias_juego]
├── ejecutarTorneo()                           [torneo_round_robin]
│   └── ejecutarPartida()   x 28 partidas      [partida_iterada]
│       ├── estrategia.decidir(...)  → decidirXxx()   [estrategias_juego]
│       ├── registrarJugada()
│       └── calcularPuntosRonda()              [matriz_pagos]
├── calcularEstadisticas()                     [estadisticas_torneo]
├── ordenarRanking()                           [estadisticas_torneo]
├── mostrarDetalleTorneo()                     [reporte_resultados]
│   └── mostrarDetalleEstrategia()  x 8
├── mostrarRanking()                           [reporte_resultados]
└── mostrarGanador()                           [reporte_resultados]
```

(La versión gráfica en Mermaid está en `docs/diagramas.md`.)

### Diagrama de flujo del programa principal

[INSERTAR DIAGRAMA DE FLUJO AQUÍ]

*(Exportar el diagrama Mermaid de la sección 2 de `docs/diagramas.md` como imagen, por ejemplo
desde https://mermaid.live.)*

---

## 4.5 Análisis de resultados

Número de rondas usado: [ ]

[PEGAR AQUÍ LA TABLA DEL RANKING FINAL QUE MUESTRA EL PROGRAMA]

### ¿Cuál fue la estrategia ganadora?

[COMPLETAR CON RESULTADOS REALES DEL TORNEO]

### ¿Por qué consideran que la estrategia ganadora obtuvo el mayor puntaje?

[COMPLETAR CON RESULTADOS REALES DEL TORNEO]

### ¿Contra qué estrategia obtuvo peores resultados? Explicar las posibles razones.

[COMPLETAR CON RESULTADOS REALES DEL TORNEO]

### ¿Las estrategias propias funcionaron como esperaban?

[COMPLETAR CON RESULTADOS REALES DEL TORNEO]

*(Idea para el análisis: comparar lo que sacaron Pavlov y Sonda contra Siempre Cooperar, contra
Siempre Traicionar y contra Tit for Tat. Por ejemplo, Pavlov contra Siempre Traicionar alterna C y
T y pierde puntos cada dos rondas, mientras que la Sonda explota a Siempre Cooperar desde la
ronda 4.)*

---

## 4.6 Conclusiones

- [COMPLETAR]
- [COMPLETAR]
- [COMPLETAR]
- [COMPLETAR]

---

## Bibliografía

*(La rúbrica pide describir las fuentes utilizadas, incluida la IA.)*

- Axelrod, R. (1984). *The Evolution of Cooperation*. Basic Books.
- Nowak, M., & Sigmund, K. (1993). A strategy of win-stay, lose-shift that outperforms tit-for-tat
  in the Prisoner's Dilemma game. *Nature, 364*, 56–58.
- [Material del curso Programación II — UTEC]
- [Herramientas de IA utilizadas: indicar cuál, para qué partes y cómo se verificó su resultado]
