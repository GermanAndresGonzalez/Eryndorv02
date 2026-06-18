#pragma once

#include "partidas.h"

class ArchivoPartidas
{
private:
    const char* _nombreArchivo;

public:
    ArchivoPartidas(const char* nombreArchivo);

    // Cuenta todos los registros (activos y borrados lógicamente)
    int contarRegistros();

    // Genera un nuevo ID basado en la cantidad de registros
    int generarID();

    // Agrega un nuevo Partidas al final del archivo
    // Asigna ID automáticamente y marca eliminado=false
    bool agregar(Partidas& partidas);

    // Lee el registro en la posición dada (0-indexed)
    bool leer(int posicion, Partidas& partidas);

    // Sobreescribe el registro en la posición dada
    bool modificar(int posicion, const Partidas& partidas);

    // Marca como eliminado el registro con el ID dado (borrado lógico)
    bool borradoLogico(int id);

    // Busca por ID y carga el resultado en partidas
    // Ignora registros con eliminado=true
    bool buscarPorID(int id, Partidas& partidas);

    // Devuelve la posición (0-indexed) del registro con ese ID
    // Devuelve -1 si no se encuentra o está eliminado
    int buscarPosicionPorID(int id);
};
