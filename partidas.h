#pragma once

class Partidas
{
public:


    Partidas();
    Partidas(int id, int idPersonaje, int idNivel);

    int getId() const;
    int getIdPersonaje() const;
    int getIdNivel() const;
    bool estaEliminada() const;

    void setID(int _id);
    void setEliminado(bool _eliminado);


    bool getEliminado();



    int ContarRegistros() const;
    void imprimirPartidas();

private:
    int id;
    int idPersonaje;
    int idNivel;
    bool eliminado;
};
