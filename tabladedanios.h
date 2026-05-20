#ifndef TABLADANIO_H
#define TABLADANIO_H

#include "elementos.h"

class TablaDanio {
private:
    //filas = atacante, columnas = defensor
    int matrizDano[3][3];

public:
    TablaDanio(); //para poner todo en 0
    void confDanio(TipoElem atacante, TipoElem defensor, int puntosDano);
    int Danio(TipoElem atacante, TipoElem defensor) const;
};

#endif