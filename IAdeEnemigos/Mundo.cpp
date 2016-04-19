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
#include "Camara.h"

Mundo* Mundo::pinstance = 0;
Mundo* Mundo::Instance(){
    
    if(pinstance == 0) pinstance = new Mundo();

    return pinstance;
}

Mundo::Mundo() {
    
    camaraVel = 10;
    
    crearNivel(1);
    
}

void Mundo::crearNivel(int nivel){
    
    
    mapa = Mapa::Instance();
    mapa->leerMapa(1);
    //mapa->camara = new Camara();
    
    
}

void Mundo::Render(){
    
    mapa->dibuja();
    
}

Mundo::~Mundo() {
   
    delete mapa;
    pinstance = 0;
    std::cout << "Mundo ha sido eliminado"   << std::endl;
}
