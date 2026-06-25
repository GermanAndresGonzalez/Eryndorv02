
#pragma once
#include "Pantalla.h"
#include "GestorPantallas.h"
#include "PanelTexto.h"
#include "botonera.h"
#include "explorarCueva.h"
#include "crafteo.h"
#include "crafteoMan.h"

/*
struct material
{
    int id;
    int cantidad;
};
*/
class VentanaCrafteo : public Pantalla
{
public:
// Recibe una referencia al gestor para poder cambiar pantallas desde  adentro
    explicit VentanaCrafteo(GestorPantallas& gestor);
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
    void obtenerVisibles();
    //void ManejoPartida();
    void actualizarNombreJug(const std::string& nombre);
    Inventario inventarioJug;
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
    sf::Text nombreJug;
    sf::Text nombreCue;
    sf::Text txtPanelJug;
    sf::Text txtPanelJug2;


    sf::Text txtPanelCue;
    sf::Text txtPanelCueDos;
    std::string nomcadJug;
    std::string nomcadCueva;
    bool guardado=false;


    CrafteoMan m_craftear;
    Material materiales;


};
