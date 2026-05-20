#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include "elementos.h"

class jugador { //el jugador, y sus elementos
private:
    std::string nombre;

    Elemento* equipo[5];

public:

    jugador(std::string _nombre);
    ~jugador();
    std::string getNombre() const;

    void ElEl(int i, Elemento* nElem); // función para elegir el elemento
    Elemento* obtEl(int i) const;

    bool EquipoVivo() const;
};

#endif