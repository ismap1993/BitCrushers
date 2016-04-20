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

#include "Enemigo.h"
#include <iostream>

Enemigo::Enemigo() : patrullaje(true) {
    
    std::cout<<"hola, soy un enemigo vacio"<<std::endl;
    
    
}

Enemigo::Enemigo(bool valorPatrullaje) : patrullaje(valorPatrullaje) {
 
    std::cout<<"hola, soy un enemigo con un parametro, el del patrullaje"<<std::endl;
    
}


bool Enemigo::getPatrullaje(){
    
    return patrullaje;
    
}

void Enemigo::setPatrullaje(bool valorPatrullaje){
    
    patrullaje = valorPatrullaje;
    
}

Enemigo::~Enemigo() {
}

