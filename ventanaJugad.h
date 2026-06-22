// VentanaJug.h
#pragma once
#include "Pantalla.h"
#include "GestorPantallas.h"
#include "botonera.h"
#include "PanelTexto.h"
#include "ArchivoPartidas.h"

class VentanaJug : public Pantalla
{
public:
    explicit VentanaJug(GestorPantallas& gestor);
    void alMostrar() override;
    void alOcultar() override;
    void actualizar(float dt) override;
    void dibujar(sf::RenderWindow& ventana) override;
    void cargarRec();
    void ejecutarAccion(int i);
    void manejarEvento(const sf::Event& evento) override;
    void CargarJugadores();
    void cargarPartidas();

private:
    bool primera=true;
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
    sf::Text jugadElegido;

    ArchivoPartidas archivoPartidas;
    Botonera botonera;
    Panel panelJug1;
    Panel panelJug2;

    // Selección visual del jugador (NO modifica Partida hasta confirmar)
    // 0 = ninguno, 1 = Kael Draven, 2 = Lyra Voss
    int m_jugadorSeleccionado = 0;

    void actualizarSeleccionVisual();
};
