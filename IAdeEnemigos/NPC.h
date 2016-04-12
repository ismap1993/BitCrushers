/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NPC.h
 * Author: chiri
 *
 * Created on 12 de abril de 2016, 17:31
 */
#include <SFML/Graphics.hpp>
#ifndef NPC_H
#define NPC_H

#include "Jugador.h"

class NPC {
public:
    NPC();
    virtual int getX();
    virtual int getY();
    virtual int getAtaque();
    virtual int getHp();
    virtual void atacar(Jugador* jugador);
    //virtual Mundo* getMundo();
    virtual ~NPC();
private:

    int x; //posicion del personaje en x
    int y; //posicion del personaje en y
    int ataque; // daño que el NPC inflinje al jugador
    int hp; // vida que tiene el NPC
    //Mundo* mundo;
    //IA* ia;
    sf::Texture* spriteSheet; // spritesheet que usará el sprite

};

#endif /* NPC_H */

