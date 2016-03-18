/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Camara.cpp
 * Author: alfon
 * 
 * Created on 17 de marzo de 2016, 22:14
 */

#include "Camara.h"
#include "Cargar.h"
#include <iostream>

Camara::Camara(int width, int height, int desp, Cargar &map){
    
    ancho=width;
    alto=height;
    camara = new sf::View(sf::FloatRect(0,0, ancho, alto));
    desplazamientoCamara=0;
    posicionOrigenCamara=camara->getCenter().x;
    kVel=desp;
    mapa= new Cargar();
    
    mapa->_tileWidth=map._tileWidth;
    mapa->_width=map._width;
    mapa->fondo=map.fondo;
    background=mapa->fondo;
}

Camara::Camara(const Camara& orig) {
}

Camara::~Camara() {
}

void Camara::draw(sf::RenderWindow& window){
    
    window.setView(*camara);
}

void Camara::moveRight(sf::RectangleShape &personaje){
    
    if(desplazamientoCamara==0){
        std::cout<<mapa->_tileWidth*mapa->_width<<std::endl;
        if(personaje.getPosition().x >= camara->getSize().x*0.6 && camara->getCenter().x <=(mapa->_tileWidth*mapa->_width*0.79)){
            //con background.getLocalBounds().width*0.79 calculo la parte derecha del mapa para fijar la camara
            camara->move(kVel,0);
            desplazamientoCamara=desplazamientoCamara+kVel; 
        }
        /*if(personaje.getPosition().x >= camara->getSize().x*0.6 && camara->getCenter().x <=(background.getLocalBounds().width*0.79)){
            //con background.getLocalBounds().width*0.79 calculo la parte derecha del mapa para fijar la camara
            camara->move(kVel,0);
            desplazamientoCamara=desplazamientoCamara+kVel; 
        }*/

    }else{
        if(personaje.getPosition().x>= camara->getSize().x*0.6 + desplazamientoCamara && camara->getCenter().x<=(mapa->_tileWidth*mapa->_width*0.79)){
            camara->move(kVel,0);
            desplazamientoCamara=desplazamientoCamara+kVel;  

        }
    } 
}

void Camara::moveLeft(sf::RectangleShape& personaje){
    
    if(desplazamientoCamara!=0){
        if(personaje.getPosition().x<= camara->getSize().x*0.4 + desplazamientoCamara && camara->getCenter().x!=posicionOrigenCamara){
            camara->move(-kVel,0);
            desplazamientoCamara=desplazamientoCamara-kVel;   
        }
    }
    
}