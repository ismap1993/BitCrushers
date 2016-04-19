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

#include <iostream>
#include "Camara.h"
#include "Mapa.h"
#include "Jugador.h"
#include "Juego.h"
#include "Mundo.h"

Camara* Camara::pinstance = 0;
Camara* Camara::Instance(){
    
    if(pinstance == 0) pinstance = new Camara();

    return pinstance;
}

Camara::Camara(){
    
    ancho = Juego::Instance()->window->getSize().x;
    alto = Juego::Instance()->window->getSize().y;
    camara = new sf::View(sf::FloatRect(0,0, ancho, alto));
    desplazamientoCamara=0;
    posicionOrigenCamara = camara->getCenter().x;
    kVel = Mundo::Instance()->camaraVel;
    background = Mapa::Instance()->fondo;
}


void Camara::draw(sf::RenderWindow& window){
    
    window.setView(*camara);
    
}

void Camara::moveRight(Jugador *personaje){
    
    if(desplazamientoCamara==0){
        //comprobamos que la posicion del personaje sea mayor que la camara y que el centro de la camara sea menor del fondo
        if(personaje->getSprite().getPosition().x >= camara->getSize().x*0.6 && camara->getCenter().x <=(background.getLocalBounds().width*0.79)){
        //if(personaje.getPosition().x >= camara->getSize().x*0.6 && camara->getCenter().x <=(mapa->_tileWidth*mapa->_width*0.79)){
            std::cout<<(Mapa::Instance()->_tileWidth*Mapa::Instance()->_width*0.79)<<std::endl;
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
        //con esto averiguamos el margen derecho para saber cuando parar la camara al llegar al final del mapa
        int margen= background.getLocalBounds().width-(background.getLocalBounds().width*0.79);
        if(personaje->getSprite().getPosition().x>= camara->getSize().x*0.6 + desplazamientoCamara && camara->getCenter().x<=(personaje->getSprite().getPosition().x+margen) &&
            (personaje->getSprite().getPosition().x+margen)<(Mapa::Instance()->_tileWidth*Mapa::Instance()->_width)){
        //if(personaje.getPosition().x>= camara->getSize().x*0.6 + desplazamientoCamara && camara->getCenter().x<=(background.getLocalBounds().width*0.79)){
        //if(personaje.getPosition().x>= camara->getSize().x*0.6 + desplazamientoCamara && camara->getCenter().x<=(mapa->_tileWidth*mapa->_width*0.79)){
            camara->move(kVel,0);
            desplazamientoCamara=desplazamientoCamara+kVel;  

        }
    } 
}

void Camara::moveLeft(Jugador *personaje){
    
    if(desplazamientoCamara!=0){
        if(personaje->getSprite().getPosition().x<= camara->getSize().x*0.4 + desplazamientoCamara && camara->getCenter().x!=posicionOrigenCamara){
            camara->move(-kVel,0);
            desplazamientoCamara=desplazamientoCamara-kVel;   
        }
    }
    
}


Camara::~Camara() {
    
    pinstance = 0;
    
}