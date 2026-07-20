#include "salida.h"
#include "centrar.h"
#include "VentanaCombat.h"
#include "botonera.h"
#include "panelTxtImg.h"
#include "ventanaConfirmacion.h"
#include "datosFuentes.h"
#include "datosVenCombat.h"
#include "datosBotonCombat.h"
#include "plantillaEnemigos.h"
#include "datosVenCombate.h"

#include <iostream>
#include <string>

VentanaCombat::VentanaCombat(GestorPantallas& gestor)
    : m_gestor(gestor)
    , m_combate(gestor.obtenerPartida(), 10)
{
    Partida* datos = m_gestor.obtenerPartida();
    idJugador = datos->id;
    idEnemigo = datos->nivel;
    nomcadEnemigo = plantillasEnemigos[idEnemigo].nombre;
    Botonera botonera;
}

void VentanaCombat::alMostrar()
{
    Partida* datos = m_gestor.obtenerPartida();
    nomcadJug = datos->nombre;
    idJugador = datos->id;
    idEnemigo = datos->nivel;
    nomcadEnemigo = plantillasEnemigos[idEnemigo].nombre;

    std::cout << "\nID de jugador (al mostrar)" << idJugador << std::endl;

    // Recarga inventario, genera enemigo a vida completa y limpia el estado
    // del combate anterior.
    m_combate.iniciarCombate();

    nombreJug.setString(datos->nombre);
    Centrado::centrar(nombreJug, panelJug.obtenerLimites(), panelJug.getPosInternaY() + 25.f);
    cargarRec();

    m_turnos.setString("");
    Centrado::centrar(m_turnos, m_gestor.obtenerVentana(), 120.f);

    for (int i = 0; i < CANT_BOTONES_COM; i++)
    {
        botonera.setActivo(i, true);
    }

    actualizarEstado();

    if (m_combate.guardarPartida())
        std::cout << "Partida guardada\n";
    else
        std::cout << "No se guardo la partida\n";

    actualizarNombreJug(datos->nombre);
}

void VentanaCombat::actualizarNombreJug(const std::string& nombre)
{
    nombreJug.setString(nombre);
    Centrado::centrar(nombreJug, panelJug.obtenerLimites(), panelJug.getPosInternaY() + 10);
}

void VentanaCombat::alOcultar()
{
    //Por si
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
    ventana.draw(panelJug);
    ventana.draw(panelEne);

    ventana.draw(nombreJug);
    ventana.draw(nombreEne);
    ventana.draw(vidaJug);
    ventana.draw(vidaEne);
    ventana.draw(txtPanelCue);
    ventana.draw(txtPanelJug);
    ventana.draw(txtPanelJug2);
    ventana.draw(botonera);
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
    m_texto.setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
    m_texto.setPosition(sf::Vector2f(m_gestor.obtenerVentana().getSize().x / 2.0f, 50.f));

    m_turnos.setFont(m_fuente);
    m_turnos.setCharacterSize(35);
    m_turnos.setColor(CLR_RECUA_PA_COM_RES);
    Centrado::centrar(m_turnos, m_gestor.obtenerVentana(), 120.f);

    panelJug = PanelConImagen(posPanJugX, posPanJugY, anchoPaneles, alturaPanelesY,
                               m_combate.devolverRuta(idJugador, 1), 35.0f);

    panelEne = PanelConImagen(posPanEneX, posPanEneY, anchoPaneles, alturaPanelesY,
                               m_combate.devolverRuta(idEnemigo, 2), 35.0f);

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

    nombreEne.setFont(m_fuente);
    nombreEne.setCharacterSize(TAM_CAR_PARR_COM);
    nombreEne.setString(nomcadEnemigo);
    Centrado::centrar(nombreEne, panelEne.obtenerLimites(), panelEne.getPosInternaY() + 10.f);
    nombreEne.setColor(CLR_RECUA_PA_COM);

    vidaJug.setFont(m_fuente);
    vidaJug.setCharacterSize(TAM_CAR_PARR_COM);
    vidaJug.setColor(CLR_RECUA_PA_COM);

    vidaEne.setFont(m_fuente);
    vidaEne.setCharacterSize(TAM_CAR_PARR_COM);
    vidaEne.setColor(CLR_RECUA_PA_COM);

    txtPanelCue.setFont(m_fuente);
    txtPanelCue.setCharacterSize(TAM_CAR_PARR_COM);
    txtPanelCue.setColor(CLR_RECUA_PA_COM);
    txtPanelCue.setString("");

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
    case 0: // Atacar
        std::cout << "Atacar\n";
        m_combate.atacar();
        actualizarEstado();

        if (m_combate.combateFinalizado() && m_combate.esVictoria())
        {
            VentanaConfirmacion conf("Combate exitoso", MENSAJE_COMBATE_EXITOSO);
            if (!conf.mostrar(m_gestor.obtenerVentana()))
                break;
            m_gestor.ocultar("combatir");
            m_gestor.mostrar("explorar");
        }
        break;

    case 1: // Curar
        std::cout << "Curar\n";
        m_combate.curar();
        actualizarEstado();
        break;

    case 2: // Huir
        std::cout << "Huir\n";
        m_gestor.ocultar("combatir");
        m_gestor.mostrar("explorar");
        break;

    case 3: // Volver
        if (m_combate.guardarPartida())
        {
            std::cout << "Partida guardada: combate \n";
        }
        m_gestor.ocultar("combatir");
        m_gestor.mostrar("explorar");
        break;
    }
}

void VentanaCombat::actualizarEstado()
{
    m_combate.cargarPanel(panelJug, txtPanelJug, txtPanelJug2);
    actualizarVidas();

    std::string mensajeVictoria;
    if (m_combate.consumirMensajeVictoria(mensajeVictoria))
    {
        m_turnos.setString(mensajeVictoria);
        Centrado::centrar(m_turnos, m_gestor.obtenerVentana(), 120.f);
    }

    if (m_combate.combateFinalizado())
    {
        botonera.setActivo(0, false); // Atacar
        botonera.setActivo(1, false); // Curar
    }
}

void VentanaCombat::actualizarVidas()
{
    vidaJug.setString("Vida: " + std::to_string(m_combate.getVidaActualHeroe()) +
                       "/" + std::to_string(m_combate.getVidaMaximaHeroe()));
    vidaEne.setString("Vida: " + std::to_string(m_combate.getVidaActualEnemigo()) +
                       "/" + std::to_string(m_combate.getVidaMaximaEnemigo()));

    sf::FloatRect boundsImgJug = panelJug.getImagen().getGlobalBounds();
    vidaJug.setPosition(boundsImgJug.left - vidaJug.getGlobalBounds().width - 90.0f,
                         boundsImgJug.top);

    sf::FloatRect boundsImgEne = panelEne.getImagen().getGlobalBounds();
    vidaEne.setPosition(boundsImgEne.left - vidaEne.getGlobalBounds().width - 90.0f,
                         boundsImgEne.top);
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
