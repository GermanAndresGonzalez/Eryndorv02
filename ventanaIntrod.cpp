#include "ventanaIntrod.h"
#include "botonera.h"
#include "PanelTexto.h"
#include "datosVenIntro.h"
#include "carousel.h"

#include "datosBotonIntro.h"
#include <iostream>


VentanaIntro::VentanaIntro(GestorPantallas& gestor): m_gestor(gestor)
{
    m_fuente.loadFromFile("recursos/fuentes/AlexandriaFLF.ttf");
    m_texto.setFont(m_fuente);
    //m_texto.setString("Presiona ENTER para comenzar\nIntroducción");
    m_texto.setString("");
    m_texto.setCharacterSize(30);
    m_texto.setPosition(200.f, 300.f);
    Botonera botonera;
    cargarRec();
}
void VentanaIntro::alMostrar()
{
    std::cout << "VentanaIntro: ahora visible\n";
    sf::Event e;
    while (m_gestor.obtenerVentana().pollEvent(e)) { /* descartar */ }
    //panelCarr
    panelCarr = Panel(xPanelIn_INTRO,yPanelIn_INTRO,xPanelAn_INTRO,yPanelAl_INTRO);
    panelCarr.setColor(CLR_FONDO_INTRO);
    panelCarr.setColContorno(CLR_RECUA_INTRO);

    carousel.cargar();
    carousel.setPosition(panelCarr.getPosInternaX(),panelCarr.getPosInternaY());
    std::cout << xPanelIn_INTRO << "  " << yPanelIn_INTRO << "\n";
    std::cout << panelCarr.getPosInternaX() << "  " << panelCarr.getPosInternaY() << "\n";
    //carousel.setPosition(400,300);



}
void VentanaIntro::alOcultar()
{
    std::cout << "VentanaIntro: ahora oculta\n";
}
void VentanaIntro::actualizar(float dt)
{

    /*
    // Si el usuario presiona ENTER, ir a la intro
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        m_gestor.ocultar("principal");
        m_gestor.mostrar("intro");
    }
    */

}
void VentanaIntro::dibujar(sf::RenderWindow& ventana)
{
    ventana.draw(spriteFondo);
    ventana.draw(m_texto);
    ventana.draw(botonera);

    //botonera.draw(ventana);
    ventana.draw(panelCarr);
    ventana.draw(carousel);
}

void VentanaIntro::cargarRec()
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
void VentanaIntro::ejecutarAccion(int i)
{

    Partida* datos= m_gestor.obtenerPartida();
    //std::cout << "Pantalla anterior: " <<datos->pantallaAnterior <<"\n";
    datos->pantallaAnterior="intro";
    //std::cout << "Pantalla anterior: " <<datos->pantallaAnterior <<"\n";
    //std::cout << "Numero de partida: " <<datos->partida <<"\n";
    switch (i)
    {
    case 0:
        carousel.anterior();
        break;

    case 1:
        carousel.siguiente();
        break;

    case 2:
        m_gestor.ocultar("intro");
        m_gestor.mostrar("jugador");
        break;
    }

}

void VentanaIntro::manejarEvento(const sf::Event& evento)
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

