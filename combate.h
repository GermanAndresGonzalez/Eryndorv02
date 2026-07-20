#pragma once

#include <string>

#include "datosPartida.h"
#include "Enemigos.h"
#include "inventario.h"
#include "ArchivoPartidas.h"
#include "plantillaEnemigos.h"
#include "plantillaHeroes.h"
#include "nombres.h"
#include "panelTxtImg.h"
#include "personaje.h"

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

    // Nuevos getters para el estado del arma y armadura
    int getVidaArma() const;
    int getVidaArmadura() const;
    int getVidaMaximaArma() const;
    int getVidaMaximaArmadura() const;
    std::string getNombreArma() const;
    std::string getNombreArmadura() const;
    bool tieneArma() const;
    bool tieneArmadura() const;

    // Vuelca el ultimo mensaje de accion del heroe/enemigo en los sf::Text
    // dados, posicionados debajo de la imagen del panel.
    void cargarPanel(PanelConImagen& panel,
                      sf::Text& txtAccionHeroe,
                      sf::Text& txtAccionEnemigo) const;

    // Se mantiene tal cual: id-1 para jugador (NOMBRES/rutaImaChicas son
    // 0-based con id 1/2), id directo para enemigo (nivel ya es 0-3).
    const char* devolverRuta(int id, int tipoJug) const;

    bool esCombateFinal() const;

private:
    void cargarEnemigo();
    void turnoEnemigo();
    void subirNivel();
    void actualizarPartida();
    int  indiceHeroe() const; // 0 = Kael, 1 = Lyra, segun Partida::id
    
    // Nuevos métodos para la gestión de equipamiento
    void inicializarPersonaje();
    void equiparArmaDelInventario();
    void equiparArmaduraDelInventario();
    void verificarYReemplazarArma();
    void verificarYReemplazarArmadura();
    int obtenerMejorItemPorTipo(TipoItem tipo) const;

    Partida*  m_partida = nullptr; // no es dueño
    Enemigos* m_enemigo = nullptr;
    Personaje* m_personaje = nullptr; // Nuevo: personaje del jugador

    Inventario m_inventario;
    ArchivoPartidas ArPartidas;

    bool m_combateFinalizado = false;
    bool m_victoria           = false;

    int m_turnosIniciales; // heredado de una version anterior; ya no se cuentan turnos

    std::string m_ultimaAccionHeroe;
    std::string m_ultimaAccionEnemigo;

    bool m_mensajeVictoriaPendiente = false;
    std::string m_mensajeVictoria;

    static const unsigned int NIVEL_MAXIMO = 3;
    bool m_eraJefe = false;
};