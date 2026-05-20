#include "tabladedanios.h"

TablaDanio::TablaDanio() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrizDano[i][j] = 0;
        }
    }
}

// configura un valor en la matriz usando casting
void TablaDanio::confDanio(TipoElem atacante, TipoElem defensor, int ptsDanio) {
    int i = static_cast<int>(atacante);
    int j = static_cast<int>(defensor);

    matrizDano[i][j] = ptsDanio;
}

int TablaDanio::Danio(TipoElem atacante, TipoElem defensor) const {
    int i = static_cast<int>(atacante);
    int j = static_cast<int>(defensor);

    return matrizDano[i][j];
}