#include "salida.h"
#include "centrar.h"
#include "VentanaEquipar.h"
#include "botonera.h"
#include "PanelTexto.h"
#include "ventanaConfirmacion.h"

#include "datosFuentes.h"
#include "datosVenAr.h"
#include "datosBotonArmar.h"

#include "items_juego.h"

#include <iostream>
#include <string>


namespace
{
// Botones 0-3 de la botonera -> id de item que equipan (ver datosBotonArmar.cpp,
// tienen que ir en el mismo orden que ETI_BOTONES_ARMAR).
const int ITEMS_BOTON_ARMAR[4] = { ESPADA_MADERA, ESPADA_HIERRO, ESCUDO_MADERA, ESCUDO_HIERRO };
}


VentanaEquipar::VentanaEquipar(GestorPantallas& gestor)
    : m_gestor(gestor)
    , m_equipar(gestor.obtenerPartida(), 0)   // el 2do parámetro (turnos) no se usa en esta pantalla
{
    cargarRec();
}

void VentanaEquipar::alMostrar()
{
    Partida* datos = m_gestor.obtenerPartida();
    nomcadJug = datos->nombre;

    // Reset crítico: descarta cualquier inventario en memoria y carga el de
    // la partida activa desde disco. Evita mostrar datos de otra partida.
    m_equipar.resetearInventario();

    nombreJug.setString(datos->nombre);
    Centrado::centrar(nombreJug, panelJug.obtenerLimites(), panelJug.getPosInternaY()+25.f);

    refrescarPanel();

    // guardarPartida() solo crea el registro si todavía no existe.
    // Si ya existía, hay que sincronizarlo igual con el estado actual
    // del puntero Partida (por si venimos de otra pantalla con cambios).
    if (m_equipar.guardarPartida())
        std::cout << "Partida creada\n";
    else
        guardarCambios();

    for (int i = 0; i < CANT_BOTONES_ARMAR; i++)
        botonera.setActivo(i, true);

    actualizarNombreJug(datos->nombre);
}

void VentanaEquipar::refrescarPanel()
{
    m_equipar.cargarPanel(panelJug, txtPanelJug, txtPanelJug2);
}

void VentanaEquipar::guardarCambios()
{
    // Persiste el registro de la partida (idArma/idArmadura/vidaArma/vidaArmadura, etc.)
    // con el estado actual del puntero Partida. El inventario ya se guarda aparte
    // dentro de Equipar::confirmarEquipar, pero lo dejamos explícito acá también
    // para que quede centralizado y no dependa de la implementación interna.
    if (!m_equipar.modificarPartida())
        std::cout << "No se pudo guardar la partida (el registro no existe)\n";
    else
        std::cout << "Partida guardada\n";
}

void VentanaEquipar::actualizarNombreJug(const std::string& nombre)
{
    nombreJug.setString(nombre);
    Centrado::centrar(nombreJug, panelJug.obtenerLimites(), panelJug.getPosInternaY()+10);
}

void VentanaEquipar::alOcultar()
{
}

void VentanaEquipar::actualizar(float dt)
{
}

void VentanaEquipar::dibujar(sf::RenderWindow& ventana)
{
    ventana.draw(spriteFondo);
    ventana.draw(m_texto);

    ventana.draw(panelJug);

    ventana.draw(nombreJug);
    ventana.draw(txtPanelJug);
    ventana.draw(txtPanelJug2);

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

    panelJug = Panel(210.f, 200.f, 450.f, 400.f);

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

    txtPanelJug.setFont(m_fuente);
    txtPanelJug.setCharacterSize(TAM_CAR_PARR_ARMAR);
    txtPanelJug.setColor(CLR_RECUA_PA_ARMAR);
    txtPanelJug.setString("");

    txtPanelJug2.setFont(m_fuente);
    txtPanelJug2.setCharacterSize(TAM_CAR_PARR_ARMAR);
    txtPanelJug2.setColor(CLR_RECUA_PA_ARMAR);
    txtPanelJug2.setString("");
}

void VentanaEquipar::ejecutarAccion(int i)
{
    std::cout << "Click\n";
    switch (i)
    {
    case 0:
    case 1:
    case 2:
    case 3:
        intentarEquipar(ITEMS_BOTON_ARMAR[i]);
        break;

    case 4:
        // Avanzar al siguiente paso del flujo.
        // TODO: reemplazar "explorar" por el nombre real de la pantalla siguiente.

        m_gestor.ocultar("equipar");
        m_gestor.mostrar("combatir");
        break;

    case 5:
        // Volver, con confirmación (mismo patrón que el resto de las pantallas).
        m_gestor.ocultar("equipar");
        // TODO: reemplazar "jugador" por el nombre real de la pantalla anterior.
        m_gestor.mostrar("explorar");

        break;
    }
}

void VentanaEquipar::intentarEquipar(int idItem)
{
    InfoEquipar info = m_equipar.consultarEquipar(idItem);
    std::string nombreNuevo = obtenerItemPorId(idItem).getNombre();

    switch (info.resultado)
    {
    case ResultadoEquipar::SinItemEnInventario:
        Salida::Mensaje(m_gestor, "", "No tenés " + nombreNuevo + " en el inventario.");
        break;

    case ResultadoEquipar::YaEquipadoMaximo:
        Salida::Mensaje(m_gestor, "", "Ya tenés " + nombreNuevo + " equipado con la vida máxima.");
        break;

    case ResultadoEquipar::Equipado:
        if (m_equipar.confirmarEquipar(idItem))
        {
            refrescarPanel();
            guardarCambios();
            std::cout << "Equipado: " << nombreNuevo << "\n";
        }
        break;

    case ResultadoEquipar::RequiereConfirmacion:
    {
        std::string nombreActual = obtenerItemPorId(info.idActual).getNombre();
        std::string mensaje =
            "Tenés equipado " + nombreActual + " (" +
            std::to_string(info.vidaActual) + "/" + std::to_string(info.vidaMaximaActual) +
            " de vida).\n¿Querés cambiarlo por " + nombreNuevo + "?";

        VentanaConfirmacion dialogo("", mensaje);
        if (dialogo.mostrar(m_gestor.obtenerVentana()))
        {
            if (m_equipar.confirmarEquipar(idItem))
            {
                refrescarPanel();
                guardarCambios();
                std::cout << "Equipado: " << nombreNuevo << "\n";
            }
        }
        break;
    }
    }
}

void VentanaEquipar::manejarEvento(const sf::Event& evento)
{
    if (evento.type == sf::Event::Closed)
    {
        if (Salida::Volver(m_gestor))
        {
            m_gestor.ocultar("equipar");
            m_gestor.mostrar("jugador");
        }
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
