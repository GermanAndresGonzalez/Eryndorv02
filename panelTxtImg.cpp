#include "panelTxtImg.h"
#include <iostream>

PanelConImagen::PanelConImagen() : Panel(), padding(10.0f)
{
}

PanelConImagen::PanelConImagen(const PanelConImagen& otro)
    : Panel(otro), _textura(otro._textura), padding(otro.padding)
{
    _imagen = otro._imagen;
    _imagen.setTexture(_textura); // re-vincula a NUESTRA copia de la textura
}

PanelConImagen& PanelConImagen::operator=(const PanelConImagen& otro)
{
    if (this != &otro)
    {
        Panel::operator=(otro); // Panel no tiene punteros, la copia por defecto está bien
        _textura = otro._textura;
        _imagen = otro._imagen;
        _imagen.setTexture(_textura); // re-vincula
        padding = otro.padding;
    }
    return *this;
}

PanelConImagen::PanelConImagen(float posX, float posY, float tamX, float tamY,
                               const std::string& rutaImagen, float paddingImagen)
    : Panel(posX, posY, tamX, tamY), padding(paddingImagen)
{
    cargarImagen(rutaImagen);
}

PanelConImagen::~PanelConImagen()
{
}

void PanelConImagen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // Dibujar el panel base
    Panel::draw(target, states);

    // Dibujar la imagen encima del panel
    target.draw(_imagen, states);
}

bool PanelConImagen::cargarImagen(const std::string& rutaImagen)
{
    if (!_textura.loadFromFile(rutaImagen))
    {
        std::cerr << "Error: No se pudo cargar la imagen desde " << rutaImagen << std::endl;
        return false;
    }

    _imagen.setTexture(_textura);

    // Posicionar la imagen en la esquina superior derecha del interior del panel
    float posXImagen = getBordeX() - _imagen.getGlobalBounds().width - padding;
    float posYImagen = getPosInternaY() + padding;
    _imagen.setPosition(posXImagen, posYImagen);

    return true;
}

void PanelConImagen::setPosicionImagen(float x, float y)
{
    _imagen.setPosition(x, y);
}

void PanelConImagen::setEscalaImagen(float escalaX, float escalaY)
{
    _imagen.setScale(escalaX, escalaY);
}

void PanelConImagen::setTamanioImagen(float ancho, float alto)
{
    // Obtener el tamaño actual de la textura
    sf::Vector2u texturaSize = _textura.getSize();

    // Calcular escalas para mantener el aspecto
    float escalaX = ancho / texturaSize.x;
    float escalaY = alto / texturaSize.y;

    // Usar la escala más pequeña para mantener el aspecto
    float escala = std::min(escalaX, escalaY);
    _imagen.setScale(escala, escala);

    // Reposicionar la imagen en la esquina superior derecha
    float posXImagen = getPosInternaX() + getBordeX() - (texturaSize.x * escala) - 5.0f;
    float posYImagen = getPosInternaY() + 5.0f;
    _imagen.setPosition(posXImagen, posYImagen);
}

void PanelConImagen::setColorImagen(const sf::Color& color)
{
    _imagen.setColor(color);
}

sf::Vector2f PanelConImagen::obtenerCoordenadasDebajoImagen() const
{
    return obtenerCoordenadasDebajoImagen(0.0f);
}

sf::Vector2f PanelConImagen::obtenerCoordenadasDebajoImagen(float paddingAdicional) const
{
    // Obtener la posición y dimensiones de la imagen
    sf::FloatRect boundsImagen = _imagen.getGlobalBounds();

    // Calcular coordenadas debajo de la imagen
    float x = getPosInternaX() + padding + paddingAdicional;
    float y = boundsImagen.top + boundsImagen.height + padding + paddingAdicional;

    return sf::Vector2f(x, y);
}

sf::Sprite& PanelConImagen::getImagen()
{
    return _imagen;
}

const sf::Sprite& PanelConImagen::getImagen() const
{
    return _imagen;
}

float PanelConImagen::getPadding() const
{
    return padding;
}

void PanelConImagen::setPadding(float nuevoPadding)
{
    padding = nuevoPadding;
}
