#include <iostream>
#include <string>
#include "partida.h"

int main() {
    std::string nombre;

    std::cout << "==========================================" << std::endl;
    std::cout << "           JUEGO DE ELEMENTOS     " << std::endl;
    std::cout << "==========================================" << std::endl;
    std::cout << "Ingresa tu nombre: ";
    std::cin >> nombre;

    Partida juego(nombre);

    std::cout << "\n ---INICIA LA BATALLA! ---" << std::endl;
    while (!juego.Endgame()) {
        juego.VidaActual();
        int jugada;
        std::cout << nombre << ", que elemento usaras? (0-4): ";
        std::cin >> jugada;

        // validación rápida por si el usuario mete cualquiera
        if (jugada < 0 || jugada > 4) {
            std::cout << ">> Indice invalido. Elige un numero entre 0 y 4.\n" << std::endl;
            continue;
        }
        int eleccionIA = juego.pensarJugadaIA(jugada);
        juego.resolverCombate(jugada, eleccionIA);
    }


    std::cout << "\n==========================================" << std::endl;
    std::cout << "             ¡FIN DE LA PARTIDA!          " << std::endl;
    std::cout << "==========================================" << std::endl;

    // vida final y el ganador
    juego.VidaActual();
    juego.Winner();

    std::cout << "¡Gracias por jugar!" << std::endl;

    return 0;
}