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
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
//#include "NPC.h"
class Enemigo {
public:
    Enemigo();
    Enemigo(float x, float y, int tipo);
    Enemigo(bool valorPatrullaje);
    bool getPatrullaje();
    void setPatrullaje(bool valorPatrullaje);
    void leerXML();
    ~Enemigo();
    void draw(sf::RenderWindow &window);
    void handle();
    sf::Sprite getSprite();
private:
    bool patrullaje;
    int **matriz;
    sf::Texture texturaEnemigo;
    sf::Sprite spriteEnemigo;
    

};

#endif /* ENEMIGO_H */

