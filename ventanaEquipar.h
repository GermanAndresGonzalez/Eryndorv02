
#pragma once
#include "Pantalla.h"
#include "GestorPantallas.h"
#include "PanelTexto.h"
#include "botonera.h"
#include "equipar.h"


class VentanaEquipar : public Pantalla
{
public:
// Recibe una referencia al gestor para poder cambiar pantallas desde  adentro
    explicit VentanaEquipar(GestorPantallas& gestor);
    void alMostrar() override;
    void alOcultar() override;
    void actualizar(float dt) override;
    void dibujar(sf::RenderWindow& ventana) override;
    void cargarRec();

    void ejecutarAccion(int i);
    void manejarEvento(const sf::Event& evento);
    void actualizarNombreJug(const std::string& nombre);

    // Vuelve a leer el inventario y redibuja el panel (llamar tras cualquier cambio)
    void refrescarPanel();

    // Botones 0-3: intenta equipar idItem (ver Equipar::consultarEquipar/confirmarEquipar)
    void intentarEquipar(int idItem);

    // Persiste en disco el estado actual de la partida (puntero Partida + inventario).
    // Llamar siempre que refrescarPanel() refleje un cambio real (equipar, etc).
    void guardarCambios();

    Panel panelJug;


private:
    GestorPantallas& m_gestor;
    Botonera botonera;
    sf::Sprite spriteFondo;
    sf::Texture texturaFondo;
    sf::Font fuenteBotonera;
    sf::Font m_fuente;
    sf::Text m_texto;
    sf::Text nombreJug;
    sf::Text txtPanelJug;
    sf::Text txtPanelJug2;

    std::string nomcadJug;

    Equipar m_equipar;
};
