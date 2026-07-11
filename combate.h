#pragma once

#include <string>

#include "Partida.h"
#include "Enemigos.h"
#include "inventario.h"
#include "plantillaEnemigos.h"
#include "plantillaHeroes.h"
#include "nombres.h"
#include "panelTxtImg.h"

// ---------------------------------------------------------------------------
// Combatir
// Logica de un combate por turnos entre el heroe de la Partida activa y un
// Enemigos generado a partir de Partida::nivel. No es dueño de Partida*
// (lo administra GestorPantallas).
// ---------------------------------------------------------------------------
class Combatir
{
public:
    explicit Combatir(Partida* partida, int turnos = 10);
    ~Combatir();

    Combatir(const Combatir&)            = delete;
    Combatir& operator=(const Combatir&) = delete;

    // Se llama cada vez que se entra a la pantalla de combate: recarga
    // inventario desde disco, genera el enemigo a vida completa y limpia
    // el estado de la pelea anterior.
    void iniciarCombate();

    // Descarta el inventario en memoria y lo recarga desde disco
    // (Partida::partida es el ID de busqueda).
    void resetearInventario();

    // Persiste el inventario actual en disco.
    bool guardarPartida();

    // Acciones de la botonera
    void atacar();
    void curar();
    // Huir y Volver no requieren logica de combate: los maneja VentanaCombat
    // directamente cambiando de pantalla.

    // Estado
    bool combateFinalizado() const { return m_combateFinalizado; }
    bool esVictoria()        const { return m_victoria; }
    bool consumirMensajeVictoria(std::string& mensaje);

    int getVidaActualHeroe()   const;
    int getVidaMaximaHeroe()   const;
    int getVidaActualEnemigo() const;
    int getVidaMaximaEnemigo() const;

    const char* getNombreHeroe()   const;
    const char* getNombreEnemigo() const;

    // Vuelca el ultimo mensaje de accion del heroe/enemigo en los sf::Text
    // dados, posicionados debajo de la imagen del panel.
    void cargarPanel(PanelConImagen& panel,
                      sf::Text& txtAccionHeroe,
                      sf::Text& txtAccionEnemigo) const;

    // Se mantiene tal cual: id-1 para jugador (NOMBRES/rutaImaChicas son
    // 0-based con id 1/2), id directo para enemigo (nivel ya es 0-3).
    const char* devolverRuta(int id, int tipoJug) const;

private:
    void cargarEnemigo();
    void turnoEnemigo();
    int  indiceHeroe() const; // 0 = Kael, 1 = Lyra, segun Partida::id

    Partida*  m_partida = nullptr; // no es dueño
    Enemigos* m_enemigo = nullptr;

    Inventario m_inventario;

    bool m_combateFinalizado = false;
    bool m_victoria           = false;

    int m_turnosIniciales; // heredado de una version anterior; ya no se cuentan turnos

    std::string m_ultimaAccionHeroe;
    std::string m_ultimaAccionEnemigo;

    bool m_mensajeVictoriaPendiente = false;
    std::string m_mensajeVictoria;
};
