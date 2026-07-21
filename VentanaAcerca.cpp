#include "datosFuentes.h"
#include "VentanaAcerca.h"
#include "botonera.h"
#include "PanelTexto.h"
#include "datosVenAcerca.h"
#include "datosBotonAcerca.h"
#include "datosVenIntro.h"
#include "centrar.h"

#include <iostream>


VentanaAcerca::VentanaAcerca(GestorPantallas& gestor): m_gestor(gestor)
{
    cargarRec();
}

void VentanaAcerca::alMostrar()
{
    std::cout << "VentanaAcerca: ahora visible\n";
    sf::Event e;
    while (m_gestor.obtenerVentana().pollEvent(e)) { /* descartar */ }

    Centrado::centrar(m_titulo, m_gestor.obtenerVentana(), posYTitulo_ACERCA);
    Centrado::centrar(m_subtitulo, m_gestor.obtenerVentana(), posYSubtitulo_ACERCA);

    panelIzq = Panel(xPanelIzqIn_ACERCA, yPanelIn_ACERCA, xPanelAn_ACERCA, yPanelAl_ACERCA);
    panelIzq.setColor(CLR_FONDO_ACERCA);
    panelIzq.setColContorno(CLR_RECUA_ACERCA);
    panelIzq.setGroContorno(GROS_RECUA_ACERCA);

    panelDer = Panel(xPanelDerIn_ACERCA, yPanelIn_ACERCA, xPanelAn_ACERCA, yPanelAl_ACERCA);
    panelDer.setColor(CLR_FONDO_ACERCA);
    panelDer.setColContorno(CLR_RECUA_ACERCA);
    panelDer.setGroContorno(GROS_RECUA_ACERCA);

    m_textoIzq.setPosition(panelIzq.getPosInternaX() + 20.f, panelIzq.getPosInternaY() + 20.f);
    m_textoDer.setPosition(panelDer.getPosInternaX() + 20.f, panelDer.getPosInternaY() + 20.f);
}

void VentanaAcerca::alOcultar()
{
    std::cout << "VentanaAcerca: ahora oculta\n";
}

void VentanaAcerca::actualizar(float dt)
{
    // Sin lógica de actualización por ahora
}

void VentanaAcerca::dibujar(sf::RenderWindow& ventana)
{
    ventana.draw(spriteFondo);

    ventana.draw(m_titulo);
    ventana.draw(m_subtitulo);

    ventana.draw(panelIzq);
    ventana.draw(m_textoIzq);

    ventana.draw(panelDer);
    ventana.draw(m_textoDer);

    ventana.draw(botonera);
}

void VentanaAcerca::cargarRec()
{
    if (!texturaFondo.loadFromFile(RUTA_FONDO_INTRO))
    {
        std::cerr << ERROR_FONDO_INTRO;
    }
    spriteFondo.setTexture(texturaFondo);

    if (!m_fuenteTitulo.loadFromFile(FUENTES))
    {
        std::cerr << ERROR_FUENTE;
    }
    m_fuentePanel  = m_fuenteTitulo;
    fuenteBotonera = m_fuenteTitulo;

    m_titulo.setFont(m_fuenteTitulo);
    m_titulo.setString(TIT_ACERCA);
    m_titulo.setCharacterSize(TAM_TITULO_ACERCA);
    m_titulo.setFillColor(sf::Color::White);

    m_subtitulo.setFont(m_fuenteTitulo);
    m_subtitulo.setString(SUBTIT_ACERCA);
    m_subtitulo.setCharacterSize(TAM_SUBTITULO_ACERCA);
    m_subtitulo.setFillColor(sf::Color::White);

    m_textoIzq.setFont(m_fuentePanel);
    m_textoIzq.setString(
        "Matias Martin Aquino\n"
        "Legajo numero 32906\n"
        "Matias.Aquino1@alumnos.frgp.utn.edu.ar"
    );
    m_textoIzq.setCharacterSize(TAM_TEXTO_PANEL_ACERCA);
    m_textoIzq.setFillColor(COLOR_TEXTO_PANEL_ACERCA);

    m_textoDer.setFont(m_fuentePanel);
    m_textoDer.setString(
        "German Andres Gonzalez\n"
        "Legajo numero 33047\n"
        "German.Gonzalez1@alumnos.frgp.utn.edu.ar"
    );
    m_textoDer.setCharacterSize(TAM_TEXTO_PANEL_ACERCA);
    m_textoDer.setFillColor(COLOR_TEXTO_PANEL_ACERCA);

    botonera.inicializar(CANT_BOTONES_ACERCA, fuenteBotonera);
    botonera.seColoresBot(COLOR_FONDO_ACERCA, COLOR_RECUA_BOTON_ACERCA);
    botonera.inicializarRectangulos(tamRectBotonX_ACERCA, tamRectBotonY_ACERCA);
    botonera.setTamCar(TAM_CARACTER_ACERCA);
    botonera.setColorTexto(COLOR_LETRA_ACERCA);
    botonera.inicializarEtiquetas(ETI_BOTONES_ACERCA, CANT_BOTONES_ACERCA);
    botonera.inicializarBotones(posBotonX_ACERCA, posBotonY_ACERCA, true);
}

void VentanaAcerca::ejecutarAccion(int i)
{
    switch (i)
    {
    case 0:
        m_gestor.ocultar("acerca");
        m_gestor.mostrar("principal");
        break;
    }
}

void VentanaAcerca::manejarEvento(const sf::Event& evento)
{
    if (evento.type == sf::Event::MouseMoved)
    {
        for (int i = 0; i < CANT_BOTONES_ACERCA; i++)
        {
            if (!botonera.obtPosicion(i).contains(static_cast<float>(evento.mouseMove.x), static_cast<float>(evento.mouseMove.y)))
            {
                botonera.igualarBotones(COLOR_FONDO_ACERCA, COLOR_LETRA_ACERCA);
                break;
            }
        }

        for (int i = 0; i < CANT_BOTONES_ACERCA; i++)
        {
            if (botonera.obtPosicion(i).contains(static_cast<float>(evento.mouseMove.x), static_cast<float>(evento.mouseMove.y)))
            {
                botonera.resaltarBoton(i, COLOR_FONDO_RES_ACERCA, COLOR_LETRA_RES_ACERCA);
                break;
            }
        }
    }
    if (evento.type == sf::Event::MouseButtonPressed && evento.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(m_gestor.obtenerVentana());
        for (int i = 0; i < CANT_BOTONES_ACERCA; i++)
        {
            if (botonera.obtPosicion(i).contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
            {
                ejecutarAccion(i);
                break;
            }
        }
    }
}
