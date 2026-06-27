#include "centrar.h"
#include "datosArchivos.h"
#include "ventanaJugad.h"
#include "botonera.h"
#include "datosBotonJug.h"
#include "datosPanelJug.h"
#include "datosVenJug.h"
#include "PanelTexto.h"
#include "ArchivoPartidas.h"
#include "nombres.h"
#include "salida.h"
#include "ventanaConfirmacion.h"
#include <cstring>
#include <iostream>


VentanaJug::VentanaJug(GestorPantallas& gestor)
    : m_gestor(gestor)
    , archivoPartidas(RUTA_DAT_PART)
{
    m_fuente.loadFromFile(FUENTE_JUG);
    m_texto.setFont(m_fuente);
    m_texto.setString("Hace click en el personaje con el que quieres jugar");
    m_texto.setCharacterSize(40);
    Centrado::centrar(m_texto, m_gestor.obtenerVentana(), 60.f);

    jugadElegido.setFont(m_fuente);
    jugadElegido.setCharacterSize(30);
    jugadElegido.setString("Todavia no se eligio un jugador");
    jugadElegido.setColor(CLR_RECUA_PA_JUG_RES);
    Centrado::centrar(jugadElegido, m_gestor.obtenerVentana(), 100.f);

    panelJug1 = Panel(300.f, 210.f, 292.f, 303.f);
    panelJug2 = Panel(688.f, 210.f, 292.f, 303.f);

    nombreJug1.setFont(m_fuente);
    nombreJug1.setString("Kael Draven");
    nombreJug1.setCharacterSize(TAM_CAR_JUG);
    nombreJug1.setPosition(352.f, 525.f);
    nombreJug1.setColor(CLR_RECUA_PA_JUG);

    nombreJug2.setFont(m_fuente);
    nombreJug2.setString("Lyra Voss");
    nombreJug2.setCharacterSize(TAM_CAR_JUG);
    nombreJug2.setPosition(760.f, 525.f);
    nombreJug2.setColor(CLR_RECUA_PA_JUG);

    Botonera botonera;
    cargarRec();
    CargarJugadores();
}

// ---------------------------------------------------------------------------
// cargarPartidas: genera un nuevo número de partida y lo escribe en Partida*
// ---------------------------------------------------------------------------
void VentanaJug::cargarPartidas()
{
    int noPartida = archivoPartidas.generarID();
    std::cout << "\nNum. partida: " << noPartida << "\n";
    if (noPartida > 0)
    {
        Partida* datos = m_gestor.obtenerPartida();
        datos->partida = noPartida;
        std::cout << "\nPartida: " << datos->partida << std::endl;
        std::cout << "\nNombre del jugador: " << datos->nombre << std::endl;
    }
}

// ---------------------------------------------------------------------------
// alMostrar: refleja el estado de Partida en la UI sin modificarlo
// ---------------------------------------------------------------------------
void VentanaJug::alMostrar()
{
    std::cout << "VentanaJug: ahora visible\n";
    sf::Event e;
    while (m_gestor.obtenerVentana().pollEvent(e)) { /* descartar */ }
    Partida* datos = m_gestor.obtenerPartida();

    if (datos->id != 0 && datos->nombre[0] != '\0')
    {
        // Hay partida activa: mostrarla, pre-seleccionar su jugador visualmente
        jugadElegido.setString(std::string("Jugando con ") + datos->nombre);
        m_jugadorSeleccionado = datos->id;   // solo para resaltado visual
    }
    else
    {
        jugadElegido.setString("Todavia no se eligio un jugador");
        m_jugadorSeleccionado = 0;
    }

    actualizarSeleccionVisual();
}

void VentanaJug::alOcultar()
{
    std::cout << "VentanaJug: ahora oculta\n";
}

void VentanaJug::actualizar(float dt)
{
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
    ventana.draw(jugadElegido);

    ventana.draw(panelJug1);
    ventana.draw(panelJug2);

    //panelJug1.dibujar(m_gestor.obtenerVentana());
    //panelJug2.dibujar(m_gestor.obtenerVentana());

    ventana.draw(spriteJug1);
    ventana.draw(spriteJug2);

    ventana.draw(botonera);

    //botonera.draw(ventana);
}

void VentanaJug::cargarRec()
{
    if (!texturaFondo.loadFromFile(RUTA_FONDO_JUG))
        std::cerr << ERROR_FONDO_JUG;
    if (!fuenteBotonera.loadFromFile(FUENTE_JUG))
        std::cerr << ERROR_FUENTE_JUG;

    spriteFondo.setTexture(texturaFondo);

    botonera.inicializar(CANT_BOTONES_JUG, fuenteBotonera);
    botonera.seColoresBot(COLOR_FONDO_JUG, COLOR_RECUA_JUG);
    botonera.inicializarRectangulos(tamRectBotonX_JUG, tamRectBotonY_JUG);
    botonera.setTamCar(TAM_CARACTER_JUG);
    botonera.setColorTexto(COLOR_LETRA_JUG);
    botonera.inicializarEtiquetas(ETI_BOTONES_JUG, CANT_BOTONES_JUG);
    botonera.inicializarBotones(posBotonX_JUG, posBotonY_JUG, true);
}

void VentanaJug::CargarJugadores()
{
    if (!texturaJug1.loadFromFile(RUTA_JUG_1))
        std::cerr << ERROR_JUG;
    spriteJug1.setTexture(texturaJug1);
    spriteJug1.setPosition(301.f, 211.f);

    if (!texturaJug2.loadFromFile(RUTA_JUG_2))
        std::cerr << ERROR_JUG;
    spriteJug2.setTexture(texturaJug2);
    spriteJug2.setPosition(689.f, 211.f);
}

// ---------------------------------------------------------------------------
// actualizarSeleccionVisual: resalta el panel del jugador seleccionado
// ---------------------------------------------------------------------------
void VentanaJug::actualizarSeleccionVisual()
{
    // Restablecer ambos primero
    nombreJug1.setColor(CLR_RECUA_PA_JUG);
    panelJug1.setColContorno(CLR_RECUA_PA_JUG);
    nombreJug2.setColor(CLR_RECUA_PA_JUG);
    panelJug2.setColContorno(CLR_RECUA_PA_JUG);

    if (m_jugadorSeleccionado == 1)
    {
        nombreJug1.setColor(CLR_RECUA_PA_JUG_RES);
        panelJug1.setColContorno(CLR_RECUA_PA_JUG_RES);
    }
    else if (m_jugadorSeleccionado == 2)
    {
        nombreJug2.setColor(CLR_RECUA_PA_JUG_RES);
        panelJug2.setColContorno(CLR_RECUA_PA_JUG_RES);
    }
}

// ---------------------------------------------------------------------------
// ejecutarAccion
//   [0] Atras       → volver sin tocar Partida
//   [1] Partida Nueva → confirmar, crear nueva partida con jugador seleccionado
//   [2] Seguir      → ir a explorar con la partida activa (sin cambios)
// ---------------------------------------------------------------------------
void VentanaJug::ejecutarAccion(int i)
{
    std::cout << "Click boton " << i << "\n";
    Partida* datos = m_gestor.obtenerPartida();

    switch (i)
    {
    // ── [0] Atras ─────────────────────────────────────────────────────────
    case 0:
        m_gestor.ocultar("jugador");
        m_gestor.mostrar("principal");
        break;

    // ── [1] Partida Nueva ─────────────────────────────────────────────────
    case 1:
    {
        // Solo pedir jugador si no hay ninguno seleccionado NI hay partida activa
        if (m_jugadorSeleccionado == 0 && datos->id == 0)
        {
            Salida::Mensaje(m_gestor, "Error", "Primero elige un jugador.");
            break;
        }

        int jugadorId = (m_jugadorSeleccionado != 0) ? m_jugadorSeleccionado : datos->id;

        std::string msgConfirm = (datos->partida > 0)
                                 ? "Se creara una partida nueva.\nLa partida actual se perdera.\nContinuar?"
                                 : "Se creara una partida nueva.\nContinuar?";

        VentanaConfirmacion conf("Partida Nueva", msgConfirm);
        if (!conf.mostrar(m_gestor.obtenerVentana()))
            break;

        datos->partida     = archivoPartidas.generarID();
        datos->nivel       = 0;
        datos->id          = jugadorId;
        datos->turnoJugador = 10;

        const std::string& nombre = NOMBRES[jugadorId - 1];
        std::strncpy(datos->nombre, nombre.c_str(), 49);
        datos->nombre[49] = '\0';

        m_gestor.ocultar("jugador");
        m_gestor.mostrar("explorar");
        break;
    }

    // ── [2] Seguir ────────────────────────────────────────────────────────
    case 2:
        std::cout << "Datos pantalla anterior: " << datos->pantallaAnterior << "\n";
        // Check if player is selected or if there's an existing game
        if (datos->id == 0 || datos->partida == 0)
        {
            Salida::Mensaje(m_gestor, "Error", "No hay partida activa.");
            break;
        }
        // No se toca nada de Partida, se continúa tal cual
        m_gestor.ocultar("jugador");
        m_gestor.mostrar("explorar");


        break;
    }
}

// ---------------------------------------------------------------------------
// manejarEvento
// Clicks en paneles SOLO actualizan m_jugadorSeleccionado (visual),
// nunca modifican Partida*.
// ---------------------------------------------------------------------------
void VentanaJug::manejarEvento(const sf::Event& evento)
{
    if (evento.type == sf::Event::MouseMoved)
    {
        // Hover en botonera
        for (int i = 0; i < CANT_BOTONES_JUG; i++)
        {
            if (!botonera.obtPosicion(i).contains(
                        static_cast<float>(evento.mouseMove.x),
                        static_cast<float>(evento.mouseMove.y)))
            {
                botonera.igualarBotones(COLOR_FONDO_JUG, COLOR_LETRA_JUG);
                break;
            }
        }
        for (int i = 0; i < CANT_BOTONES_JUG; i++)
        {
            if (botonera.obtPosicion(i).contains(
                        static_cast<float>(evento.mouseMove.x),
                        static_cast<float>(evento.mouseMove.y)))
            {
                botonera.resaltarBoton(i, COLOR_FONDO_RES_JUG, COLOR_LETRA_RES_JUG);
                break;
            }
        }

        // Hover en paneles de jugadores
        if (panelJug1.obtenerLimites().contains(
                    static_cast<float>(evento.mouseMove.x),
                    static_cast<float>(evento.mouseMove.y)))
        {
            nombreJug1.setColor(CLR_RECUA_PA_JUG_RES);
            panelJug1.setColContorno(CLR_RECUA_PA_JUG_RES);
        }
        else
        {
            // Solo restaurar si no es el seleccionado
            if (m_jugadorSeleccionado != 1)
            {
                nombreJug1.setColor(CLR_RECUA_PA_JUG);
                panelJug1.setColContorno(CLR_RECUA_PA_JUG);
            }
        }

        if (panelJug2.obtenerLimites().contains(
                    static_cast<float>(evento.mouseMove.x),
                    static_cast<float>(evento.mouseMove.y)))
        {
            nombreJug2.setColor(CLR_RECUA_PA_JUG_RES);
            panelJug2.setColContorno(CLR_RECUA_PA_JUG_RES);
        }
        else
        {
            if (m_jugadorSeleccionado != 2)
            {
                nombreJug2.setColor(CLR_RECUA_PA_JUG);
                panelJug2.setColContorno(CLR_RECUA_PA_JUG);
            }
        }
    }

    if (evento.type == sf::Event::MouseButtonPressed &&
            evento.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(m_gestor.obtenerVentana());

        // Botonera
        for (int i = 0; i < CANT_BOTONES_JUG; i++)
        {
            if (botonera.obtPosicion(i).contains(
                        static_cast<float>(mousePos.x),
                        static_cast<float>(mousePos.y)))
            {
                ejecutarAccion(i);
                return;
            }
        }

        // Panel jugador 1 → solo actualiza selección visual
        if (panelJug1.obtenerLimites().contains(
                    static_cast<float>(mousePos.x),
                    static_cast<float>(mousePos.y)))
        {
            m_jugadorSeleccionado = 1;
            jugadElegido.setString("Seleccionado: " + NOMBRES[0]);
            Centrado::centrar(jugadElegido, m_gestor.obtenerVentana(), 100.f);
            actualizarSeleccionVisual();
            std::cout << "Jugador seleccionado: 1 (visual, sin cambiar partida)\n";
        }

        // Panel jugador 2 → solo actualiza selección visual
        if (panelJug2.obtenerLimites().contains(
                    static_cast<float>(mousePos.x),
                    static_cast<float>(mousePos.y)))
        {
            m_jugadorSeleccionado = 2;
            jugadElegido.setString("Seleccionado: " + NOMBRES[1]);
            Centrado::centrar(jugadElegido, m_gestor.obtenerVentana(), 100.f);
            actualizarSeleccionVisual();
            std::cout << "Jugador seleccionado: 2 (visual, sin cambiar partida)\n";
        }
    }
}
