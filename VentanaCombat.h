
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
// Recibe una referencia al gestor para poder cambiar pantallas desde  adentro
    explicit VentanaCombat(GestorPantallas& gestor);
    void alMostrar() override;
    void alOcultar() override;
    void actualizar(float dt) override;
    void dibujar(sf::RenderWindow& ventana) override;
    void cargarRec();
    void v_explorar();
    void v_agregar();
    void v_actualizar();

    void ejecutarAccion(int i);
    void manejarEvento(const sf::Event& evento);
    //void ManejoPartida();
    void actualizarNombreJug(const std::string& nombre);




    PanelConImagen panelJug;
    PanelConImagen panelEne;


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
    sf::Text nombreJug;
    sf::Text nombreEne; //nombreCue
    sf::Text txtPanelJug;
    sf::Text txtPanelJug2;

    sf::Text txtPanelCue;
    std::string nomcadJug;
    std::string nomcadEnemigo;
    bool guardado=false;
    int idJugador;
    int idEnemigo;


    Combatir m_combate;
    Material materiales;


};
