#include "botonera.h"
#include <iostream>

// ── Constructores / Destructor ─────────────────────────────────────────────────

Botonera::Botonera()
    : cantidad(0),
      textoBotones(nullptr),
      etiquetas(nullptr),
      botones(nullptr),
      tamCar(30),
      colorBotonera(sf::Color::Transparent),
      colorRecBot(sf::Color::White),
      colorTexto(sf::Color::White)
{}

Botonera::Botonera(int n, sf::Font& f)
    : cantidad(n), fuente(f)
{
    textoBotones = new sf::Text[cantidad];
    botones      = new grupoBoton[cantidad];
    etiquetas    = new std::string[cantidad];

    for (int i = 0; i < cantidad; i++)
    {
        botones[i].activo = true;
        botones[i].id     = 0;
    }
}

Botonera::~Botonera()
{
    delete[] textoBotones;
    delete[] botones;
    delete[] etiquetas;
    textoBotones = nullptr;
    botones      = nullptr;
    etiquetas    = nullptr;
}

// ── Inicialización ─────────────────────────────────────────────────────────────

void Botonera::inicializar(int n, sf::Font& f)
{
    cantidad = n;
    fuente   = f;

    delete[] textoBotones;
    delete[] botones;
    delete[] etiquetas;

    textoBotones = new sf::Text[cantidad];
    etiquetas    = new std::string[cantidad];
    botones      = new grupoBoton[cantidad];

    for (int i = 0; i < cantidad; i++)
    {
        botones[i].activo = true;
        botones[i].id     = 0;
    }
}

void Botonera::inicializarEtiquetas(const std::string etiquetasExternas[], int cantidadEtiquetas)
{
    for (int i = 0; i < cantidad && i < cantidadEtiquetas; i++)
        setEtiqueta(i, etiquetasExternas[i]);
}

void Botonera::inicializarRectangulos(float ancho, float alto)
{
    anchoRect = ancho;
    altoRect  = alto;

    for (int i = 0; i < cantidad; i++)
    {
        botones[i].boton.setSize(sf::Vector2f(ancho, alto));
        botones[i].boton.setFillColor(colorBotonera);
        botones[i].boton.setOutlineThickness(1.f);
        botones[i].boton.setOutlineColor(colorRecBot);
    }
}

void Botonera::inicializarBotones(float x, float y, bool horiz)
{
    // Posicionamiento
    for (int i = 0; i < cantidad; i++)
    {
        if (horiz)
            botones[i].boton.setPosition(x + i * (anchoRect + 10.f), y);
        else
            botones[i].boton.setPosition(x, y + i * (altoRect + 10.f));
    }

    // Centrado del texto dentro de cada botón
    for (int i = 0; i < cantidad; i++)
    {
        sf::FloatRect bounds = textoBotones[i].getLocalBounds();

        float xTexto = botones[i].boton.getPosition().x + (anchoRect - bounds.width)  / 2.f - bounds.left;
        float yTexto = botones[i].boton.getPosition().y + (altoRect  - bounds.height) / 2.f - bounds.top;

        textoBotones[i].setPosition(xTexto, yTexto);
    }
}

// ── Dibujo ─────────────────────────────────────────────────────────────────────

void Botonera::draw(sf::RenderWindow& ventana)
{
    for (int i = 0; i < cantidad; i++)
    {
        if (botones[i].activo)          // solo se dibujan los botones activos
        {
            ventana.draw(botones[i].boton);
            ventana.draw(textoBotones[i]);
        }
    }
}

// ── Resaltar / igualar ─────────────────────────────────────────────────────────

void Botonera::resaltarBoton(int n, sf::Color color, sf::Color color2)
{
    if (n >= 0 && n < cantidad)
    {
        botones[n].boton.setFillColor(color);
        textoBotones[n].setFillColor(color2);
    }
}

void Botonera::igualarBotones(sf::Color color, sf::Color color2)
{
    for (int i = 0; i < cantidad; i++)
    {
        if (botones[i].activo==true)
        {
            botones[i].boton.setFillColor(color);
            textoBotones[i].setFillColor(color2);
        }


    }
}

// ── Setters generales ──────────────────────────────────────────────────────────

void Botonera::setEtiqueta(int i, const std::string& texto)
{
    if (i >= 0 && i < cantidad &&(botones[i].activo==true))
    {

        etiquetas[i] = texto;
        textoBotones[i].setFont(fuente);
        textoBotones[i].setString(texto);
        textoBotones[i].setCharacterSize(tamCar);
        textoBotones[i].setFillColor(colorTexto);
    }
}

void Botonera::setTamCar(unsigned int tamCaracter)
{
    tamCar = tamCaracter;
}

void Botonera::seColoresBot(sf::Color color, sf::Color colorRec)
{
    colorBotonera = color;
    colorRecBot   = colorRec;
}

void Botonera::setColorTexto(sf::Color color)
{
    colorTexto = color;
}

// ── Setters de grupoBoton ──────────────────────────────────────────────────────

void Botonera::setActivo(int i, bool estado)
{
    if (i >= 0 && i < cantidad)
        botones[i].activo = estado;
}

void Botonera::setId(int i, int nuevoId)
{
    if (i >= 0 && i < cantidad)
        botones[i].id = nuevoId;
}

void Botonera::setColorBoton(int i, sf::Color color)
{
    if (i >= 0 && i < cantidad)
        botones[i].boton.setFillColor(color);
}

void Botonera::setOutlineBoton(int i, sf::Color color, float grosor)
{
    if (i >= 0 && i < cantidad)
    {
        botones[i].boton.setOutlineColor(color);
        botones[i].boton.setOutlineThickness(grosor);
    }
}

// ── Getters de grupoBoton ──────────────────────────────────────────────────────

bool Botonera::getActivo(int i) const
{
    if (i >= 0 && i < cantidad)
        return botones[i].activo;
    return false;
}

int Botonera::getId(int i) const
{
    if (i >= 0 && i < cantidad)
        return botones[i].id;
    return -1;
}

sf::Color Botonera::getColorBoton(int i) const
{
    if (i >= 0 && i < cantidad)
        return botones[i].boton.getFillColor();
    return sf::Color::Transparent;
}

const sf::FloatRect Botonera::obtPosicion(int i) const
{
    if (i >= 0 && i < cantidad)
        return botones[i].boton.getGlobalBounds();
    return sf::FloatRect();
}

// ── Getters generales ──────────────────────────────────────────────────────────

int Botonera::getCantidad() const
{
    return cantidad;
}

float Botonera::getAnchoRect() const
{
    return anchoRect;
}

float Botonera::getAltoRect() const
{
    return altoRect;
}

unsigned int Botonera::getTamCar() const
{
    return tamCar;
}

sf::Color Botonera::getColorTexto() const
{
    return colorTexto;
}

sf::Color Botonera::getColorBotonera() const
{
    return colorBotonera;
}

std::string Botonera::getEtiqueta(int i) const
{
    if (i >= 0 && i < cantidad)
        return etiquetas[i];
    return "";
}
