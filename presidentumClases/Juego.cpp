/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Juego.cpp
 * Author: chiri
 * 
 * Created on 5 de abril de 2016, 17:56
 */

#include "Juego.h"
#include "EMenu.h"
#include "EIntro.h"

Juego::Juego() {
    
    _state = 0;
    
}


Escena* Juego::currentState(){
    
    return _state;
   
}

void Juego::setState(Escena* state){
    
    _state = state;
        
}

Juego::~Juego() {
    
}
