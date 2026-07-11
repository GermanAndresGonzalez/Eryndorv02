
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
    std::string pantallaAnterior;
    char nombre[50];
    unsigned int vidaActual = 0;
};


#endif
