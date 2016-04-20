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



Mundo* Mundo::pinstance = 0;
Mundo* Mundo::Instance(){
    
    if(pinstance == 0) pinstance = new Mundo();

    return pinstance;
}

Mundo::Mundo() : camaraVel(10) {
    
    
}

void Mundo::crearMundo(int l){
    

        nivel = l;
        //Jugador::Instance()->iniciarJugador(200, 340, 2, true);
        mapa = new Mapa();
        mapa->leerMapa(nivel);
        //camara = new Camara();
        
        //std::cout<<"Jugador: "<<Jugador::Instance()<<std::endl;
        ///std::cout<<"Mapa: "<<&mapa<<std::endl;
        //std::cout<<"Camara: "<<&camara<<std::endl;
    

    
}

void Mundo::Render(){
    
      mapa->dibuja();
    //camara->draw();
    
}

Mundo::~Mundo() {
   
    //delete camara;
    delete mapa;
    
    mapa = 0;
    //camara = 0;
    //delete pinstance;
    pinstance = 0;
    
    nivel = -1;
    std::cout << "Mundo ha sido eliminado"   << std::endl;
    //std::cout<<"Mapa: "<<&mapa<<std::endl;
    //std::cout<<"Camara: "<<&camara<<std::endl;
}
