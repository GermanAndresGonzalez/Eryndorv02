#include "eventos.h"
#include "inventarioCueva.h"
#include <cstdlib>
#include <iostream>

// ---------------------------------------------------------------------------
// Pesos para cada tipo de evento.
// La suma total (100) define el rango del dado virtual.
// ---------------------------------------------------------------------------
static const int PESO_EXPLORAR      = 75;
static const int PESO_DESCANSO      = 10;
static const int PESO_COFRE         = 10;
static const int PESO_AGREGAR_TURNO = 5;
static const int TOTAL_PESOS =
    PESO_EXPLORAR +
    PESO_DESCANSO +
    PESO_COFRE +
    PESO_AGREGAR_TURNO; // 100

// ---------------------------------------------------------------------------
// seleccionarEvento
//
// 1. Tira un número aleatorio entre 1 y TOTAL_PESOS.
// 2. Recorre los pesos acumulados para determinar qué evento ocurre.
// 3. Puebla el struct Evento con mensaje y datos según el tipo.
//
// Los eventos alternativos (DESCANSO, COFRE) usan un helper temporal
// InventarioCueva para generar cantidades aleatorias, igual que hace
// ExplorCueva::obtenerMaterial() con el comportamiento normal.
// ---------------------------------------------------------------------------
Evento seleccionarEvento()
{
    // Objeto helper para acceder a valorAleatorio(), misma semilla global
    InventarioCueva helper;

    int tirada = helper.valorAleatorio(1, TOTAL_PESOS);   // [1..100]
    Evento ev = {};

    // ── Acumulamos pesos en orden ────────────────────────────────────────
    int acumulado = PESO_EXPLORAR;

    if (tirada <= acumulado)
    {
        // EVENTO_EXPLORAR (~80%): comportamiento original
        ev.tipo       = EVENTO_EXPLORAR;
        ev.idMaterial = helper.valorAleatorio(0, 2);        // 0=Hierro, 1=Madera, 2=Hongos
        ev.cantidad   = helper.valorAleatorio(1, 15);
        ev.mensaje    = "Encontraste:\n"
                      + std::to_string(ev.cantidad)
                      + " de material "
                      + std::to_string(ev.idMaterial)
                      + ".";
    }
    else
    {
    acumulado += PESO_DESCANSO;

    if (tirada <= acumulado)
    {
        // EVENTO_DESCANSO
        ev.tipo       = EVENTO_DESCANSO;
        ev.idMaterial = -1;
        ev.cantidad   = 20;
        ev.mensaje    = "Encontraste un claro tranquilo.\n"
                        "Descansas un momento y te curas.";
    }
    else
    {
        acumulado += PESO_COFRE;

        if (tirada <= acumulado)
        {
            // EVENTO_COFRE
            ev.tipo       = EVENTO_COFRE;
            ev.idMaterial = -1;
            ev.cantidad   = helper.valorAleatorio(20, 60);
            ev.mensaje    = "Encontraste un cofre escondido!\n"
                            "Contiene "
                          + std::to_string(ev.cantidad)
                          + " monedas de oro.";
        }
        else
        {
            // EVENTO_AGREGAR_TURNO
            ev.tipo       = EVENTO_AGREGAR_TURNO;
            ev.idMaterial = -1;
            ev.cantidad   = helper.valorAleatorio(1, 5);

            ev.mensaje    = "Tiempo parece detenerse!\n"
                            "Obtienes: "
                          + std::to_string(ev.cantidad)
                          + " turno(s) adicional(es).";
        }
    }
    }

    return ev;
}
