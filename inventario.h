
#pragma once
#include <string>

struct SlotInventario
{
    int idItem;
    int cantidad;
};


class Inventario
{
private:

    static constexpr int tam=100;
    char arregloNombres[tam][32];

    SlotInventario _slotsTotales[tam];
    int _cantidadDeSlotsOcupados;



public:
    int id;
    bool eliminado;
    Inventario();
    const int getID() const;
    void setID(int _id);
    void inicializarNombres();

    void agregarItem(int id, int cantidad);

    bool quitarItem(int id, int cantidad);

    int obtenerCantidad(int id) const;

    int getCantidadSlotsOcupados() const;
    SlotInventario getSlot(int i) const;

    int obtenerID(std::string nombreBuscado) const;

    std::string obtenerNombre(int id) const;
    const int obtenerRanuraidItem(int indice) const;
    const int obtenerRanuraCantidad(int indice) const;

    bool tieneCantidadNecesaria(int id, int cantidad) const;
    void imprimirSlots();
    std::string mostrarSlots(std::string lado="izquierda");

};

/*
#ifndef INVENTARIO_H_INCLUDED
#define INVENTARIO_H_INCLUDED

#include "archivos.h"

struct SlotInventario
{
    int idItem;
    int cantidad;
};

class Inventario
{
public:
    int id;
    bool eliminado;

    Inventario();

    int obtenerID(std::string nombreBuscado) const;
    void setId(int nuevoId);

    bool GuardarInventario(const char* nombreArchivo = "recursos/archivos/inventarios.dat");
    bool CargarInventario(int idBuscado, const char* nombreArchivo = "recursos/archivos/inventarios.dat");
    std::string obtenerNombre(int id) const;
    void agregarItem(int id, int cantidad);

    bool quitarItem(int id, int cantidad);

    int obtenerCantidad(int id) const;

    bool tieneCantidadNecesaria(int id, int cantidad) const;
    void mostrarSlots();

private:
    void inicializarNombres();
    static constexpr int tam=100;
    std::string arregloNombres[tam];
    SlotInventario _slotsTotales[tam];
    int _cantidadDeSlotsOcupados;
};

#endif // INVENTARIO_H_INCLUDED


*/
