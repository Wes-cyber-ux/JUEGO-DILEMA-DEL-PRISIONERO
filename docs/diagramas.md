# Diagramas del programa

Ambos diagramas corresponden exactamente al código de este repositorio.
Se pueden ver renderizados en GitHub, en VS Code (extensión *Markdown Preview Mermaid Support*)
o pegando el bloque en https://mermaid.live para exportarlo como PNG/SVG al informe.

---

## 1. Diagrama de módulos y funciones

### 1.1 Qué contiene cada archivo

```text
tipos_torneo.h ............ NUM_ESTRATEGIAS, MIN_RONDAS (no hay máximo),
                            typedef FuncionDecision, struct Estrategia
                            (lo incluyen todos los demás módulos)

lectura_rondas.h/.cpp ..... leerNumeroRondas()

estrategias_juego.h/.cpp .. decidirSiempreCooperar()
                            decidirSiempreTraicionar()
                            decidirAleatoria()
                            decidirTitForTat()
                            decidirVengativa()
                            decidirOjoPorDosOjos()
                            decidirPavlov()          (propia)
                            decidirSonda()           (propia)
                            inicializarEstrategias()

matriz_pagos.h/.cpp ....... calcularPuntosRonda()

partida_iterada.h/.cpp .... ejecutarPartida()
                            registrarJugada()        (auxiliar interna del .cpp)

torneo_round_robin.h/.cpp . ejecutarTorneo()

estadisticas_torneo.h/.cpp  calcularEstadisticas()
                            ordenarRanking()

reporte_resultados.h/.cpp . mostrarDetalleTorneo()
                            mostrarDetalleEstrategia()
                            mostrarRanking()
                            mostrarGanador()
                            mostrarSeparador()       (auxiliar interna del .cpp)

main_torneo.cpp ........... main()
```

### 1.2 Quién llama a quién

```text
main()
├── srand(time(0))
├── leerNumeroRondas()                         [lectura_rondas]
├── inicializarEstrategias()                   [estrategias_juego]
├── ejecutarTorneo()                           [torneo_round_robin]
│   └── ejecutarPartida()   x 28 partidas      [partida_iterada]
│       ├── estrategia.decidir(...)  → una de las 8 funciones decidirXxx()  [estrategias_juego]
│       ├── registrarJugada()
│       └── calcularPuntosRonda()              [matriz_pagos]
├── calcularEstadisticas()                     [estadisticas_torneo]
├── ordenarRanking()                           [estadisticas_torneo]
├── mostrarDetalleTorneo()                     [reporte_resultados]
│   └── mostrarDetalleEstrategia()  x 8
│       └── mostrarSeparador()
├── mostrarRanking()                           [reporte_resultados]
│   └── mostrarSeparador()
└── mostrarGanador()                           [reporte_resultados]
```

### 1.3 Versión Mermaid

```mermaid
flowchart TD
    subgraph MAIN["main_torneo.cpp"]
        main["main()"]
    end

    subgraph LEC["lectura_rondas.h / .cpp"]
        leer["leerNumeroRondas()"]
    end

    subgraph EST["estrategias_juego.h / .cpp"]
        init["inicializarEstrategias()"]
        dec["decidirSiempreCooperar()<br/>decidirSiempreTraicionar()<br/>decidirAleatoria()<br/>decidirTitForTat()<br/>decidirVengativa()<br/>decidirOjoPorDosOjos()<br/>decidirPavlov()<br/>decidirSonda()"]
    end

    subgraph TOR["torneo_round_robin.h / .cpp"]
        torneo["ejecutarTorneo()"]
    end

    subgraph PAR["partida_iterada.h / .cpp"]
        partida["ejecutarPartida()"]
        registrar["registrarJugada()"]
    end

    subgraph PAG["matriz_pagos.h / .cpp"]
        puntos["calcularPuntosRonda()"]
    end

    subgraph STA["estadisticas_torneo.h / .cpp"]
        calc["calcularEstadisticas()"]
        orden["ordenarRanking()"]
    end

    subgraph REP["reporte_resultados.h / .cpp"]
        detTorneo["mostrarDetalleTorneo()"]
        detEst["mostrarDetalleEstrategia()"]
        rank["mostrarRanking()"]
        gan["mostrarGanador()"]
        sep["mostrarSeparador()"]
    end

    TIPOS[["tipos_torneo.h<br/>struct Estrategia · FuncionDecision<br/>NUM_ESTRATEGIAS · MIN_RONDAS"]]

    main --> leer
    main --> init
    main --> torneo
    main --> calc
    main --> orden
    main --> detTorneo
    main --> rank
    main --> gan

    torneo --> partida
    partida -- "puntero decidir" --> dec
    partida --> registrar
    partida --> puntos

    detTorneo --> detEst
    detEst --> sep
    rank --> sep

    TIPOS -.-> EST
    TIPOS -.-> TOR
    TIPOS -.-> PAR
    TIPOS -.-> STA
    TIPOS -.-> REP
    TIPOS -.-> LEC
```

---

## 2. Diagrama de flujo del programa principal (`main()`)

Para la sección 4.4 del informe. Muestra los bucles reales del programa:
la validación de la entrada, el doble bucle del torneo (`i`, `j = i + 1`)
y el bucle de rondas de cada partida.

```mermaid
flowchart TD
    A([Inicio]) --> B["srand(time(0))<br/>semilla para la estrategia Aleatoria"]
    B --> C[/"Pedir número de rondas"/]
    C --> D{"¿Es un entero<br/>mayor a 200?"}
    D -- No --> E[/"Mostrar mensaje de error"/]
    E --> C
    D -- Sí --> F["inicializarEstrategias()<br/>8 estrategias: nombre, función,<br/>contadores y puntajes en 0"]

    F --> G["ejecutarTorneo()<br/>i = 0"]
    G --> H{"¿i < 8?"}
    H -- Sí --> I["j = i + 1"]
    I --> J{"¿j < 8?"}
    J -- No --> K["i = i + 1"]
    K --> H

    J -- Sí --> L["ejecutarPartida(i, j)<br/>historiales con new char[numeroRondas]<br/>ronda = 1, puntos de la partida = 0"]
    L --> M{"¿ronda ≤ número<br/>de rondas?"}
    M -- Sí --> N["Ambas estrategias deciden C o T<br/>mirando los historiales"]
    N --> O["Guardar jugadas en el historial<br/>y sumar veces C / T"]
    O --> P["calcularPuntosRonda()<br/>y sumar a los puntos de la partida"]
    P --> Q["ronda = ronda + 1"]
    Q --> M
    M -- No --> X["delete[] historialA / historialB<br/>liberar la memoria de la partida"]
    X --> R["Guardar puntosContra[i][j] y [j][i]<br/>sumar al puntajeTotal de i y de j"]
    R --> S["j = j + 1"]
    S --> J

    H -- No --> T["calcularEstadisticas()<br/>victorias, derrotas, empates,<br/>% cooperación y % traición"]
    T --> U["ordenarRanking()<br/>burbuja de mayor a menor puntaje"]
    U --> V[/"mostrarDetalleTorneo()<br/>puntos contra cada rival + estadísticas"/]
    V --> W[/"mostrarRanking()<br/>tabla final"/]
    W --> X[/"mostrarGanador()"/]
    X --> Y([Fin])
```
