#pragma once
#include "inventario.h"
#include "ArchivoInventario.h"
#include "ArchivoPartidas.h"
#include "partidas.h"

#include "PanelTexto.h"

#include <iostream>

class CrafteoMan
{
    public:
        CrafteoMan();//struct RegistroPartida& partida);
        ~CrafteoMan();

        void setPartida(struct RegistroPartida& partida);
        void mostrarDatosPanel(Panel& panel,std::string nomP);
        void dibujar(sf::RenderWindow& window);

    private:

        //struct RegistroPartida _partida;




};

