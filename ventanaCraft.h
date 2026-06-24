
#pragma once
#include "Pantalla.h"
#include "GestorPantallas.h"
#include "PanelTexto.h"
#include "botonera.h"
#include "explorarCueva.h"




class VentanaCraft : public Pantalla
{
public:
// Recibe una referencia al gestor para poder cambiar pantallas desde  adentro
    explicit VentanaCraft(GestorPantallas& gestor);
    void alMostrar() override;
    void alOcultar() override;
    void actualizar(float dt) override;
    void dibujar(sf::RenderWindow& ventana) override;
    void cargarRec();
    void v_craftear();
    void v_agregar();
    void v_actualizar();

    void ejecutarAccion(int i);
    void manejarEvento(const sf::Event& evento);
    //void ManejoPartida();
    void actualizarNombreJug(const std::string& nombre);




    Panel panelJug;
    Panel panelCueva;


private:
    GestorPantallas& m_gestor;
    bool partidaNueva=false;

    private:
    sf::Texture texturaFondo;
    sf::Sprite spriteFondo;
    sf::RectangleShape fondo;

    sf::Font m_fuente;
    sf::Font fuenteBotonera;
    Botonera botoneraCra;
    Panel panelInvJug;
    Panel panelCrafteo;
    sf::Text m_turnos;
    sf::Text m_texto;
    sf::Text textoTitulo;
    sf::Text textoMensaje;

    //RegistroPartida partida;






    sf::Text nombreJug;
    sf::Text nombreCue;
    sf::Text txtPanelJug;
    sf::Text txtPanelJug2;

    sf::Text txtPanelCue;
    std::string nomcadJug;
    std::string nomcadCueva;
    bool guardado=false;


    ExplorCueva m_craftear;
    Material materiales;


};
