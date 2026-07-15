#pragma once

class Partidas
{
public:


    Partidas();
    Partidas(int id, int idPersonaje, int turnoJugador, int vidasJugador, int idNivel, int vidaMaxima, int vidaActual);

    int getId() const;
    int getIdPersonaje() const;
    int getIdNivel() const;
    
    int getVidasJugador() const;
    void setVidasJugador(int vidas);
    void agregarVidasJugador(int vidas);

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
    int vidasJugador;
    bool eliminado;
};
