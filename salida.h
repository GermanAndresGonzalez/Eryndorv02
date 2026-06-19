#ifndef SALIDA_H
#define SALIDA_H
#include <SFML/Graphics.hpp>

// Necesitamos pasarle el gestor a la función para que sepa qué ventana cerrar
class GestorPantallas; // Declaración adelantada (forward declaration) si m_gestor es de tipo Gestor

class Salida
{
public:
    // Cambiado de Salida() a Salir() y agregando el parámetro del gestor
    static void Salir(GestorPantallas& gestor);
    static bool Volver(GestorPantallas& gestor);
    static bool Mensaje(GestorPantallas& gestor,std::string tit,std::string mensaje);

};

#endif
