#include "ArchivoPartidas.h"
#include <cstdio>

ArchivoPartidas::ArchivoPartidas(const char* nombreArchivo)
{
    _nombreArchivo = nombreArchivo;
}

int ArchivoPartidas::contarRegistros()
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

    return static_cast<int>(bytes / sizeof(Partidas));
}

int ArchivoPartidas::generarID()
{
    return contarRegistros() + 1;
}

bool ArchivoPartidas::agregar(Partidas& partidas)
{
    FILE* archivo = std::fopen(_nombreArchivo, "ab");

    if (archivo == nullptr)
        return false;

    partidas.setID(generarID())       ;
    partidas.setEliminado(false);

    bool ok = std::fwrite(&partidas, sizeof(Partidas), 1, archivo) == 1;

    std::fclose(archivo);
    return ok;
}

bool ArchivoPartidas::leer(int posicion, Partidas& partidas)
{
    if (posicion < 0)
        return false;

    FILE* archivo = std::fopen(_nombreArchivo, "rb");

    if (archivo == nullptr)
        return false;

    long offset = posicion * static_cast<long>(sizeof(Partidas));

    if (std::fseek(archivo, offset, SEEK_SET) != 0)
    {
        std::fclose(archivo);
        return false;
    }

    bool ok = std::fread(&partidas, sizeof(Partidas), 1, archivo) == 1;

    std::fclose(archivo);
    return ok;
}

bool ArchivoPartidas::modificar(int posicion, const Partidas& partidas)
{
    if (posicion < 0)
        return false;

    FILE* archivo = std::fopen(_nombreArchivo, "rb+");

    if (archivo == nullptr)
        return false;

    long offset = posicion * static_cast<long>(sizeof(Partidas));

    if (std::fseek(archivo, offset, SEEK_SET) != 0)
    {
        std::fclose(archivo);
        return false;
    }

    bool ok = std::fwrite(&partidas, sizeof(Partidas), 1, archivo) == 1;

    std::fclose(archivo);
    return ok;
}

bool ArchivoPartidas::borradoLogico(int id)
{
    FILE* archivo = std::fopen(_nombreArchivo, "rb+");

    if (archivo == nullptr)
        return false;

    Partidas registro;
    long posicion = 0;

    while (std::fread(&registro, sizeof(Partidas), 1, archivo) == 1)
    {
        if (registro.getId() == id && !registro.getEliminado())
        {
            registro.setEliminado(true);

            long offset = posicion * static_cast<long>(sizeof(Partidas));

            if (std::fseek(archivo, offset, SEEK_SET) != 0)
            {
                std::fclose(archivo);
                return false;
            }

            bool ok = std::fwrite(&registro, sizeof(Partidas), 1, archivo) == 1;
            std::fclose(archivo);
            return ok;
        }

        posicion++;
    }

    std::fclose(archivo);
    return false;
}

bool ArchivoPartidas::buscarPorID(int id, Partidas& partidas)
{
    FILE* archivo = std::fopen(_nombreArchivo, "rb");

    if (archivo == nullptr)
        return false;

    while (std::fread(&partidas, sizeof(Partidas), 1, archivo) == 1)
    {
        if (partidas.getId()== id && !partidas.getEliminado())
        {
            std::fclose(archivo);
            return true;
        }
    }

    std::fclose(archivo);
    return false;
}

int ArchivoPartidas::buscarPosicionPorID(int id)
{
    FILE* archivo = std::fopen(_nombreArchivo, "rb");

    if (archivo == nullptr)
        return -1;

    Partidas registro;
    int posicion = 0;

    while (std::fread(&registro, sizeof(Partidas), 1, archivo) == 1)
    {
        if (registro.getId() == id && !registro.getEliminado())
        {
            std::fclose(archivo);
            return posicion;
        }

        posicion++;
    }

    std::fclose(archivo);
    return -1;
}
