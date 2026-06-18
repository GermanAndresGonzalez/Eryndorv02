#pragma once

#include "inventario.h"

class ArchivoInventario
{
private:
    const char* _nombreArchivo;

public:
    ArchivoInventario(const char* nombreArchivo);

    // Cuenta todos los registros (activos y borrados lógicamente)
    int contarRegistros();

    // Genera un nuevo ID basado en la cantidad de registros
    int generarID();

    // Agrega un nuevo Inventario al final del archivo
    // Asigna ID automáticamente y marca eliminado=false
    bool agregar(Inventario& inventario);

    // Lee el registro en la posición dada (0-indexed)
    bool leer(int posicion, Inventario& inventario);

    // Sobreescribe el registro en la posición dada
    bool modificar(int posicion, const Inventario& inventario);

    // Marca como eliminado el registro con el ID dado (borrado lógico)
    bool borradoLogico(int id);

    // Busca por ID y carga el resultado en inventario
    // Ignora registros con eliminado=true
    bool buscarPorID(int id, Inventario& inventario);

    // Devuelve la posición (0-indexed) del registro con ese ID
    // Devuelve -1 si no se encuentra o está eliminado
    int buscarPosicionPorID(int id);
};
