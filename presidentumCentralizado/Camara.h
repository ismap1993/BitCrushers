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




class Camara {
public:
    Camara();
    Camara(const Camara& orig);
    virtual ~Camara();
    
    void draw();
    void moveRight();
    void moveLeft();
    
    
private:
    
    int ancho;
    int alto;
    int desplazamientoCamara;
    int posicionOrigenCamara;
    int kVel;
    
    sf::View *camara;
    
    sf::Sprite background;
    
};

#endif /* CAMARA_H */

