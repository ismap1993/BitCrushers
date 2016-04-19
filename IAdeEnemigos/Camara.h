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


#include "Jugador.h"
#include "Mapa.h"

class Camara {
public:
    static Camara* Instance();
    
    Camara();
  
    virtual ~Camara();
    
    void draw(sf::RenderWindow &window);
    void moveRight(Jugador *personaje);
    void moveLeft(Jugador *personaje);
    
    
private:
    
    int ancho;
    int alto;
    int desplazamientoCamara;
    int posicionOrigenCamara;
    int kVel;
    
    sf::View* camara;
    
    
    
    sf::Sprite background;
    
    static Camara* pinstance;
    
};

#endif /* CAMARA_H */

