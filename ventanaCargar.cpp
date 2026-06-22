#include "VentanaCargar.h"
#include "datosVenCargar.h"
#include "datosBotonCargar.h"
#include "centrar.h"
#include <iostream>
#include <string>

// ─────────────────────────────────────────────────────────────────────────────
//  Constructor
// ─────────────────────────────────────────────────────────────────────────────
VentanaCargar::VentanaCargar(GestorPantallas& gestor)
    : m_gestor(gestor),
      m_panelIzq  (PANEL_IZQ_X, PANEL_IZQ_Y, PANEL_IZQ_W, PANEL_IZQ_H),
      m_panelCentral(PANEL_CTR_X, PANEL_CTR_Y, PANEL_CTR_W, PANEL_CTR_H),
      m_indiceSeleccionado(-1),
      m_indiceHover(-1)
{
    cargarRec();
    cargarPartidas();
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
            m_indiceSeleccionado < static_cast<int>(m_partidas.size()))
        {
            m_partidaSeleccionada = m_partidas[m_indiceSeleccionado];
            std::cout << "Partida seleccionada: ID="
                      << m_partidaSeleccionada.getId() << "\n";
            // TODO: agregar tu lógica aquí (cambiar pantalla, etc.)
        }
        break;

    case 1: // Volver
        m_gestor.ocultar("cargar");
        m_gestor.mostrar("principal");
        break;
    }
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
    botonera.inicializarBotones(posBotonX_CARGAR, posBotonY_CARGAR, true);

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
    m_partidas.clear();
    m_indiceSeleccionado = -1;
    m_indiceHover        = -1;
    m_filas.clear();

    ArchivoPartidas archivo(RUTA_PARTIDAS);
    int total = archivo.contarRegistros();

    // Recorremos de atrás hacia adelante para obtener las últimas 10 activas
    for (int pos = total - 1;
         pos >= 0 && static_cast<int>(m_partidas.size()) < MAX_PARTIDAS_MOSTRAR;
         pos--)
    {
        Partidas p;
        if (archivo.leer(pos, p) && !p.estaEliminada())
            m_partidas.push_back(p);
    }

    // Construir las FilaUI
    float filaX = PANEL_IZQ_X + FILA_PADDING_X;
    float filaW = PANEL_IZQ_W - FILA_PADDING_X * 2.f;

    for (int i = 0; i < static_cast<int>(m_partidas.size()); i++)
    {
        float filaY = PANEL_IZQ_Y + FILA_PADDING_Y + i * (FILA_ALTO + 4.f);

        FilaUI fui;

        fui.fondo.setSize(sf::Vector2f(filaW, FILA_ALTO));
        fui.fondo.setPosition(filaX, filaY);
        fui.fondo.setFillColor(COLOR_FILA_NORMAL);
        fui.fondo.setOutlineThickness(1.f);
        fui.fondo.setOutlineColor(sf::Color(255, 255, 255, 80));

        fui.texto.setFont(m_fuente);
        fui.texto.setCharacterSize(FILA_TAM_CAR);
        fui.texto.setFillColor(COLOR_FILA_TEXTO);
        fui.texto.setPosition(filaX + 10.f, filaY + FILA_PADDING_Y);

        // Etiqueta de la fila
        const Partidas& p = m_partidas[i];
        fui.texto.setString(
            "Partida #" + std::to_string(p.getId()) +
            "  |  Personaje: " + std::to_string(p.getIdPersonaje()) +
            "  |  Nivel: "     + std::to_string(p.getIdNivel()));

        m_filas.push_back(fui);
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

    if (m_partidas.empty())
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

    for (int i = 0; i < static_cast<int>(m_filas.size()); i++)
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
        m_indiceSeleccionado >= static_cast<int>(m_partidas.size()))
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
    for (int i = 0; i < static_cast<int>(m_filas.size()); i++)
    {
        if (m_filas[i].fondo.getGlobalBounds().contains(mouseX, mouseY))
            return i;
    }
    return -1;
}
