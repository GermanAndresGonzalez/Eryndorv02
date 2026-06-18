#pragma once

#include <SFML/Graphics.hpp>

// ─────────────────────────────────────────────────────────────────────────────
//  Pantalla  —  interfaz base (clase abstracta)
//
//  Toda pantalla concreta (PantallaExplorar, PantallaCombate, etc.)
//  debe heredar de esta clase e implementar los tres métodos virtuales.
//
//  La ventana se pasa en dibujar() para no almacenarla en cada subclase,
//  pero si lo preferís podés guardarla en el constructor.
// ─────────────────────────────────────────────────────────────────────────────

class Pantalla {
public:
    virtual ~Pantalla() = default;

    // Se llama cada frame solo si la pantalla está visible.
    // dt: tiempo transcurrido desde el último frame (en segundos).
    virtual void actualizar(float dt) = 0;

    // Se llama cada frame solo si la pantalla está visible.
    virtual void dibujar(sf::RenderWindow& ventana) = 0;

    // Opcional: se llama al mostrar u ocultar la pantalla.
    virtual void alMostrar() {}
    virtual void alOcultar() {}
    virtual void manejarEvento(const sf::Event& evento) {}
};
