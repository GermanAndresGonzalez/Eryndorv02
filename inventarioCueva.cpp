#include "inventarioCueva.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>
#include <cstring>
using namespace std;

// Hierro = 0, Madera = 1, Hongos = 2

bool InventarioCueva::aleatorioInicializado = false;

void InventarioCueva::inicializarAleatorio()
{
    if (!aleatorioInicializado)
    {
        srand(static_cast<unsigned int>(time(nullptr)));
        aleatorioInicializado = true;
    }
}

InventarioCueva::InventarioCueva()
{
    inicializarAleatorio();
    inventarioCueva.agregarItem(0,CANTIDAD_MAXIMA_ITEMS);
    inventarioCueva.agregarItem(1,CANTIDAD_MAXIMA_ITEMS);
    inventarioCueva.agregarItem(2,CANTIDAD_MAXIMA_ITEMS);

}

InventarioCueva::InventarioCueva(int hierro, int madera, int hongos)
{
    inicializarAleatorio();
    inventarioCueva.agregarItem(0,hierro);
    inventarioCueva.agregarItem(1,madera);
    inventarioCueva.agregarItem(2,hongos);

}

void InventarioCueva::inicializarResto()
{
    for (int i=0;i<MAXIMO_ALEATORIO;i++)
    {
        inventarioCueva.agregarItem(i,0);
    }
}


//

InventarioCueva::~InventarioCueva() {}

const int InventarioCueva::obtenerCantidadItem(int id) const
{
    return inventarioCueva.obtenerCantidad(id);

}

int InventarioCueva::valorAleatorio(int maximo)
{
    return (std::rand() % maximo) + 1;
}

int InventarioCueva::valorAleatorio(int minimo, int maximo)
{
    return (std::rand() % (maximo - minimo + 1)) + minimo;
}

int InventarioCueva::descubrirItemCueva(int id)
{
    int cantidad = valorAleatorio(MAXIMO_ALEATORIO);
    agregarItem(id, cantidad);
    return cantidad;
}

bool InventarioCueva::restarItem(int id, int cantidad)
{
    if (inventarioCueva.obtenerCantidad(id) < cantidad)
    {
        return false;
    }
    inventarioCueva.quitarItem(id,cantidad);

    return true;
}

bool InventarioCueva::agregarItem(int id, int cantidad)
{
    if ((inventarioCueva.obtenerCantidad(id) + cantidad) >= CANTIDAD_MAXIMA_ITEMS)
        return false;

    inventarioCueva.agregarItem(id,cantidad);
    return true;
}

void InventarioCueva::imprimirStock() const
{
    std::cout << "Hierro\tMadera\tHongos\n";
    std::cout << inventarioCueva.obtenerCantidad(0) << "\t"
              << inventarioCueva.obtenerCantidad(1) << "\t"
              << inventarioCueva.obtenerCantidad(2) << "\n";
}
//void obtenerStock() const;

string InventarioCueva::obtenerStock(std::string lado)
{
    return inventarioCueva.mostrarSlots(lado);
}

