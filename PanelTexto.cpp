#include "PanelTexto.h"
#include "datosPanel.h"

Panel::Panel()
{

}
Panel::Panel(float posX, float posY, float tamX, float tamY)
{
    _Panel.setSize(sf::Vector2f(tamX, tamY));
    _Panel.setPosition(posX, posY);

    // Color por defecto
    _Panel.setFillColor(CLR_FONDO_PA);
    _Panel.setOutlineThickness(GROS_RECUA_PA);
    _Panel.setOutlineColor(CLR_RECUA_PA);
    setPosX(posX);
    setPosY(posY);
    setBordeX(tamX);
    setBordeY(tamY);

}
Panel::~Panel()
{
}

void Panel::dibujar(sf::RenderWindow& ventana)
{
    ventana.draw(_Panel);
}

void Panel::setPosicion(float x, float y)
{
    _Panel.setPosition(x, y);
}

void Panel::setColor(const sf::Color& color)
{
    _Panel.setFillColor(color);
}

sf::RectangleShape& Panel::getShape()
{
    return _Panel;
}

void Panel::setBordeX(float x)
{
    bordeX=x;
}

void Panel::setBordeY(float y)
{
    bordeY=y;
}


float Panel::getBordeX()
{
    return posX+bordeX;
}
float Panel::getBordeY()
{
    return posY+bordeY;
}

void Panel::setGroContorno(const float gro)
{
     _Panel.setOutlineThickness(gro);
}

void Panel::setColContorno(const sf::Color& col)
{
     _Panel.setOutlineColor(col);
}



void Panel::setTam(const sf::Vector2f& tamPan)
{
    _Panel.setSize(tamPan);
}

void Panel::setPosX(float x)
{
    posX=x;
}
void Panel::setPosY(float y)
{
    posY=y;
}

float Panel::getPosX()
{
    return posX;
}
float Panel::getPosY()
{
    return posY;
}

float Panel::getPosInternaX()
{
    return posX+_Panel.getOutlineThickness();
}

float Panel::getPosInternaY()
{
    return posY+_Panel.getOutlineThickness();
}

sf::FloatRect Panel::obtenerLimites() const
{
    return _Panel.getGlobalBounds();
}


