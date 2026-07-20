
#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <string>

struct Partida
{
    int partida;
    unsigned int nivel;
    unsigned int id;
    unsigned int turnoJugador;
    unsigned int turnoComput;
    unsigned int vidas;
    std::string pantallaAnterior;
    char nombre[50];
    unsigned int vidaActual = 0;
    unsigned int vidaMaxima = 0;
    unsigned int idArma = 0;
    unsigned int idArmadura = 0;
    unsigned int vidaArma = 0;
    unsigned int vidaArmadura = 0;

};


#endif
