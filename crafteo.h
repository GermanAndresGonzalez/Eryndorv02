#pragma once

#include "inventario.h"
#include "items_juego.h"

class Crafteo
{
public:

    static bool crearPocionCurativa(Inventario& inventario);
    static bool puedoCrearPocionCurativa(Inventario& inventario);

    static bool crearEspadaMadera(Inventario& inventario);
    static bool puedoCrearEspadaMadera(Inventario& inventario);

    static bool crearEspadaHierro(Inventario& inventario);
    static bool puedoCrearEspadaHierro(Inventario& inventario);

    static bool crearEscudoMadera(Inventario& inventario);
    static bool puedoCrearEscudoMadera(Inventario& inventario);

    static bool crearEscudoHierro(Inventario& inventario);
    static bool puedoCrearEscudoHierro(Inventario& inventario);


};


