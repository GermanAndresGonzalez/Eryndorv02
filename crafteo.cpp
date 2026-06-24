#include "crafteo.h"
#include <iostream>


bool Crafteo::crearPocionCurativa(Inventario& inventario)
{

    int idElemento=inventario.obtenerID("HONGOS MAGICOS");
    if (!inventario.tieneCantidadNecesaria(idElemento, 3))
    {
        return false;
    }
    inventario.quitarItem(idElemento,3);

    idElemento=inventario.obtenerID("POCION CURATIVA");

    inventario.agregarItem(idElemento, 1);

    return true;
}

bool Crafteo::crearEspadaMadera(Inventario& inventario)
{
    int idElemento=inventario.obtenerID("MADERA");
    if (!inventario.tieneCantidadNecesaria(idElemento, 3))
    {
        return false;
    }
    inventario.quitarItem(idElemento,3);

    idElemento=inventario.obtenerID("ESPADA MADERA");

    inventario.agregarItem(idElemento, 1);

    return true;

}

bool Crafteo::crearEspadaHierro(Inventario& inventario)
{
    int idElemento=inventario.obtenerID("HIERRO");
    if (!inventario.tieneCantidadNecesaria(idElemento, 3))
    {
        return false;
    }
    inventario.quitarItem(idElemento,5);

    idElemento=inventario.obtenerID("ESPADA HIERRO");

    inventario.agregarItem(idElemento, 1);

    return true;

}

bool Crafteo::crearEscudoMadera(Inventario& inventario)
{
    int idElemento=inventario.obtenerID("MADERA");
    if (!inventario.tieneCantidadNecesaria(idElemento, 3))
    {
        return false;
    }
    inventario.quitarItem(idElemento,5);

    idElemento=inventario.obtenerID("ESCUDO MADERA");

    inventario.agregarItem(idElemento, 1);

    return true;

}

bool Crafteo::crearEscudoHierro(Inventario& inventario)
{
    if (!inventario.tieneCantidadNecesaria(HIERRO, 5))
    {
        return false;
    }

    inventario.quitarItem(HIERRO, 5);

    inventario.agregarItem(ESCUDO_HIERRO, 1);

    return true;
}



bool Crafteo::puedoCrearPocionCurativa(Inventario& inventario)
{
    if (!inventario.tieneCantidadNecesaria(HONGOS_MAGICOS, 3))
    {
        return false;
    }
    return true;
}
bool Crafteo::puedoCrearEspadaMadera(Inventario& inventario)
{
    if (!inventario.tieneCantidadNecesaria(MADERA, 5))
    {
        return false;
    }
    return true;
}
bool Crafteo::puedoCrearEspadaHierro(Inventario& inventario)
{
    if (!inventario.tieneCantidadNecesaria(HIERRO, 5))
    {
        return false;
    }
    return true;
}
bool Crafteo::puedoCrearEscudoMadera(Inventario& inventario)
{
    if (!inventario.tieneCantidadNecesaria(MADERA, 5))
    {
        return false;
    }
    return true;
}
bool Crafteo::puedoCrearEscudoHierro(Inventario& inventario)
{
    if (!inventario.tieneCantidadNecesaria(HIERRO, 5))
    {
        return false;
    }
    return true;
}

