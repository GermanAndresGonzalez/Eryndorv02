
#include "salida.h"
#include "ventanaExplor.h"
#include "botonera.h"
#include "PanelTexto.h"


#include "datosFuentes.h"
#include "datosVenEx.h"
#include "datosBotonExplor.h"

#include "ArchivoInventario.h"
#include "ArchivoPartidas.h"
#include "inventarioCueva.h"



#include <iostream>
VentanaExplo::VentanaExplo(GestorPantallas& gestor): m_gestor(gestor)
{


    Botonera botonera;
    cargarRec();
    ManejoPartida();
    CargarJugadores();
}


void VentanaExplo::alMostrar()
{
    std::cout << "VentanaExplo: ahora visible\n";

}
void VentanaExplo::alOcultar()
{
    std::cout << "VentanaExplo: ahora oculta\n";
}
void VentanaExplo::actualizar(float dt)
{
// Si el usuario presiona ENTER, ir a la intro
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        m_gestor.ocultar("principal");
        m_gestor.mostrar("intro");
    }
}

void VentanaExplo::ManejoPartida()
{
    Partida* datos = m_gestor.obtenerPartida();
    std::cout << "Partida\n";
    std::cout << "Partida: " <<datos->partida <<std::endl;
    std::cout << "Nivel: " <<datos->nivel<<std::endl;
    std::cout << "ID: " <<datos->id<<std::endl;
    std::cout << "Turno jug: " <<datos->turnoJugador<<std::endl;
    std::cout << "Turno pc: " <<datos->turnoComput<<std::endl<<std::endl;;


}



void VentanaExplo::dibujar(sf::RenderWindow& ventana)
{
    ventana.draw(spriteFondo);
    ventana.draw(m_texto);
    ventana.draw(txtPanelJug);
    ventana.draw(txtPanelCue);
    ventana.draw(m_turnos);

    panelJug.dibujar(m_gestor.obtenerVentana());
    panelCueva.dibujar(m_gestor.obtenerVentana());

    //ventana.draw(spriteJug1);
    //ventana.draw(spriteJug2);
    //panelJug=Panel(300.f,210.f,292.f,303.f);
    //panelCueva=Panel(688.f,210.f,292.f,303.f);

    botonera.draw(ventana);
}

void VentanaExplo::cargarRec()
{

    m_fuente.loadFromFile(FUENTES);
    m_texto.setFont(m_fuente);
    m_texto.setString(TEXTO_TIT);

    m_texto.setCharacterSize(45);
    m_texto.setColor(CLR_RECUA_PA_EX_RES);


    sf::FloatRect rect=m_texto.getLocalBounds();
    m_texto.setOrigin(rect.left+rect.width/2.0f,rect.top+rect.height/2.0f);
    m_texto.setPosition(sf::Vector2f(m_gestor.obtenerVentana().getSize().x / 2.0f, 50.f));




    m_turnos.setFont(m_fuente);
    m_turnos.setString(TEXTO_TURNOS);
    m_turnos.setCharacterSize(35);
    m_turnos.setColor(CLR_RECUA_PA_EX_RES);

    rect=m_turnos.getLocalBounds();
    m_turnos.setOrigin(rect.left+rect.width/2.0f,rect.top+rect.height/2.0f);
    m_turnos.setPosition(sf::Vector2f(m_gestor.obtenerVentana().getSize().x / 2.0f, 120.f));

    panelJug=Panel(160.f,200.f,300.f,400.f);
    panelCueva=Panel(490.f,200.f,300.f,400.f);

    txtPanelJug.setFont(m_fuente);
    txtPanelJug.setString("");
    txtPanelJug.setCharacterSize(TAM_CAR_PARR_EX);
    txtPanelJug.setPosition(352.f, 525.f);
    txtPanelJug.setColor(CLR_RECUA_PA_EX);

    txtPanelCue.setFont(m_fuente);
    txtPanelCue.setString("");
    txtPanelCue.setCharacterSize(TAM_CAR_PARR_EX);
    txtPanelCue.setPosition(760.f, 525.f);//688
    txtPanelCue.setColor(CLR_RECUA_PA_EX);


    if (!texturaFondo.loadFromFile(RUTA_FONDO_EX))
    {
        std::cerr << ERROR_FONDO_EX;
    }
    if (!fuenteBotonera.loadFromFile(FUENTES))
    {
        std::cerr << ERROR_FUENTE;
    }


    spriteFondo.setTexture(texturaFondo);

    botonera.inicializar(CANT_BOTONES_EXP, fuenteBotonera);
    botonera.seColoresBot(COLOR_FONDO_EXP,COLOR_RECUA_EXP);
    botonera.inicializarRectangulos(tamRectBotonX_EXP, tamRectBotonY_EXP);
    botonera.setTamCar(TAM_CARACTER_EXP);
    botonera.setColorTexto(COLOR_LETRA_EXP); //COLOR_FONDO
    botonera.inicializarEtiquetas(ETI_BOTONES_EXP,CANT_BOTONES_EXP);
    botonera.inicializarBotones(posBotonX_EXP,posBotonY_EXP);

    InventarioCueva cueva(999,999,999);


}

void VentanaExplo::CargarJugadores()
{
    std::cout << "Jugadores";



}
void VentanaExplo::ejecutarAccion(int i)
{
    /*
    "Agregar",
    "Craftear",
    "Siguiente",
    "Volver"
    */
    std::cout << "Click\n";
    switch (i)
    {
    case 0:
        m_gestor.ocultar("explorar");
        m_gestor.mostrar("explorar");

        break;

    case 1:
        m_gestor.ocultar("explorar");
        m_gestor.mostrar("explorar");
        break;

    case 2:
        m_gestor.ocultar("explorar");
        m_gestor.mostrar("explorar");
        break;
    case 3:
        if (Salida::Volver(m_gestor))
        {
            m_gestor.ocultar("explorar");
            m_gestor.mostrar("jugador");
        }
        break;
    }
}

void VentanaExplo::manejarEvento(const sf::Event& evento)
{
    if (evento.type == sf::Event::Closed)
    {
        if (Salida::Volver(m_gestor))
            m_gestor.ocultar("explorar");
        m_gestor.mostrar("jugador");
    }

    if (evento.type==sf::Event::MouseMoved)
    {
        for (int i=0; i <CANT_BOTONES_EXP; i++)
        {
            if (!botonera.obtPosicion(i).contains(static_cast<float>(evento.mouseMove.x), static_cast<float>(evento.mouseMove.y)))
            {
                botonera.igualarBotones(COLOR_FONDO_EXP,COLOR_LETRA_EXP);
                break;
            }
        }

        for (int i=0; i <CANT_BOTONES_EXP; i++)
        {
            if (botonera.obtPosicion(i).contains(static_cast<float>(evento.mouseMove.x), static_cast<float>(evento.mouseMove.y)))
            {
                botonera.resaltarBoton(i,COLOR_FONDO_RES_EXP,COLOR_LETRA_RES_EXP);
                break;
            }
        }

        if (panelJug.obtenerLimites().contains(static_cast<float>(evento.mouseMove.x), static_cast<float>(evento.mouseMove.y)))
        {
            //panelJug.setBordeX(2.f);
            panelJug.setColor(CLR_RECUA_PA_EX_RES);
            panelJug.setColContorno(CLR_RECUA_PA_EX_RES);


        }

        else
        {
            //panelJug.setBordeX(2.f);
            txtPanelJug.setColor(CLR_RECUA_PA_EX);
            panelJug.setColContorno(CLR_RECUA_PA_EX);

        }

        if (panelCueva.obtenerLimites().contains(static_cast<float>(evento.mouseMove.x), static_cast<float>(evento.mouseMove.y)))
        {
            txtPanelCue.setColor(CLR_RECUA_PA_EX_RES);
            //panelCueva.setBordeX(2.f);
            panelCueva.setColContorno(CLR_RECUA_PA_EX_RES);

        }
        else
        {
            //panelCueva.setBordeX(2.f);
            txtPanelCue.setColor(CLR_RECUA_PA_EX);
            panelCueva.setColContorno(CLR_RECUA_PA_EX);

        }
    }
    if (evento.type == sf::Event::MouseButtonPressed && evento.mouseButton.button == sf::Mouse::Left)
    {


        sf::Vector2i mousePos = sf::Mouse::getPosition(m_gestor.obtenerVentana());
        for (int i=0; i<CANT_BOTONES_EXP; i++)
        {
            if (botonera.obtPosicion(i).contains(static_cast<float>(mousePos.x),static_cast<float>(mousePos.y)))
            {
                ejecutarAccion(i);
                break;
            }
        }
        if (panelJug.obtenerLimites().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
        {
            m_gestor.obtenerPartida()->id = 1;
            std::cout << "Partida.id = 1" << std::endl;
        }

        if (panelCueva.obtenerLimites().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
        {
            m_gestor.obtenerPartida()->id = 2;
            std::cout << "Partida.id = 2" << std::endl;
        }
    }

}

