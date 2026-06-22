#include "VentanaCargar.h"
#include "botonera.h"
//#include "datosArchivos.h"
#include "datosVenCargar.h"
#include "datosBotonCargar.h"
#include <iostream>


VentanaCargar::VentanaCargar(GestorPantallas& gestor): m_gestor(gestor)
{
    m_fuente.loadFromFile("recursos/fuentes/AlexandriaFLF.ttf");
    m_texto.setFont(m_fuente);
    m_texto.setString("Presiona ENTER para comenzar\nIntroducción");
    m_texto.setCharacterSize(30);
    m_texto.setPosition(200.f, 300.f);
    Botonera botonera;
    cargarRec();
}
void VentanaCargar::alMostrar()
{
    std::cout << "VentanaCargar: ahora visible\n";

}
void VentanaCargar::alOcultar()
{
    std::cout << "VentanaCargar: ahora oculta\n";
}
void VentanaCargar::actualizar(float dt)
{
// Si el usuario presiona ENTER, ir a la intro
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        m_gestor.ocultar("principal");
        m_gestor.mostrar("intro");
    }


}
void VentanaCargar::dibujar(sf::RenderWindow& ventana)
{
    ventana.draw(spriteFondo);
    ventana.draw(m_texto);
    botonera.draw(ventana);
}

void VentanaCargar::cargarRec()
{
    if (!texturaFondo.loadFromFile(RUTA_FONDO_INTRO))
    {
        std::cerr << ERROR_FONDO_INTRO;
    }
    if (!fuenteBotonera.loadFromFile(FUENTE_INTRO))
    {
        std::cerr << ERROR_FUENTE_INTRO;
    }

    spriteFondo.setTexture(texturaFondo);

    botonera.inicializar(CANT_BOTONES_INTRO, fuenteBotonera);
    botonera.seColoresBot(COLOR_FONDO_INTRO,COLOR_RECUA_INTRO);
    botonera.inicializarRectangulos(tamRectBotonX_INTRO, tamRectBotonY_INTRO);
    botonera.setTamCar(TAM_CARACTER_INTRO);
    botonera.setColorTexto(COLOR_LETRA_INTRO); //COLOR_FONDO
    botonera.inicializarEtiquetas(ETI_BOTONES_INTRO,CANT_BOTONES_INTRO);
    botonera.inicializarBotones(posBotonX_INTRO,posBotonY_INTRO,true);
    //inicializarDatos();


}
void VentanaCargar::ejecutarAccion(int i)
{
    //std::cout << "Presion click";
    std::cout << "Click\n";
    switch (i)
    {
    case 0:
        m_gestor.ocultar("intro");
        m_gestor.mostrar("principal");
        break;

    case 1:
        m_gestor.ocultar("principal");
        m_gestor.mostrar("intro");
        break;

    case 2:
        m_gestor.ocultar("intro");
        m_gestor.mostrar("jugador");
        break;
    }

}

void VentanaCargar::manejarEvento(const sf::Event& evento)
{

    if (evento.type==sf::Event::MouseMoved)
    {
        for (int i=0; i <CANT_BOTONES_INTRO; i++)
        {
            if (!botonera.obtPosicion(i).contains(static_cast<float>(evento.mouseMove.x), static_cast<float>(evento.mouseMove.y)))
            {
                botonera.igualarBotones(COLOR_FONDO_INTRO,COLOR_LETRA_INTRO);
                break;
            }
        }

        for (int i=0; i <CANT_BOTONES_INTRO; i++)
        {
            if (botonera.obtPosicion(i).contains(static_cast<float>(evento.mouseMove.x), static_cast<float>(evento.mouseMove.y)))
            {
                botonera.resaltarBoton(i,COLOR_FONDO_RES_INTRO,COLOR_LETRA_RES_INTRO);
                break;
            }
        }
    }
    if (evento.type == sf::Event::MouseButtonPressed && evento.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(m_gestor.obtenerVentana());
        for (int i=0; i<CANT_BOTONES_INTRO; i++)
        {
            if (botonera.obtPosicion(i).contains(static_cast<float>(mousePos.x),static_cast<float>(mousePos.y)))
            {
                ejecutarAccion(i);
                break;
            }
        }
    }
}

