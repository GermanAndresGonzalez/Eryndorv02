#ifndef PERSONAJE_H
#define PERSONAJE_H

#include "item.h"

class Personaje {
private:
    char nombre[50];
    int nivel, vidaActual, vidaMaxima, ataque, defensa, oro;
    bool eliminado;
    Item* armaEquipada;      // Cambiar de const Item* a Item* para poder crear copias
    Item* armaduraEquipada;  // Cambiar de const Item* a Item* para poder crear copias
    int vidaArmaActual;
    int vidaArmaduraActual;

public:
    // Constructor
    Personaje(const char* nom, int niv, int vidaMax, int atk, int def, int oroInicial, bool elim);
    ~Personaje(); // Agregar destructor para liberar los Items

    // Equipo: armas y armaduras
    void equiparArma(Item* arma);      // Cambiar a Item*
    void equiparArmadura(Item* armadura); // Cambiar a Item*

    Item* desequiparArma();    // Cambiar a Item*
    Item* desequiparArmadura(); // Cambiar a Item*

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
    
    // Nuevos getters para el equipamiento
    const Item* getArmaEquipada() const;
    const Item* getArmaduraEquipada() const;
};

#endif // PERSONAJE_H