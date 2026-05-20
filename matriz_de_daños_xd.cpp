#include "tablaEfectividad.h"

// Constructor: Inicializa toda la matriz en 0 para arrancar limpios
TablaEfectividad::TablaEfectividad() {
    for (int f = 0; f < 3; f++) {
        for (int c = 0; c < 3; c++) {
            matrizDano[f][c] = 0;
        }
    }
}

// Configura un valor en la matriz usando casting
void TablaEfectividad::configurarDano(TipoElem atacante, TipoElem defensor, int puntosDano) {
    int fila = static_cast<int>(atacante);
    int col = static_cast<int>(defensor);

    matrizDano[fila][col] = puntosDano;
}

// Busca el daño directo. ¡Cero ifs, cero switchs!
int TablaEfectividad::obtenerDano(TipoElem atacante, TipoElem defensor) const {
    int fila = static_cast<int>(atacante);
    int col = static_cast<int>(defensor);

    return matrizDano[fila][col];