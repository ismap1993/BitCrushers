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
    Camara(int width, int height, int desp, sf::Sprite fondo, int ancho, int tileAncho);
    Camara(const Camara& orig);
    virtual ~Camara();
    
    void draw(sf::RenderWindow &window);
    void moveRight(sf::Sprite& personaje);
    void moveLeft(sf::Sprite& personaje);
    
    
private:
    
    int ancho;
    int alto;
    int desplazamientoCamara;
    int posicionOrigenCamara;
    int kVel;
    
    int _width_Map;
    int _tileWidth_Map;
    
    sf::View *camara;
    
    Mapa *mapa;
    
    sf::Sprite background;
    
};

#endif /* CAMARA_H */

