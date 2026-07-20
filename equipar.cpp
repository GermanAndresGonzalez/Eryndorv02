#include "partidas.h"
#include "equipar.h"
#include "datosArchivos.h"
#include "ArchivoInventario.h"
#include "ArchivoPartidas.h"
#include "plantillaHeroes.h"
#include "eventos.h"
#include <string>

#include <iostream>
#include <SFML/Graphics.hpp>

namespace
{
const int CURACION_POCION = 25;
}


Equipar::Equipar(Partida* _partida, int turnos)
    :turnosCueva(turnos)
    ,ArInventario(RUTA_DAT_INVN)
    ,ArPartidas(RUTA_DAT_PART)
    ,partidaEx(_partida)
{
    material.cantidad=0;
    material.id=0;
}

Equipar::~Equipar()
{
}

void Equipar::setTurnos(unsigned int _turnos)
{
    turnosCueva=_turnos;
}

// ---------------------------------------------------------------------------
// resetearInventario: descarta cualquier dato en memoria y carga desde disco.
// Si no hay registro en disco para esta partida, deja inventarioJug vacío
// con el id correcto. Llamar siempre que cambie la partida activa.
// ---------------------------------------------------------------------------
void Equipar::resetearInventario()
{
    inventarioJug = Inventario();                    // objeto limpio en memoria
    inventarioJug.id = partidaEx->partida;           // id correcto desde ya

    // intentar cargar desde disco; si no existe, queda vacío (correcto)
    ArInventario.buscarPorID(partidaEx->partida, inventarioJug);

    std::cout << "Equipar::resetearInventario — partida="
              << partidaEx->partida
              << "  slots cargados (id en inv)=" << inventarioJug.id << "\n";
}

void Equipar::equipar(Panel& panel,sf::Text& texto)
{

    std::string mensaje="";
    cargarInventario();
    cargarPanel(panel,texto,mensaje);

}
/*
Material Equipar::obtenerMaterial()
{

    material.id=invCueva.valorAleatorio(0,3);
    material.cantidad=invCueva.valorAleatorio(10);
    return material;
}
*/

std::string Equipar::Informar(Material& material)
{
    std::string mensaje="Encontraste:\n"+std::to_string(material.cantidad)+" de "+inventarioJug.obtenerNombre(material.id)+"\n";
    return mensaje;
}

std::string Equipar::Informar(Material& material, std::string lado)
{
    // reservado para uso futuro
    return "";
}

// ---------------------------------------------------------------------------
// cargarInventario: sincroniza inventarioJug con el archivo.
// Si no hay registro para la partida actual, resetea a vacío con id correcto.
// ---------------------------------------------------------------------------
Inventario Equipar::cargarInventario()
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

bool Equipar::agregarInventario()
{
    if (turnosCueva > 0)
    {
        // Antes de agregar, recargar desde disco para no acumular
        // sobre datos de una sesión anterior en memoria
        cargarInventario();

        inventarioJug.agregarItem(material.id, material.cantidad);
        /*
        if (invCueva.restarItem(material.id, material.cantidad))
        {
            if (guardarInventario(inventarioJug))
                return true;
        }
        */
    }
    return false;
}

void Equipar::cargarPanel(Panel& panel, sf::Text& texto, std::string mensaje)
{
    texto.setPosition(panel.getPosInternaX()+10.f, panel.getPosInternaY()+50.f);
    texto.setString(mensaje);
}




void Equipar::cargarPanel(Panel& panel, sf::Text& texto, sf::Text& texto2)
{

    cargarInventario();   // siempre desde disco, nunca desde cache stale
    texto.setPosition(panel.getPosInternaX()+10.f, panel.getPosInternaY()+50.f);
    texto.setString(inventarioJug.mostrarSlots("izquierda"));
    texto2.setPosition(panel.getPosInternaX()+230.f, panel.getPosInternaY()+25.f);
    texto2.setString(inventarioJug.mostrarSlots("derecha"));

}

void Equipar::transferirMat()
{
    //Sin implementar
}





bool Equipar::guardarInventario(Inventario& inventario)
{
    inventario.id = partidaEx->partida;  // sincronizar antes de todo

    int posicion = ArInventario.buscarPosicionPorID(inventario.id);

    if (posicion >= 0)
        return ArInventario.modificar(posicion, inventario);

    return ArInventario.agregar(inventario);
}

Partidas Equipar::construirRegistroPartida()
{
    return Partidas(partidaEx->partida, partidaEx->id, partidaEx->turnoJugador,partidaEx->vidas, partidaEx->nivel, partidaEx->vidaMaxima,partidaEx->vidaActual,partidaEx->idArma, partidaEx->idArmadura,partidaEx->vidaArma,partidaEx->vidaArmadura);
}

bool Equipar::guardarPartida()
{
    std::cout << "GuardoPartida:"<<std::endl;
    std::cout << partidaEx->id<<std::endl;
    std::cout << partidaEx->partida<<std::endl;
    std::cout << partidaEx->nombre <<std::endl;

    if (ArPartidas.buscarPosicionPorID(partidaEx->partida) < 0)
    {
        Partidas registro = construirRegistroPartida();
        return ArPartidas.agregar(registro);   // solo AGREGA si no existe
    }
    return false;   // si ya existe el registro, no hace nada y devuelve false
}

bool Equipar::modificarPartida()
{
    int posicion = ArPartidas.buscarPosicionPorID(partidaEx->partida);
    if (posicion >= 0)
    {
        Partidas registro = construirRegistroPartida();
        return ArPartidas.modificar(posicion, registro);
    }
    return false;
}

// ---------------------------------------------------------------------------
// consultarEquipar: NO modifica nada. Solo determina qué se debe hacer si el
// jugador pide equipar idNuevo: equipar directo, avisar que no hay stock,
// bloquear (mismo item ya equipado con vida máxima) o pedir confirmación
// (hay otro item, o el mismo pero no está a full, equipado en ese slot).
// ---------------------------------------------------------------------------
InfoEquipar Equipar::consultarEquipar(int idNuevo)
{
    InfoEquipar info;

    Item itemNuevo = obtenerItemPorId(idNuevo);
    info.tipo = itemNuevo.getTipo();

    cargarInventario();   // siempre desde disco, nunca desde cache stale

    if (inventarioJug.obtenerCantidad(idNuevo) <= 0)
    {
        info.resultado = ResultadoEquipar::SinItemEnInventario;
        return info;
    }

    unsigned int idEquipado   = (info.tipo == ARMA) ? partidaEx->idArma   : partidaEx->idArmadura;
    unsigned int vidaEquipada = (info.tipo == ARMA) ? partidaEx->vidaArma : partidaEx->vidaArmadura;

    info.idActual   = static_cast<int>(idEquipado);
    info.vidaActual = vidaEquipada;

    if (idEquipado == 0)
    {
        // No hay nada equipado en ese slot: se pone directo, sin preguntar nada.
        info.resultado = ResultadoEquipar::Equipado;
        return info;
    }

    Item itemActual = obtenerItemPorId(idEquipado);
    info.vidaMaximaActual = itemActual.getVidaMaxima();

    if (idEquipado == static_cast<unsigned int>(idNuevo) && vidaEquipada >= info.vidaMaximaActual)
    {
        // Mismo item, ya a vida máxima: no tiene sentido reemplazarlo.
        info.resultado = ResultadoEquipar::YaEquipadoMaximo;
        return info;
    }

    // Item distinto, o el mismo pero no está a vida máxima: se puede cambiar,
    // pero hay que avisarle al jugador antes de hacerlo.
    info.resultado = ResultadoEquipar::RequiereConfirmacion;
    return info;
}

// ---------------------------------------------------------------------------
// confirmarEquipar: ejecuta el cambio. Se asume que la UI ya llamó a
// consultarEquipar() y, si hacía falta, ya confirmó con el jugador.
// - Si había algo equipado con vida máxima, vuelve al inventario.
// - Si había algo equipado sin vida máxima, se pierde (no vuelve).
// - Descuenta el item nuevo del inventario y lo deja equipado a vida máxima.
// - Persiste inventario y partida.
// ---------------------------------------------------------------------------
bool Equipar::confirmarEquipar(int idNuevo)
{
    Item itemNuevo = obtenerItemPorId(idNuevo);
    TipoItem tipo = itemNuevo.getTipo();

    cargarInventario();

    if (inventarioJug.obtenerCantidad(idNuevo) <= 0)
        return false;

    unsigned int idEquipado   = (tipo == ARMA) ? partidaEx->idArma   : partidaEx->idArmadura;
    unsigned int vidaEquipada = (tipo == ARMA) ? partidaEx->vidaArma : partidaEx->vidaArmadura;

    if (idEquipado != 0)
    {
        Item itemActual = obtenerItemPorId(idEquipado);
        if (vidaEquipada >= itemActual.getVidaMaxima())
        {
            // Estaba a vida máxima: vuelve al inventario.
            inventarioJug.agregarItem(idEquipado, 1);
        }
        // Si no estaba a vida máxima, se pierde: no se hace nada más.
    }

    if (!inventarioJug.quitarItem(idNuevo, 1))
        return false;

    unsigned int vidaMaximaNuevo = itemNuevo.getVidaMaxima();

    if (tipo == ARMA)
    {
        partidaEx->idArma   = idNuevo;
        partidaEx->vidaArma = vidaMaximaNuevo;
    }
    else
    {
        partidaEx->idArmadura   = idNuevo;
        partidaEx->vidaArmadura = vidaMaximaNuevo;
    }

    guardarInventario(inventarioJug);
    modificarPartida();

    return true;
}
