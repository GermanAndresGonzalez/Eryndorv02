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


void ExplorCueva::explorarCueva(Panel& panel,sf::Text& texto)
{
    if (turnosCueva >0)
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
    int encontrado;
    int idItem;
    material.id=invCueva.valorAleatorio(0,2);
    material.cantidad=invCueva.valorAleatorio(10);
    return material;
}

std::string ExplorCueva::Informar(Material& material)
{
    std::string mensaje="Encontraste:\n"+std::to_string(material.cantidad)+" de "+inventarioJug.obtenerNombre(material.id)+"\n";
    return mensaje;
}
std::string ExplorCueva::Informar(Material& material,std::string lado)
{
    // Para el inventario del Jugador
    /*
    std::string mensaje;
    if(lado=="izquierda")
    {
        mensaje="Encontraste:\n"+std::to_string(material.cantidad)+" de "+inventarioJug.obtenerNombre(material.id)+"\n";
    }
    else
    {
        mensaje="Encontraste:\n"+std::to_string(material.cantidad)+" de "+inventarioJug.obtenerNombre(material.id)+"\n";
    }



    return mensaje;
    */
}

Inventario ExplorCueva::cargarInventario()
{
    //ventario inventarioJug;
    if (ArInventario.buscarPorID(partidaEx->partida, inventarioJug))
    {
        return inventarioJug; // ya está cargado
    }
    return Inventario(); // objeto vacío

}

bool ExplorCueva::agregarInventario()
{
    if (turnosCueva >0)
    {
        inventarioJug.agregarItem(material.id, material.cantidad);
        if(invCueva.restarItem(material.id, material.cantidad))
        {
            if (guardarInventario(inventarioJug))
            {
                return true;
            }
        }
    }

    return false;

}

void ExplorCueva::cargarPanel(Panel& panel,sf::Text& texto,std::string mensaje)
{
    texto.setPosition(panel.getPosInternaX()+10.f, panel.getPosInternaY()+50.f);
    texto.setString(mensaje);
}

void ExplorCueva::cargarPanel(Panel& panel,sf::Text& texto,sf::Text& texto2)
{
    inventarioJug=cargarInventario();
    texto.setPosition(panel.getPosInternaX()+10.f, panel.getPosInternaY()+50.f);
    texto.setString(inventarioJug.mostrarSlots("izquierda"));
    texto2.setPosition(panel.getPosInternaX()+230.f, panel.getPosInternaY()+50.f);
    texto2.setString(inventarioJug.mostrarSlots("derecha"));
}


void ExplorCueva::transferirMat()
{

}

// explorarCueva.cpp — forzar que el id siempre coincida con la partida
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
