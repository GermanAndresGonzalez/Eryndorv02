#include "salida.h"
#include "ventanaConfirmacion.h"
#include "GestorPantallas.h" // Asegúrate de incluir la clase de tu m_gestor

// Agregamos el parámetro 'gestor' a la implementación
void Salida::Salir(GestorPantallas& gestor)
{
    VentanaConfirmacion dialogo("", "Realmente deseas salir?");

    // Ahora usamos 'gestor' (el parámetro) en lugar de 'm_gestor'
    bool respuesta = dialogo.mostrar(gestor.obtenerVentana());
    if (respuesta)
    {
        gestor.obtenerVentana().close();
    }
}

bool Salida::Volver(GestorPantallas& gestor)
{
    VentanaConfirmacion dialogo("", "Realmente deseas salir?");

    // Ahora usamos 'gestor' (el parámetro) en lugar de 'm_gestor'
    bool respuesta = dialogo.mostrar(gestor.obtenerVentana());
    if (respuesta)
    {
        return true;
    }
    return false;
}


bool Salida::Mensaje(GestorPantallas& gestor,std::string tit,std::string mensaje)
{
    VentanaConfirmacion dialogo(tit, mensaje,1);

    // Ahora usamos 'gestor' (el parámetro) en lugar de 'm_gestor'
    bool respuesta = dialogo.mostrar(gestor.obtenerVentana());
    if (respuesta)
    {
        return true;
    }
    return false;
}
