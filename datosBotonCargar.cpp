#include "datosBotonCargar.h"

const char* FUENTE_CARGAR       = "recursos/fuentes/AlexandriaFLF-Bold.ttf";
const char* ERROR_FUENTE_CARGAR = "No se pudo cargar la fuente";

// 2 botones: "Seleccionar" y "Volver"
const int CANT_BOTONES_CARGAR = 2;

const sf::Color COLOR_FONDO_CARGAR     = sf::Color::Transparent;
const sf::Color COLOR_FONDO_RES_CARGAR = sf::Color(90, 140, 210);

const sf::Color COLOR_LETRA_CARGAR     = sf::Color::White;
const sf::Color COLOR_LETRA_RES_CARGAR = sf::Color(39, 87, 59);

const sf::Color COLOR_RECUA_CARGAR = sf::Color::White;

const unsigned int TAM_CARACTER_CARGAR = 25;

const float posBotonX_CARGAR      = 460.f;
const float posBotonY_CARGAR      = 630.f;
const float tamRectBotonX_CARGAR  = 200.f;
const float tamRectBotonY_CARGAR  = 50.f;

const std::string ETI_BOTONES_CARGAR[] = {
    "Seleccionar",
    "Volver"
};

// ── Fila de lista de partidas ─────────────────────────────────────────────────
const float        FILA_ALTO      = 44.f;
const float        FILA_PADDING_X = 12.f;
const float        FILA_PADDING_Y = 8.f;
const unsigned int FILA_TAM_CAR   = 19;

const sf::Color COLOR_FILA_NORMAL = sf::Color(0,   0,   0,   140);
const sf::Color COLOR_FILA_HOVER  = sf::Color(90,  140, 210, 180);
const sf::Color COLOR_FILA_SEL    = sf::Color(50,  58,  122, 220);
const sf::Color COLOR_FILA_TEXTO  = sf::Color::White;

// ── Detalle (panel central) ───────────────────────────────────────────────────
const float        DETALLE_PADDING     = 30.f;
const unsigned int DETALLE_TAM_CAR     = 22;
const unsigned int DETALLE_TAM_CAR_TIT = 28;
const sf::Color    COLOR_DETALLE_TEXTO = sf::Color::White;
