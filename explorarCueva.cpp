#include "partidas.h"
#include "explorarCueva.h"
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


ExplorCueva::ExplorCueva(Partida* _partida, int turnos)
    :invCueva(999,999,999,999)
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
        Evento ev=seleccionarEvento();
        std::cout << ev.tipo << std::endl;
        std::cout << ev.idMaterial << std::endl;
        std::cout << ev.cantidad << std::endl;

        //std::string mensaje="";
        std::string mensaje=ev.mensaje;

        if (ev.idMaterial>=0)
        {
            std::cout << "idMaterial>=0: " << ev.idMaterial << std::endl;
            material.id=ev.idMaterial;
            material.cantidad=ev.cantidad;
            mensaje=Informar(material);
        }
        else
        {
            mensaje=ev.mensaje;
            if ((ev.idMaterial==-1)&&(ev.tipo==2))
            {
                if (!curar(texto))
                {
                    mensaje= "No se pudo curar";
                }
                else
                {
                    mensaje=ev.mensaje;
                    guardarPartida();
                }
            }
            if ((ev.idMaterial==-1)&&(ev.tipo==3))
            {
                partidaEx->turnoComput+=ev.cantidad;
                guardarPartida();
                //mensaje= "No se pudo agregar\nturnos";

            }

        }

        /*
        std::cout << "Mensaje: "<< mensaje << std::endl;

        std::cout << "Fin del mensaje.\n" << std::endl;

        std::cout << "\nInicio mensaje struct:\n" << std::endl;
        std::cout << ev.mensaje << std::endl;
        std::cout << "Fin mensaje struct.\n" << std::endl;
        */








        //material=obtenerMaterial();
        //mensaje=Informar(material);
        cargarInventario();
        cargarPanel(panel,texto,mensaje);
    }
}

Material ExplorCueva::obtenerMaterial()
{
    material.id=invCueva.valorAleatorio(0,3);
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

void ExplorCueva::cargarVida(Panel& panel, sf::Text& texto2, sf::Text& texto3)
{
    sf::FloatRect limites = texto2.getGlobalBounds();
    float posic_y = limites.top+limites.height;
    texto3.setPosition(panel.getPosInternaX()+10.f, posic_y+10.f);
    int vidACtual = partidaEx->vidaActual;
    texto3.setString("Vida actual: "+std::to_string(vidACtual));

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
    //Sin implementar
}

bool ExplorCueva::curar(sf::Text& text)
{
    const int idCura = inventarioJug.obtenerID("POCION CURATIVA");
    std::cout << "[curar] idCura=" << idCura << std::endl;

    if (idCura < 0 || !inventarioJug.tieneCantidadNecesaria(idCura, 1))
    {
        std::cout << "[curar] corta: no hay pocion o id invalido\n";
        return false;
    }

    const int vidMaxima = plantillasHeroes[partidaEx->id - 1].vidaMaxima;
    int vidaNueva = static_cast<int>(partidaEx->vidaActual) + CURACION_POCION;

    std::cout << "[curar] vidaActual=" << partidaEx->vidaActual
               << " vidMaxima=" << vidMaxima
               << " vidaNueva(antes de clamp)=" << vidaNueva << std::endl;

    if (vidaNueva > vidMaxima)
    {
        vidaNueva = vidMaxima;
    }

    std::cout << "[curar] vidaNueva(final)=" << vidaNueva << std::endl;

    if (static_cast<unsigned int>(vidaNueva) == partidaEx->vidaActual)
    {
        std::cout << "[curar] corta: vidaNueva == vidaActual (ya esta al tope o no cambia)\n";
        return false;
    }

    partidaEx->vidaActual = static_cast<unsigned int>(vidaNueva);
    partidaEx->turnoJugador+=100;

    if (inventarioJug.quitarItem(idCura, 1))
    {
        guardarInventario(inventarioJug);
        modificarPartida();
        std::cout << "[curar] EXITO: vidaActual ahora=" << partidaEx->vidaActual << std::endl;
        return true;
    }
    std::cout << "[curar] corta: quitarItem fallo\n";
    return false;
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
    return Partidas(partidaEx->partida, partidaEx->id, partidaEx->turnoJugador,partidaEx->vidas, partidaEx->nivel, partidaEx->vidaMaxima,partidaEx->vidaActual);
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
        return ArPartidas.agregar(registro);   // solo AGREGA si no existe
    }
    return false;   // si ya existe el registro, no hace nada y devuelve false
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
