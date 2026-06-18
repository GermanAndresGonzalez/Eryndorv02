
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

        oss << "ID: " << getID() << "\n";
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
                (cantidadRanura < 9 ? numero+=to_string(cantidadRanura): numero=to_string(cantidadRanura));
                oss << "x" << numero << "\n";
            }
        }

    }


    return oss.str();
}






/*
string Inventario::mostrarSlots()
{
    string cadena="ID: "+to_string(getID())+"\n";
    for (int i=0; i<tam-1; i++)
    {
        if (_slotsTotales[i].cantidad > 0)
        {
            cadena+=obtenerNombre(i)+ " x" + to_string(_slotsTotales[i].cantidad)+"\n";
            //cout << obtenerNombre(i)+ " x" + to_string(_slotsTotales[i].cantidad)+"\n";
        }
    }
    return cadena;
}
*/


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

/*
#include <iostream>
#include "inventario.h"

using namespace std;

string Inventario::obtenerNombre(int id) const
{
    string nombre;
    for (int i=0;i<tam-1;i++)
    {
        if (id==i)
        {
            nombre=arregloNombres[id];
        }
    }
    return nombre;
}




void Inventario::inicializarNombres()
{
    arregloNombres[0]= "HIERRO";
    arregloNombres[1]= "MADERA";
    arregloNombres[2]= "HONGOS MAGICOS";
    arregloNombres[3]= "ESPADA MADERA";
    arregloNombres[4]= "ESPADA HIERRO",
    arregloNombres[5]= "ESCUDO MADERA";
    arregloNombres[6]= "ESCUDO HIERRO";
    arregloNombres[7]= "POCION CURATIVA";
    for (int i=8;i<99;i++)
    {
        arregloNombres[i]= "";
    }
}




Inventario::Inventario()
{
    id = 0;
    eliminado = false;
    _cantidadDeSlotsOcupados = 0;
      for (int i = 0; i < 100; i++)
    {
                _slotsTotales[i].idItem = 0;
                _slotsTotales[i].cantidad = 0;
    }
}

int Inventario::obtenerID(string nombreBuscado) const
{
    for (int i=0;i< tam-1;i++)
    {
        if (arregloNombres[i]==nombreBuscado)
            {
                return i;
            }
    }
    return -1;
}

void Inventario::setId(int nuevoId)
{
    id = nuevoId;
}

bool Inventario::GuardarInventario(const char* nombreArchivo)
{
    ArchivoBinario<Inventario> archivo(nombreArchivo);
    const int posicion = archivo.BuscarPosicionPorID(id);

    if (posicion >= 0)
    {
        return archivo.Modificar(posicion, *this);
    }

    return archivo.Agregar(*this);
}

bool Inventario::CargarInventario(int idBuscado, const char* nombreArchivo)
{
    ArchivoBinario<Inventario> archivo(nombreArchivo);
    return archivo.BuscarPorID(idBuscado, *this);
}


void Inventario::agregarItem(int id, int cantidad)
{
    // 1. buscar si ya existe el item
    for (int i = 0; i < _cantidadDeSlotsOcupados; i++)
    {
        if (_slotsTotales[i].idItem == id)
        {
            _slotsTotales[i].cantidad += cantidad;
            return;
        }
    }

    // 2. si no existe, crear nuevo slot
    if (_cantidadDeSlotsOcupados < 100)
    {
        _slotsTotales[_cantidadDeSlotsOcupados].idItem = id;
        _slotsTotales[_cantidadDeSlotsOcupados].cantidad = cantidad;
        _cantidadDeSlotsOcupados++;
    }
}

bool Inventario::quitarItem(int id, int cantidad)
{
    for (int i = 0; i < _cantidadDeSlotsOcupados; i++)
    {
        if (_slotsTotales[i].idItem == id)
        {
            if (_slotsTotales[i].cantidad < cantidad)
            {
                return false;
            }

            _slotsTotales[i].cantidad -= cantidad;

            // si queda en 0, eliminar slot
            if (_slotsTotales[i].cantidad == 0)
            {
                for (int j = i; j < _cantidadDeSlotsOcupados - 1; j++)
                {
                    _slotsTotales[j] = _slotsTotales[j + 1];
                }

                _cantidadDeSlotsOcupados--;
            }

            return true;
        }
    }

    return false;
}


int Inventario::obtenerCantidad(int id) const
{
    for (int i = 0; i < _cantidadDeSlotsOcupados; i++)
    {
        if (_slotsTotales[i].idItem == id)
        {
            return _slotsTotales[i].cantidad;
        }
    }

    return 0;
}

bool Inventario::tieneCantidadNecesaria(int id, int cantidad) const
{
    for (int i = 0; i < _cantidadDeSlotsOcupados; i++)
    {
        if (_slotsTotales[i].idItem == id)
        {
            return _slotsTotales[i].cantidad >= cantidad;
        }
    }

    return false;
}
void Inventario::mostrarSlots()
{

    for (int i=0; i<99; i++)
    {
        if (_slotsTotales[i].cantidad >0)
        {
            cout << obtenerNombre(i) << " " << _slotsTotales[i].cantidad << endl;
        }
    }
}
*/
