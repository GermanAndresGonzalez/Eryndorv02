#pragma once

#include "datosPanel.h"
#include <SFML/Graphics.hpp>

class Panel
{
private:
    sf::RectangleShape _Panel;
    float posX;
    float posY;
    float bordeX;
    float bordeY;

public:
    // Constructor
    Panel();
    Panel(float posX, float posY, float tamX, float tamY);
    ~Panel();


    // Dibujar en la ventana
    void dibujar(sf::RenderWindow& ventana);

    // Setters opcionales
    void setPosicion(float x, float y);
    void setColor(const sf::Color& color);

    // Getter opcional
    sf::RectangleShape& getShape();


    void setTam(const sf::Vector2f& tamPan);


	void setGroContorno(float gro);
	void setColContorno(const sf::Color& col);

	void setBordeX(float x);
	void setBordeY(float y);

	float getBordeX();
	float getBordeY();

    void setPosX(float x);
	void setPosY(float y);

	float getPosX();
	float getPosY();

	float getPosInternaX();
	float getPosInternaY();

    sf::FloatRect obtenerLimites() const;
    sf::FloatRect getLocalBounds() const;

	//const sf::FloatRect obtPosicion(sf::RenderWindow& ventana) const;
};





