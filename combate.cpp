#include "combate.h"
#include "datosArchivos.h"
#include "archivoInventario.h"
#include "items_juego.h"
#include <iostream>

namespace
{

// Curacion fija de la pocion. Ajustar segun balance del juego.
const int CURACION_POCION = 25;
} // namespace

Combatir::Combatir(Partida* partida, int turnos)
    : m_partida(partida)
    , m_turnosIniciales(turnos)
    , ArPartidas(RUTA_DAT_PART)
    , m_personaje(nullptr)
{
    if (m_partida)
    {
        resetearInventario();
        cargarEnemigo();
        inicializarPersonaje();

        // Nueva partida: la vida del heroe todavia no fue inicializada.
        if (m_partida->vidaActual == 0)
        {
            const PlantillaHeroe& datosHeroe = plantillasHeroes[indiceHeroe()];
            m_partida->vidaActual = static_cast<unsigned int>(datosHeroe.vidaMaxima);
            m_partida->vidaMaxima = static_cast<unsigned int>(datosHeroe.vidaMaxima);
        }
    }
}

Combatir::~Combatir()
{
    delete m_enemigo;
    delete m_personaje;
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
        m_partida->turnoJugador += 10;
        actualizarPartida();
    }
}

int Combatir::indiceHeroe() const
{
    return (m_partida && m_partida->id == 2) ? 1 : 0;
}

void Combatir::inicializarPersonaje()
{
    if (!m_partida) return;

    delete m_personaje;

    const PlantillaHeroe& datosHeroe = plantillasHeroes[indiceHeroe()];

    // Crear personaje con los datos base
    m_personaje = new Personaje(
        m_partida->nombre,
        1, // nivel base (se actualizará después)
        static_cast<int>(m_partida->vidaMaxima),
        datosHeroe.ataque,
        datosHeroe.defensa,
        0, // oro inicial (se maneja aparte)
        false
    );

    // Restaurar vida actual
    m_personaje->curar(static_cast<int>(m_partida->vidaActual));

    // Equipar arma si existe
    if (m_partida->idArma != 0)
    {
        Item arma = obtenerItemPorId(static_cast<int>(m_partida->idArma));
        if (arma.getId() != 0) // Item válido en la tabla de items
        {
            // Restaurar el desgaste ya guardado, no reparar a full
            m_personaje->equiparArma(new Item(arma), static_cast<int>(m_partida->vidaArma));
            m_partida->vidaArma = m_personaje->getVidaArmaActual();
        }
        else
        {
            // El id guardado no corresponde a ningún item real: sí limpiar
            m_partida->idArma = 0;
            m_partida->vidaArma = 0;
        }
    }

    // Equipar armadura si existe
    if (m_partida->idArmadura != 0)
    {
        Item armadura = obtenerItemPorId(static_cast<int>(m_partida->idArmadura));
        if (armadura.getId() != 0) // Item válido en la tabla de items
        {
            // La armadura equipada ya fue descontada del inventario al
            // equiparse (ver Equipar::confirmarEquipar); no hay que volver
            // a chequear/descontar stock acá, solo restaurar el desgaste
            // ya guardado en vez de repararla a full.
            m_personaje->equiparArmadura(new Item(armadura), static_cast<int>(m_partida->vidaArmadura));
            m_partida->vidaArmadura = m_personaje->getVidaArmaduraActual();
        }
        else
        {
            // El id guardado no corresponde a ningún item real: sí limpiar
            m_partida->idArmadura = 0;
            m_partida->vidaArmadura = 0;
        }
    }
}

void Combatir::equiparArmaDelInventario()
{
    if (!m_personaje || !m_partida) return;

    // Buscar la primera arma en el inventario
    for (int i = 0; i < 100; i++)
    {
        int cantidad = m_inventario.obtenerCantidad(i);
        if (cantidad > 0)
        {
            Item item = obtenerItemPorId(i);
            if (item.getId() != 0 && item.getTipo() == ARMA)
            {
                // Equipar el arma
                m_inventario.quitarItem(i, 1);
                Item* armaNueva = new Item(item);
                m_personaje->equiparArma(armaNueva);
                m_partida->idArma = i;
                // La durabilidad se inicializa al máximo al equipar del inventario
                m_partida->vidaArma = m_personaje->getVidaArmaActual();
                actualizarPartida();
                guardarPartida();
                return;
            }
        }
    }

    // No hay arma en el inventario
    m_personaje->equiparArma(nullptr);
    m_partida->idArma = 0;
    m_partida->vidaArma = 0;
    actualizarPartida();
    guardarPartida();
}

void Combatir::equiparArmaduraDelInventario()
{
    if (!m_personaje || !m_partida) return;

    // Buscar la primera armadura en el inventario
    for (int i = 0; i < 100; i++)
    {
        int cantidad = m_inventario.obtenerCantidad(i);
        if (cantidad > 0)
        {
            Item item = obtenerItemPorId(i);
            if (item.getId() != 0 && item.getTipo() == ARMADURA)
            {
                // Equipar la armadura
                m_inventario.quitarItem(i, 1);
                m_personaje->equiparArmadura(new Item(item));
                m_partida->idArmadura = i;
                m_partida->vidaArmadura = m_personaje->getVidaArmaduraActual();
                actualizarPartida();
                guardarPartida();
                return;
            }
        }
    }

    // No hay armadura en el inventario
    m_personaje->equiparArmadura(nullptr);
    m_partida->idArmadura = 0;
    m_partida->vidaArmadura = 0;
    actualizarPartida();
    guardarPartida();
}

void Combatir::verificarYReemplazarArma()
{
    if (!m_personaje || !m_partida) return;

    if (m_personaje->armaRota())
    {
        m_ultimaAccionHeroe = "El arma se ha roto!\nBuscando reemplazo...";
        equiparArmaDelInventario();
        if (m_personaje->armaRota())
        {
            m_ultimaAccionHeroe = "No hay armas disponibles.\nAtacando sin arma.";
        }
        else
        {
            m_ultimaAccionHeroe = "Nueva arma equipada.";
        }
    }
}

void Combatir::verificarYReemplazarArmadura()
{
    if (!m_personaje || !m_partida) return;

    if (m_personaje->armaduraRota())
    {
        m_ultimaAccionEnemigo = "La armadura se ha roto!\nBuscando reemplazo...";
        equiparArmaduraDelInventario();
        if (m_personaje->armaduraRota())
        {
            m_ultimaAccionEnemigo = "No hay armaduras disponibles.\nDefensa reducida.";
        }
        else
        {
            m_ultimaAccionEnemigo = "Nueva armadura equipada.";
        }
    }
}

void Combatir::iniciarCombate()
{
    if (!m_partida)
    {
        return;
    }

    resetearInventario();
    cargarEnemigo();
    inicializarPersonaje();

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
        Partidas registro(m_partida->partida, m_partida->id, m_partida->turnoJugador,
                          m_partida->vidas, m_partida->nivel,
                          m_partida->vidaMaxima, m_partida->vidaActual,
                          m_partida->idArma, m_partida->idArmadura,
                          m_partida->vidaArma, m_partida->vidaArmadura);
        ArPartidas.modificar(posicion, registro);
    }
}

void Combatir::resetearInventario()
{
    if (!m_partida)
    {
        return;
    }

    ArchivoInventario archivo(RUTA_DAT_INVN);
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
    ArchivoInventario archivo(RUTA_DAT_INVN);

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
    if (!m_enemigo || !m_partida || !m_personaje || m_combateFinalizado)
    {
        return;
    }

    // Verificar si el arma está rota antes de atacar
    verificarYReemplazarArma();

    // Realizar ataque
    int danio = m_personaje->atacar();

    // Actualizar la vida del arma en la partida
    m_partida->vidaArma = m_personaje->getVidaArmaActual();

    m_enemigo->recibirDanio(danio);

    m_ultimaAccionHeroe = std::string(m_partida->nombre) + " ataca por " +
                          std::to_string(danio) + " de danio.";

    // Verificar si el arma se rompió después del ataque
    if (m_personaje->armaRota())
    {
        m_ultimaAccionHeroe += "\nEl arma se ha roto!";
        verificarYReemplazarArma();
        // Actualizar la partida después de reemplazar
        actualizarPartida();
        guardarPartida();
    }

    if (m_enemigo->estaEliminado())
    {
        m_combateFinalizado = true;
        m_victoria = true;
        m_ultimaAccionEnemigo = std::string(m_enemigo->getNombre()) + " fue derrotado.";

        const bool eraJefe = esCombateFinal();

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

        actualizarPartida();
        return;
    }

    turnoEnemigo();
}

void Combatir::curar()
{
    if (!m_enemigo || !m_partida || !m_personaje || m_combateFinalizado)
    {
        return;
    }

    const int idCura = m_inventario.obtenerID("POCION CURATIVA");
    if (idCura < 0 || !m_inventario.tieneCantidadNecesaria(idCura, 1))
    {
        m_ultimaAccionHeroe = "No hay pociones curativas disponibles.";
        return;
    }

    if (m_personaje->curar(CURACION_POCION))
    {
        m_inventario.quitarItem(idCura, 1);
        m_partida->vidaActual = m_personaje->getVidaActual();
        guardarPartida();
        actualizarPartida();

        m_ultimaAccionHeroe = std::string(m_partida->nombre) + " se cura " +
                              std::to_string(CURACION_POCION) + " puntos de vida.";

        turnoEnemigo();
    }
    else
    {
        m_ultimaAccionHeroe = std::string(m_partida->nombre) + " ya tiene la vida al maximo.";
    }
}

void Combatir::turnoEnemigo()
{
    if (!m_enemigo || !m_partida || !m_personaje || m_combateFinalizado)
    {
        return;
    }

    // Verificar si la armadura está rota antes de recibir daño
    verificarYReemplazarArmadura();

    int danioEnemigo = m_enemigo->atacar();

    // El personaje recibe el daño
    m_personaje->recibirDanio(danioEnemigo);

    // Actualizar la vida de la armadura en la partida
    m_partida->vidaArmadura = m_personaje->getVidaArmaduraActual();
    m_partida->vidaActual = m_personaje->getVidaActual();

    m_ultimaAccionEnemigo = std::string(m_enemigo->getNombre()) + " ataca por " +
                            std::to_string(danioEnemigo) + " de danio.";

    // Verificar si la armadura se rompió después de recibir daño
    if (m_personaje->armaduraRota())
    {
        m_ultimaAccionEnemigo += "\nLa armadura se ha roto!";
        verificarYReemplazarArmadura();
        // Actualizar la partida después de reemplazar
        actualizarPartida();
        guardarPartida();
    }

    if (m_personaje->estaEliminado())
    {
        m_combateFinalizado = true;
        m_victoria = false;
        m_ultimaAccionHeroe = std::string(m_partida->nombre) + " fue derrotado...";
    }

    actualizarPartida();
}


int Combatir::getVidaActualHeroe() const
{
    return m_personaje ? m_personaje->getVidaActual() : 0;
}

int Combatir::getVidaMaximaHeroe() const
{
    return m_personaje ? m_personaje->getVidaMaxima() : 0;
}

int Combatir::getVidaActualEnemigo() const
{
    return m_enemigo ? m_enemigo->getVidaActual() : 0;
}

int Combatir::getVidaMaximaEnemigo() const
{
    return m_enemigo ? m_enemigo->getVidaMaxima() : 0;
}

int Combatir::getVidaArma() const
{
    return m_personaje ? m_personaje->getVidaArmaActual() : 0;
}

int Combatir::getVidaArmadura() const
{
    return m_personaje ? m_personaje->getVidaArmaduraActual() : 0;
}

int Combatir::getVidaMaximaArma() const
{
    if (!m_personaje || m_personaje->armaRota()) return 0;
    // Necesitarías acceder al Item equipado para obtener la vida máxima
    // Como Personaje no expone el Item directamente, podrías agregar un método
    // o almacenar la vida máxima en otro lado.
    // Por ahora, retornamos 0 si no está equipada.
    return 0;
}

int Combatir::getVidaMaximaArmadura() const
{
    if (!m_personaje || m_personaje->armaduraRota()) return 0;
    return 0;
}

std::string Combatir::getNombreArma() const
{
    if (!m_personaje || m_personaje->armaRota()) return "Sin arma";
    if (m_partida->idArma>0)
        return m_inventario.obtenerNombre(m_partida->idArma);
    return "Arma equipada"; // Placeholder


}

std::string Combatir::getNombreArmadura() const
{
    if (!m_personaje || m_personaje->armaduraRota()) return "Sin armadura";
    if (m_partida->idArmadura>0)
        return m_inventario.obtenerNombre(m_partida->idArmadura);
    return "Armadura equipada"; // Placeholder
}

bool Combatir::tieneArma() const
{
    return m_personaje && !m_personaje->armaRota();
}

bool Combatir::tieneArmadura() const
{
    return m_personaje && !m_personaje->armaduraRota();
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
    txtAccionHeroe.setPosition(pos.x, pos.y+85.0f);
    //txtAccionEnemigo.setPosition(pos.x-5.0f, pos.y + txtAccionHeroe.getGlobalBounds().height + 10.f);
    txtAccionEnemigo.setPosition(pos.x+450.0f, pos.y + txtAccionHeroe.getGlobalBounds().height+75.0f);
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
