#include "salida.h"
#include "ventanaPrincipal.h"
#include "botonera.h"
#include "datosBotonera.h"
#include "datosVentana.h"

#include <iostream>


VentanaPrincipal::VentanaPrincipal(GestorPantallas& gestor): m_gestor(gestor)
{
    m_fuente.loadFromFile("recursos/fuentes/AlexandriaFLF.ttf");
    m_texto.setFont(m_fuente);
    m_texto.setString("Presiona ENTER para comenzar\nPrincipal");
    m_texto.setCharacterSize(30);
    m_texto.setPosition(200.f, 300.f);
    Botonera botonera;
    cargarRec();
}
void VentanaPrincipal::alMostrar()
{
    std::cout << "VentanaPrincipal: ahora visible\n";

}
void VentanaPrincipal::alOcultar()
{
    std::cout << "VentanaPrincipal: ahora oculta\n";
}
void VentanaPrincipal::actualizar(float dt)
{
// Si el usuario presiona ENTER, ir a la intro
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        m_gestor.ocultar("principal");
        m_gestor.mostrar("intro");
    }




}
void VentanaPrincipal::dibujar(sf::RenderWindow& ventana)
{
    ventana.draw(m_texto);
    ventana.draw(spriteFondo);

    botonera.draw(ventana);
}

void VentanaPrincipal::cargarRec()
{
    if (!texturaFondo.loadFromFile(RUTA_FONDO))
    {
        std::cerr << ERROR_FONDO;
    }
    if (!fuenteBotonera.loadFromFile(FUENTE))
    {
        std::cerr << ERROR_FUENTE_B;
    }

    spriteFondo.setTexture(texturaFondo);

    botonera.inicializar(5, fuenteBotonera);
    botonera.seColoresBot(COLOR_FONDO,COLOR_RECUA);
    botonera.inicializarRectangulos(tamRectBotonX, tamRectBotonY);
    botonera.setTamCar(TAM_CARACTER);
    botonera.setColorTexto(COLOR_LETRA); //COLOR_FONDO
    botonera.inicializarEtiquetas(ETI_BOTONES,5);
    botonera.inicializarBotones(posBotonX,posBotonY);
    //inicializarDatos();


}
void VentanaPrincipal::ejecutarAccion(int i)
{
    switch (i)
    {
    case 0:
        m_gestor.ocultar("principal");
        m_gestor.mostrar("intro");
        break;
    case 2:
        m_gestor.ocultar("principal");
        m_gestor.mostrar("cargar");
        break;
    case 4:
        Salida::Salir(m_gestor);
        break;
    }
}

void VentanaPrincipal::manejarEvento(const sf::Event& evento)
{

    if (evento.type==sf::Event::MouseMoved)
    {
        for (int i=0; i <CANT_BOTONES; i++)
        {
            if (!botonera.obtPosicion(i).contains(static_cast<float>(evento.mouseMove.x), static_cast<float>(evento.mouseMove.y)))
            {
                botonera.igualarBotones(COLOR_FONDO,COLOR_LETRA);
                break;
            }
        }

        for (int i=0; i <CANT_BOTONES; i++)
        {
            if (botonera.obtPosicion(i).contains(static_cast<float>(evento.mouseMove.x), static_cast<float>(evento.mouseMove.y)))
            {
                botonera.resaltarBoton(i,COLOR_FONDO_RES,COLOR_LETRA_RES);
                break;
            }
        }
    }
    if (evento.type == sf::Event::MouseButtonPressed && evento.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(m_gestor.obtenerVentana());
        for (int i=0; i<CANT_BOTONES; i++)
        {
            if (botonera.obtPosicion(i).contains(static_cast<float>(mousePos.x),static_cast<float>(mousePos.y)))
            {
                ejecutarAccion(i);
                break;
            }
        }
    }
}

