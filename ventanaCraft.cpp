
#include "salida.h"
#include "datosArchivos.h"
#include "centrar.h"
#include "VentanaCraft.h"
#include "botonera.h"
#include "PanelTexto.h"

#include "datosFuentes.h"
#include "datosVenCraft.h"
#include "datosBotonCraf.h"

#include "ArchivoInventario.h"
#include "ArchivoPartidas.h"
#include "inventarioCueva.h"
//#include "crafteoMan.h"

#include <iostream>
#include <string>

VentanaCraft::VentanaCraft(GestorPantallas& gestor)
    : m_gestor(gestor)
    , m_craftear(gestor.obtenerPartida(), 10)
{
    nomcadCueva = "Cueva";
    Botonera botonera;
    cargarRec();
}

void VentanaCraft::alMostrar()
{
    Partida* datos = m_gestor.obtenerPartida();
    nomcadJug = datos->nombre;
    datos->turnoJugador = 10;
    guardado = false;   // resetear flag de turno al entrar

    // ── Reset crítico: descarta inventario en memoria y carga el de
    //    la partida activa desde disco. Evita mostrar datos de otra partida.
    m_craftear.resetearInventario();

    nombreJug.setString(datos->nombre);
    Centrado::centrar(nombreJug, panelJug.obtenerLimites(), panelJug.getPosInternaY()+25.f);

    std::string textoTurnos = "Te quedan " + std::to_string(datos->turnoJugador) + " turnos para craftear.";
    std::cout << "\n" << textoTurnos << std::endl;
    m_turnos.setString(textoTurnos);
    Centrado::centrar(m_turnos, m_gestor.obtenerVentana(), 120.f);

    m_craftear.cargarPanel(panelJug, txtPanelJug, txtPanelJug2);
    m_craftear.explorarCueva(panelCueva, txtPanelCue);

    if (m_craftear.guardarPartida())
        std::cout << "Partida guardada\n";
    else
        std::cout << "No se guardó la partida\n";

    actualizarNombreJug(datos->nombre);
}

void VentanaCraft::actualizarNombreJug(const std::string& nombre)
{
    nombreJug.setString(nombre);
    Centrado::centrar(nombreJug, panelJug.obtenerLimites(), panelJug.getPosInternaY()+10);
}

void VentanaCraft::alOcultar()
{
}

void VentanaCraft::actualizar(float dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        m_gestor.ocultar("principal");
        m_gestor.mostrar("intro");
    }
}

void VentanaCraft::dibujar(sf::RenderWindow& ventana)
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

    botoneraCra.draw(ventana);
}

void VentanaCraft::cargarRec()
{
    if (m_fuente.loadFromFile(FUENTES))
        std::cerr << ERROR_FUENTE;
    m_texto.setFont(m_fuente);
    m_texto.setString(TEXTO_TIT_CR);
    m_texto.setCharacterSize(45);
    m_texto.setColor(COLOR_FONDO_CR);

    sf::FloatRect rect = m_texto.getLocalBounds();
    m_texto.setOrigin(rect.left + rect.width/2.0f, rect.top + rect.height/2.0f);
    m_texto.setPosition(sf::Vector2f(m_gestor.obtenerVentana().getSize().x / 2.0f, 50.f));

    m_turnos.setFont(m_fuente);
    m_turnos.setCharacterSize(35);
    m_turnos.setColor(COLOR_FONDO_CR);
    Centrado::centrar(m_turnos, m_gestor.obtenerVentana(), 120.f);

    panelJug   = Panel(160.f, 200.f, 300.f, 400.f);
    panelCueva = Panel(490.f, 200.f, 300.f, 400.f);

    if (!texturaFondo.loadFromFile(RUTA_FONDO_CR))
        std::cerr << ERROR_FONDO_CR;
    if (!fuenteBotonera.loadFromFile(FUENTES))
        std::cerr << ERROR_FUENTE;

    spriteFondo.setTexture(texturaFondo);

    botoneraCra.inicializar(CANT_BOTONES_CR, fuenteBotonera);
    botoneraCra.seColoresBot(COLOR_FONDO_CR, COLOR_RECUA_CR);
    botoneraCra.inicializarRectangulos(tamRectBotonX_CR, tamRectBotonY_CR);
    botoneraCra.setTamCar(TAM_CARACTER_CR);
    botoneraCra.setColorTexto(COLOR_LETRA_CR);
    botoneraCra.inicializarEtiquetas(ETI_BOTONES_CR, CANT_BOTONES_CR);
    botoneraCra.inicializarBotones(posBotonX_CR, posBotonY_CR);

    nombreJug.setFont(m_fuente);
    nombreJug.setCharacterSize(TAM_CAR_PARR_CR);
    nombreJug.setColor(CLR_RECUA_PA_CR);

    nombreCue.setFont(m_fuente);
    nombreCue.setCharacterSize(TAM_CAR_PARR_CR);
    nombreCue.setString(nomcadCueva);
    Centrado::centrar(nombreCue, panelCueva.obtenerLimites(), panelCueva.getPosInternaY()+10.f);
    nombreCue.setColor(CLR_RECUA_PA_CR);

    txtPanelCue.setFont(m_fuente);
    txtPanelCue.setCharacterSize(TAM_CAR_PARR_CR);
    txtPanelCue.setColor(CLR_RECUA_PA_CR);
    txtPanelCue.setString(nomcadCueva);

    txtPanelJug.setFont(m_fuente);
    txtPanelJug.setCharacterSize(TAM_CAR_PARR_CR);
    txtPanelJug.setColor(CLR_RECUA_PA_CR);
    txtPanelJug.setString("");

    txtPanelJug2.setFont(m_fuente);
    txtPanelJug2.setCharacterSize(TAM_CAR_PARR_CR);
    txtPanelJug2.setColor(CLR_RECUA_PA_CR);
    txtPanelJug2.setString("");
}

void VentanaCraft::ejecutarAccion(int i)
{
    std::cout << "Click\n";
    switch (i)
    {
    case 0:
        std::cout << "explorar\n";
        v_craftear();
        break;
    case 1:
        std::cout << "agregar\n";
        v_agregar();
        break;
    case 2:
        break;
    case 3:
        m_gestor.ocultar("explorar");
        m_gestor.mostrar("explorar");
        break;
    case 4:
        m_gestor.ocultar("explorar");
        m_gestor.mostrar("explorar");
        break;


    case 5:
        m_craftear.modificarPartida();
        m_gestor.ocultar("craftear");
        m_gestor.mostrar("explorar");
        break;
    }
}

void VentanaCraft::v_craftear()
{
    m_craftear.explorarCueva(panelCueva, txtPanelCue);
    guardado = false;
    v_actualizar();
}

void VentanaCraft::v_agregar()
{
    if (!guardado)
    {
        if (m_craftear.agregarInventario())
        {
            std::cout << "Agregar\n";
            txtPanelCue.setString("\nAgregado.");
            guardado = true;
            Partida* datos = m_gestor.obtenerPartida();
            datos->turnoJugador--;
            m_craftear.setTurnos(datos->turnoJugador);
            v_actualizar();
            std::cout << "Turnos jugador: " << datos->turnoJugador << std::endl;
            m_craftear.cargarPanel(panelJug, txtPanelJug, txtPanelJug2);
        }
    }
}

void VentanaCraft::v_actualizar()
{
    m_craftear.cargarPanel(panelJug, txtPanelJug, txtPanelJug2);
    Partida* datos = m_gestor.obtenerPartida();
    std::string textoTurnos = "Te quedan " + std::to_string(datos->turnoJugador) + " turnos para llenar tu mochila.";
    m_turnos.setString(textoTurnos);
    Centrado::centrar(m_turnos, m_gestor.obtenerVentana(), 120.f);
}

void VentanaCraft::manejarEvento(const sf::Event& evento)
{
    if (evento.type == sf::Event::Closed)
    {
        if (Salida::Volver(m_gestor))
            m_gestor.ocultar("explorar");
        m_gestor.mostrar("jugador");
    }

    if (evento.type == sf::Event::MouseMoved)
    {
        for (int i = 0; i < CANT_BOTONES_CR; i++)
        {
            if (!botoneraCra.obtPosicion(i).contains(
                    static_cast<float>(evento.mouseMove.x),
                    static_cast<float>(evento.mouseMove.y)))
            {
                botoneraCra.igualarBotones(COLOR_FONDO_CR, COLOR_LETRA_CR);
                break;
            }
        }
        for (int i = 0; i < CANT_BOTONES_CR; i++)
        {
            if (botoneraCra.obtPosicion(i).contains(
                    static_cast<float>(evento.mouseMove.x),
                    static_cast<float>(evento.mouseMove.y)))
            {
                botoneraCra.resaltarBoton(i, COLOR_FONDO_RES_CR, COLOR_LETRA_RES_CR);
                break;
            }
        }
    }

    if (evento.type == sf::Event::MouseButtonPressed &&
        evento.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(m_gestor.obtenerVentana());
        for (int i = 0; i < CANT_BOTONES_CR; i++)
        {
            if (botoneraCra.obtPosicion(i).contains(
                    static_cast<float>(mousePos.x),
                    static_cast<float>(mousePos.y)))
            {
                ejecutarAccion(i);
                break;
            }
        }
    }
}
