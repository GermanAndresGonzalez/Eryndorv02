#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include "Partida.h"
#include "Pantalla.h"  // interfaz base (ver abajo)

// ─────────────────────────────────────────────────────────────────────────────
//  GestorPantallas
//
//  Responsabilidades:
//    · Ser el único dueño de la Partida (new/delete).
//    · Registrar pantallas con un nombre clave ("explorar", "combate", etc.).
//    · Mostrar u ocultar pantallas individualmente.
//    · Delegar update() y draw() solo a las pantallas visibles.
//
//  Uso mínimo:
//      GestorPantallas gestor(ventana);
//      gestor.agregar("explorar", new PantallaExplorar(gestor.obtenerPartida()));
//      gestor.mostrar("explorar");
//      // en el game loop:
//      gestor.actualizar(dt);
//      gestor.dibujar();
// ─────────────────────────────────────────────────────────────────────────────

class GestorPantallas {
public:
    // El gestor crea la ventana y la Partida; los destruye al final.
    explicit GestorPantallas(sf::RenderWindow& ventana);
    ~GestorPantallas();

    // ── Gestión del ciclo de vida de pantallas ────────────────────────────
    // Registra una pantalla con una clave. El gestor toma la propiedad del puntero.
    void agregar(const std::string& clave, Pantalla* pantalla);

    // Elimina y destruye la pantalla asociada a esa clave.
    void quitar(const std::string& clave);

    // ── Visibilidad ───────────────────────────────────────────────────────
    void mostrar(const std::string& clave);
    void ocultar(const std::string& clave);
    bool estaVisible(const std::string& clave) const;

    // ── Acceso a la Partida compartida ────────────────────────────────────
    Partida* obtenerPartida();

    // ── Game loop ─────────────────────────────────────────────────────────
    // Llama a update() de cada pantalla visible.
    void actualizar(float dt);

    // Llama a draw() de cada pantalla visible.
    void dibujar();
    void manejarEvento(const sf::Event& evento);
    sf::RenderWindow& obtenerVentana();





private:
    struct Entrada {
        Pantalla* pantalla;   // dueño del puntero
        bool      visible;
    };

    sf::RenderWindow&                        m_ventana;
    Partida*                                 m_partida;   // único dueño
    std::unordered_map<std::string, Entrada> m_pantallas;

    // Helpers internos
    Entrada*       buscar(const std::string& clave);
    const Entrada* buscar(const std::string& clave) const;
};
