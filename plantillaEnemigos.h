

#ifndef DATOS_PLANTILLA_ENEMIGOS_H
#define DATOS_PLANTILLA_ENEMIGOS_H

struct PlantillaEnemigo
{
    const char* imagen;
    const char* nombre;
    const char* descripcion;
    int vidaMaxima;
    int defensa;
    int ataque;
    int oroOtorgado;
    int expOtorgada;
};

extern const PlantillaEnemigo plantillasEnemigos[4];

#endif
