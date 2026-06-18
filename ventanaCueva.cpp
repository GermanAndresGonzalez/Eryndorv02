

#include "botonera.h"
#include "ventanaCueva.h"
#include "datosFuentes.h"
#include "datosVenCueva.h"


#include <iostream>


VentanaCueva::VentanaCueva(GestorPantallas& gestor): m_gestor(gestor)
{

    if (!m_fuente.loadFromFile(FUENTES))
    {
        std::cerr << ERROR_FUENTE;
    }
    m_texto.setFont(m_fuente);
    m_parra.setFont(m_fuente);
    m_desped.setFont(m_fuente);


    m_texto.setString(TEXT_TIT);
    m_parra.setString(TEXT_PARR);
    m_desped.setString(TEXT_DESP);

    m_texto.setCharacterSize(TAM_CAR_TIT);
    m_parra.setCharacterSize(TAM_CAR_PARR);
    m_desped.setCharacterSize(TAM_CAR_DESP);


    m_texto.setPosition(200.f, 50.f);
    m_texto.setPosition(200.f, 100.f);
    m_texto.setPosition(200.f, 150.f);

}
void VentanaCueva::alMostrar()
{
    std::cout << "VentanaCueva: ahora visible\n";
}
void VentanaCueva::alOcultar()
{
    std::cout << "VentanaCueva: ahora oculta\n";
}
void VentanaCueva::actualizar(float dt)
{
// Si el usuario presiona ENTER, ir a la intro
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        m_gestor.ocultar("principal");
        m_gestor.mostrar("intro");
    }
}
void VentanaCueva::dibujar(sf::RenderWindow& ventana)
{
    ventana.draw(m_texto);
}
