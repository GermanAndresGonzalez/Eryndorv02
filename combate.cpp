#include "Combate.h"
#include "datosArchivos.h"

#include "ArchivoInventario.h"

#include <iostream>

namespace
{
const char* ARCHIVO_INVENTARIOS = RUTA_DAT_INVN;

// Curacion fija de la pocion. Ajustar segun balance del juego.
const int CURACION_POCION = 25;
} // namespace

Combatir::Combatir(Partida* partida, int turnos)
    : m_partida(partida)
    , m_turnosIniciales(turnos)
    , ArPartidas(RUTA_DAT_PART)
{
    if (m_partida)
    {
        resetearInventario();
        cargarEnemigo();

        // Nueva partida: la vida del heroe todavia no fue inicializada.
        if (m_partida->vidaActual == 0)
        {
            m_partida->vidaActual =
                static_cast<unsigned int>(plantillasHeroes[indiceHeroe()].vidaMaxima);
        }
    }
}

bool Combatir::esCombateFinal() const
{
    return m_partida && m_partida->nivel == NIVEL_MAXIMO;
}

void Combatir::subirNivel()
{
    if (!m_partida) return;

    if (m_partida->nivel < NIVEL_MAXIMO)
    {
        m_partida->nivel++;
        m_partida->turnoJugador=10;
        actualizarPartida();
    }
    // si ya estaba en NIVEL_MAXIMO (se ganó al Jefe), no sube mas:
    // no hay mas enemigos en esta version acotada.
}

Combatir::~Combatir()
{
    delete m_enemigo;
}

int Combatir::indiceHeroe() const
{
    return (m_partida && m_partida->id == 2) ? 1 : 0;
}

void Combatir::iniciarCombate()
{
    if (!m_partida)
    {
        return;
    }

    resetearInventario();
    cargarEnemigo(); // el enemigo siempre arranca a vida completa

    m_combateFinalizado = false;
    m_victoria           = false;
    m_ultimaAccionHeroe.clear();
    m_ultimaAccionEnemigo.clear();
}
void Combatir::actualizarPartida()
{
    if (!m_partida) return;

    int posicion = ArPartidas.buscarPosicionPorID(m_partida->partida);
    if (posicion >= 0)
    {
        Partidas registro(m_partida->partida, m_partida->id, m_partida->nivel);
        ArPartidas.modificar(posicion, registro);
    }
}

void Combatir::resetearInventario()
{
    if (!m_partida)
    {
        return;
    }

    ArchivoInventario archivo(ARCHIVO_INVENTARIOS);
    Inventario cargado;

    if (archivo.buscarPorID(m_partida->partida, cargado))
    {
        m_inventario = cargado;
    }
    else
    {
        std::cerr << "Combatir: no se encontro inventario para la partida "
                  << m_partida->partida << "\n";
        m_inventario    = Inventario();
        m_inventario.id = m_partida->partida;
    }
}

bool Combatir::guardarPartida()
{
    ArchivoInventario archivo(ARCHIVO_INVENTARIOS);

    int posicion = archivo.buscarPosicionPorID(m_inventario.id);
    if (posicion >= 0)
    {
        return archivo.modificar(posicion, m_inventario);
    }

    return archivo.agregar(m_inventario);
}

void Combatir::cargarEnemigo()
{
    if (!m_partida)
    {
        return;
    }

    unsigned int nivel = m_partida->nivel;
    if (nivel > 3)
    {
        nivel = 0; // seguridad ante datos corruptos
    }

    const PlantillaEnemigo& plantilla = plantillasEnemigos[nivel];

    Enemigos* nuevo = new Enemigos(
        plantilla.vidaMaxima,
        plantilla.vidaMaxima,
        plantilla.defensa,
        plantilla.ataque,
        static_cast<int>(nivel) + 1,
        plantilla.oroOtorgado,
        plantilla.expOtorgada,
        plantilla.nombre,
        plantilla.descripcion);

    delete m_enemigo;
    m_enemigo = nuevo;
}

void Combatir::atacar()
{
    if (!m_enemigo || !m_partida || m_combateFinalizado)
    {
        return;
    }

    const PlantillaHeroe& datosHeroe = plantillasHeroes[indiceHeroe()];

    int danio = datosHeroe.ataque;
    m_enemigo->recibirDanio(danio); // Enemigos::recibirDanio ya resta su defensa

    m_ultimaAccionHeroe = std::string(m_partida->nombre) + " ataca por " +
                          std::to_string(danio) + " de danio.";

    if (m_enemigo->estaEliminado())
    {
        m_combateFinalizado = true;
        m_victoria           = true;
        m_ultimaAccionEnemigo = std::string(m_enemigo->getNombre()) + " ha sido derrotado.";

        const bool eraJefe = esCombateFinal();   // chequear ANTES de subirNivel()

        const int idOro = m_inventario.obtenerID("ORO");
        if (idOro >= 0)
            m_inventario.agregarItem(idOro, m_enemigo->getOroOtorgado());

        guardarPartida();
        subirNivel();

        m_mensajeVictoriaPendiente = true;
        if (eraJefe)
        {
            m_mensajeVictoria =
                "!Has derrotado al Jefe " + std::string(m_enemigo->getNombre()) + "! " +
                "Ganaste " + std::to_string(m_enemigo->getOroOtorgado()) + " de oro. !Felicitaciones!";
        }
        else
        {
            m_mensajeVictoria =
                "!Has vencido a " + std::string(m_enemigo->getNombre()) + "! " +
                "Ganaste " + std::to_string(m_enemigo->getOroOtorgado()) + " de oro.";
        }

        return;
    }

    turnoEnemigo();
}

void Combatir::curar()
{
    if (!m_enemigo || !m_partida || m_combateFinalizado)
    {
        return;
    }

    const int idCura = m_inventario.obtenerID("POCION CURATIVA");
    if (idCura < 0 || !m_inventario.tieneCantidadNecesaria(idCura, 1))
    {
        m_ultimaAccionHeroe = "No hay pociones curativas disponibles.";
        return;
    }

    const int vidaMaxima = plantillasHeroes[indiceHeroe()].vidaMaxima;
    int vidaNueva = static_cast<int>(m_partida->vidaActual) + CURACION_POCION;
    if (vidaNueva > vidaMaxima)
    {
        vidaNueva = vidaMaxima;
    }

    if (static_cast<unsigned int>(vidaNueva) == m_partida->vidaActual)
    {
        m_ultimaAccionHeroe = std::string(m_partida->nombre) + " ya tiene la vida al maximo.";
        return;
    }

    m_partida->vidaActual = static_cast<unsigned int>(vidaNueva);
    m_inventario.quitarItem(idCura, 1);
    guardarPartida();

    m_ultimaAccionHeroe = std::string(m_partida->nombre) + " se cura " +
                          std::to_string(CURACION_POCION) + " puntos de vida.";

    turnoEnemigo();
}

void Combatir::turnoEnemigo()
{
    if (!m_enemigo || !m_partida || m_combateFinalizado)
    {
        return;
    }

    const PlantillaHeroe& datosHeroe = plantillasHeroes[indiceHeroe()];

    int danio = m_enemigo->atacar() - datosHeroe.defensa;
    if (danio < 0)
    {
        danio = 0;
    }

    int vidaRestante = static_cast<int>(m_partida->vidaActual) - danio;
    if (vidaRestante < 0)
    {
        vidaRestante = 0;
    }
    m_partida->vidaActual = static_cast<unsigned int>(vidaRestante);

    m_ultimaAccionEnemigo = std::string(m_enemigo->getNombre()) + " ataca por " +
                            std::to_string(danio) + " de danio.";

    if (m_partida->vidaActual == 0)
    {
        m_combateFinalizado = true;
        m_victoria           = false;
        m_ultimaAccionHeroe = std::string(m_partida->nombre) + " ha sido derrotado...";
    }
}

int Combatir::getVidaActualHeroe() const
{
    return m_partida ? static_cast<int>(m_partida->vidaActual) : 0;
}

int Combatir::getVidaMaximaHeroe() const
{
    return plantillasHeroes[indiceHeroe()].vidaMaxima;
}

int Combatir::getVidaActualEnemigo() const
{
    return m_enemigo ? m_enemigo->getVidaActual() : 0;
}

int Combatir::getVidaMaximaEnemigo() const
{
    return m_enemigo ? m_enemigo->getVidaMaxima() : 0;
}

const char* Combatir::getNombreHeroe() const
{
    return m_partida ? m_partida->nombre : "";
}

const char* Combatir::getNombreEnemigo() const
{
    return m_enemigo ? m_enemigo->getNombre() : "";
}

void Combatir::cargarPanel(PanelConImagen& panel,
                           sf::Text& txtAccionHeroe,
                           sf::Text& txtAccionEnemigo) const
{
    txtAccionHeroe.setString(m_ultimaAccionHeroe);
    txtAccionEnemigo.setString(m_ultimaAccionEnemigo);

    sf::Vector2f pos = panel.obtenerCoordenadasDebajoImagen();
    txtAccionHeroe.setPosition(pos.x, pos.y);
    txtAccionEnemigo.setPosition(pos.x, pos.y + txtAccionHeroe.getGlobalBounds().height + 10.f);
}

const char* Combatir::devolverRuta(int id, int tipoJug) const
{
    switch (tipoJug)
    {
    case 1:
        std::cerr << "Error combate.cpp: " << id << " " << NOMBRES[id] << "\n";
        return rutaImaChicas[id - 1];

    case 2:
        std::cerr << "Error combate.cpp: " << id << "\n";
        return plantillasEnemigos[id].imagen;

    default:
        return nullptr;
    }
}

bool Combatir::consumirMensajeVictoria(std::string& mensaje)
{
    if (!m_mensajeVictoriaPendiente)
    {
        return false;
    }

    mensaje = m_mensajeVictoria;
    m_mensajeVictoriaPendiente = false;
    return true;
}

