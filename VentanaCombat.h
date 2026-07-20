#pragma once
#include "Pantalla.h"
#include "GestorPantallas.h"
#include "panelTxtImg.h"
#include "botonera.h"
#include "combate.h"
#include "material.h"

class VentanaCombat : public Pantalla
{
public:
    explicit VentanaCombat(GestorPantallas& gestor);
    void alMostrar() override;
    void alOcultar() override;
    void actualizar(float dt) override;
    void dibujar(sf::RenderWindow& ventana) override;
    void cargarRec();

    void ejecutarAccion(int i);
    void manejarEvento(const sf::Event& evento);
    void actualizarNombreJug(const std::string& nombre);

    PanelConImagen panelJug;
    PanelConImagen panelEne;

private:
    void actualizarEstado();
    void actualizarVidas();
    void actualizarEquipamiento(); // Nuevo método

    GestorPantallas& m_gestor;
    Botonera botonera;
    bool partidaNueva = false;
    sf::Sprite spriteFondo;
    sf::Texture texturaFondo;
    sf::Font fuenteBotonera;
    sf::Font m_fuente;
    sf::Text m_texto;
    sf::Text m_turnos;
    sf::Text nombreJug;
    sf::Text nombreEne;
    sf::Text txtPanelJug;
    sf::Text txtPanelJug2;
    sf::Text txtPanelCue;

    sf::Text vidaJug;
    sf::Text vidaEne;
    sf::Text infoArma;      // Nuevo: para mostrar información del arma
    sf::Text infoArmadura;  // Nuevo: para mostrar información de la armadura

    std::string nomcadJug;
    std::string nomcadEnemigo;
    int idJugador;
    int idEnemigo;

    Combatir m_combate;
    Material materiales;
};