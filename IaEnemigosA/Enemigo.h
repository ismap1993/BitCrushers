/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Enemigo.h
 * Author: chiri
 *
 * Created on 12 de abril de 2016, 20:25
 */

#ifndef ENEMIGO_H
#define ENEMIGO_H
#include "NPC.h"
#include "Jugador.h"
#include "Proyectil.h"

class Enemigo: public NPC {
public:
    Enemigo();
    Enemigo(bool valorPatrullaje, float posx, float posy, int type);
    bool getPatrullaje();
    void setPatrullaje(bool valorPatrullaje);
    void leerXML();
    ~Enemigo();
    void draw(sf::RenderWindow &window);
    void handle(Jugador* jugador);
    void disparar();
    
    std::vector<Proyectil*>* proyectiles;
    float paso;
    sf::Clock pasoTime;
private:
    sf::Clock aparicionProyectil;
    int direccion;//0 derecha. 1 izquierda
    int tipo;//0 cuerpo. 1 distancia
    bool patrullaje;
    int **matriz;
    sf::Texture texturaEnemigo;
    

};

#endif /* ENEMIGO_H */

