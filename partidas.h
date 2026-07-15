#pragma once

class Partidas
{
public:


    Partidas();
    Partidas(int id, int idPersonaje, int turnoJugador, int idNivel, int vidaMaxima, int vidaActual);

    int getId() const;
    int getIdPersonaje() const;
    int getIdNivel() const;
    int getVidaMaxima() const;
    int getVidaActual() const;
    int getTurnoJugador() const;

    bool estaEliminada() const;

    void setID(int _id);
    void setEliminado(bool _eliminado);


    bool getEliminado();


    int ContarRegistros() const;
    void imprimirPartidas();

private:
    int id;
    int idPersonaje;
    int idNivel;
    int vidaMaxima;
    int vidaActual;
    int turnoJugador;
    bool eliminado;
};
