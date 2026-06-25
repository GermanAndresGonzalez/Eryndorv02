#include "VentanaCargar.h"
#include "datosVenCargar.h"
#include "datosBotonCargar.h"
#include "centrar.h"
#include "nombres.h"
#include <iostream>
#include <cstring>
#include <string>

// ─────────────────────────────────────────────────────────────────────────────
//  Constructor
// ─────────────────────────────────────────────────────────────────────────────
VentanaCargar::VentanaCargar(GestorPantallas& gestor)
    : m_gestor(gestor),
      m_panelIzq  (PANEL_IZQ_X, PANEL_IZQ_Y, PANEL_IZQ_W, PANEL_IZQ_H),
      m_panelCentral(PANEL_CTR_X, PANEL_CTR_Y, PANEL_CTR_W, PANEL_CTR_H),
      m_partidas(nullptr),
      m_cantPartidas(0),
      m_indiceSeleccionado(-1),
      m_indiceHover(-1),
      m_filas(nullptr),
      m_cantFilas(0)
{
    cargarRec();
    cargarPartidas();
}

// ─────────────────────────────────────────────────────────────────────────────
//  Destructor
// ─────────────────────────────────────────────────────────────────────────────
VentanaCargar::~VentanaCargar()
{
    delete[] m_partidas;
    delete[] m_filas;
}

// ─────────────────────────────────────────────────────────────────────────────
//  Pantalla overrides
// ─────────────────────────────────────────────────────────────────────────────
void VentanaCargar::alMostrar()
{

    std::cout << "VentanaCargar: ahora visible\n";
    // Recargar partidas cada vez que la pantalla se muestra,
    // por si se guardó una nueva partida en otra pantalla.
    cargarPartidas();
}

void VentanaCargar::alOcultar()
{
    std::cout << "VentanaCargar: ahora oculta\n";
}

void VentanaCargar::actualizar(float /*dt*/) {}

void VentanaCargar::dibujar(sf::RenderWindow& ventana)
{
    ventana.draw(spriteFondo);
    m_panelIzq    .dibujar(ventana);
    m_panelCentral.dibujar(ventana);
    dibujarPanelIzq    (ventana);
    dibujarPanelCentral(ventana);
    botonera.draw(ventana);
}

// ─────────────────────────────────────────────────────────────────────────────
//  Manejo de eventos
// ─────────────────────────────────────────────────────────────────────────────
void VentanaCargar::manejarEvento(const sf::Event& evento)
{
    // ── MouseMove: hover en lista y en botonera ───────────────────────────────
    if (evento.type == sf::Event::MouseMoved)
    {
        float mx = static_cast<float>(evento.mouseMove.x);
        float my = static_cast<float>(evento.mouseMove.y);

        // hover en filas de la lista
        m_indiceHover = filaEnPosicion(mx, my);

        // hover en botonera
        bool sobreBoton = false;
        for (int i = 0; i < CANT_BOTONES_CARGAR; i++)
        {
            if (botonera.obtPosicion(i).contains(mx, my))
            {
                botonera.igualarBotones(COLOR_FONDO_CARGAR, COLOR_LETRA_CARGAR);
                botonera.resaltarBoton(i, COLOR_FONDO_RES_CARGAR, COLOR_LETRA_RES_CARGAR);
                sobreBoton = true;
                break;
            }
        }
        if (!sobreBoton)
            botonera.igualarBotones(COLOR_FONDO_CARGAR, COLOR_LETRA_CARGAR);
    }

    // ── MouseButton: seleccionar fila o botón ────────────────────────────────
    if (evento.type == sf::Event::MouseButtonPressed &&
            evento.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(m_gestor.obtenerVentana());
        float mx = static_cast<float>(mousePos.x);
        float my = static_cast<float>(mousePos.y);

        // ¿Clickeó en una fila de la lista?
        int fila = filaEnPosicion(mx, my);
        if (fila >= 0)
        {
            m_indiceSeleccionado = fila;
            actualizarDetalle();
            return;
        }

        // ¿Clickeó en un botón?
        for (int i = 0; i < CANT_BOTONES_CARGAR; i++)
        {
            if (botonera.obtPosicion(i).contains(mx, my))
            {
                ejecutarAccion(i);
                return;
            }
        }
    }
}

// ─────────────────────────────────────────────────────────────────────────────
//  Acciones de la botonera
//  índice 0 → "Seleccionar"
//  índice 1 → "Volver"
// ─────────────────────────────────────────────────────────────────────────────
void VentanaCargar::ejecutarAccion(int i)
{
    switch (i)
    {
    case 0: // Seleccionar
        if (m_indiceSeleccionado >= 0 &&
                m_indiceSeleccionado < m_cantPartidas)
        {
            m_partidaSeleccionada = m_partidas[m_indiceSeleccionado];
            std::cout << "Partida seleccionada: ID="
                      << m_partidaSeleccionada.getId() << "\n";

            obtenerDatos();
            m_gestor.ocultar("cargar");
            m_gestor.mostrar("explorar");
        }
        break;

    case 1: // Borrar partida (borrado lógico)
        if (m_indiceSeleccionado >= 0 &&
                m_indiceSeleccionado < m_cantPartidas)
        {
            // 1. Obtener la partida seleccionada de la lista en memoria
            m_partidaSeleccionada = m_partidas[m_indiceSeleccionado];

            // 2. Hacer el borrado lógico en el archivo usando su ID
            ArchivoPartidas archivo(RUTA_PARTIDAS);
            bool ok = archivo.borradoLogico(m_partidaSeleccionada.getId());

            if (ok)
                std::cout << "Partida ID=" << m_partidaSeleccionada.getId() << " eliminada.\n";
            else
                std::cerr << "Error al eliminar la partida.\n";

            // 3. Recargar la lista (ya sin la partida borrada)
            m_textoDetalleTitulo.setString("Se borro la partida.");
            cargarPartidas();
        }
        break;
    case 2: // Volver
        m_gestor.ocultar("cargar");
        m_gestor.mostrar("principal");
        break;
    }
}

void VentanaCargar::obtenerDatos()
{
    Partida* datos = m_gestor.obtenerPartida();
    std::cout << "Primero:" << datos->partida << std::endl;
    datos->partida=m_partidaSeleccionada.getId();
    datos->nivel=m_partidaSeleccionada.getIdNivel();
    datos->id=m_partidaSeleccionada.getIdPersonaje();
    const std::string& nombre = NOMBRES[m_partidaSeleccionada.getIdPersonaje() - 1];
    std::strncpy(datos->nombre, nombre.c_str(), 49);
    std::cout << "Segundo:" << datos->partida << std::endl;
    std::cout << "Nombre: " << nombre;

}

// ─────────────────────────────────────────────────────────────────────────────
//  Carga de recursos
// ─────────────────────────────────────────────────────────────────────────────
void VentanaCargar::cargarRec()
{
    if (!texturaFondo.loadFromFile(RUTA_FONDO_CARGAR))
        std::cerr << ERROR_FONDO_CARGAR << "\n";
    spriteFondo.setTexture(texturaFondo);

    if (!fuenteBotonera.loadFromFile(FUENTE_CARGAR))
        std::cerr << ERROR_FUENTE_CARGAR << "\n";

    m_fuente = fuenteBotonera; // reutilizar la misma fuente

    // ── Botonera ─────────────────────────────────────────────────────────────
    botonera.inicializar(CANT_BOTONES_CARGAR, fuenteBotonera);
    botonera.seColoresBot(COLOR_FONDO_CARGAR, COLOR_RECUA_CARGAR);
    botonera.inicializarRectangulos(tamRectBotonX_CARGAR, tamRectBotonY_CARGAR);
    botonera.setTamCar(TAM_CARACTER_CARGAR);
    botonera.setColorTexto(COLOR_LETRA_CARGAR);
    botonera.inicializarEtiquetas(ETI_BOTONES_CARGAR, CANT_BOTONES_CARGAR);
    botonera.inicializarBotones(posBotonX_CARGAR, posBotonY_CARGAR);

    // ── Paneles ───────────────────────────────────────────────────────────────
    m_panelIzq    .setColor(sf::Color(0, 0, 0, 160));
    m_panelIzq    .setColContorno(sf::Color::White);
    m_panelIzq    .setGroContorno(1.5f);

    m_panelCentral.setColor(sf::Color(0, 0, 0, 160));
    m_panelCentral.setColContorno(sf::Color::White);
    m_panelCentral.setGroContorno(1.5f);

    // ── Texto de detalle ──────────────────────────────────────────────────────
    m_textoDetalleTitulo.setFont(m_fuente);
    m_textoDetalleTitulo.setCharacterSize(DETALLE_TAM_CAR_TIT);
    m_textoDetalleTitulo.setFillColor(COLOR_DETALLE_TEXTO);
    m_textoDetalleTitulo.setString("Selecciona una partida");
    m_textoDetalleTitulo.setPosition(
        PANEL_CTR_X + DETALLE_PADDING,
        PANEL_CTR_Y + DETALLE_PADDING);

    m_textoDetalleBody.setFont(m_fuente);
    m_textoDetalleBody.setCharacterSize(DETALLE_TAM_CAR);
    m_textoDetalleBody.setFillColor(COLOR_DETALLE_TEXTO);
    m_textoDetalleBody.setPosition(
        PANEL_CTR_X + DETALLE_PADDING,
        PANEL_CTR_Y + DETALLE_PADDING + 60.f);
}

// ─────────────────────────────────────────────────────────────────────────────
//  Carga de partidas desde el archivo (últimas MAX_PARTIDAS_MOSTRAR activas)
// ─────────────────────────────────────────────────────────────────────────────
void VentanaCargar::cargarPartidas()
{
    // Liberar arreglos anteriores
    delete[] m_partidas;
    delete[] m_filas;
    m_partidas     = nullptr;
    m_filas        = nullptr;
    m_cantPartidas = 0;
    m_cantFilas    = 0;
    m_indiceSeleccionado = -1;
    m_indiceHover        = -1;

    ArchivoPartidas archivo(RUTA_PARTIDAS);
    int total = archivo.contarRegistros();

    // Reservar el máximo posible
    Partidas* temp = new Partidas[MAX_PARTIDAS_MOSTRAR];
    int cuenta = 0;

    // Recorremos de atrás hacia adelante para obtener las últimas activas
    for (int pos = total - 1;
            pos >= 0 && cuenta < MAX_PARTIDAS_MOSTRAR;
            pos--)
    {
        Partidas p;
        if (archivo.leer(pos, p) && !p.estaEliminada())
            temp[cuenta++] = p;
    }

    // Copiar al arreglo definitivo del tamaño exacto
    m_cantPartidas = cuenta;
    if (m_cantPartidas > 0)
    {
        m_partidas = new Partidas[m_cantPartidas];
        for (int i = 0; i < m_cantPartidas; i++)
            m_partidas[i] = temp[i];
    }
    delete[] temp;

    // Construir las FilaUI
    m_cantFilas = m_cantPartidas;
    if (m_cantFilas > 0)
        m_filas = new FilaUI[m_cantFilas];

    float filaX = PANEL_IZQ_X + FILA_PADDING_X;
    float filaW = PANEL_IZQ_W - FILA_PADDING_X * 2.f;

    for (int i = 0; i < m_cantFilas; i++)
    {
        float filaY = PANEL_IZQ_Y + FILA_PADDING_Y + i * (FILA_ALTO + 4.f);

        m_filas[i].fondo.setSize(sf::Vector2f(filaW, FILA_ALTO));
        m_filas[i].fondo.setPosition(filaX, filaY);
        m_filas[i].fondo.setFillColor(COLOR_FILA_NORMAL);
        m_filas[i].fondo.setOutlineThickness(1.f);
        m_filas[i].fondo.setOutlineColor(sf::Color(255, 255, 255, 80));

        m_filas[i].texto.setFont(m_fuente);
        m_filas[i].texto.setCharacterSize(FILA_TAM_CAR);
        m_filas[i].texto.setFillColor(COLOR_FILA_TEXTO);
        m_filas[i].texto.setPosition(filaX + 10.f, filaY + FILA_PADDING_Y);

        const Partidas& p = m_partidas[i];
        m_filas[i].texto.setString(
            "Partida #" + std::to_string(p.getId()) +
            "  |  Personaje: " + std::to_string(p.getIdPersonaje()) +
            "  |  Nivel: "     + std::to_string(p.getIdNivel()));
    }

    // Limpiar texto de detalle
    m_textoDetalleTitulo.setString("Selecciona una partida");
    m_textoDetalleBody.setString("");
}

// ─────────────────────────────────────────────────────────────────────────────
//  Dibujo del panel izquierdo (lista)
// ─────────────────────────────────────────────────────────────────────────────
void VentanaCargar::dibujarPanelIzq(sf::RenderWindow& ventana)
{
    // Título del panel
    sf::Text titulo;
    titulo.setFont(m_fuente);
    titulo.setCharacterSize(35);
    titulo.setFillColor(sf::Color::White);
    titulo.setString("Partidas guardadas");
    Centrado::centrar(titulo,ventana,PANEL_IZQ_Y - 40.f);
    //titulo.setPosition(PANEL_IZQ_X + 12.f, PANEL_IZQ_Y - 25.f); //y=6.f
    ventana.draw(titulo);

    if (m_cantPartidas == 0)
    {
        sf::Text vacio;
        vacio.setFont(m_fuente);
        vacio.setCharacterSize(18);
        vacio.setFillColor(sf::Color(200, 200, 200));
        vacio.setString("No hay partidas guardadas.");
        vacio.setPosition(PANEL_IZQ_X + 20.f, PANEL_IZQ_Y + 60.f);
        ventana.draw(vacio);
        return;
    }

    for (int i = 0; i < m_cantFilas; i++)
    {
        FilaUI fui = m_filas[i]; // copia para modificar color sin alterar m_filas

        if (i == m_indiceSeleccionado)
            fui.fondo.setFillColor(COLOR_FILA_SEL);
        else if (i == m_indiceHover)
            fui.fondo.setFillColor(COLOR_FILA_HOVER);
        else
            fui.fondo.setFillColor(COLOR_FILA_NORMAL);

        ventana.draw(fui.fondo);
        ventana.draw(fui.texto);
    }
}

// ─────────────────────────────────────────────────────────────────────────────
//  Dibujo del panel central (detalle)
// ─────────────────────────────────────────────────────────────────────────────
void VentanaCargar::dibujarPanelCentral(sf::RenderWindow& ventana)
{
    ventana.draw(m_textoDetalleTitulo);
    ventana.draw(m_textoDetalleBody);
}

// ─────────────────────────────────────────────────────────────────────────────
//  Actualiza el texto del panel central según la fila seleccionada
// ─────────────────────────────────────────────────────────────────────────────
void VentanaCargar::actualizarDetalle()
{
    if (m_indiceSeleccionado < 0 ||
            m_indiceSeleccionado >= m_cantPartidas)
        return;

    const Partidas& p = m_partidas[m_indiceSeleccionado];

    m_textoDetalleTitulo.setString(
        "Partida #" + std::to_string(p.getId()));

    m_textoDetalleBody.setString(
        "ID de partida  : " + std::to_string(p.getId())          + "\n" +
        "ID de personaje: " + std::to_string(p.getIdPersonaje()) + "\n" +
        "ID de nivel    : " + std::to_string(p.getIdNivel())      + "\n" +
        "Estado         : " + (p.estaEliminada() ? "Eliminada" : "Activa"));
}

// ─────────────────────────────────────────────────────────────────────────────
//  Devuelve el índice de la fila bajo el cursor, o -1
// ─────────────────────────────────────────────────────────────────────────────
int VentanaCargar::filaEnPosicion(float mouseX, float mouseY) const
{
    for (int i = 0; i < m_cantFilas; i++)
    {
        if (m_filas[i].fondo.getGlobalBounds().contains(mouseX, mouseY))
            return i;
    }
    return -1;
}
