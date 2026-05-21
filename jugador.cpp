#include "jugador.h"


jugador::jugador(std::string _nombre) {
    nombre = _nombre;
    for (int i = 0; i < 5; i++) {
        equipo[i] = nullptr;
    }
}

jugador::~jugador() {
    for (int i = 0; i < 5; i++) {
        if (equipo[i] != nullptr) {
            delete equipo[i];
        }
    }
}

std::string jugador::getNombre() const {
    return nombre;
}

// asignamos elemento y obtenemos
void jugador::ElEl(int i, Elemento* newElemento) {
    if (i >= 0 && i < 5) {
        if (equipo[i] != nullptr) { //si no hay borramos
        }
        equipo[i] = newElemento;
    }
}
Elemento* jugador::obtEl(int i) const {
    if (i >= 0 && i < 5) {
        return equipo[i];
    }
    return nullptr;
}

// is your team alive?
bool jugador::EquipoVivo() const {
    for (int i = 0; i < 5; i++) {
        if (equipo[i] != nullptr && equipo[i]->AreUAlive()) {
            return true; // never back down never what?
        }
    }
    return false;
}