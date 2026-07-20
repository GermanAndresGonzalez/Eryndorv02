
#include "salida.h"
#include "centrar.h"
#include "VentanaEquipar.h"
#include "botonera.h"
#include "PanelTexto.h"

#include "datosFuentes.h"
#include "datosVenAr.h"
#include "datosBotonArmar.h"

#include "ArchivoInventario.h"
#include "ArchivoPartidas.h"
#include "inventarioCueva.h"
#include "explorarCueva.h"

#include <iostream>
#include <string>



VentanaEquipar::VentanaEquipar(GestorPantallas& gestor)
    : m_gestor(gestor)
    , m_explorar(gestor.obtenerPartida(), 10)
{
    nomcadCueva = "Cueva";
    Botonera botonera;

    cargarRec();
}

void VentanaEquipar::alMostrar()
{
    Partida* datos = m_gestor.obtenerPartida();
    nomcadJug = datos->nombre;
    //datos->turnoJugador = 10;
    guardado = false;   // resetear flag de turno al entrar

    // ── Reset crítico: descarta inventario en memoria y carga el de
    //    la partida activa desde disco. Evita mostrar datos de otra partida.
    m_explorar.resetearInventario();
    m_explorar.setTurnos(datos->turnoJugador);

    nombreJug.setString(datos->nombre);
    Centrado::centrar(nombreJug, panelJug.obtenerLimites(), panelJug.getPosInternaY()+25.f);

    std::string textoTurnos = "Te quedan " + std::to_string(datos->turnoJugador) + " turnos para llenar tu mochila.";
    std::cout << "\n" << textoTurnos << std::endl;
    m_turnos.setString(textoTurnos);
    Centrado::centrar(m_turnos, m_gestor.obtenerVentana(), 120.f);

    m_explorar.cargarPanel(panelJug, txtPanelJug, txtPanelJug2);
    m_explorar.explorarCueva(panelCueva, txtPanelCue);
    m_explorar.cargarVida(panelJug,txtPanelJug2, txtVidaJugador);

    if (m_explorar.guardarPartida())
        std::cout << "Partida guardada\n";
    else
        std::cout << "No se guardó la partida\n";

    bool vidaIgual=(datos->vidaActual==datos->vidaMaxima);
    verBotones(vidaIgual);
    actualizarNombreJug(datos->nombre);

}

void VentanaEquipar::actualizarNombreJug(const std::string& nombre)
{
    nombreJug.setString(nombre);
    Centrado::centrar(nombreJug, panelJug.obtenerLimites(), panelJug.getPosInternaY()+10);
}

void VentanaEquipar::verBotones(bool vidaIgual)
{
    for (int i=0; i<CANT_BOTONES_ARMAR; i++)
    {
        botonera.setActivo(i,true);
    }
    botonera.setActivo(3, !vidaIgual);
}
void VentanaEquipar::alOcultar()
{
}

void VentanaEquipar::actualizar(float dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        m_gestor.ocultar("principal");
        m_gestor.mostrar("intro");
    }
}

void VentanaEquipar::dibujar(sf::RenderWindow& ventana)
{
    ventana.draw(spriteFondo);
    ventana.draw(m_texto);
    ventana.draw(m_turnos);

    ventana.draw(panelJug);
    ventana.draw(panelCueva);

    //panelJug.dibujar(m_gestor.obtenerVentana());
    //panelCueva.dibujar(m_gestor.obtenerVentana());
    ventana.draw(nombreJug);
    ventana.draw(nombreCue);
    ventana.draw(txtPanelCue);
    ventana.draw(txtPanelJug);
    ventana.draw(txtPanelJug2);
    ventana.draw(txtVidaJugador);

    ventana.draw(botonera);


}

void VentanaEquipar::cargarRec()
{
    if (!m_fuente.loadFromFile(FUENTES))
        std::cerr << ERROR_FUENTE << " VenArmar\n";
    m_texto.setFont(m_fuente);
    m_texto.setString(TEXTO_TIT_ARMAR);
    m_texto.setCharacterSize(45);
    m_texto.setColor(CLR_RECUA_PA_ARMAR_RES);

    sf::FloatRect rect = m_texto.getLocalBounds();
    m_texto.setOrigin(rect.left + rect.width/2.0f, rect.top + rect.height/2.0f);
    m_texto.setPosition(sf::Vector2f(m_gestor.obtenerVentana().getSize().x / 2.0f, 50.f));

    m_turnos.setFont(m_fuente);
    m_turnos.setCharacterSize(35);
    m_turnos.setColor(CLR_RECUA_PA_ARMAR_RES);
    Centrado::centrar(m_turnos, m_gestor.obtenerVentana(), 120.f);

    panelJug   = Panel(110.f, 200.f, 300.f, 400.f);
    panelCueva = Panel(490.f, 200.f, 400.f, 400.f);

    if (!texturaFondo.loadFromFile(RUTA_FONDO_ARMAR))
        std::cerr << ERROR_FONDO_ARMAR;
    if (!fuenteBotonera.loadFromFile(FUENTES))
        std::cerr << ERROR_FUENTE;

    spriteFondo.setTexture(texturaFondo);

    botonera.inicializar(CANT_BOTONES_ARMAR, fuenteBotonera);
    botonera.seColoresBot(COLOR_FONDO_ARMAR, COLOR_RECUA_ARMAR);
    botonera.inicializarRectangulos(tamRectBotonX_ARMAR, tamRectBotonY_ARMAR);
    botonera.setTamCar(TAM_CARACTER_ARMAR);
    botonera.setColorTexto(COLOR_LETRA_ARMAR);
    botonera.inicializarEtiquetas(ETI_BOTONES_ARMAR, CANT_BOTONES_ARMAR);
    botonera.inicializarBotones(posBotonX_ARMAR, posBotonY_ARMAR);

    nombreJug.setFont(m_fuente);
    nombreJug.setCharacterSize(TAM_CAR_PARR_ARMAR);
    nombreJug.setColor(CLR_RECUA_PA_ARMAR);

    nombreCue.setFont(m_fuente);
    nombreCue.setCharacterSize(TAM_CAR_PARR_ARMAR);
    nombreCue.setString(nomcadCueva);
    Centrado::centrar(nombreCue, panelCueva.obtenerLimites(), panelCueva.getPosInternaY()+10.f);
    nombreCue.setColor(CLR_RECUA_PA_ARMAR);

    txtPanelCue.setFont(m_fuente);
    txtPanelCue.setCharacterSize(TAM_CAR_PARR_ARMAR);
    txtPanelCue.setColor(CLR_RECUA_PA_ARMAR);
    txtPanelCue.setString(nomcadCueva);

    txtPanelJug.setFont(m_fuente);
    txtPanelJug.setCharacterSize(TAM_CAR_PARR_ARMAR);
    txtPanelJug.setColor(CLR_RECUA_PA_ARMAR);
    txtPanelJug.setString("");

    txtPanelJug2.setFont(m_fuente);
    txtPanelJug2.setCharacterSize(TAM_CAR_PARR_ARMAR);
    txtPanelJug2.setColor(CLR_RECUA_PA_ARMAR);
    txtPanelJug2.setString("");


    txtVidaJugador.setFont(m_fuente);
    txtVidaJugador.setCharacterSize(TAM_CAR_PARR_ARMAR);
    txtVidaJugador.setColor(CLR_RECUA_PA_ARMAR_RES);
    txtVidaJugador.setString("Vida actual: ");


}

void VentanaEquipar::ejecutarAccion(int i)
{

    std::cout << "Click\n";
    switch (i)
    {
    case 0:
        std::cout << "explorar\n";
        v_explorar();
        break;
    case 1:
        std::cout << "agregar\n";
        v_agregar();
        break;
    case 2:
        m_gestor.ocultar("explorar");
        m_gestor.mostrar("craftear");
        break;
    case 3:
        v_curar();
        std::cout <<"\n\nCurar\n\n";
        break;
    case 4:
        m_gestor.ocultar("explorar");
        m_gestor.mostrar("combatir");
        break;
    case 5:
        m_explorar.modificarPartida();
        m_gestor.ocultar("explorar");
        m_gestor.mostrar("jugador");
        break;
    }
}

void VentanaEquipar::v_explorar()
{
    m_explorar.explorarCueva(panelCueva, txtPanelCue);
    guardado = false;
    v_actualizar();
}

void VentanaEquipar::v_curar()
{
    if (m_explorar.curar(txtVidaJugador))
    {
       guardado = false;
       m_explorar.cargarPanel(panelJug, txtPanelJug, txtPanelJug2);
       m_explorar.cargarVida(panelJug,txtPanelJug2, txtVidaJugador);
    }
}


void VentanaEquipar::v_agregar()
{
    if (!guardado)
    {
        if (m_explorar.agregarInventario())
        {
            std::cout << "Agregar\n";
            txtPanelCue.setString("\nAgregado.");
            guardado = true;
            Partida* datos = m_gestor.obtenerPartida();
            datos->turnoJugador--;
            m_explorar.setTurnos(datos->turnoJugador);
            v_actualizar();
            std::cout << "Turnos jugador: " << datos->turnoJugador << std::endl;
            m_explorar.cargarPanel(panelJug, txtPanelJug, txtPanelJug2);
        }
    }
}

void VentanaEquipar::v_actualizar()
{
    for (int i=0; i<4; i++)
    {
        botonera.setActivo(i,true);
    }
    m_explorar.cargarPanel(panelJug, txtPanelJug, txtPanelJug2);
    Partida* datos = m_gestor.obtenerPartida();
    std::string textoTurnos = "Te quedan " + std::to_string(datos->turnoJugador) + " turnos para llenar tu mochila.";
    m_turnos.setString(textoTurnos);
    Centrado::centrar(m_turnos, m_gestor.obtenerVentana(), 120.f);
    if (datos->turnoJugador==0)
    {
        for (int i=0; i<2; i++)
        {
            botonera.setActivo(i,false);
        }
        //std::cout << "Turnos: 0\n";
    }

}

void VentanaEquipar::manejarEvento(const sf::Event& evento)
{
    if (evento.type == sf::Event::Closed)
    {
        if (Salida::Volver(m_gestor))
            m_gestor.ocultar("explorar");
        m_gestor.mostrar("jugador");
    }

    if (evento.type == sf::Event::MouseMoved)
    {
        for (int i = 0; i < CANT_BOTONES_ARMAR; i++)
        {
            if (!botonera.obtPosicion(i).contains(
                        static_cast<float>(evento.mouseMove.x),
                        static_cast<float>(evento.mouseMove.y)))
            {
                botonera.igualarBotones(COLOR_FONDO_ARMAR, COLOR_LETRA_ARMAR);
                break;
            }
        }
        for (int i = 0; i < CANT_BOTONES_ARMAR; i++)
        {
            if (botonera.obtPosicion(i).contains(
                        static_cast<float>(evento.mouseMove.x),
                        static_cast<float>(evento.mouseMove.y)))
            {
                botonera.resaltarBoton(i, COLOR_FONDO_RES_ARMAR, COLOR_LETRA_RES_ARMAR);
                break;
            }
        }
    }

    if (evento.type == sf::Event::MouseButtonPressed &&
            evento.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(m_gestor.obtenerVentana());
        for (int i = 0; i < CANT_BOTONES_ARMAR; i++)
        {
            if (botonera.obtPosicion(i).contains(
                        static_cast<float>(mousePos.x),
                        static_cast<float>(mousePos.y)))
            {
                ejecutarAccion(i);
                break;
            }
        }
    }
}
