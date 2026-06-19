
#include "GestorPantallas.h"
#include "salida.h"
#include "ventanaPrincipal.h"
#include "ventanaIntrod.h"
#include "ventanaJugad.h"
#include "ventanaCueva.h"
#include "ventanaExplor.h"




int main() {
    sf::RenderWindow principal(sf::VideoMode(1280, 720), "Eryndor");

    GestorPantallas gestor(principal);

    gestor.agregar("principal", new VentanaPrincipal(gestor));
    gestor.agregar("intro", new VentanaIntro(gestor));
    gestor.agregar("jugador", new VentanaJug(gestor));
    gestor.agregar("cueva", new VentanaCueva(gestor));
    gestor.agregar("explorar", new VentanaExplo(gestor));
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
