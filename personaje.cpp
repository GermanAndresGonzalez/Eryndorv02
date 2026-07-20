#include "personaje.h"

#include <cstring>

Personaje::Personaje(const char* nom, int niv, int vidaMax, int atk, int def, int oroInicial, bool elim)
{
    std::strncpy(nombre, nom, sizeof(nombre) - 1);
    nombre[sizeof(nombre) - 1] = '\0';

    nivel = niv;
    vidaMaxima = vidaMax;
    vidaActual = vidaMax;
    ataque = atk;
    defensa = def;
    oro = oroInicial;
    eliminado = elim;
    armaEquipada = nullptr;
    armaduraEquipada = nullptr;
    vidaArmaActual = 0;
    vidaArmaduraActual = 0;
}

void Personaje::equiparArma(const Item* arma)
{
    armaEquipada = arma;
    vidaArmaActual = (arma != nullptr) ? arma->getVidaMaxima() : 0;
}

void Personaje::equiparArmadura(const Item* armadura)
{
    armaduraEquipada = armadura;
    vidaArmaduraActual = (armadura != nullptr) ? armadura->getVidaMaxima() : 0;
}

const Item* Personaje::desequiparArma()
{
    if (armaEquipada == nullptr) return nullptr;

    const Item* item = armaEquipada;
    bool esComoNueva = (vidaArmaActual == item->getVidaMaxima());

    armaEquipada = nullptr;
    vidaArmaActual = 0;

    return esComoNueva ? item : nullptr;  // solo vuelve al inventario si está intacta
}

const Item* Personaje::desequiparArmadura()
{
    if (armaduraEquipada == nullptr) return nullptr;

    const Item* item = armaduraEquipada;
    bool esComoNueva = (vidaArmaduraActual == item->getVidaMaxima());

    armaduraEquipada = nullptr;
    vidaArmaduraActual = 0;

    return esComoNueva ? item : nullptr;
}

bool Personaje::armaRota() const
{
    return armaEquipada == nullptr;
}

bool Personaje::armaduraRota() const
{
    return armaduraEquipada == nullptr;
}

int Personaje::getVidaArmaActual() const
{
    return vidaArmaActual;
}

int Personaje::getVidaArmaduraActual() const
{
    return vidaArmaduraActual;
}

int Personaje::atacar()
{
    int danio = ataque + (nivel * 2);

    if (armaEquipada != nullptr && armaEquipada->getTipo() == ARMA)
    {
        danio += armaEquipada->getBonusAtaque();

        vidaArmaActual--;
        if (vidaArmaActual <= 0)
        {
            armaEquipada = nullptr;   // se rompe y se destruye
            vidaArmaActual = 0;
        }
    }

    return danio;
}


void Personaje::recibirDanio(int danio)
{
    if (estaEliminado())
    {
        return;
    }

    int defensaTotal = defensa;

    if (armaduraEquipada != nullptr && armaduraEquipada->getTipo() == ARMADURA)
    {
        defensaTotal += armaduraEquipada->getBonusDefensa();

        vidaArmaduraActual--;
        if (vidaArmaduraActual <= 0)
        {
            armaduraEquipada = nullptr;  // se rompe y se destruye
            vidaArmaduraActual = 0;
        }
    }

    int danioReal = danio - defensaTotal;
    if (danioReal < 0)
    {
        danioReal = 0;
    }

    vidaActual -= danioReal;
    if (vidaActual < 0)
    {
        vidaActual = 0;
    }

    if (vidaActual == 0)
    {
        eliminado = true;
    }
}

bool Personaje::curar(int puntos)
{
    if (estaEliminado())
    {
        return false;
    }

    if (vidaActual >= vidaMaxima)
    {
        return false;
    }

    vidaActual += puntos;
    if (vidaActual > vidaMaxima)
    {
        vidaActual = vidaMaxima;
    }

    return true;
}

void Personaje::agregarOro(int cantidad)
{
    oro += cantidad;
}

bool Personaje::gastarOro(int cantidad)
{
    if (oro >= cantidad)
    {
        oro -= cantidad;
        return true;
    }

    return false;
}

const char* Personaje::getNombre() const
{
    return nombre;
}

int Personaje::getAtaque() const
{
    return ataque;
}

int Personaje::getDefensa() const
{
    return defensa;
}

int Personaje::getNivel() const
{
    return nivel;
}

int Personaje::getVidaActual() const
{
    return vidaActual;
}

int Personaje::getVidaMaxima() const
{
    return vidaMaxima;
}

int Personaje::getOro() const
{
    return oro;
}

bool Personaje::estaEliminado() const
{
    return eliminado;
}
