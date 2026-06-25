
#include "salida.h"
#include "centrar.h"
#include "ventanaExplor.h"
#include "botonera.h"
#include "PanelTexto.h"

#include "datosFuentes.h"
#include "datosVenEx.h"
#include "datosBotonExplor.h"

#include "ArchivoInventario.h"
#include "ArchivoPartidas.h"
#include "inventarioCueva.h"
#include "explorarCueva.h"

#include <iostream>
#include <string>

VentanaExplo::VentanaExplo(GestorPantallas& gestor)
    : m_gestor(gestor)
    , m_explorar(gestor.obtenerPartida(), 10)
{
    nomcadCueva = "Cueva";
    Botonera botonera;
    cargarRec();
}

void VentanaExplo::alMostrar()
{
    Partida* datos = m_gestor.obtenerPartida();
    nomcadJug = datos->nombre;
    //datos->turnoJugador = 10;
    guardado = false;   // resetear flag de turno al entrar

    // ── Reset crítico: descarta inventario en memoria y carga el de
    //    la partida activa desde disco. Evita mostrar datos de otra partida.
    m_explorar.resetearInventario();

    nombreJug.setString(datos->nombre);
    Centrado::centrar(nombreJug, panelJug.obtenerLimites(), panelJug.getPosInternaY()+25.f);

    std::string textoTurnos = "Te quedan " + std::to_string(datos->turnoJugador) + " turnos para llenar tu mochila.";
    std::cout << "\n" << textoTurnos << std::endl;
    m_turnos.setString(textoTurnos);
    Centrado::centrar(m_turnos, m_gestor.obtenerVentana(), 120.f);

    m_explorar.cargarPanel(panelJug, txtPanelJug, txtPanelJug2);
    m_explorar.explorarCueva(panelCueva, txtPanelCue);

    if (m_explorar.guardarPartida())
        std::cout << "Partida guardada\n";
    else
        std::cout << "No se guardó la partida\n";

    actualizarNombreJug(datos->nombre);
}

void VentanaExplo::actualizarNombreJug(const std::string& nombre)
{
    nombreJug.setString(nombre);
    Centrado::centrar(nombreJug, panelJug.obtenerLimites(), panelJug.getPosInternaY()+10);
}

void VentanaExplo::alOcultar()
{
}

void VentanaExplo::actualizar(float dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        m_gestor.ocultar("principal");
        m_gestor.mostrar("intro");
    }
}

void VentanaExplo::dibujar(sf::RenderWindow& ventana)
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

void VentanaExplo::cargarRec()
{
    if (m_fuente.loadFromFile(FUENTES))
        std::cerr << ERROR_FUENTE;
    m_texto.setFont(m_fuente);
    m_texto.setString(TEXTO_TIT);
    m_texto.setCharacterSize(45);
    m_texto.setColor(CLR_RECUA_PA_EX_RES);

    sf::FloatRect rect = m_texto.getLocalBounds();
    m_texto.setOrigin(rect.left + rect.width/2.0f, rect.top + rect.height/2.0f);
    m_texto.setPosition(sf::Vector2f(m_gestor.obtenerVentana().getSize().x / 2.0f, 50.f));

    m_turnos.setFont(m_fuente);
    m_turnos.setCharacterSize(35);
    m_turnos.setColor(CLR_RECUA_PA_EX_RES);
    Centrado::centrar(m_turnos, m_gestor.obtenerVentana(), 120.f);

    panelJug   = Panel(160.f, 200.f, 300.f, 400.f);
    panelCueva = Panel(490.f, 200.f, 300.f, 400.f);

    if (!texturaFondo.loadFromFile(RUTA_FONDO_EX))
        std::cerr << ERROR_FONDO_EX;
    if (!fuenteBotonera.loadFromFile(FUENTES))
        std::cerr << ERROR_FUENTE;

    spriteFondo.setTexture(texturaFondo);

    botonera.inicializar(CANT_BOTONES_EXP, fuenteBotonera);
    botonera.seColoresBot(COLOR_FONDO_EXP, COLOR_RECUA_EXP);
    botonera.inicializarRectangulos(tamRectBotonX_EXP, tamRectBotonY_EXP);
    botonera.setTamCar(TAM_CARACTER_EXP);
    botonera.setColorTexto(COLOR_LETRA_EXP);
    botonera.inicializarEtiquetas(ETI_BOTONES_EXP, CANT_BOTONES_EXP);
    botonera.inicializarBotones(posBotonX_EXP, posBotonY_EXP);

    nombreJug.setFont(m_fuente);
    nombreJug.setCharacterSize(TAM_CAR_PARR_EX);
    nombreJug.setColor(CLR_RECUA_PA_EX);

    nombreCue.setFont(m_fuente);
    nombreCue.setCharacterSize(TAM_CAR_PARR_EX);
    nombreCue.setString(nomcadCueva);
    Centrado::centrar(nombreCue, panelCueva.obtenerLimites(), panelCueva.getPosInternaY()+10.f);
    nombreCue.setColor(CLR_RECUA_PA_EX);

    txtPanelCue.setFont(m_fuente);
    txtPanelCue.setCharacterSize(TAM_CAR_PARR_EX);
    txtPanelCue.setColor(CLR_RECUA_PA_EX);
    txtPanelCue.setString(nomcadCueva);

    txtPanelJug.setFont(m_fuente);
    txtPanelJug.setCharacterSize(TAM_CAR_PARR_EX);
    txtPanelJug.setColor(CLR_RECUA_PA_EX);
    txtPanelJug.setString("");

    txtPanelJug2.setFont(m_fuente);
    txtPanelJug2.setCharacterSize(TAM_CAR_PARR_EX);
    txtPanelJug2.setColor(CLR_RECUA_PA_EX);
    txtPanelJug2.setString("");
}

void VentanaExplo::ejecutarAccion(int i)
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
        /*
        m_gestor.ocultar("explorar");
        m_gestor.mostrar("explorar");
        */
        break;
    case 4:
        m_explorar.modificarPartida();
        m_gestor.ocultar("explorar");
        m_gestor.mostrar("jugador");
        break;
    }
}

void VentanaExplo::v_explorar()
{
    m_explorar.explorarCueva(panelCueva, txtPanelCue);
    guardado = false;
    v_actualizar();
}

void VentanaExplo::v_agregar()
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

void VentanaExplo::v_actualizar()
{
    for (int i=0;i<4;i++)
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
        for (int i=0;i<2;i++)
        {
            botonera.setActivo(i,false);
        }
        //std::cout << "Turnos: 0\n";
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

    if (evento.type == sf::Event::MouseMoved)
    {
        for (int i = 0; i < CANT_BOTONES_EXP; i++)
        {
            if (!botonera.obtPosicion(i).contains(
                    static_cast<float>(evento.mouseMove.x),
                    static_cast<float>(evento.mouseMove.y)))
            {
                botonera.igualarBotones(COLOR_FONDO_EXP, COLOR_LETRA_EXP);
                break;
            }
        }
        for (int i = 0; i < CANT_BOTONES_EXP; i++)
        {
            if (botonera.obtPosicion(i).contains(
                    static_cast<float>(evento.mouseMove.x),
                    static_cast<float>(evento.mouseMove.y)))
            {
                botonera.resaltarBoton(i, COLOR_FONDO_RES_EXP, COLOR_LETRA_RES_EXP);
                break;
            }
        }
    }

    if (evento.type == sf::Event::MouseButtonPressed &&
        evento.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(m_gestor.obtenerVentana());
        for (int i = 0; i < CANT_BOTONES_EXP; i++)
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
