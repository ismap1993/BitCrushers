/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Mundo.cpp
 * Author: chiri
 * 
 * Created on 14 de abril de 2016, 18:00
 */
#include <iostream>
#include "Mundo.h"
#include "Juego.h"
#include "jugador.h"
#include "Camara.h"
#include "LevelFactory.h"

Mundo::Mundo() : camaraVel(10) {
    
    
}

void Mundo::crearMundo(int l){
    

        nivel = l;
        Jugador::Instance()->iniciarJugador(200, 340, 2, true);
        mapa = new Mapa();
        mapa->leerMapa(nivel);
        camara = new Camara();
        
        //std::cout<<"Jugador: "<<Jugador::Instance()<<std::endl;
        ///std::cout<<"Mapa: "<<&mapa<<std::endl;
        //std::cout<<"Camara: "<<&camara<<std::endl;
    

    
}

void Mundo::Update(){
    
    Jugador::Instance()->handle();
    
}

void Mundo::Render(){
    
      mapa->dibuja();
      Jugador::Instance()->draw();
      camara->draw();
    
}


Mundo::~Mundo() {
   
    //delete camara;
    delete mapa;
    
    mapa = 0;
    //camara = 0;
    //delete pinstance;
    
    nivel = -1;
    std::cout << "Mundo ha sido eliminado"   << std::endl;
    //std::cout<<"Mapa: "<<&mapa<<std::endl;
    //std::cout<<"Camara: "<<&camara<<std::endl;
}
