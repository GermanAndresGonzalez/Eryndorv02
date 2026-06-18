// VentanaJug.h
#pragma once
#include "Pantalla.h"
#include "GestorPantallas.h"
#include "botonera.h"
#include "PanelTexto.h"

class VentanaJug : public Pantalla
{
public:
// Recibe una referencia al gestor para poder cambiar pantallas desde  adentro
    explicit VentanaJug(GestorPantallas& gestor);
    void alMostrar() override;
    void alOcultar() override;
    void actualizar(float dt) override;
    void dibujar(sf::RenderWindow& ventana) override;
    void cargarRec();
    void ejecutarAccion(int i);
    void manejarEvento(const sf::Event& evento) override;
    void CargarJugadores();
private:
    GestorPantallas& m_gestor;
    sf::Font m_fuente;
    sf::Text m_texto;
    sf::Font fuenteBotonera;
    sf::Texture texturaFondo;
    sf::Sprite spriteFondo;

    sf::Texture texturaJug1;
    sf::Sprite spriteJug1;
    sf::Text nombreJug1;

    sf::Texture texturaJug2;
    sf::Sprite spriteJug2;
    sf::Text nombreJug2;


    Botonera botonera;
    Panel panelJug1;
    Panel panelJug2;
};
