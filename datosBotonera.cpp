#include "datosBotonera.h"


const char* FUENTE="recursos/fuentes/AlexandriaFLF-Bold.ttf";
const char* ERROR_FUENTE_B="No se pudo cargar la fuente";
const int CANT_BOTONES=5;

//const sf::Color COLOR_FONDO_RES = sf::Color(90, 140, 210);
const sf::Color COLOR_FONDO = sf::Color::Transparent;
const sf::Color COLOR_FONDO_RES = sf::Color(90, 140, 210);
const sf::Color COLOR_LETRA = sf::Color::White;
const sf::Color COLOR_LETRA_RES = sf::Color(39,87,59);
const sf::Color COLOR_RECUA = sf::Color::White;

const unsigned int TAM_CARACTER=30;

const float posBotonX=750;
const float posBotonY=250;

const float tamRectBotonX=230.f;
const float tamRectBotonY=50.f;


const std::string ETI_BOTONES[] = {
    "Jugar",
    "Opciones",
    "Cargar Partida",
    "Acerca de",
    "Salir"
};


