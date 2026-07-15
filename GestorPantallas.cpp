#include "GestorPantallas.h"
#include <stdexcept>
#include <iostream>

// ─────────────────────────────────────────────────────────────────────────────
//  Constructor / Destructor
// ─────────────────────────────────────────────────────────────────────────────


void GestorPantallas::manejarEvento(const sf::Event& evento)
{
    {
    const int MAX_PANTALLAS = 9; // ajustá según cuántas pantallas tenés en total
    Pantalla* visibles[MAX_PANTALLAS];
    int cantVisibles = 0;

    // Snapshot: guardamos qué pantallas estaban visibles ANTES de procesar
    // este evento, para no despachar el mismo evento dos veces si una
    // acción cambia visibilidad en el medio (ver bug de "craftear"->"jugador").
    for (auto& par : m_pantallas)
    {
        if (par.second.visible)
        {
            if (cantVisibles < MAX_PANTALLAS)
            {
                visibles[cantVisibles] = par.second.pantalla;
                cantVisibles++;
            }
            else
            {
                std::cerr << "[GestorPantallas] manejarEvento(): se excedió MAX_PANTALLAS\n";
            }
        }
    }

    for (int i = 0; i < cantVisibles; i++)
    {
        visibles[i]->manejarEvento(evento);
    }
}
}

//Cambié la segunda línea
//, m_partida(new Partida{0, 1, 0})   // valores iniciales por defecto
GestorPantallas::GestorPantallas(sf::RenderWindow& ventana)
    : m_ventana(ventana)
    , m_partida(new Partida{-1, 0, 0, 0, 0,{}, {}})   // valores iniciales por defecto
{
}

GestorPantallas::~GestorPantallas()
{
    // 1) Destruir todas las pantallas primero (dejan de usar m_partida).
    for (auto& par : m_pantallas)
    {
        delete par.second.pantalla;
        par.second.pantalla = nullptr;
    }
    m_pantallas.clear();

    // 2) Destruir la Partida al final, cuando nadie la referencia ya.
    delete m_partida;
    m_partida = nullptr;
}

// ─────────────────────────────────────────────────────────────────────────────
//  Gestión del ciclo de vida
// ─────────────────────────────────────────────────────────────────────────────

void GestorPantallas::agregar(const std::string& clave, Pantalla* pantalla)
{
    if (!pantalla)
    {
        std::cerr << "[GestorPantallas] agregar(): puntero nulo para clave '"
                  << clave << "'\n";
        return;
    }

    // Si ya existe una pantalla con esa clave, la destruimos antes de reemplazar.
    auto it = m_pantallas.find(clave);
    if (it != m_pantallas.end())
    {
        std::cerr << "[GestorPantallas] agregar(): clave '" << clave
                  << "' ya existe; se reemplaza la pantalla anterior.\n";
        delete it->second.pantalla;
        m_pantallas.erase(it);
    }

    m_pantallas[clave] = Entrada{pantalla, false};   // oculta por defecto
}

void GestorPantallas::quitar(const std::string& clave)
{
    auto it = m_pantallas.find(clave);
    if (it == m_pantallas.end())
    {
        std::cerr << "[GestorPantallas] quitar(): clave '" << clave
                  << "' no encontrada.\n";
        return;
    }

    if (it->second.visible)
    {
        it->second.pantalla->alOcultar();
    }

    delete it->second.pantalla;
    m_pantallas.erase(it);
}

// ─────────────────────────────────────────────────────────────────────────────
//  Visibilidad
// ─────────────────────────────────────────────────────────────────────────────

void GestorPantallas::mostrar(const std::string& clave)
{
    Entrada* e = buscar(clave);
    if (!e) return;

    if (!e->visible)
    {
        e->visible = true;
        e->pantalla->alMostrar();
    }
}

void GestorPantallas::ocultar(const std::string& clave)
{
    Entrada* e = buscar(clave);
    if (!e) return;

    if (e->visible)
    {
        e->visible = false;
        e->pantalla->alOcultar();
    }
}

bool GestorPantallas::estaVisible(const std::string& clave) const
{
    const Entrada* e = buscar(clave);
    return e ? e->visible : false;
}

// ─────────────────────────────────────────────────────────────────────────────
//  Acceso a la Partida compartida
// ─────────────────────────────────────────────────────────────────────────────

Partida* GestorPantallas::obtenerPartida()
{
    return m_partida;
}

// ─────────────────────────────────────────────────────────────────────────────
//  Game loop
// ─────────────────────────────────────────────────────────────────────────────

void GestorPantallas::actualizar(float dt)
{
    for (auto& par : m_pantallas)
    {
        if (par.second.visible)
        {
            par.second.pantalla->actualizar(dt);
        }
    }
}

void GestorPantallas::dibujar()
{
    for (auto& par : m_pantallas)
    {
        if (par.second.visible)
        {
            par.second.pantalla->dibujar(m_ventana);
        }
    }
}

// ─────────────────────────────────────────────────────────────────────────────
//  Helpers internos
// ─────────────────────────────────────────────────────────────────────────────

GestorPantallas::Entrada* GestorPantallas::buscar(const std::string& clave)
{
    auto it = m_pantallas.find(clave);
    if (it == m_pantallas.end())
    {
        std::cerr << "[GestorPantallas] clave '" << clave << "' no encontrada.\n";
        return nullptr;
    }
    return &it->second;
}

const GestorPantallas::Entrada* GestorPantallas::buscar(const std::string& clave) const
{
    auto it = m_pantallas.find(clave);
    if (it == m_pantallas.end())
    {
        std::cerr << "[GestorPantallas] clave '" << clave << "' no encontrada.\n";
        return nullptr;
    }
    return &it->second;
}

sf::RenderWindow& GestorPantallas::obtenerVentana()
{
    return m_ventana;
}
