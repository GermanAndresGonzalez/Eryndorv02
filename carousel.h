#ifndef CAROUSEL_H
#define CAROUSEL_H

#include <SFML/Graphics.hpp>

class Carousel: public sf::Drawable
{
private:

    static const int CAROUSEL_SIZE = 4;

    sf::Texture _textures[CAROUSEL_SIZE];
    const char* _filenames[CAROUSEL_SIZE];

    sf::Sprite _sprite;

    int _currentIndex;

public:

    Carousel();

    bool cargar();

    void siguiente();
    void anterior();

    void setPosition(float x, float y);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif