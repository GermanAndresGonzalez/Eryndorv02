#ifndef CENTRADO_H
#define CENTRADO_H
#include <SFML/Graphics.hpp>

// Necesitamos pasarle el gestor a la función para que sepa qué ventana cerrar
//class GestorPantallas; // Declaración adelantada (forward declaration) si m_gestor es de tipo Gestor

class Centrado
{
public:
    // Cambiado de Salida() a Salir() y agregando el parámetro del gestor
    // Declaración en el .h (dentro de la clase, por ejemplo en VentanaExplo)
    static void centrar(sf::Text& texto, const sf::RenderWindow& ventana, float posY);
    static void centrar(sf::Text& texto, const sf::FloatRect& rect, float posY);
};

#endif
