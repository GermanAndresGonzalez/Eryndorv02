#pragma once

#include "item.h"

enum IdItem
{
    HIERRO = 0,
    MADERA = 1,
    HONGOS_MAGICOS = 2,
    ORO = 3,

    ESPADA_MADERA = 4,
    ESPADA_HIERRO = 5,

    ESCUDO_MADERA = 6,
    ESCUDO_HIERRO = 7,

    POCION_CURATIVA = 8
};

Item obtenerItemPorId(int id);


