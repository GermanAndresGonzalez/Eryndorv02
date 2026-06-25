#pragma once
#include "inventario.h"
#include "inventarioCueva.h"
#include "PanelTexto.h"
#include "Partida.h"
#include "ArchivoInventario.h"
#include "ArchivoPartidas.h"
#include "material.h"
#include <SFML/Graphics.hpp>




class ExplorCueva
{
public:
    ExplorCueva(Partida* _partida, int turnos);
    ~ExplorCueva();

    // Llamar cada vez que se muestra VentanaExplo para descartar
    // cualquier inventario en memoria y cargar el de la partida activa
    void resetearInventario();

    void cargarPanel(Panel& panel, sf::Text& texto, std::string mensaje);
    void cargarPanel(Panel& panel, sf::Text& texto, sf::Text& texto2);
    void explorarCueva(Panel& panel, sf::Text& texto);
    Material obtenerMaterial();
    std::string Informar(Material& material);
    std::string Informar(Material& material, std::string lado);
    void transferirMat();
    bool agregarInventario();
    bool guardarInventario(Inventario& inventario);
    bool guardarPartida();
    bool modificarPartida();
    void setTurnos(unsigned int _turnos);
    Inventario cargarInventario();
    Partidas construirRegistroPartida();

private:
    int turnosCueva;

    ArchivoInventario ArInventario;
    ArchivoPartidas ArPartidas;

    InventarioCueva invCueva;
    Inventario inventarioJug;
    Partida* partidaEx;
    Material material;
};
