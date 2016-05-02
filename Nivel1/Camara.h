/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Camara.h
 * Author: alfon
 *
 * Created on 17 de marzo de 2016, 22:14
 */

#ifndef CAMARA_H
#define CAMARA_H
#include <SFML/Graphics.hpp>
#include "Mapa.h"
#include "Jugador.h"

class Camara {
public:
    Camara(int width, int height, int desp, Mapa &mapa);
    Camara(const Camara& orig);
    virtual ~Camara();
    
    void draw(sf::RenderWindow &window);
    void moveRight(Jugador *personaje);
    void moveLeft(Jugador *personaje);
    
    
private:
    
    sf::Clock updateClock;
    int UPDATE_TICK_TIME = 1000/15;
    sf::Vector2i lastPosVec; //Posicion anterior
    sf::Vector2i newPosVec;  //Posicion actual
    sf::Vector2i velVector;  //Vector de velocidad
    float percentTick;
    int acceleration;
    
    int ancho;
    int alto;
    int desplazamientoCamara;
    int posicionOrigenCamara;
    int kVel;
    
    sf::View *camara;
    
    Mapa *mapa;
    
    sf::Sprite background;
    
};

#endif /* CAMARA_H */

