#include "crafteoMan.h"
#include "ArchivoInventario.h"
#include "ArchivoPartidas.h"
#include "Inventario.h"

//struct RegistroPartida& partida
CrafteoMan::CrafteoMan() //struct RegistroPartida& partida)
{

    /*
    ArchivoBinario<Partidas> archivoPartidas("recursos/archivos/partidas.dat");
    Inventario inventarioJug();
    */
}

CrafteoMan::~CrafteoMan()
{
}

void CrafteoMan::setPartida(struct RegistroPartida& partida)
{
    _partida= partida;
}

void CrafteoMan::dibujar(sf::RenderWindow& window)
{
    texto.dibujar(window);
    texto2.dibujar(window);
}


void CrafteoMan::mostrarDatosPanel(Panel& panel,std::string nomP)
{
    //std::cout << panel.getBordeX()+10 << " " << panel.getBordeX()+10 << std::endl;



    ArchivoInventario archivoInventario(rutaPartidas);
    Inventario inventarioJug;


    //ArchivoBinario<Inventario> archivoInventarios("recursos/archivos/inventarios4.dat");
    std::string cadena;
    //cadena=inventarioJug.mostrarSlots();
    if (nomP=="jugador")
    {

        std::cout << "partida: " << _partida.partida
                  << " nivel: "  << _partida.nivel
                  << " id: "     << _partida.id
                  << " turnoJug: " << _partida.turnoJugador << std::endl;



        std::cout <<"_partida.partida "<<_partida.partida<<std::endl;;
        if (archivoInventario.buscarPorID(_partida.partida,inventarioJug))
        {

            texto.setPos(panel.getPosX()+10.f,panel.getPosY()+10.f);
            texto.setCade(inventarioJug.mostrarSlots("izquierda"));
            //texto.setPos(panel.getPosX()+10,panel.getPosY()+10);
            texto2.setCade(inventarioJug.mostrarSlots("derecha"));
            texto2.setPos(panel.getPosX()+230.f,panel.getPosY()+10.f);
        }


    }


}








