#pragma once

#include "PanelTexto.h"
#include <SFML/Graphics.hpp>

class PanelConImagen : public Panel
{
private:
    sf::Sprite _imagen;
    sf::Texture _textura;
    float padding; // Padding para las coordenadas debajo de la imagen

public:
    // Constructores
    PanelConImagen();
    PanelConImagen(float posX, float posY, float tamX, float tamY,
                   const std::string& rutaImagen, float paddingImagen = 10.0f);
    PanelConImagen(const PanelConImagen& otro);
    PanelConImagen& operator=(const PanelConImagen& otro);
    ~PanelConImagen();

    // Sobrescritura del método draw para dibujar también la imagen
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    // Métodos para manejar la imagen
    bool cargarImagen(const std::string& rutaImagen);
    void setPosicionImagen(float x, float y);
    void setEscalaImagen(float escalaX, float escalaY);
    void setTamanioImagen(float ancho, float alto); // Redimensiona manteniendo aspecto
    void setColorImagen(const sf::Color& color);

    // Método para obtener coordenadas debajo de la imagen en el margen izquierdo
    // Devuelve {x, y} donde comenzar a dibujar texto/elementos
    sf::Vector2f obtenerCoordenadasDebajoImagen() const;
    sf::Vector2f obtenerCoordenadasDebajoImagen(float paddingAdicional) const;

    // Getters
    sf::Sprite& getImagen();
    const sf::Sprite& getImagen() const;
    float getPadding() const;
    void setPadding(float nuevoPadding);
};
