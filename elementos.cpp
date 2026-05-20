#include "elementos.h"

Elemento::Elemento() { //constructor
    energia=100;
}
Elemento::~Elemento() { //destructor
}

void Elemento::RecDanio(int cantidad){ //funcion para recibir daño
    energia -= cantidad;
    if (energia <0){
        energia = 0;

    }
}

bool Elemento::AreUAlive() const { // is bro alive?
    return energia > 0;
}

//reglas de los elements para defena y ataque
TipoElem Agua::Ataque() const {
    return TipoElem::Agua;
}
TipoElem Agua::Defensa() const {
    return TipoElem::Agua;
}

TipoElem Tierra::Ataque() const {
    return TipoElem::Tierra;
}
TipoElem Tierra::Defensa() const {
    return TipoElem::Tierra;
}

TipoElem Fuego::Ataque() const {
    return TipoElem::Fuego;
}
TipoElem Fuego::Defensa() const {
    return TipoElem::Fuego;
}