#ifndef PERSONAJE_H
#define PERSONAJE_H

#include "item.h"

class Personaje {
private:
    char nombre[50];
    int nivel, vidaActual, vidaMaxima, ataque, defensa, oro;
    bool eliminado;
    const Item* armaEquipada;
    const Item* armaduraEquipada;
    int vidaArmaActual;
    int vidaArmaduraActual;

public:
    // Constructor
    Personaje(const char* nom, int niv, int vidaMax, int atk, int def, int oroInicial, bool elim);


    // Equipo: armas y armaduras

    void equiparArma(const Item* arma);
    void equiparArmadura(const Item* armadura);

    const Item* desequiparArma();
    const Item* desequiparArmadura();

    bool armaRota() const;
    bool armaduraRota() const;
    int getVidaArmaActual() const;
    int getVidaArmaduraActual() const;

    // Métodos principales
    int atacar();
    void recibirDanio(int danio);
    bool curar(int puntos);
    void agregarOro(int cantidad);
    bool gastarOro(int cantidad);

    // Getters
    const char* getNombre() const;
    int getAtaque() const;
    int getDefensa() const;
    int getNivel() const;
    int getVidaActual() const;
    int getVidaMaxima() const;
    int getOro() const;
    bool estaEliminado() const;
};

#endif // PERSONAJE_H
