#include "ArchivoInventario.h"
#include <cstdio>

ArchivoInventario::ArchivoInventario(const char* nombreArchivo)
{
    _nombreArchivo = nombreArchivo;
}

int ArchivoInventario::contarRegistros()
{
    FILE* archivo = std::fopen(_nombreArchivo, "rb");

    if (archivo == nullptr)
        return 0;

    if (std::fseek(archivo, 0, SEEK_END) != 0)
    {
        std::fclose(archivo);
        return 0;
    }

    long bytes = std::ftell(archivo);
    std::fclose(archivo);

    if (bytes < 0)
        return 0;

    return static_cast<int>(bytes / sizeof(Inventario));
}

int ArchivoInventario::generarID()
{
    return contarRegistros() + 1;
}

bool ArchivoInventario::agregar(Inventario& inventario)
{
    FILE* archivo = std::fopen(_nombreArchivo, "ab");

    if (archivo == nullptr)
        return false;

    inventario.id       = generarID();
    inventario.eliminado = false;

    bool ok = std::fwrite(&inventario, sizeof(Inventario), 1, archivo) == 1;

    std::fclose(archivo);
    return ok;
}

bool ArchivoInventario::leer(int posicion, Inventario& inventario)
{
    if (posicion < 0)
        return false;

    FILE* archivo = std::fopen(_nombreArchivo, "rb");

    if (archivo == nullptr)
        return false;

    long offset = posicion * static_cast<long>(sizeof(Inventario));

    if (std::fseek(archivo, offset, SEEK_SET) != 0)
    {
        std::fclose(archivo);
        return false;
    }

    bool ok = std::fread(&inventario, sizeof(Inventario), 1, archivo) == 1;

    std::fclose(archivo);
    return ok;
}

bool ArchivoInventario::modificar(int posicion, const Inventario& inventario)
{
    if (posicion < 0)
        return false;

    FILE* archivo = std::fopen(_nombreArchivo, "rb+");

    if (archivo == nullptr)
        return false;

    long offset = posicion * static_cast<long>(sizeof(Inventario));

    if (std::fseek(archivo, offset, SEEK_SET) != 0)
    {
        std::fclose(archivo);
        return false;
    }

    bool ok = std::fwrite(&inventario, sizeof(Inventario), 1, archivo) == 1;

    std::fclose(archivo);
    return ok;
}

bool ArchivoInventario::borradoLogico(int id)
{
    FILE* archivo = std::fopen(_nombreArchivo, "rb+");

    if (archivo == nullptr)
        return false;

    Inventario registro;
    long posicion = 0;

    while (std::fread(&registro, sizeof(Inventario), 1, archivo) == 1)
    {
        if (registro.id == id && !registro.eliminado)
        {
            registro.eliminado = true;

            long offset = posicion * static_cast<long>(sizeof(Inventario));

            if (std::fseek(archivo, offset, SEEK_SET) != 0)
            {
                std::fclose(archivo);
                return false;
            }

            bool ok = std::fwrite(&registro, sizeof(Inventario), 1, archivo) == 1;
            std::fclose(archivo);
            return ok;
        }

        posicion++;
    }

    std::fclose(archivo);
    return false;
}

bool ArchivoInventario::buscarPorID(int id, Inventario& inventario)
{
    FILE* archivo = std::fopen(_nombreArchivo, "rb");

    if (archivo == nullptr)
        return false;

    while (std::fread(&inventario, sizeof(Inventario), 1, archivo) == 1)
    {
        if (inventario.id == id && !inventario.eliminado)
        {
            std::fclose(archivo);
            return true;
        }
    }

    std::fclose(archivo);
    return false;
}

int ArchivoInventario::buscarPosicionPorID(int id)
{
    FILE* archivo = std::fopen(_nombreArchivo, "rb");

    if (archivo == nullptr)
        return -1;

    Inventario registro;
    int posicion = 0;

    while (std::fread(&registro, sizeof(Inventario), 1, archivo) == 1)
    {
        if (registro.id == id && !registro.eliminado)
        {
            std::fclose(archivo);
            return posicion;
        }

        posicion++;
    }

    std::fclose(archivo);
    return -1;
}
