// VentanaCargar.h
#pragma once
#include "Pantalla.h"
#include "botonera.h"
#include "GestorPantallas.h"

class VentanaCargar : public Pantalla
{
public:
// Recibe una referencia al gestor para poder cambiar pantallas desde  adentro
    explicit VentanaCargar(GestorPantallas& gestor);
    void alMostrar() override;
    void alOcultar() override;
    void actualizar(float dt) override;
    void dibujar(sf::RenderWindow& ventana) override;
    void ejecutarAccion(int i);
    void manejarEvento(const sf::Event& evento) override;
    void carrusel();
    void switchCarrusel();

    void cargarRec();

private:
    GestorPantallas& m_gestor;
    sf::Font m_fuente;
    sf::Text m_texto;
    sf::Font fuenteBotonera;
    sf::Texture texturaFondo;
    sf::Sprite spriteFondo;
    Botonera botonera;
};
