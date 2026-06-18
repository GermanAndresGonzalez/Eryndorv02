#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Botonera {
public:
    struct grupoBoton
    {
        sf::RectangleShape boton;
        bool activo;
        int id;
    };

private:
    int cantidad;

    sf::Text*       textoBotones;   // array dinámico
    std::string*    etiquetas;      // array dinámico
    grupoBoton*     botones;        // array dinámico de structs

    sf::Font        fuente;
    unsigned int    tamCar;
    sf::Color       colorBotonera;
    sf::Color       colorRecBot;
    sf::Color       colorTexto;
    float           anchoRect = 0;
    float           altoRect  = 0;

public:
    Botonera();
    Botonera(int n, sf::Font& f);
    ~Botonera();

    // ── Inicialización ────────────────────────────────────────────────────────
    void inicializar(int n, sf::Font& f);
    void inicializarRectangulos(float ancho, float alto);
    void inicializarEtiquetas(const std::string etiquetasExternas[], int cantidadEtiquetas);
    void inicializarBotones(float x, float y, bool horiz = false);

    // ── Dibujo ────────────────────────────────────────────────────────────────
    void draw(sf::RenderWindow& ventana);

    // ── Resaltar / igualar ────────────────────────────────────────────────────
    void resaltarBoton(int n, sf::Color color, sf::Color color2);
    void igualarBotones(sf::Color color, sf::Color color2);

    // ── Setters generales ─────────────────────────────────────────────────────
    void setEtiqueta(int i, const std::string& texto);
    void setTamCar(unsigned int tamCaracter);
    void seColoresBot(sf::Color color, sf::Color colorRec);
    void setColorTexto(sf::Color color);

    // ── Setters de grupoBoton ─────────────────────────────────────────────────
    void setActivo(int i, bool estado);          // activa o desactiva un botón
    void setId(int i, int nuevoId);              // cambia el id de un botón
    void setColorBoton(int i, sf::Color color);  // color de fondo individual
    void setOutlineBoton(int i, sf::Color color, float grosor); // borde individual

    // ── Getters de grupoBoton ─────────────────────────────────────────────────
    bool            getActivo(int i) const;
    int             getId(int i) const;
    sf::Color       getColorBoton(int i) const;
    const sf::FloatRect obtPosicion(int i) const;  // bounds globales del botón i

    // ── Getters generales ─────────────────────────────────────────────────────
    int             getCantidad()   const;
    float           getAnchoRect()  const;
    float           getAltoRect()   const;
    unsigned int    getTamCar()     const;
    sf::Color       getColorTexto() const;
    sf::Color       getColorBotonera() const;
    std::string     getEtiqueta(int i) const;
};
