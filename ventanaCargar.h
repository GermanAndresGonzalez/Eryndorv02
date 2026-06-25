#pragma once
#include "Pantalla.h"
#include "botonera.h"
#include "GestorPantallas.h"
#include "PanelTexto.h"
#include "ArchivoPartidas.h"
#include "partidas.h"
class VentanaCargar : public Pantalla
{
public:
    explicit VentanaCargar(GestorPantallas& gestor);
    ~VentanaCargar();

    void alMostrar()  override;
    void alOcultar()  override;
    void actualizar(float dt) override;
    void dibujar(sf::RenderWindow& ventana) override;
    void manejarEvento(const sf::Event& evento) override;
    void obtenerDatos();

    // Devuelve la partida seleccionada (válida solo si haySeleccion() == true)
    const Partidas& getPartidaSeleccionada() const { return m_partidaSeleccionada; }
    bool            haySeleccion()           const { return m_indiceSeleccionado >= 0; }

private:
    // ── Recursos ──────────────────────────────────────────────────────────────
    void cargarRec();
    void cargarPartidas();

    // ── Dibujo interno ────────────────────────────────────────────────────────
    void dibujarPanelIzq  (sf::RenderWindow& ventana);
    void dibujarPanelCentral(sf::RenderWindow& ventana);
    void actualizarDetalle();

    // ── Acciones ──────────────────────────────────────────────────────────────
    void ejecutarAccion(int i);

    // ── Helpers ───────────────────────────────────────────────────────────────
    int  filaEnPosicion(float mouseX, float mouseY) const;

    // ── Datos ─────────────────────────────────────────────────────────────────
    GestorPantallas& m_gestor;

    sf::Font    m_fuente;
    sf::Font    fuenteBotonera;
    sf::Texture texturaFondo;
    sf::Sprite  spriteFondo;

    Panel    m_panelIzq;
    Panel    m_panelCentral;
    Botonera botonera;

    // Lista de hasta MAX_PARTIDAS_MOSTRAR partidas cargadas del archivo
    Partidas* m_partidas;
    int       m_cantPartidas;       // cantidad actualmente usada
    int m_indiceSeleccionado;   // -1 = ninguna
    int m_indiceHover;          // -1 = ninguna

    // Filas de la lista (un RectangleShape + Text por fila)
    struct FilaUI
    {
        sf::RectangleShape fondo;
        sf::Text           texto;
    };
    FilaUI* m_filas;
    int     m_cantFilas;

    // Texto de detalle en panel central
    sf::Text m_textoDetalleTitulo;
    sf::Text m_textoDetalleBody;

    // Partida copiada al confirmar selección
    Partidas m_partidaSeleccionada;
};
