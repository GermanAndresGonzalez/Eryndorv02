#include "Partidas.h"
#include "explorarCueva.h"
#include "datosArchivos.h"
#include "ArchivoInventario.h"
#include "ArchivoPartidas.h"

#include <iostream>

ExplorCueva::ExplorCueva(Partida* _partida, int turnos)
    :invCueva(999,999,999)
    ,turnosCueva(turnos)
    ,ArInventario(RUTA_DAT_INVN)
    ,ArPartidas(RUTA_DAT_PART)
    ,partidaEx(_partida)
{
    material.cantidad=0;
    material.id=0;
}

ExplorCueva::~ExplorCueva()
{
}

void ExplorCueva::setTurnos(unsigned int _turnos)
{
    turnosCueva=_turnos;
}

// ---------------------------------------------------------------------------
// resetearInventario: descarta cualquier dato en memoria y carga desde disco.
// Si no hay registro en disco para esta partida, deja inventarioJug vacío
// con el id correcto. Llamar siempre que cambie la partida activa.
// ---------------------------------------------------------------------------
void ExplorCueva::resetearInventario()
{
    inventarioJug = Inventario();                    // objeto limpio en memoria
    inventarioJug.id = partidaEx->partida;           // id correcto desde ya

    // intentar cargar desde disco; si no existe, queda vacío (correcto)
    ArInventario.buscarPorID(partidaEx->partida, inventarioJug);

    std::cout << "ExplorCueva::resetearInventario — partida="
              << partidaEx->partida
              << "  slots cargados (id en inv)=" << inventarioJug.id << "\n";
}

void ExplorCueva::explorarCueva(Panel& panel,sf::Text& texto)
{
    if (turnosCueva > 0)
    {
        std::string mensaje="";
        material=obtenerMaterial();
        mensaje=Informar(material);
        cargarInventario();
        cargarPanel(panel,texto,mensaje);
    }
}

Material ExplorCueva::obtenerMaterial()
{
    material.id=invCueva.valorAleatorio(0,2);
    material.cantidad=invCueva.valorAleatorio(10);
    return material;
}

std::string ExplorCueva::Informar(Material& material)
{
    std::string mensaje="Encontraste:\n"+std::to_string(material.cantidad)+" de "+inventarioJug.obtenerNombre(material.id)+"\n";
    return mensaje;
}

std::string ExplorCueva::Informar(Material& material, std::string lado)
{
    // reservado para uso futuro
    return "";
}

// ---------------------------------------------------------------------------
// cargarInventario: sincroniza inventarioJug con el archivo.
// Si no hay registro para la partida actual, resetea a vacío con id correcto.
// ---------------------------------------------------------------------------
Inventario ExplorCueva::cargarInventario()
{
    Inventario temp;
    if (ArInventario.buscarPorID(partidaEx->partida, temp))
    {
        inventarioJug = temp;   // hay datos en disco → usarlos
    }
    else
    {
        // no existe en disco → asegurarse de que la memoria esté limpia
        inventarioJug = Inventario();
        inventarioJug.id = partidaEx->partida;
    }
    return inventarioJug;
}

bool ExplorCueva::agregarInventario()
{
    if (turnosCueva > 0)
    {
        // Antes de agregar, recargar desde disco para no acumular
        // sobre datos de una sesión anterior en memoria
        cargarInventario();

        inventarioJug.agregarItem(material.id, material.cantidad);
        if (invCueva.restarItem(material.id, material.cantidad))
        {
            if (guardarInventario(inventarioJug))
                return true;
        }
    }
    return false;
}

void ExplorCueva::cargarPanel(Panel& panel, sf::Text& texto, std::string mensaje)
{
    texto.setPosition(panel.getPosInternaX()+10.f, panel.getPosInternaY()+50.f);
    texto.setString(mensaje);
}

void ExplorCueva::cargarPanel(Panel& panel, sf::Text& texto, sf::Text& texto2)
{
    cargarInventario();   // siempre desde disco, nunca desde cache stale
    texto.setPosition(panel.getPosInternaX()+10.f, panel.getPosInternaY()+50.f);
    texto.setString(inventarioJug.mostrarSlots("izquierda"));
    texto2.setPosition(panel.getPosInternaX()+230.f, panel.getPosInternaY()+25.f);
    texto2.setString(inventarioJug.mostrarSlots("derecha"));
}

void ExplorCueva::transferirMat()
{
}

bool ExplorCueva::guardarInventario(Inventario& inventario)
{
    inventario.id = partidaEx->partida;  // sincronizar antes de todo

    int posicion = ArInventario.buscarPosicionPorID(inventario.id);

    if (posicion >= 0)
        return ArInventario.modificar(posicion, inventario);

    return ArInventario.agregar(inventario);
}

Partidas ExplorCueva::construirRegistroPartida()
{
    return Partidas(partidaEx->partida, partidaEx->id, partidaEx->nivel);
}

bool ExplorCueva::guardarPartida()
{
    std::cout << "GuardoPartida:"<<std::endl;
    std::cout << partidaEx->id<<std::endl;
    std::cout << partidaEx->partida<<std::endl;
    std::cout << partidaEx->nombre <<std::endl;

    if (ArPartidas.buscarPosicionPorID(partidaEx->partida) < 0)
    {
        Partidas registro = construirRegistroPartida();
        return ArPartidas.agregar(registro);
    }
    return false;
}

bool ExplorCueva::modificarPartida()
{
    int posicion = ArPartidas.buscarPosicionPorID(partidaEx->partida);
    if (posicion >= 0)
    {
        Partidas registro = construirRegistroPartida();
        return ArPartidas.modificar(posicion, registro);
    }
    return false;
}
