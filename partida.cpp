#include "partida.h"
#include <iostream>
#include <cstdlib> //  rand() y srand()
#include <ctime>   //  time()

std::string tipoAString(TipoElem tipo) {
    if (tipo == TipoElem::Agua) return "Agua";
    if (tipo == TipoElem::Tierra) return "Tierra";
    return "Fuego";
}


bool esSuperEfectivo(TipoElem atq, TipoElem def) {
    if (atq == TipoElem::Agua && def == TipoElem::Fuego) return true;
    if (atq == TipoElem::Fuego && def == TipoElem::Tierra) return true;
    if (atq == TipoElem::Tierra && def == TipoElem::Agua) return true;
    return false;
}


Partida::Partida(std::string nombre) {
    // random
    std::srand(std::time(nullptr));

    // los jugadores
    Humano = new jugador(nombre);
    IA = new jugador("Computadora");

    confReglas();
    confDificultad();

    repartirElementosAleatorios(Humano);
    repartirElementosAleatorios(IA);
}


Partida::~Partida() {
    delete Humano;
    delete IA;
}


void Partida::confReglas() {
    int danio, Critico;

    std::cout << "\n CONFIGURACION DE REGLAS" << std::endl;
    std::cout << "Define los puntos de danio para esta partida:" << std::endl;

    std::cout << "> Ingresa el danioo: ";
    std::cin >> danio;

    std::cout << "> Ingresa el danio EFECTIVO (counter de elemento): ";
    std::cin >> Critico;

    //💧
    tabla.confDanio(TipoElem::Agua, TipoElem::Agua, danio);
    tabla.confDanio(TipoElem::Agua, TipoElem::Fuego, Critico);
    tabla.confDanio(TipoElem::Agua, TipoElem::Tierra, danio);

    //🔥
    tabla.confDanio(TipoElem::Fuego, TipoElem::Agua, danio);
    tabla.confDanio(TipoElem::Fuego, TipoElem::Fuego, danio);
    tabla.confDanio(TipoElem::Fuego, TipoElem::Tierra, Critico);

    //🌱
    tabla.confDanio(TipoElem::Tierra, TipoElem::Agua, Critico);
    tabla.confDanio(TipoElem::Tierra, TipoElem::Fuego, danio);
    tabla.confDanio(TipoElem::Tierra, TipoElem::Tierra, danio);

    std::cout << "Danios configurado!\n" << std::endl;
}

void Partida::confDificultad() {
    int opcion;
    std::cout << "\n=== DIFICULTAD DE LA IA ===" << std::endl;
    std::cout << "1 IA Aleatoria (Facil)" << std::endl;
    std::cout << "2 IA Estrategica (Media)" << std::endl;
    std::cout << "3 Super IA (DIFICIL!)" << std::endl;
    std::cout << "Elige una opcion (1-3): ";
    std::cin >> opcion;

    if (opcion == 1) dificultad = TipoIA::Aleatoria;
    else if (opcion == 2) dificultad = TipoIA::Estrategica;
    else dificultad = TipoIA::SuperIA;

    std::cout << ">> Dificultad establecida!\n" << std::endl;
}

void Partida::repartirElementosAleatorios(jugador* j) { //repartir elementos
    for (int i = 0; i < 5; i++) {
        int r = std::rand() % 3;

        Elemento* nuevo = nullptr;
        if (r == 0) nuevo = new Agua();
        else if (r == 1) nuevo = new Tierra();
        else nuevo = new Fuego();

        j->ElEl(i, nuevo);
    }
}

//CEREBRO DE LA IA
int Partida::pensarJugadaIA(int ihumano) {
    Elemento* elHumano = Humano->obtEl(ihumano);
    int mejorIndice = -1;

    if (dificultad == TipoIA::Aleatoria) {
        do {
            mejorIndice = std::rand() % 5;
        } while (IA->obtEl(mejorIndice) == nullptr || !IA->obtEl(mejorIndice)->AreUAlive());
        return mejorIndice;
    }

    if (dificultad == TipoIA::Estrategica) {
        int maxPuntaje = -9999;

        for (int i = 0; i < 5; i++) {
            Elemento* elIA = IA->obtEl(i);
            if (elIA != nullptr && elIA->AreUAlive()) {
                int danioHago = tabla.Danio(elIA->Ataque(), elHumano->Defensa());
                int danioRecibo = tabla.Danio(elHumano->Ataque(), elIA->Defensa());

                int puntaje = danioHago - danioRecibo;

                if (puntaje > maxPuntaje) {
                    maxPuntaje = puntaje;
                    mejorIndice = i;
                }
            }
        }
        return mejorIndice;
    }

    if (dificultad == TipoIA::SuperIA) {
        int hp = elHumano->getEnergia();
        int maxPuntaje = -9999;

        int mejorIndiceLetal = -1;
        int minDanioRecibidoLetal = 9999;

        for (int i = 0; i < 5; i++) {
            Elemento* elIA = IA->obtEl(i);
            if (elIA != nullptr && elIA->AreUAlive()) {
                int danioHago = tabla.Danio(elIA->Ataque(), elHumano->Defensa());
                int danioRecibo = tabla.Danio(elHumano->Ataque(), elIA->Defensa());

                if (danioHago >= hp) {
                    if (danioRecibo < minDanioRecibidoLetal) {
                        minDanioRecibidoLetal = danioRecibo;
                        mejorIndiceLetal = i;
                    }
                } else {
                    int puntaje = danioHago - danioRecibo;
                    if (puntaje > maxPuntaje) {
                        maxPuntaje = puntaje;
                        mejorIndice = i;
                    }
                }
            }
        }
        if (mejorIndiceLetal != -1) return mejorIndiceLetal;
        return mejorIndice;
    }

    return 0;
}

// combate
void Partida::resolverCombate(int ihumano, int iIA) {
    Elemento* elHumano = Humano->obtEl(ihumano);
    Elemento* elPC = IA->obtEl(iIA);

    if (elHumano != nullptr && elPC != nullptr && elHumano->AreUAlive() && elPC->AreUAlive()) {

        std::cout << "\n------------------------------------------------------------" << std::endl;


        TipoElem atqHumano = elHumano->Ataque();
        TipoElem defPC = elPC->Defensa();
        int danioAIA = tabla.Danio(atqHumano, defPC);
        elPC->RecDanio(danioAIA);

        std::cout << "-> " << Humano->getNombre() << " ha usado el elemento " << tipoAString(atqHumano);
        if (esSuperEfectivo(atqHumano, defPC)) {
            std::cout << " contra " << tipoAString(defPC) << " Ha sido super EFECTIVO! " << danioAIA << " PV)";
        } else {
            std::cout << " contra " << tipoAString(defPC) << " (-" << danioAIA << " PV).";
        }
        std::cout << std::endl;

        // 2. La PC ataca al humano
        TipoElem atqPC = elPC->Ataque();
        TipoElem defHumano = elHumano->Defensa();
        int danioAHumano = tabla.Danio(atqPC, defHumano);
        elHumano->RecDanio(danioAHumano);

        std::cout << "-> " << IA->getNombre() << " ha usado el elemento " << tipoAString(atqPC);
        if (esSuperEfectivo(atqPC, defHumano)) {
            std::cout << " contra " << tipoAString(defHumano) << " Ha sido super EFECTIVO! " << danioAHumano << " PV)";
        } else {
            std::cout << " contra " << tipoAString(defHumano) << " (-" << danioAHumano << " PV).";
        }
        std::cout << std::endl;

        std::cout << "------------------------------------------------------------\n" << std::endl;
    }
}

bool Partida::Endgame() const {
    return !Humano->EquipoVivo() || !IA->EquipoVivo();
}

// vida y elementos
void Partida::VidaActual() const {
    std::cout << "\n=== ESTADO ===" << std::endl;

    // jugador
    std::cout << Humano->getNombre() << ":" << std::endl;
    for (int i = 0; i < 5; i++) {
        Elemento* e = Humano->obtEl(i);
        std::cout << "  [" << i << "] Elemento: ";
        if (e != nullptr && e->AreUAlive()) {
            std::cout << tipoAString(e->Ataque()) << " - VIDA " << e->getEnergia() << "% PV)";
        } else {
            std::cout << "MUERTO X_x";
        }
        std::cout << std::endl;
    }

    // computadora
    std::cout << "\n" << IA->getNombre() << ":" << std::endl;
    for (int i = 0; i < 5; i++) {
        Elemento* e = IA->obtEl(i);
        std::cout << "  [" << i << "] Elemento: ";
        if (e != nullptr && e->AreUAlive()) {
            std::cout << tipoAString(e->Ataque()) << " - VIDA " << e->getEnergia() << "% PV)";
        } else {
            std::cout << "MUERTO X_x";
        }
        std::cout << std::endl;
    }
    std::cout << "=============================" << std::endl;
}

void Partida::Winner() const {
    bool humanoVivo = Humano->EquipoVivo();
    bool iaViva = IA->EquipoVivo();

    std::cout << "\n==========================================" << std::endl;
    if (!humanoVivo && !iaViva) {
        std::cout << "  EMPATE! Parece que ambos pueden coexistir en Armonia?" << std::endl;
    } else if (humanoVivo && !iaViva) {
        std::cout << "  VICTORIA! " << Humano->getNombre() << " es el GANADOR: Ambos equipos cayeron a la vez. La IA nunca superará al indomable espiritu humano. " << std::endl;
    } else {
        std::cout << "  DERROTA!: La Computadora ha ganado. La IA Destruye el mundo y somete a la humanidad...  " << std::endl;
    }
    std::cout << "==========================================\n" << std::endl;
}