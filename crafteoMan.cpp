#include "Partidas.h"
#include "crafteoMan.h"
#include "crafteo.h"
#include "datosArchivos.h"
#include "ArchivoInventario.h"
#include "ArchivoPartidas.h"

#include <iostream>

CrafteoMan::CrafteoMan(Partida* _partida, int turnos)
    :turnosCueva(turnos)
    ,invCueva(999,999,999)
    ,ArInventario(RUTA_DAT_INVN)
    ,ArPartidas(RUTA_DAT_PART)
    ,partidaEx(_partida)
{
    material.cantidad=0;
    material.id=0;
}

CrafteoMan::~CrafteoMan()
{
}

void CrafteoMan::setTurnos(unsigned int _turnos)
{
    turnosCueva=_turnos;
}

// ---------------------------------------------------------------------------
// resetearInventario: descarta cualquier dato en memoria y carga desde disco.
// Si no hay registro en disco para esta partida, deja inventarioJug vacío
// con el id correcto. Llamar siempre que cambie la partida activa.
// ---------------------------------------------------------------------------
void CrafteoMan::resetearInventario()
{
    inventarioJug = Inventario();                    // objeto limpio en memoria
    inventarioJug.id = partidaEx->partida;           // id correcto desde ya

    // intentar cargar desde disco; si no existe, queda vacío (correcto)
    ArInventario.buscarPorID(partidaEx->partida, inventarioJug);

    std::cout << "CrafteoMan::resetearInventario — partida="
              << partidaEx->partida
              << "  slots cargados (id en inv)=" << inventarioJug.id << "\n";
}

void CrafteoMan::crafteoCueva(Panel& panel,sf::Text& texto)
{
    if (turnosCueva > 0)
    {
        std::string mensaje="";
        mensaje="Usa tu inventario para\ncrear objetos.\nNecesitas 5 elementos\npara crear.";
        cargarInventario();
        cargarPanel(panel,texto,mensaje);
    }
}



std::string CrafteoMan::Informar(Material& material)
{
    std::string mensaje="Encontraste:\n"+std::to_string(material.cantidad)+" de "+inventarioJug.obtenerNombre(material.id)+"\n";
    return mensaje;
}

std::string CrafteoMan::Informar(Material& material, std::string lado)
{
    // reservado para uso futuro
    return "";
}

// ---------------------------------------------------------------------------
// cargarInventario: sincroniza inventarioJug con el archivo.
// Si no hay registro para la partida actual, resetea a vacío con id correcto.
// ---------------------------------------------------------------------------
Inventario CrafteoMan::cargarInventario()
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

bool CrafteoMan::agregarInventario()
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

void CrafteoMan::cargarPanel(Panel& panel, sf::Text& texto, std::string mensaje)
{
    texto.setPosition(panel.getPosInternaX()+10.f, panel.getPosInternaY()+50.f);
    texto.setString(mensaje);
}

void CrafteoMan::cargarPanel(Panel& panel, sf::Text& texto, sf::Text& texto2)
{
    cargarInventario();   // siempre desde disco, nunca desde cache stale
    texto.setPosition(panel.getPosInternaX()+10.f, panel.getPosInternaY()+50.f);
    texto.setString(inventarioJug.mostrarSlots("izquierda"));
    texto2.setPosition(panel.getPosInternaX()+230.f, panel.getPosInternaY()+25.f);
    texto2.setString(inventarioJug.mostrarSlots("derecha"));
}

void CrafteoMan::transferirMat()
{
}

bool CrafteoMan::guardarInventario(Inventario& inventario)
{
    inventario.id = partidaEx->partida;  // sincronizar antes de todo

    int posicion = ArInventario.buscarPosicionPorID(inventario.id);

    if (posicion >= 0)
        return ArInventario.modificar(posicion, inventario);

    return ArInventario.agregar(inventario);
}

Partidas CrafteoMan::construirRegistroPartida()
{
    return Partidas(partidaEx->partida, partidaEx->id, partidaEx->nivel);
}

bool CrafteoMan::guardarPartida()
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

bool CrafteoMan::modificarPartida()
{
    int posicion = ArPartidas.buscarPosicionPorID(partidaEx->partida);
    if (posicion >= 0)
    {
        Partidas registro = construirRegistroPartida();
        return ArPartidas.modificar(posicion, registro);
    }
    return false;
}


//bool CrafteoMan::pocionCurativa(sf::Text& texto, Panel& panel)
bool CrafteoMan::pocionCurativa(sf::Text& texto)
{
    Inventario inventario;
    inventario=cargarInventario();
    if(Crafteo::puedoCrearPocionCurativa(inventario))
    {
        Crafteo::crearPocionCurativa(inventario);
        int pos = ArInventario.buscarPosicionPorID(partidaEx->partida);
        if (pos >= 0)
            texto.setString("Creaste una Pocion curativa");
            return ArInventario.modificar(pos, inventario);
        return ArInventario.agregar(inventario);
    }

}
bool CrafteoMan::espadaMadera(sf::Text& texto)
{
    Inventario inventario;
    inventario=cargarInventario();
    if(Crafteo::puedoCrearEspadaMadera(inventario))
    {
        Crafteo::crearEspadaMadera(inventario);
        int pos = ArInventario.buscarPosicionPorID(partidaEx->partida);

        if (pos >= 0)
            texto.setString("Creaste una Espada\nde Madera");
            return ArInventario.modificar(pos, inventario);
        return ArInventario.agregar(inventario);
    }
}

