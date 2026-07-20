#pragma once
#include "inventario.h"
#include "PanelTexto.h"
#include "datosPartida.h"
#include "ArchivoInventario.h"
#include "ArchivoPartidas.h"
#include "material.h"
#include "items_juego.h"
#include <SFML/Graphics.hpp>

// Resultado de consultar si se puede equipar un item (ver Equipar::consultarEquipar)
enum class ResultadoEquipar
{
    Equipado,               // no había nada equipado: se puede poner directo
    SinItemEnInventario,    // no hay unidades de ese item en el inventario
    YaEquipadoMaximo,       // ya está equipado el mismo item con vida máxima: bloqueado
    RequiereConfirmacion    // hay algo distinto (o no-full) equipado: hay que confirmar el cambio
};

// Info sobre el item actualmente equipado en el slot correspondiente (arma o armadura),
// necesaria para armar el mensaje de confirmación en la UI.
struct InfoEquipar
{
    ResultadoEquipar resultado = ResultadoEquipar::SinItemEnInventario;
    int idActual = 0;                  // id del item actualmente equipado (0 = nada)
    unsigned int vidaActual = 0;       // vida restante del item actualmente equipado
    unsigned int vidaMaximaActual = 0; // vida máxima de ese mismo item
    TipoItem tipo = RECURSO;           // tipo del item que se quiere equipar (ARMA/ARMADURA)
};

class Equipar
{
public:
    Equipar(Partida* _partida, int turnos);
    ~Equipar();

    // Llamar cada vez que se muestra VentanaExplo para descartar
    // cualquier inventario en memoria y cargar el de la partida activa
    void resetearInventario();

    void cargarPanel(Panel& panel, sf::Text& texto, std::string mensaje);
    void cargarPanel(Panel& panel, sf::Text& texto, sf::Text& texto2);

    void equipar(Panel& panel, sf::Text& texto);
    Material obtenerMaterial();
    std::string Informar(Material& material);
    std::string Informar(Material& material, std::string lado);
    void transferirMat();
    bool agregarInventario();
    bool guardarInventario(Inventario& inventario);
    bool guardarPartida();
    bool modificarPartida();
    void setTurnos(unsigned int _turnos);

    // Equipamiento de arma/armadura (ver ResultadoEquipar/InfoEquipar más arriba)
    InfoEquipar consultarEquipar(int idNuevo);
    bool confirmarEquipar(int idNuevo);

    Inventario cargarInventario();
    Partidas construirRegistroPartida();

private:
    int turnosCueva;

    ArchivoInventario ArInventario;
    ArchivoPartidas ArPartidas;

    //InventarioCueva invCueva;
    Inventario inventarioJug;
    Partida* partidaEx;
    Material material;
};
