#include "centrar.h"
#include "ventanaConfirmacion.h"
#include "GestorPantallas.h" // Asegúrate de incluir la clase de tu m_gestor
#include <iostream>

// Agregamos el parámetro 'gestor' a la implementación
void Centrado::centrar(sf::Text& texto, const sf::RenderWindow& ventana, float posY)
{
    sf::FloatRect rect = texto.getLocalBounds();
    texto.setOrigin(rect.left + rect.width  / 2.0f,
                    rect.top  + rect.height / 2.0f);
    texto.setPosition(ventana.getSize().x / 2.0f, posY);
}
void Centrado::centrar(sf::Text& texto, const sf::FloatRect& rect, float posY)
{
    sf::FloatRect limites = texto.getLocalBounds();

    // Debug: ver qué valores tenemos

    std::cout << "Texto localBounds  left=" << limites.left << " width=" << limites.width << "\n";
    std::cout << "Rect               left=" << rect.left    << " width=" << rect.width    << "\n";
    std::cout << "Centro calculado X=" << rect.left + rect.width / 2.0f << "\n";

    texto.setOrigin(limites.left + limites.width  / 2.0f,
                    limites.top  + limites.height / 2.0f);
    texto.setPosition(rect.left + rect.width / 2.0f, posY);

}

/*
void Centrado::centrar(sf::Text& texto, const sf::FloatRect& rect, float posY)
{
    sf::FloatRect limites = texto.getGlobalBounds();
    texto.setOrigin(limites.left + limites.width  / 2.0f,
                    limites.top  + limites.height / 2.0f);

    // Corrección: Usar directamente left y width de la estructura FloatRect
    texto.setPosition(rect.left + rect.width / 2.0f, posY);

}
*/
