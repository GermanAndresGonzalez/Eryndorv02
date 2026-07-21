// VentanaAcerca.h
#pragma once
#include "Pantalla.h"
#include "botonera.h"
#include "GestorPantallas.h"
#include "PanelTexto.h"

class VentanaAcerca : public Pantalla
{
public:
    // Recibe una referencia al gestor para poder cambiar pantallas desde adentro
    explicit VentanaAcerca(GestorPantallas& gestor);
    void alMostrar() override;
    void alOcultar() override;
    void actualizar(float dt) override;
    void dibujar(sf::RenderWindow& ventana) override;
    void ejecutarAccion(int i);
    void manejarEvento(const sf::Event& evento) override;

    void cargarRec();

private:
    GestorPantallas& m_gestor;

    sf::Font m_fuenteTitulo;
    sf::Text m_titulo;
    sf::Text m_subtitulo;

    sf::Font m_fuentePanel;
    sf::Text m_textoIzq;
    sf::Text m_textoDer;

    Panel panelIzq;
    Panel panelDer;

    sf::Texture texturaFondo;
    sf::Sprite spriteFondo;

    sf::Font fuenteBotonera;
    Botonera botonera;
};
