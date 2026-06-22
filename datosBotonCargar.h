#ifndef DATOS_BOTON_CARGAR_H
#define DATOS_BOTON_CARGAR_H

#include <SFML/Graphics.hpp>
#include <string>

extern const char* FUENTE_CARGAR;
extern const char* ERROR_FUENTE_CARGAR;

extern const int CANT_BOTONES_CARGAR;

extern const sf::Color COLOR_FONDO_CARGAR;
extern const sf::Color COLOR_FONDO_RES_CARGAR;

extern const sf::Color COLOR_LETRA_CARGAR;
extern const sf::Color COLOR_LETRA_RES_CARGAR;

extern const sf::Color COLOR_RECUA_CARGAR;

extern const unsigned int TAM_CARACTER_CARGAR;

extern const float posBotonX_CARGAR;
extern const float posBotonY_CARGAR;

extern const float tamRectBotonX_CARGAR;
extern const float tamRectBotonY_CARGAR;

extern const std::string ETI_BOTONES_CARGAR[];

// ── Fila de lista de partidas ─────────────────────────────────────────────────
extern const float  FILA_ALTO;
extern const float  FILA_PADDING_X;
extern const float  FILA_PADDING_Y;
extern const unsigned int FILA_TAM_CAR;

extern const sf::Color COLOR_FILA_NORMAL;
extern const sf::Color COLOR_FILA_HOVER;
extern const sf::Color COLOR_FILA_SEL;
extern const sf::Color COLOR_FILA_TEXTO;

// ── Detalle (panel central) ───────────────────────────────────────────────────
extern const float        DETALLE_PADDING;
extern const unsigned int DETALLE_TAM_CAR;
extern const unsigned int DETALLE_TAM_CAR_TIT;
extern const sf::Color    COLOR_DETALLE_TEXTO;

#endif
