#include "carousel.h"

Carousel::Carousel()
{
    _filenames[0] = "recursos/imag/intro/Uno.png";
    _filenames[1] = "recursos/imag/intro/Dos.png";
    _filenames[2] = "recursos/imag/intro/Tres.png";
    _filenames[3] = "recursos/imag/intro/Cuatro.png";

    _currentIndex = 0;
}

bool Carousel::cargar()
{
    for (int i = 0; i < CAROUSEL_SIZE; i++)
    {
        if (!_textures[i].loadFromFile(_filenames[i]))
            return false;
    }

    _sprite.setTexture(_textures[_currentIndex], true);

    // Set origin to top-left instead of center
    _sprite.setOrigin(0, 0);

    return true;

    /*
    for (int i = 0; i < CAROUSEL_SIZE; i++)
    {
        if (!_textures[i].loadFromFile(_filenames[i]))
            return false;
    }

    _sprite.setTexture(_textures[_currentIndex], true);

    sf::FloatRect r = _sprite.getLocalBounds();

    _sprite.setOrigin(r.width / 2.f, r.height / 2.f);

    return true;
    */
}

void Carousel::siguiente()
{
    _currentIndex++;

    if (_currentIndex >= CAROUSEL_SIZE)
        _currentIndex = 0;

    _sprite.setTexture(_textures[_currentIndex], true);
}

void Carousel::anterior()
{
    _currentIndex--;

    if (_currentIndex < 0)
        _currentIndex = CAROUSEL_SIZE - 1;

    _sprite.setTexture(_textures[_currentIndex], true);
}

void Carousel::setPosition(float x, float y)
{
    _sprite.setPosition(x, y);
}

void Carousel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}
