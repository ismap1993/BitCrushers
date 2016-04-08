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
#include "Cargar.h"

class Camara {
public:
    Camara(int width, int height, int desp, Cargar &mapa);
    Camara(const Camara& orig);
    virtual ~Camara();
    
    void draw(sf::RenderWindow &window);
    void moveRight(sf::RectangleShape& personaje);
    void moveLeft(sf::RectangleShape& personaje);
    
    
private:
    
    int ancho;
    int alto;
    int desplazamientoCamara;
    int posicionOrigenCamara;
    int kVel;
    
    sf::View *camara;
    
    Cargar *mapa;
    
    sf::Sprite background;
    
};

#endif /* CAMARA_H */

