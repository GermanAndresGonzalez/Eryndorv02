#pragma once
#include <string>
#include "material.h"

// ---------------------------------------------------------------------------
// Tipos de evento que pueden ocurrir al pulsar "Explorar".
//
// - EXPLORAR (~80%):  el comportamiento actual, encontrar material normal
// - DESCANSO  (~10%): un lugar seguro que recupera energía (20% de vida)
// - COFRE     (~10%): un cofre oculto con una recompensa extra
// ---------------------------------------------------------------------------
enum TipoEvento {
    EVENTO_EXPLORAR = 0,
    EVENTO_DESCANSO,
    EVENTO_COFRE,
    EVENTO_AGREGAR_TURNO
};

// ---------------------------------------------------------------------------
// Evento: resultado de una tirada al explorar.
//   tipo       → qué sucedió
//   mensaje    → texto para mostrar al jugador
//   cantidad   → oro / curacion / cantidad extra de material
//   idMaterial → id del material involucrado (solo EXPLORAR)
// ---------------------------------------------------------------------------
struct Evento {
    TipoEvento tipo;
    std::string mensaje;
    int cantidad;
    int idMaterial;
};

// ---------------------------------------------------------------------------
// Selecciona un evento mediante pesos:
//   EXPLORAR → peso 80
//   DESCANSO → peso 10
//   COFRE    → peso 10
//   AGREGAR_TURNO → peso 5
// Devuelve un Evento ya poblado con mensaje y datos asociados.
// ---------------------------------------------------------------------------
Evento seleccionarEvento();


