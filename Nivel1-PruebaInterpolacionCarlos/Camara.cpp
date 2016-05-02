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
#include "Mapa.h"
#include <iostream>
#include "Jugador.h"

Camara::Camara(int width, int height, float desp, Mapa &map){
    
    ancho=width;
    alto=height;
    camara = new sf::View(sf::FloatRect(0,0, ancho, alto));
    desplazamientoCamara=0;
    posicionOrigenCamara=camara->getCenter().x;
    kVel=desp;
    mapa= new Mapa();
    
    mapa->_tileWidth=map._tileWidth;
    mapa->_width=map._width;
    mapa->fondo=map.fondo;
    background=mapa->fondo;
    bool isMoving = false;
    float aceleracion = 0.0;
    
}

Camara::Camara(const Camara& orig) {
}

Camara::~Camara() {
}

void Camara::draw(sf::RenderWindow& window, Jugador* player){
    /**/
    
    moveRight(player);
    moveLeft(player);
    
    
    if(aceleracion > 0.01){
      
           aceleracion-=increment/kVel;

    }
    
     if(aceleracion < -0.01){
      
           aceleracion+=increment/kVel;
  
    }
      
    camara->move(aceleracion,0);

   
    window.setView(*camara);
    
    
    std::cout<<"desplazamientoCamara: "<<desplazamientoCamara<<" kVel: "<< kVel<<" Aceleracion: "<<aceleracion<<" Jugador activo: "<<player->isMoving()<<std::endl;
}

void Camara::moveRight(Jugador *personaje){
    
    
   
    
    
    if(desplazamientoCamara==0){
        //comprobamos que la posicion del personaje sea mayor que la camara y que el centro de la camara sea menor del fondo
        if(personaje->getSprite().getPosition().x >= camara->getSize().x*0.6 && camara->getCenter().x <=(background.getLocalBounds().width*0.79)){
        //if(personaje.getPosition().x >= camara->getSize().x*0.6 && camara->getCenter().x <=(mapa->_tileWidth*mapa->_width*0.79)){
            std::cout<<(mapa->_tileWidth*mapa->_width*0.79)<<std::endl;
            //con background.getLocalBounds().width*0.79 calculo la parte derecha del mapa para fijar la camara
            
        
            
            //camara->move(kVel,0);
            desplazamientoCamara+=kVel; 
            
        }
        /*if(personaje.getPosition().x >= camara->getSize().x*0.6 && camara->getCenter().x <=(background.getLocalBounds().width*0.79)){
            //con background.getLocalBounds().width*0.79 calculo la parte derecha del mapa para fijar la camara
            camara->move(kVel,0);
            desplazamientoCamara+=kVel; 
        }*/

    }else{
        //con esto averiguamos el margen derecho para saber cuando parar la camara al llegar al final del mapa
        int margen= background.getLocalBounds().width-(background.getLocalBounds().width*0.79);
        if(personaje->getSprite().getPosition().x>= camara->getSize().x*0.6 + desplazamientoCamara && camara->getCenter().x<=(personaje->getSprite().getPosition().x+margen) &&
            (personaje->getSprite().getPosition().x+margen)<(mapa->_tileWidth*mapa->_width)){
        //if(personaje.getPosition().x>= camara->getSize().x*0.6 + desplazamientoCamara && camara->getCenter().x<=(background.getLocalBounds().width*0.79)){
        //if(personaje.getPosition().x>= camara->getSize().x*0.6 + desplazamientoCamara && camara->getCenter().x<=(mapa->_tileWidth*mapa->_width*0.79)){
            
            if(aceleracion<kVel)
                if(aceleracion>kVel)
                    aceleracion = kVel;
                else
                    aceleracion+=increment;
            
            //camara->move(kVel,0);
            desplazamientoCamara+=kVel;  //(kVel)
        
        }
        
    } 
    
}

void Camara::moveLeft(Jugador *personaje){
    
    if(desplazamientoCamara!=0){
        if(personaje->getSprite().getPosition().x<= camara->getSize().x*0.4 + desplazamientoCamara && camara->getCenter().x!=posicionOrigenCamara){
            
            if(aceleracion > -kVel)
                if(aceleracion < -kVel)
                    aceleracion = -kVel;
                else
                    aceleracion-=increment;
           
            //camara->move(-kVel,0);
            
            desplazamientoCamara-=kVel;   //(kVel)
       
        }
    }
    
    
}