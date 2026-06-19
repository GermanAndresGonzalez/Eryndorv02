
#pragma once
#include "Pantalla.h"
#include "GestorPantallas.h"
#include "PanelTexto.h"
#include "botonera.h"


class VentanaExplo : public Pantalla
{
public:
// Recibe una referencia al gestor para poder cambiar pantallas desde  adentro
    explicit VentanaExplo(GestorPantallas& gestor);
    void alMostrar() override;
    void alOcultar() override;
    void actualizar(float dt) override;
    void dibujar(sf::RenderWindow& ventana) override;
    void cargarRec();
    void CargarJugadores();
    void ejecutarAccion(int i);
    void manejarEvento(const sf::Event& evento);
    void ManejoPartida();

    Panel panelJug;
    Panel panelCueva;
private:
    GestorPantallas& m_gestor;
    Botonera botonera;
    bool partidaNueva=false;
    sf::Sprite spriteFondo;
    sf::Texture texturaFondo;
    sf::Font fuenteBotonera;
    sf::Font m_fuente;
    sf::Text m_texto;
    sf::Text m_turnos;
    sf::Text txtPanelJug;
    sf::Text txtPanelCue;

};
