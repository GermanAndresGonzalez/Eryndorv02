#include "ventanaJugad.h"
#include "botonera.h"
#include "datosBotonJug.h"
#include "datosPanelJug.h"
#include "datosVenJug.h"
#include "PanelTexto.h"



#include <iostream>


VentanaJug::VentanaJug(GestorPantallas& gestor): m_gestor(gestor)
{
    m_fuente.loadFromFile(FUENTE_JUG);
    m_texto.setFont(m_fuente);
    m_texto.setString("Hace click en el personaje con el que quieres jugar");
    m_texto.setCharacterSize(40);
    m_texto.setPosition(210.f, 50.f);

    panelJug1=Panel(300.f,210.f,292.f,303.f);
    //panelJug1.setColor(CLR_RECUA_PA_JUG);
    panelJug2=Panel(688.f,210.f,292.f,303.f);

    nombreJug1.setFont(m_fuente);
    nombreJug1.setString("Kael Draven");
    nombreJug1.setCharacterSize(TAM_CAR_JUG);
    nombreJug1.setPosition(352.f, 525.f);
    nombreJug1.setColor(CLR_RECUA_PA_JUG);

    nombreJug2.setFont(m_fuente);
    nombreJug2.setString("Lyra Voss");
    nombreJug2.setCharacterSize(TAM_CAR_JUG);
    nombreJug2.setPosition(760.f, 525.f);//688
    nombreJug2.setColor(CLR_RECUA_PA_JUG);


    Botonera botonera;
    cargarRec();
    CargarJugadores();
}

void VentanaJug::alMostrar()
{
    std::cout << "VentanaJug: ahora visible\n";

}
void VentanaJug::alOcultar()
{
    std::cout << "VentanaJug: ahora oculta\n";
}
void VentanaJug::actualizar(float dt)
{
// Si el usuario presiona ENTER, ir a la intro
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        m_gestor.ocultar("principal");
        m_gestor.mostrar("intro");
    }
}
void VentanaJug::dibujar(sf::RenderWindow& ventana)
{
    ventana.draw(spriteFondo);
    ventana.draw(m_texto);
    ventana.draw(nombreJug1);
    ventana.draw(nombreJug2);

    panelJug1.dibujar(m_gestor.obtenerVentana());
    panelJug2.dibujar(m_gestor.obtenerVentana());

    ventana.draw(spriteJug1);
    ventana.draw(spriteJug2);
    //panelJug1=Panel(300.f,210.f,292.f,303.f);
    //panelJug2=Panel(688.f,210.f,292.f,303.f);

    botonera.draw(ventana);
}

void VentanaJug::cargarRec()
{
    if (!texturaFondo.loadFromFile(RUTA_FONDO_JUG))
    {
        std::cerr << ERROR_FONDO_JUG;
    }
    if (!fuenteBotonera.loadFromFile(FUENTE_JUG))
    {
        std::cerr << ERROR_FUENTE_JUG;
    }


    spriteFondo.setTexture(texturaFondo);

    botonera.inicializar(CANT_BOTONES_JUG, fuenteBotonera);
    botonera.seColoresBot(COLOR_FONDO_JUG,COLOR_RECUA_JUG);
    botonera.inicializarRectangulos(tamRectBotonX_JUG, tamRectBotonY_JUG);
    botonera.setTamCar(TAM_CARACTER_JUG);
    botonera.setColorTexto(COLOR_LETRA_JUG); //COLOR_FONDO
    botonera.inicializarEtiquetas(ETI_BOTONES_JUG,CANT_BOTONES_JUG);
    botonera.inicializarBotones(posBotonX_JUG,posBotonY_JUG,true);
    //inicializarDatos();


}
void VentanaJug::CargarJugadores()
{
    if (!texturaJug1.loadFromFile(RUTA_JUG_1))
    {
        std::cerr << ERROR_JUG;
    }

    spriteJug1.setTexture(texturaJug1);


    spriteJug1.setPosition(301.f,211.f);

    if (!texturaJug2.loadFromFile(RUTA_JUG_2))
    {
        std::cerr << ERROR_JUG;
    }
    spriteJug2.setTexture(texturaJug2);
    spriteJug2.setPosition(689.f,211.f);



}
void VentanaJug::ejecutarAccion(int i)
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
        m_gestor.ocultar("jugador");
        m_gestor.mostrar("explorar");
        break;
    }

}

void VentanaJug::manejarEvento(const sf::Event& evento)
{

    if (evento.type==sf::Event::MouseMoved)
    {
        for (int i=0; i <CANT_BOTONES_JUG; i++)
        {
            if (!botonera.obtPosicion(i).contains(static_cast<float>(evento.mouseMove.x), static_cast<float>(evento.mouseMove.y)))
            {
                botonera.igualarBotones(COLOR_FONDO_JUG,COLOR_LETRA_JUG);
                break;
            }
        }

        for (int i=0; i <CANT_BOTONES_JUG; i++)
        {
            if (botonera.obtPosicion(i).contains(static_cast<float>(evento.mouseMove.x), static_cast<float>(evento.mouseMove.y)))
            {
                botonera.resaltarBoton(i,COLOR_FONDO_RES_JUG,COLOR_LETRA_RES_JUG);
                break;
            }
        }

        if (panelJug1.obtenerLimites().contains(static_cast<float>(evento.mouseMove.x), static_cast<float>(evento.mouseMove.y)))
            {
                //panelJug1.setBordeX(2.f);
                nombreJug1.setColor(CLR_RECUA_PA_JUG_RES);
                panelJug1.setColContorno(CLR_RECUA_PA_JUG_RES);


            }

        else
        {
            //panelJug1.setBordeX(2.f);
            nombreJug1.setColor(CLR_RECUA_PA_JUG);
            panelJug1.setColContorno(CLR_RECUA_PA_JUG);

        }

        if (panelJug2.obtenerLimites().contains(static_cast<float>(evento.mouseMove.x), static_cast<float>(evento.mouseMove.y)))
            {
            nombreJug2.setColor(CLR_RECUA_PA_JUG_RES);
            //panelJug2.setBordeX(2.f);
            panelJug2.setColContorno(CLR_RECUA_PA_JUG_RES);

            }
        else
            {
            //panelJug2.setBordeX(2.f);
            nombreJug2.setColor(CLR_RECUA_PA_JUG);
            panelJug2.setColContorno(CLR_RECUA_PA_JUG);

            }
    }
    if (evento.type == sf::Event::MouseButtonPressed && evento.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(m_gestor.obtenerVentana());
        for (int i=0; i<CANT_BOTONES_JUG; i++)
        {
            if (botonera.obtPosicion(i).contains(static_cast<float>(mousePos.x),static_cast<float>(mousePos.y)))
            {
                ejecutarAccion(i);
                break;
            }
        }
        if (panelJug1.obtenerLimites().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
        {
            m_gestor.obtenerPartida()->id = 1;
            std::cout << "Partida.id = 1" << std::endl;
        }

        if (panelJug2.obtenerLimites().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
        {
            m_gestor.obtenerPartida()->id = 2;
            std::cout << "Partida.id = 2" << std::endl;
        }
    }
}

