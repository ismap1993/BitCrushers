/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/* 
 * File:   Enemigo.cpp
 * Author: chiri
 * 
 * Created on 12 de abril de 2016, 20:25
 *
 * VARIABLES DE ENEMIGO HEREDADAS;
    int x; //posicion del personaje en x
    int y; //posicion del personaje en y
    int ataque; // daño que el NPC inflinje al jugador
    int hp; // vida que tiene el NPC
    //Mundo* mundo;
    //IA* ia;
    sf::Texture* spriteSheet; // spritesheet que usará el sprite
*/

#include "NPC.h"
#include "Enemigo.h"


Enemigo::Enemigo() : patrullaje(true) {
    
    
    
}

Enemigo::Enemigo(bool valorPatrullaje) : patrullaje(valorPatrullaje) {
 
    
    
}


bool Enemigo::getPatrullaje(){
    
    return patrullaje;
    
}

void Enemigo::setPatrullaje(bool valorPatrullaje){
    
    patrullaje = valorPatrullaje;
    
}

Enemigo::~Enemigo() {
}

