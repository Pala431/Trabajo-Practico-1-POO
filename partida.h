#ifndef PARTIDA_H
#define PARTIDA_H

#include "jugador.h"
#include "tabladedanios.h"

enum class TipoIA { Aleatoria, Estrategica, SuperIA };

class Partida {
private:
    jugador* Humano;
    jugador* IA;
    TablaDanio tabla;
    TipoIA dificultad; // Acá guardamos qué IA nos toca

    void repartirElementosAleatorios(jugador* j);

public:
    Partida(std::string nombre);
    ~Partida();
    void confReglas();

    // Método para que el usuario elija la dificultad
    void confDificultad();

    // El cerebro de la computadora. Recibe lo que eligió el humano y devuelve qué elige la PC.
    int pensarJugadaIA(int ihumano);

    void resolverCombate(int ihumano, int iIA);
    bool Endgame() const;
    void VidaActual() const;
    void Winner() const;
};

#endif