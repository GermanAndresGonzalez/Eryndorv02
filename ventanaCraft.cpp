#include "salida.h"
#include "centrar.h"
#include "VentanaCraft.h"
#include "botonera.h"
#include "PanelTexto.h"

#include "datosArchivos.h"
#include "datosFuentes.h"
#include "datosVenCraft.h"
#include "datosBotonCraf.h"

#include "ArchivoInventario.h"
#include "ArchivoPartidas.h"

#include <iostream>
#include <string>


VentanaCrafteo::VentanaCrafteo(GestorPantallas& gestor)
    : m_gestor(gestor)
    , m_craftear(gestor.obtenerPartida(), 10)
{
    nomcadCueva = "Mesa de Crafteo";
    Botonera botonera;
    cargarRec();
}

void VentanaCrafteo::alMostrar()
{
    Partida* datos = m_gestor.obtenerPartida();
    nomcadJug = datos->nombre;

    guardado = false;   // resetear flag de turno al entrar

    // ── Reset crítico: descarta inventario en memoria y carga el de
    //    la partida activa desde disco. Evita mostrar datos de otra partida.
    m_craftear.resetearInventario();

    nombreJug.setString(datos->nombre);
    Centrado::centrar(nombreJug, panelJug.obtenerLimites(), panelJug.getPosInternaY()+25.f);

    std::string textoTurnos = "Te quedan " + std::to_string(datos->turnoJugador) + " turnos para llenar tu mochila.";
    std::cout << "\n" << textoTurnos << std::endl;
    m_turnos.setString(textoTurnos);
    Centrado::centrar(m_turnos, m_gestor.obtenerVentana(), 120.f);

    m_craftear.cargarPanel(panelJug, txtPanelJug, txtPanelJug2);
    m_craftear.crafteoCueva(panelCueva, txtPanelCue);

    if (m_craftear.guardarPartida())
        std::cout << "Partida guardada\n";
    else
        std::cout << "No se guardó la partida\n";

    obtenerVisibles();
    actualizarNombreJug(datos->nombre);
}

void VentanaCrafteo::actualizarNombreJug(const std::string& nombre)
{
    nombreJug.setString(nombre);
    Centrado::centrar(nombreJug, panelJug.obtenerLimites(), panelJug.getPosInternaY()+10);
}

void VentanaCrafteo::alOcultar()
{
}

void VentanaCrafteo::actualizar(float dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        m_gestor.ocultar("principal");
        m_gestor.mostrar("intro");
    }
}

void VentanaCrafteo::dibujar(sf::RenderWindow& ventana)
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
    ventana.draw(txtPanelCueDos);
    ventana.draw(txtPanelJug);
    ventana.draw(txtPanelJug2);

    ventana.draw(botonera);

    //botonera.draw(ventana);
}

void VentanaCrafteo::cargarRec()
{
    if (m_fuente.loadFromFile(FUENTES))
        std::cerr << ERROR_FUENTE;
    m_texto.setFont(m_fuente);
    m_texto.setString(TEXTO_TIT_CR);
    m_texto.setCharacterSize(45);
    m_texto.setColor(CLR_RECUA_PA_CR);

    sf::FloatRect rect = m_texto.getLocalBounds();
    m_texto.setOrigin(rect.left + rect.width/2.0f, rect.top + rect.height/2.0f);
    m_texto.setPosition(sf::Vector2f(m_gestor.obtenerVentana().getSize().x / 2.0f, 50.f));

    m_turnos.setFont(m_fuente);
    m_turnos.setCharacterSize(35);
    m_turnos.setColor(CLR_RECUA_PA_RES_CR);
    Centrado::centrar(m_turnos, m_gestor.obtenerVentana(), 120.f);

    panelJug   = Panel(160.f, 200.f, 300.f, 400.f);
    panelCueva = Panel(490.f, 200.f, 300.f, 400.f);

    if (!texturaFondo.loadFromFile(RUTA_FONDO_CR))
        std::cerr << ERROR_FONDO_CR;
    if (!fuenteBotonera.loadFromFile(FUENTES))
        std::cerr << ERROR_FUENTE;

    spriteFondo.setTexture(texturaFondo);

    botonera.inicializar(CANT_BOTONES_CR, fuenteBotonera);
    botonera.seColoresBot(COLOR_FONDO_CR, COLOR_RECUA_CR);
    botonera.inicializarRectangulos(tamRectBotonX_CR, tamRectBotonY_CR);
    botonera.setTamCar(TAM_CARACTER_CR);
    botonera.setColorTexto(COLOR_LETRA_CR);
    botonera.inicializarEtiquetas(ETI_BOTONES_CR, CANT_BOTONES_CR);
    botonera.inicializarBotones(posBotonX_CR, posBotonY_CR);

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

    txtPanelCueDos.setFont(m_fuente);
    txtPanelCueDos.setString("");
    txtPanelCueDos.setCharacterSize(TAM_CAR_PARR_CR);
    txtPanelCueDos.setPosition(500.f, 400.f);
    txtPanelCueDos.setColor(CLR_RECUA_PA_RES_CR);





    txtPanelJug.setFont(m_fuente);
    txtPanelJug.setCharacterSize(TAM_CAR_PARR_CR);
    txtPanelJug.setColor(CLR_RECUA_PA_CR);
    txtPanelJug.setString("");

    txtPanelJug2.setFont(m_fuente);
    txtPanelJug2.setCharacterSize(TAM_CAR_PARR_CR);
    txtPanelJug2.setColor(CLR_RECUA_PA_CR);
    txtPanelJug2.setString("");
}

void VentanaCrafteo::ejecutarAccion(int i)
{

    std::cout << "Click\n";
    if (i <5)
    {
        inventarioJug=m_craftear.cargarInventario();
    }
    switch(i)
    {
    case 0:
        if (m_craftear.pocionCurativa(txtPanelCueDos))
        {
            obtenerVisibles();
            m_craftear.cargarPanel(panelJug, txtPanelJug, txtPanelJug2);
        }


        //return true;
        break;
    case 1:
        if (m_craftear.espadaMadera(txtPanelCueDos))
        {
            obtenerVisibles();
            m_craftear.cargarPanel(panelJug, txtPanelJug, txtPanelJug2);
        }


        break;
    case 2:
        if (m_craftear.espadaHierro(txtPanelCueDos))
        {
            obtenerVisibles();
            m_craftear.cargarPanel(panelJug, txtPanelJug, txtPanelJug2);
        }

        /*
        std::cout << "Boton 3" << std::endl;
        m_craftear.cargarPanel(panelJug, txtPanelJug, txtPanelJug2);
        //return true;
        */
        break;
    case 3:
        if (m_craftear.escudoMadera(txtPanelCueDos))
        {
            obtenerVisibles();
            m_craftear.cargarPanel(panelJug, txtPanelJug, txtPanelJug2);
        }
        /*
        std::cout << "Boton 4" << std::endl;
        m_craftear.cargarPanel(panelJug, txtPanelJug, txtPanelJug2);
        //return true;
        */
        break;
    case 4:
        if (m_craftear.escudoHierro(txtPanelCueDos))
        {
            obtenerVisibles();
            m_craftear.cargarPanel(panelJug, txtPanelJug, txtPanelJug2);
        }
        /*
        std::cout << "Boton 5" << std::endl;
        m_craftear.cargarPanel(panelJug, txtPanelJug, txtPanelJug2);
        //return true;
        */
        break;
    case 5:
        std::cout << "Boton 6" << std::endl;
        m_craftear.modificarPartida();
        m_gestor.ocultar("craftear");
        m_gestor.mostrar("explorar");
        break;
    }
}

void VentanaCrafteo::v_explorar()
{
    m_craftear.crafteoCueva(panelCueva, txtPanelCue);
    guardado = false;
    v_actualizar();
}

void VentanaCrafteo::v_agregar()
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

void VentanaCrafteo::v_actualizar()
{
    m_craftear.cargarPanel(panelJug, txtPanelJug, txtPanelJug2);
    Partida* datos = m_gestor.obtenerPartida();
    std::string textoTurnos = "Te quedan " + std::to_string(datos->turnoJugador) + " turnos para llenar tu mochila.";
    m_turnos.setString(textoTurnos);
    Centrado::centrar(m_turnos, m_gestor.obtenerVentana(), 120.f);
}

void VentanaCrafteo::manejarEvento(const sf::Event& evento)
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
            if (!botonera.obtPosicion(i).contains(
                        static_cast<float>(evento.mouseMove.x),
                        static_cast<float>(evento.mouseMove.y)))
            {
                botonera.igualarBotones(COLOR_FONDO_CR, COLOR_LETRA_CR);
                break;
            }
        }
        for (int i = 0; i < CANT_BOTONES_CR; i++)
        {
            if (botonera.obtPosicion(i).contains(
                        static_cast<float>(evento.mouseMove.x),
                        static_cast<float>(evento.mouseMove.y)))
            {
                botonera.resaltarBoton(i, COLOR_FONDO_RES_CR, COLOR_LETRA_RES_CR);
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


void VentanaCrafteo::obtenerVisibles()
{

    for (int i=0; i<CANT_BOTONES_CR; i++)
    {
        botonera.setActivo(i,true);
    }

    ArchivoInventario arcInv(RUTA_DAT_INVN);
    Inventario inventarioJug;
    Partida* datos = m_gestor.obtenerPartida();
    if(arcInv.buscarPorID(datos->partida,inventarioJug))
    {

        if(!Crafteo::puedoCrearPocionCurativa(inventarioJug))
        {
            botonera.setActivo(0,false);
        }

        if(!Crafteo::puedoCrearEspadaMadera(inventarioJug))
        {
            botonera.setActivo(1,false);
        }

        if(!Crafteo::puedoCrearEspadaHierro(inventarioJug))
        {
            botonera.setActivo(2,false);
        }

        if(!Crafteo::puedoCrearEscudoMadera(inventarioJug))
        {
            botonera.setActivo(3,false);
        }

        if(!Crafteo::puedoCrearEscudoHierro(inventarioJug))
        {
            botonera.setActivo(4,false);
        }

    }
}
