#include "partidas.h"
#include <iostream>

//#include "archivos.h"

Partidas::Partidas()
{
    id = 0;
    idPersonaje = 0;
    idNivel = 0;
    eliminado = false;
}

Partidas::Partidas(int id, int idPersonaje, int turnoJugador, int vidasJugador, int idNivel, int vidaMaxima, int vidaActual)
{
    this->id = id;
    this->idPersonaje = idPersonaje;
    this->turnoJugador = turnoJugador;
    this->vidasJugador = vidasJugador;
    this->idNivel = idNivel;
    this->vidaActual = vidaActual;
    this->vidaMaxima = vidaMaxima;
    eliminado = false;
}


bool Partidas::getEliminado()
{
    return eliminado;
}
void Partidas::setID(int _id)
{
    id=_id;
}
void Partidas::setEliminado(bool _eliminado)
{
    eliminado=_eliminado;
}

int Partidas::getId() const
{
    return id;
}

int Partidas::ContarRegistros() const
{
    return id;
}

int Partidas::getIdPersonaje() const
{
    return idPersonaje;
}

int Partidas::getIdNivel() const
{
    return idNivel;
}

int Partidas::getVidaMaxima() const
{
    return vidaMaxima;
}

int Partidas::getVidaActual() const
{
    return vidaActual;
}

int Partidas::getTurnoJugador() const
{
    return turnoJugador;
}


bool Partidas::estaEliminada() const
{
    return eliminado;
}


void Partidas::imprimirPartidas()
{
    std::cout << "ID de partida: " << getId()<<std::endl;
    std::cout << "ID de Personaje: " << getIdPersonaje()<<std::endl;
    std::cout << "ID de nivel: " << getIdNivel()<<std::endl;
    std::cout << "Eliminada: " << (estaEliminada()==false?"Activa":"Eliminada")<<std::endl;

}

int Partidas::getVidasJugador() const
{
    return vidasJugador;
}
void Partidas::setVidasJugador(int vidas)
{
    vidasJugador = vidas;
}
void Partidas::agregarVidasJugador(int vidas)
{
    vidasJugador += vidas;
}
