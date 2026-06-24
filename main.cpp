/*


#include "ArchivoInventario.h"
#include "ArchivoPartidas.h"
#include "partidas.h"
#include "inventario.h"
#include <iostream>

using namespace std;


int main()
{
    int canReg=0;
    ArchivoPartidas arPartidas("recursos/archivos/partidas.dat");
    Partidas parti;
    canReg=arPartidas.contarRegistros();
    cout << "Cant. registros: " << canReg << endl;
    for (int i=0;i<canReg;i++)
    {
        arPartidas.leer(i,parti);
        parti.imprimirPartidas();
        cout << endl << endl;


    }



    cout << endl << endl << "inventarios" << endl << endl;
    canReg=0;
    ArchivoInventario ArInv("recursos/archivos/inventarios4.dat");
    Inventario invJug;
    canReg=ArInv.contarRegistros();
    cout << "Cant. registros: " << canReg << endl;
    for (int i=0;i<canReg;i++)
    {
        ArInv.leer(i, invJug);
        invJug.imprimirSlots();
        //invJug.imprimirSlots();
    }





    return 0;
}




*/










#include "GestorPantallas.h"
#include "salida.h"
#include "ventanaPrincipal.h"
#include "ventanaIntrod.h"
#include "ventanaJugad.h"
#include "ventanaCueva.h"
#include "ventanaExplor.h"
#include "ventanaCargar.h"
#include "ventanaCraft.h"




int main() {
    sf::RenderWindow principal(sf::VideoMode(1280, 720), "Eryndor");

    GestorPantallas gestor(principal);

    gestor.agregar("principal", new VentanaPrincipal(gestor));
    gestor.agregar("intro", new VentanaIntro(gestor));
    gestor.agregar("jugador", new VentanaJug(gestor));
    gestor.agregar("cueva", new VentanaCueva(gestor));
    gestor.agregar("explorar", new VentanaExplo(gestor));
    gestor.agregar("cargar", new VentanaCargar(gestor));
    gestor.agregar("craftear", new VentanaCraft(gestor));
    gestor.mostrar("principal");

    while (principal.isOpen()) {
        sf::Event evento;
        while (principal.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed)
                Salida::Salir(gestor);

            gestor.manejarEvento(evento);
        }

        float dt = 1.f / 60.f; // o usar un sf::Clock para el dt real
        gestor.actualizar(dt);

        principal.clear();
        gestor.dibujar();
        principal.display();
    }

    return 0;
}





