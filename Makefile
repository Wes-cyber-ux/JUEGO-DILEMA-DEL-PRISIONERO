# Makefile - Torneo del Dilema del Prisionero
# Uso:  make         -> compila el programa
#       make run     -> compila y ejecuta
#       make clean   -> borra el ejecutable y los .o

CXX      = g++
CXXFLAGS = -std=c++11 -Wall
PROGRAMA = torneo_dilema

FUENTES = main_torneo.cpp \
          lectura_rondas.cpp \
          estrategias_juego.cpp \
          matriz_pagos.cpp \
          partida_iterada.cpp \
          torneo_round_robin.cpp \
          estadisticas_torneo.cpp \
          reporte_resultados.cpp

OBJETOS = $(FUENTES:.cpp=.o)

$(PROGRAMA): $(OBJETOS)
	$(CXX) $(CXXFLAGS) -o $(PROGRAMA) $(OBJETOS)

%.o: %.cpp *.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(PROGRAMA)
	./$(PROGRAMA)

clean:
	rm -f $(OBJETOS) $(PROGRAMA) $(PROGRAMA).exe

.PHONY: run clean
