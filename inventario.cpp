
#include "inventario.h"
#include "items_juego.h"

#include<iostream>
#include <cstring>



using namespace std;

void Inventario::inicializarNombres()
{
    strncpy(arregloNombres[0], "HIERRO",         32);
    strncpy(arregloNombres[1], "MADERA",         32);
    strncpy(arregloNombres[2], "HONGOS MAGICOS", 32);
    strncpy(arregloNombres[3], "ESPADA MADERA",  32);
    strncpy(arregloNombres[4], "ESPADA HIERRO",  32);
    strncpy(arregloNombres[5], "ESCUDO MADERA",  32);
    strncpy(arregloNombres[6], "ESCUDO HIERRO",  32);
    strncpy(arregloNombres[7], "POCION CURATIVA",32);
    for (int i = 8; i < tam; i++)
        arregloNombres[i][0] = '\0';
}

const int Inventario::getID() const
{
    return id;
}

void Inventario::setID(int _id)
{
    id= _id;
}



Inventario::Inventario()
{
    id=0;
    eliminado=false;
    _cantidadDeSlotsOcupados = 0;
    for (int i = 0; i < tam; i++)
    {
        _slotsTotales[i].idItem = 0;
        _slotsTotales[i].cantidad = 0;
    }
    inicializarNombres();

}

void Inventario::agregarItem(int id, int cantidad)
{
    _slotsTotales[id].cantidad+=cantidad;
    _slotsTotales[id].idItem=id;

}

bool Inventario::quitarItem(int id, int cantidad)
{
    if (_slotsTotales[id].cantidad < cantidad)
    {
        return false;
    }
    _slotsTotales[id].cantidad-=cantidad;
    return true;
}


int Inventario::obtenerCantidad(int id) const
{


    if (id >= 0 && id < tam)
        return _slotsTotales[id].cantidad;
    return 0;
    /*
    for (int i = 0; i < _cantidadDeSlotsOcupados; i++)
    {
        if (_slotsTotales[i].idItem == id)
        {
            return _slotsTotales[i].cantidad;
        }
    }
    return 0;
    */
}

int Inventario::obtenerID(std::string nombreBuscado) const
{
    for (int i = 0; i < tam; i++)
        if (nombreBuscado == arregloNombres[i])
            return i;
    return -1;
}

std::string Inventario::obtenerNombre(int id) const
{
    if (id >= 0 && id < tam)
        return std::string(arregloNombres[id]);
    return "";
}

bool Inventario::tieneCantidadNecesaria(int id, int cantidad) const
{
    for (int i = 0; i < tam-1; i++)
    {
        if (_slotsTotales[i].idItem == id)
        {
            return (_slotsTotales[i].cantidad >= cantidad);
        }
    }
    return false;
}

const int Inventario::obtenerRanuraCantidad(int indice) const
{
    return _slotsTotales[indice].cantidad;
}

const int Inventario::obtenerRanuraidItem(int indice) const
{
    return _slotsTotales[indice].idItem;
}



void Inventario::imprimirSlots()
{
    cout << "ID: " <<getID() << endl;
    cout << "Estado: "<<(eliminado==false ? "Activo" : "Eliminado") << endl;
    for (int i=0; i<tam; i++)
    {
        if (_slotsTotales[i].cantidad > 0)
        {
            cout << arregloNombres[i]<< " " << _slotsTotales[i].cantidad<<"\n";
            //obtenerNombre(i) << " " << _slotsTotales[i].cantidad << endl;

        }
    }
}

#include <sstream>
#include <iomanip>

string Inventario::mostrarSlots(std::string lado)
{
    std::ostringstream oss;
    if (lado=="izquierda")
    {
        int maxLen = 0;
        for (int i = 0; i < tam - 1; i++)
        {
            if (_slotsTotales[i].cantidad > 0)
            {
                int len = obtenerNombre(i).size();
                if (len > maxLen) maxLen = len;
            }
        }

        // Cabecera

       // oss << "ID: " << getID() << "\n"; // Es para pruebas
        oss << std::left << std::setw(maxLen+2) << "Nombre"
            << std::right << std::setw(10) << "Cantidad" << "\n";
        oss << std::string(maxLen+22, '-') << "\n";

        for (int i = 0; i < tam-1; i++)
        {
            if (_slotsTotales[i].cantidad > 0)
            {
                oss << std::left << std::setw(maxLen+2) << obtenerNombre(i)
                    //<< std::right << std::setw(5) << "x" <<_slotsTotales[i].cantidad
                    << "\n";
            }
        }
    }
    else
    {
        oss << "\n\n\n";
        for (int i = 0; i < tam-1; i++)
        {
            if (_slotsTotales[i].cantidad > 0)
            {
                int cantidadRanura= _slotsTotales[i].cantidad;
                string numero="0";
                (cantidadRanura < 10 ? numero+=to_string(cantidadRanura): numero=to_string(cantidadRanura));
                oss << "x" << numero << "\n";
            }
        }
    }
    return oss.str();
}



int Inventario::getCantidadSlotsOcupados() const
{
    return _cantidadDeSlotsOcupados;
}

SlotInventario Inventario::getSlot(int i) const
{
    // Devuelve slot vacío si el índice está fuera del rango ocupado
    if (i < 0 || i >= _cantidadDeSlotsOcupados)
        return SlotInventario{0, 0};
    return _slotsTotales[i];
}
