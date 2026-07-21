#pragma once

class Partidas
{
public:

    Partidas();
    Partidas(int id, int idPersonaje, int turnoJugador, int vidasJugador, int idNivel, int vidaMaxima, int vidaActual, int Arma, int Armadura, int vidaArma, int vidaArmadura);

    int getId() const;
    int getIdPersonaje() const;
    int getIdNivel() const;

    int getVidasJugador() const;
    void setVidasJugador(int vidas);
    void agregarVidasJugador(int vidas);

    int getVidaMaxima() const;

    int getArma() const;
    int getVidaArma() const;
    int getArmadura() const;
    int getVidaArmadura() const;

    int getVidaActual() const;
    int getTurnoJugador() const;

    bool estaEliminada() const;

    void setID(int _id);
    void setEliminado(bool _eliminado);


    bool getEliminado() const;


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
    int Arma;
    int vidaArma;
    int Armadura;
    int vidaArmadura;
    bool eliminado;
};
