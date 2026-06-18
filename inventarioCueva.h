#pragma once
#include <string>
#include "inventario.h"

class InventarioCueva
{
private:
    Inventario inventarioCueva;
    static const int CANTIDAD_MAXIMA_ITEMS = 99999;
    static const int MAXIMO_ALEATORIO      = 99;
    static const int CANTIDAD_ITEMS        = 3;

    // srand se llama una sola vez, aquí se garantiza
    static bool aleatorioInicializado;

    //int stockCueva[CANTIDAD_ITEMS]{};

    static void inicializarAleatorio();

public:
    InventarioCueva();
    InventarioCueva(int hierro, int madera, int hongos);
    ~InventarioCueva();

    const int  obtenerCantidadItem(int id) const;
    int  descubrirItemCueva(int id);
    int  valorAleatorio(int maximo);
    int  valorAleatorio(int minimo, int maximo);

    bool restarItem(int id, int cantidad);
    bool agregarItem(int id, int cantidad);

    void imprimirStock() const;
    void inicializarResto();
    std::string obtenerStock(std::string lado="izquierda");

};
