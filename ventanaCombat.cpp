
#include "salida.h"
#include "centrar.h"
#include "VentanaCombat.h"
#include "botonera.h"
#include "PanelTexto.h"

#include "datosFuentes.h"
#include "datosVenCombat.h"
#include "datosBotonCombat.h"

#include "ArchivoInventario.h"
#include "ArchivoPartidas.h"
#include "inventarioCueva.h"
#include "explorarCueva.h"

#include <iostream>
#include <string>

VentanaCombat::VentanaCombat(GestorPantallas& gestor)
    : m_gestor(gestor)
    , m_combate(gestor.obtenerPartida(), 10)
{
    nomcadCueva = "Combate";
    Botonera botonera;
    cargarRec();
}

void VentanaCombat::alMostrar()
{
    Partida* datos = m_gestor.obtenerPartida();
    nomcadJug = datos->nombre;
    //datos->turnoJugador = 10;
    guardado = false;   // resetear flag de turno al entrar

    // ── Reset crítico: descarta inventario en memoria y carga el de
    //    la partida activa desde disco. Evita mostrar datos de otra partida.
    m_combate.resetearInventario();

    nombreJug.setString(datos->nombre);
    Centrado::centrar(nombreJug, panelJug.obtenerLimites(), panelJug.getPosInternaY()+25.f);

    std::string textoTurnos = "Te quedan " + std::to_string(datos->turnoJugador) + " turnos para llenar tu mochila.";
    std::cout << "\n" << textoTurnos << std::endl;
    m_turnos.setString(textoTurnos);
    Centrado::centrar(m_turnos, m_gestor.obtenerVentana(), 120.f);

    m_combate.cargarPanel(panelJug, txtPanelJug, txtPanelJug2);
    m_combate.explorarCueva(panelCueva, txtPanelCue);

    if (m_combate.guardarPartida())
        std::cout << "Partida guardada\n";
    else
        std::cout << "No se guardó la partida\n";

    actualizarNombreJug(datos->nombre);
}

void VentanaCombat::actualizarNombreJug(const std::string& nombre)
{
    nombreJug.setString(nombre);
    Centrado::centrar(nombreJug, panelJug.obtenerLimites(), panelJug.getPosInternaY()+10);
}

void VentanaCombat::alOcultar()
{
}

void VentanaCombat::actualizar(float dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        m_gestor.ocultar("principal");
        m_gestor.mostrar("intro");
    }
}

void VentanaCombat::dibujar(sf::RenderWindow& ventana)
{
    ventana.draw(spriteFondo);
    ventana.draw(m_texto);
    ventana.draw(m_turnos);

    panelJug.dibujar(m_gestor.obtenerVentana());
    panelCueva.dibujar(m_gestor.obtenerVentana());
    ventana.draw(nombreJug);
    ventana.draw(nombreCue);
    ventana.draw(txtPanelCue);
    ventana.draw(txtPanelJug);
    ventana.draw(txtPanelJug2);

    botonera.draw(ventana);
}

void VentanaCombat::cargarRec()
{
    if (m_fuente.loadFromFile(FUENTES))
        std::cerr << ERROR_FUENTE;
    m_texto.setFont(m_fuente);
    m_texto.setString(TEXTO_TIT_COM);
    m_texto.setCharacterSize(45);
    m_texto.setColor(CLR_RECUA_PA_COM_RES);

    sf::FloatRect rect = m_texto.getLocalBounds();
    m_texto.setOrigin(rect.left + rect.width/2.0f, rect.top + rect.height/2.0f);
    m_texto.setPosition(sf::Vector2f(m_gestor.obtenerVentana().getSize().x / 2.0f, 50.f));

    m_turnos.setFont(m_fuente);
    m_turnos.setCharacterSize(35);
    m_turnos.setColor(CLR_RECUA_PA_COM_RES);
    Centrado::centrar(m_turnos, m_gestor.obtenerVentana(), 120.f);

    panelJug   = Panel(160.f, 200.f, 300.f, 400.f);
    panelCueva = Panel(490.f, 200.f, 300.f, 400.f);

    if (!texturaFondo.loadFromFile(RUTA_FONDO_COM))
        std::cerr << ERROR_FONDO_COM;
    if (!fuenteBotonera.loadFromFile(FUENTES))
        std::cerr << ERROR_FUENTE;

    spriteFondo.setTexture(texturaFondo);

    botonera.inicializar(CANT_BOTONES_COM, fuenteBotonera);
    botonera.seColoresBot(COLOR_FONDO_COM, COLOR_RECUA_COM);
    botonera.inicializarRectangulos(tamRectBotonX_COM, tamRectBotonY_COM);
    botonera.setTamCar(TAM_CARACTER_COM);
    botonera.setColorTexto(COLOR_LETRA_COM);
    botonera.inicializarEtiquetas(ETI_BOTONES_COM, CANT_BOTONES_COM);
    botonera.inicializarBotones(posBotonX_COM, posBotonY_COM);

    nombreJug.setFont(m_fuente);
    nombreJug.setCharacterSize(TAM_CAR_PARR_COM);
    nombreJug.setColor(CLR_RECUA_PA_COM);

    nombreCue.setFont(m_fuente);
    nombreCue.setCharacterSize(TAM_CAR_PARR_COM);
    nombreCue.setString(nomcadCueva);
    Centrado::centrar(nombreCue, panelCueva.obtenerLimites(), panelCueva.getPosInternaY()+10.f);
    nombreCue.setColor(CLR_RECUA_PA_COM);

    txtPanelCue.setFont(m_fuente);
    txtPanelCue.setCharacterSize(TAM_CAR_PARR_COM);
    txtPanelCue.setColor(CLR_RECUA_PA_COM);
    txtPanelCue.setString(nomcadCueva);

    txtPanelJug.setFont(m_fuente);
    txtPanelJug.setCharacterSize(TAM_CAR_PARR_COM);
    txtPanelJug.setColor(CLR_RECUA_PA_COM);
    txtPanelJug.setString("");

    txtPanelJug2.setFont(m_fuente);
    txtPanelJug2.setCharacterSize(TAM_CAR_PARR_COM);
    txtPanelJug2.setColor(CLR_RECUA_PA_COM);
    txtPanelJug2.setString("");
}

void VentanaCombat::ejecutarAccion(int i)
{
    std::cout << "Click\n";
    switch (i)
    {
    case 0:
        std::cout << "Atacar\n";
        v_explorar();
        break;
    case 1:
        std::cout << "Curar\n";
        v_agregar();
        break;
    case 2:
        std::cout << "Huir\n";

        break;
    case 3:

        //m_combate.modificarPartida();
        m_gestor.ocultar("combate");
        m_gestor.mostrar("explorar");
        break;
    }
}

void VentanaCombat::v_explorar()
{
    m_combate.explorarCueva(panelCueva, txtPanelCue);
    guardado = false;
    v_actualizar();
}

void VentanaCombat::v_agregar()
{
    if (!guardado)
    {
        if (m_combate.agregarInventario())
        {
            std::cout << "Agregar\n";
            txtPanelCue.setString("\nAgregado.");
            guardado = true;
            Partida* datos = m_gestor.obtenerPartida();
            datos->turnoJugador--;
            m_combate.setTurnos(datos->turnoJugador);
            v_actualizar();
            std::cout << "Turnos jugador: " << datos->turnoJugador << std::endl;
            m_combate.cargarPanel(panelJug, txtPanelJug, txtPanelJug2);
        }
    }
}

void VentanaCombat::v_actualizar()
{
    for (int i=0;i<4;i++)
        {
            botonera.setActivo(i,true);
        }
    m_combate.cargarPanel(panelJug, txtPanelJug, txtPanelJug2);
    Partida* datos = m_gestor.obtenerPartida();
    std::string textoTurnos = "Te quedan " + std::to_string(datos->turnoJugador) + " turnos para llenar tu mochila.";
    m_turnos.setString(textoTurnos);
    Centrado::centrar(m_turnos, m_gestor.obtenerVentana(), 120.f);
    if (datos->turnoJugador==0)
    {
        for (int i=0;i<2;i++)
        {
            botonera.setActivo(i,false);
        }
        //std::cout << "Turnos: 0\n";
    }

}

void VentanaCombat::manejarEvento(const sf::Event& evento)
{
    if (evento.type == sf::Event::Closed)
    {
        if (Salida::Volver(m_gestor))
            m_gestor.ocultar("explorar");
        m_gestor.mostrar("jugador");
    }

    if (evento.type == sf::Event::MouseMoved)
    {
        for (int i = 0; i < CANT_BOTONES_COM; i++)
        {
            if (!botonera.obtPosicion(i).contains(
                    static_cast<float>(evento.mouseMove.x),
                    static_cast<float>(evento.mouseMove.y)))
            {
                botonera.igualarBotones(COLOR_FONDO_COM, COLOR_LETRA_COM);
                break;
            }
        }
        for (int i = 0; i < CANT_BOTONES_COM; i++)
        {
            if (botonera.obtPosicion(i).contains(
                    static_cast<float>(evento.mouseMove.x),
                    static_cast<float>(evento.mouseMove.y)))
            {
                botonera.resaltarBoton(i, COLOR_FONDO_RES_COM, COLOR_LETRA_RES_COM);
                break;
            }
        }
    }

    if (evento.type == sf::Event::MouseButtonPressed &&
        evento.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(m_gestor.obtenerVentana());
        for (int i = 0; i < CANT_BOTONES_COM; i++)
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
